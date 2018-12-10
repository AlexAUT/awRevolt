#include <aw/runtime/scene/sceneWriter.hpp>

#include <aw/runtime/scene/meshNode.hpp>

#include <aw/graphics/3d/mesh.hpp>
#include <aw/graphics/3d/meshAnimation.hpp>
#include <aw/graphics/3d/meshSkeleton.hpp>

#include <json/writer.h>

namespace aw
{
/*void setNodeTypeIfNotSet(Json::Value& node, std::string type)
{
  if (!node.isMember("type"))
    node["type"] = type;
}

template <typename T>
Json::Value createJsonArray(const T& array, size_t size)
{
  Json::Value v(Json::ValueType::arrayValue);
  for (size_t i = 0; i < size; i++)
    v.append(array[i]);
  return v;
}

bool SceneWriter::parseMeshNode(Json::Value& element, const MeshNode* meshNode)
{
  setNodeTypeIfNotSet(element, "MeshNode");

  auto& mesh = meshNode->meshInstance().getMesh();
  element["mesh"] = Json::ValueType::objectValue;
  element["mesh"]["name"] = mesh.getDisplayName();
  addMeshToLibrary(mesh.getFileName(), mesh.getDisplayName());
  // Check if the mesh has an animation
  auto* anim = meshNode->meshInstance().getAnimation();
  if (anim)
  {
    element["animation"] = Json::ValueType::objectValue;
    element["animation"]["name"] = anim->getDisplayName();
    addAnimationToLibrary(anim->getFileName(), anim->getDisplayName());
  }

  return true;
}

bool parseTransform(Json::Value& element, const aw::Transform& transform)
{
  Json::Value tNode(Json::ValueType::objectValue);
  tNode["position"] = createJsonArray(transform.getPosition(), 3);
  tNode["scale"] = createJsonArray(transform.getScale(), 3);
  tNode["rotationEuler"] = createJsonArray(transform.getRotationEuler(), 3);
  tNode["origin"] = createJsonArray(transform.getOrigin(), 3);
  element["transform"] = tNode;

  return true;
}

bool SceneWriter::parseSceneNode(Json::Value& node, const aw::SceneNode* sceneNode)
{
  // Check for higher order nodes
  auto meshNode = dynamic_cast<const MeshNode*>(sceneNode);
  if (meshNode)
    parseMeshNode(node, meshNode);

  setNodeTypeIfNotSet(node, "SceneNode");
  // Every node has to have a transform
  parseTransform(node, sceneNode->localTransform());

  // Parse children
  node["children"] = Json::Value(Json::ValueType::arrayValue);
  for (auto& child : sceneNode->getChildren())
  {
    parseSceneNode(node["children"].append(Json::ValueType::objectValue), child);
  }

  return true;
}

SceneWriter::SceneWriter(const aw::Scene& scene)
{
  mRoot["scene"] = Json::Value(Json::ValueType::objectValue);
  mRoot["meshLibrary"] = Json::Value(Json::objectValue);
  mRoot["animationLibrary"] = Json::Value(Json::objectValue);
  parseSceneNode(mRoot["scene"], &scene);
}

void SceneWriter::writeToStream(std::ostream& outputStream)
{
  Json::StreamWriterBuilder writerBuilder;
  writerBuilder["indentation"] = " ";
  std::unique_ptr<Json::StreamWriter> writer(writerBuilder.newStreamWriter());
  writer->write(mRoot, &outputStream);
}

void SceneWriter::addMeshToLibrary(const std::string& fileName, const std::string& displayName)
{
  auto& meshLib = mRoot["meshLibrary"];
  if (!meshLib.isMember(displayName))
  {
    meshLib[displayName] = fileName;
  }
}
void SceneWriter::addAnimationToLibrary(const std::string& fileName, const std::string& displayName)
{
  auto& animLib = mRoot["animationLibrary"];
  if (!animLib.isMember(displayName))
  {
    animLib[displayName] = fileName;
  }
}
*/
} // namespace aw
