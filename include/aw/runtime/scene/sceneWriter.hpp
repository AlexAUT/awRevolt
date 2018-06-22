#pragma once

#include <aw/runtime/scene/scene.hpp>

#include <json/value.h>

#include <ostream>

namespace aw
{
class MeshNode;

class SceneWriter
{
public:
  SceneWriter(const aw::Scene& scene);

  void writeToStream(std::ostream& outputStream);

private:
  bool parseSceneNode(Json::Value& node, const aw::SceneNode* sceneNode);
  bool parseMeshNode(Json::Value& element, const MeshNode* meshNode);

  void addMeshToLibrary(const std::string& fileName, const std::string& displayName);
  void addAnimationToLibrary(const std::string& fileName, const std::string& displayName);

public:
  Json::Value mRoot;
};
} // namespace aw
