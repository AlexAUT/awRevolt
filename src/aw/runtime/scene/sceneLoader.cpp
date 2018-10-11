#include <aw/runtime/scene/sceneLoader.hpp>

#include <aw/runtime/loaders/assimpLoader.hpp>
#include <aw/runtime/scene/meshNode.hpp>

#include <aw/utils/file/assetInputStream.hpp>
#include <aw/utils/log.hpp>
#include <aw/utils/math/vector.hpp>

#include <json/reader.h>

DEFINE_LOG_CATEGORY(SceneLoaderDebug, aw::log::Debug, SceneLoader)
DEFINE_LOG_CATEGORY(SceneLoaderWarning, aw::log::Warning, SceneLoader)
DEFINE_LOG_CATEGORY(SceneLoaderError, aw::log::Error, SceneLoader)

aw::Vec3 jsonArrayToVec3(const Json::Value& array)
{
  using namespace Json;
  return {array.get(ArrayIndex(0), Value(0.f)).asFloat(), array.get(ArrayIndex(1), Value(0.f)).asFloat(),
          array.get(ArrayIndex(2), Value(0.f)).asFloat()};
}

namespace aw
{
bool SceneLoader::loadFromAssetFile(const std::string& assetPath, Scene& scene, TextureManager& textureManager,
                                    MeshManager& meshManager, MeshAnimationManager& animationManager)
{
  aw::AssetInputStream stream(assetPath);
  if (!stream.isOpen())
    return false;
  return loadFromStream(stream, scene, textureManager, meshManager, animationManager);
}

bool SceneLoader::loadFromStream(std::istream& stream, Scene& scene, TextureManager& textureManager,
                                 MeshManager& meshManager, MeshAnimationManager& animationManager)
{
  Json::CharReaderBuilder builder;
  Json::Value rootNode;
  std::string error;
  auto parseResult = Json::parseFromStream(builder, stream, &rootNode, &error);
  if (!parseResult)
  {
    LogSceneLoaderError() << error;
    return false;
  }
  SceneLoader loader(rootNode, scene, textureManager, meshManager, animationManager);
  return true;
}

SceneLoader::SceneLoader(const Json::Value& rootNode, Scene& scene, TextureManager& textureManager,
                         MeshManager& meshManager, MeshAnimationManager& animationManager)
    : mRootNode(rootNode), mScene(scene), mTextureManager(textureManager), mMeshManager(meshManager),
      mAnimationManager(animationManager)
{
  loadTexturesAndAnimations();
  loadSceneGraph();
  // The first node is our actual scene node after loading
  assert(scene.getChildren().size() <= 1);
  if (!scene.getChildren().empty())
  {
    scene = *scene.getChildren()[0];
    scene.setParent(nullptr);
  }
}

bool SceneLoader::loadTexturesAndAnimations()
{
  struct TargetsInFile
  {
    std::vector<std::string> meshDisplayNames;
    std::vector<std::string> animationNames;
  };
  std::map<std::string, TargetsInFile> loadList;

  auto meshLib = mRootNode["meshLibrary"];
  if (meshLib)
  {
    for (auto iter = meshLib.begin(); iter != meshLib.end(); ++iter)
    {
      LogSceneLoaderDebug() << iter.key().asString() << ": " << iter->asString();
      if (mMeshManager.count(iter->asString()) == 0)
        loadList[iter->asString()].meshDisplayNames.push_back(iter.key().asString());
    }
  }
  auto animationLib = mRootNode["animationLibrary"];
  if (animationLib)
  {
    for (auto iter = animationLib.begin(); iter != animationLib.end(); ++iter)
    {
      LogSceneLoaderDebug() << iter.key().asString() << ": " << iter->asString();
      if (mAnimationManager.count(iter->asString()) == 0)
        loadList[iter->asString()].animationNames.push_back(iter.key().asString());
    }
  }

  bool returnValue = true;
  for (auto& it : loadList)
  {
    AssimpLoader loader;
    auto foundLastPoint = it.first.find_last_of(".");
    auto hint = it.first.substr(foundLastPoint + 1);
    LogSceneLoaderDebug() << "Hint: " << hint;
    loader.loadFromAssetFile(it.first, hint.c_str());
    for (auto& displayName : it.second.meshDisplayNames)
    {
      mMeshManager.insert(std::make_pair(displayName, loader.loadMesh(displayName, true)));
      LogTemp() << "Bone count: " << displayName << "=" << mMeshManager[displayName]->getBoneCount();
    }
    if (!it.second.animationNames.empty())
    {
      auto animations = loader.loadAnimations();
      for (auto& name : it.second.animationNames)
      {
        bool found = false;
        for (auto& anim : animations)
        {
          if (anim->getDisplayName() == name)
          {
            LogTemp() << "Found animation: " << name;
            mAnimationManager.insert(std::make_pair(name, move(anim)));
            found = true;
            break;
          }
        }
        if (!found)
        {
          LogSceneLoaderError() << "Could not find animation \"" << name << "\" in: " << it.first;
          returnValue = false;
        }
      }
    }
  }

  return returnValue;
}

bool SceneLoader::loadSceneGraph()
{
  auto sceneRoot = mRootNode["scene"];
  return parseNode(sceneRoot, mScene);
}

bool SceneLoader::parseNode(const Json::Value& node, SceneNode& parent)
{
  if (node.isMember("type"))
  {
    auto type = node["type"].asString();
    if (type == "MeshNode")
      return parseMeshNode(node, parent);
    else if (type == "SceneNode")
      return parseSceneNode(node, parent);
  }
  LogSceneLoaderError() << "Node has no type!\n" << node.toStyledString();
  return false;
}

bool SceneLoader::parseMeshNode(const Json::Value& node, SceneNode& parent, MeshNode* meshNode)
{
  if (!node.isMember("mesh"))
  {
    LogSceneLoaderError() << "MeshNode has to have a mesh tag: " << node.toStyledString();
    return false;
  }
  auto meshObject = node["mesh"];
  if (!meshObject.isMember("name"))
  {
    LogSceneLoaderError() << "Mesh tag of MeshNode has to have a name: " << node.toStyledString();
    return false;
  }
  auto meshName = meshObject["name"].asString();
  auto meshIter = mMeshManager.find(meshName);
  LogTemp() << "Looking for mesh: " << meshName;
  if (meshIter == mMeshManager.end())
  {
    LogSceneLoaderError() << "Mesh \"" << meshName << "\" could not be found in mesh library!";
    return false;
  }
  meshNode = new MeshNode(*meshIter->second);

  if (node.isMember("animation"))
  {
    auto animObject = node["animation"];
    if (!animObject.isMember("name"))
      LogSceneLoaderWarning() << "If a MeshNode has an animation tag it should contain a name attribute!"
                              << node.toStyledString();
    auto animName = animObject["name"].asString();
    auto animIter = mAnimationManager.find(animName);
    if (animIter == mAnimationManager.end())
    {
      LogSceneLoaderError() << "Animation: \"" << animName << "\" could not be found in the animation library!";
      return false;
    }
    meshNode->meshInstance().setAnimation(animIter->second.get());
  }

  return parseSceneNode(node, parent, meshNode);
}

bool SceneLoader::parseSceneNode(const Json::Value& node, SceneNode& parent, SceneNode* sceneNode)
{
  if (!sceneNode)
  {
    sceneNode = new SceneNode();
  }
  // Set the parent
  sceneNode->setParent(&parent);
  if (node.isMember("name"))
    sceneNode->setName(node["name"].asString());
  // Seach transform node
  if (node.isMember("transform"))
  {
    LogTemp() << "Parse transform";
    auto& transform = node["transform"];
    if (transform.isMember("origin"))
      sceneNode->localTransform().setOrigin(jsonArrayToVec3(transform["origin"]));
    if (transform.isMember("position"))
      sceneNode->localTransform().setPosition(jsonArrayToVec3(transform["position"]));
    if (transform.isMember("scale"))
      sceneNode->localTransform().setScale(jsonArrayToVec3(transform["scale"]));
    LogTemp() << "Scale: " << sceneNode->localTransform().getScale();
    if (transform.isMember("rotationEuler"))
      sceneNode->localTransform().setRotationEuler(jsonArrayToVec3(transform["rotationEuler"]));
  }
  // Parse children
  if (node.isMember("children"))
  {
    auto childObject = node["children"];
    if (!childObject.isArray())
    {
      LogSceneLoaderError() << "Child attribute must be an array or not defined: " << node.toStyledString();
      return false;
    }
    for (unsigned i = 0; i < childObject.size(); i++)
    {
      parseNode(childObject[i], *sceneNode);
    }
    LogSceneLoaderWarning() << "Parsing childs";
  }
  return true;
}

} // namespace aw
