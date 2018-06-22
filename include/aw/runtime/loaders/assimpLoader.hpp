#pragma once

#include <aw/graphics/3d/mesh.hpp>
#include <aw/graphics/3d/meshAnimation.hpp>

#include <assimp/Importer.hpp>

#include <istream>
#include <memory>

struct aiScene;
struct aiMesh;
struct aiMaterial;
struct aiNode;

namespace aw
{
class AssimpLoader
{
public:
  bool loadFromStream(const std::string& fileName, std::istream& stream, const char* hint = "");
  bool loadFromAssetFile(const std::string& assetPath, const char* hint = "");

  std::unique_ptr<aw::Mesh> loadMesh(const std::string& displyName, bool withSkeleton = false);

  std::shared_ptr<aw::MeshSkeleton> loadSkeleton();
  std::vector<std::unique_ptr<aw::MeshAnimation>> loadAnimations();

  const aiScene* getScene() const;

private:
  bool parseMesh(aw::Mesh& mesh, const aiMesh* assimpMesh);
  bool parseMaterial(aw::Mesh& mesh, const aiMaterial* aMesh);
  bool parseBones(aw::Mesh& mesh, aw::MeshObject* object, const aiMesh* assimpMesh);

  bool parseSkeletonNode(aw::MeshSkeletonNode& targetNode, const aiNode* node);

private:
  std::string mFileName;
  Assimp::Importer mImporter;

  unsigned mBoneCount;
};
} // namespace aw
