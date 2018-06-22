#pragma once

#include <aw/runtime/managers/MeshAnimationManager.hpp>
#include <aw/runtime/managers/MeshManager.hpp>
#include <aw/runtime/managers/TextureManager.hpp>
#include <aw/runtime/scene/scene.hpp>

#include <json/value.h>

#include <istream>

namespace aw
{
class MeshNode;

class SceneLoader
{
public:
  static bool loadFromAssetFile(const std::string& assetPath, Scene& scene, TextureManager& textureManager,
                                MeshManager& meshManager, MeshAnimationManager& animationManager);
  static bool loadFromStream(std::istream& stream, Scene& scene, TextureManager& textureManager,
                             MeshManager& meshManager, MeshAnimationManager& animationManager);

private:
  SceneLoader(const Json::Value& mRootNode, Scene& scene, TextureManager& textureManager, MeshManager& meshManager,
              MeshAnimationManager& animationManager);

  bool loadTexturesAndAnimations();
  bool loadSceneGraph();

  bool parseNode(const Json::Value& node, SceneNode& parent);

  bool parseMeshNode(const Json::Value& node, SceneNode& parent, MeshNode* meshNode = nullptr);
  bool parseSceneNode(const Json::Value& node, SceneNode& parent, SceneNode* sceneNode = nullptr);

private:
  const Json::Value& mRootNode;
  Scene& mScene;
  TextureManager& mTextureManager;
  MeshManager& mMeshManager;
  MeshAnimationManager& mAnimationManager;
};
} // namespace aw
