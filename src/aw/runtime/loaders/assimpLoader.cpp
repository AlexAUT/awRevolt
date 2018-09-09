#include <aw/runtime/loaders/assimpLoader.hpp>

#include <aw/graphics/core/image.hpp>
#include <aw/graphics/core/texture2D.hpp>

#include <assimp/postprocess.h>
#include <assimp/scene.h>

#include <aw/utils/assetInputStream.hpp>
#include <aw/utils/log.hpp>
#include <aw/utils/streamReading.hpp>
DEFINE_LOG_CATEGORY(AssimpD, aw::log::Debug, AssimpLoader)
DEFINE_LOG_CATEGORY(AssimpE, aw::log::Error, AssimpLoader)

#include <vector>

namespace aw
{
inline Vec3 aiVec3ToGlm(const aiVector3D* from)
{
  return Vec3{from->x, from->y, from->z};
}

inline Quaternion aiQuat3ToGlm(const aiQuaternion* from)
{
  return Quaternion{from->w, from->x, from->y, from->z};
}

inline Mat4 aiMatrix4x4ToGlm(const aiMatrix4x4* from)
{
  Mat4 to;

  to[0][0] = static_cast<float>(from->a1);
  to[0][1] = static_cast<float>(from->b1);
  to[0][2] = static_cast<float>(from->c1);
  to[0][3] = static_cast<float>(from->d1);
  to[1][0] = static_cast<float>(from->a2);
  to[1][1] = static_cast<float>(from->b2);
  to[1][2] = static_cast<float>(from->c2);
  to[1][3] = static_cast<float>(from->d2);
  to[2][0] = static_cast<float>(from->a3);
  to[2][1] = static_cast<float>(from->b3);
  to[2][2] = static_cast<float>(from->c3);
  to[2][3] = static_cast<float>(from->d3);
  to[3][0] = static_cast<float>(from->a4);
  to[3][1] = static_cast<float>(from->b4);
  to[3][2] = static_cast<float>(from->c4);
  to[3][3] = static_cast<float>(from->d4);

  return to;
}

bool AssimpLoader::loadFromStream(const std::string& fileName, std::istream& stream, const char* hint)
{
  mFileName = fileName;
  auto fileContent = stream::toUint8(stream);
  if (fileContent.empty())
  {
    LogAssimpE() << "The stream did not contain any content!: " << fileName;
    return false;
  }
  auto flags = aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs;
  const aiScene* scene = mImporter.ReadFileFromMemory(fileContent.data(), fileContent.size(), flags, hint);
  if (!scene)
  {
    LogAssimpE() << "Error parsing file: " << mImporter.GetErrorString();
    return false;
  }
  LogAssimpD() << "Meshes: " << scene->mNumMeshes << ", tex: " << scene->mNumTextures;
  LogAssimpD() << "Materials: " << scene->mNumMaterials;
  LogAssimpD() << "Animations: " << scene->mNumAnimations;
  LogAssimpD() << scene->mNumAnimations;
  return true;
}

bool AssimpLoader::loadFromAssetFile(const std::string& assetPath, const char* hint)
{
  aw::AssetInputStream file(assetPath);
  return loadFromStream(assetPath, file, hint);
}

std::unique_ptr<aw::Mesh> AssimpLoader::loadMesh(const std::string& displayName, bool withSkeleton)
{
  auto scene = getScene();

  auto mesh = std::make_unique<aw::Mesh>(mFileName, displayName);

  Mat4 rootTransform = aiMatrix4x4ToGlm(&scene->mRootNode->mTransformation);
  Mat4 inverseRootTransform = glm::inverse(rootTransform);
  mesh->setGlobalInverseTransform(inverseRootTransform);
  for (unsigned i = 0; i < scene->mNumMeshes; i++)
  {
    if (!parseMesh(*mesh, scene->mMeshes[i]))
      return nullptr;
  }

  for (unsigned i = 0; i < scene->mNumMaterials; i++)
  {
    if (!parseMaterial(*mesh, scene->mMaterials[i]))
      return nullptr;
  }

  if (withSkeleton)
  {
    auto skeleton = loadSkeleton();
    if (skeleton)
      mesh->setSkeleton(skeleton);
    else
      return nullptr;
  }

  return mesh;
}

bool AssimpLoader::parseMesh(aw::Mesh& mesh, const aiMesh* assimpMesh)
{
  LogTemp() << "UV channels: " << assimpMesh->GetNumUVChannels() << ", " << assimpMesh->mName.C_Str();
  MeshObject* part = new MeshObject();
  part->name = assimpMesh->mName.C_Str();

  part->materialIndex = assimpMesh->mMaterialIndex;
  part->vertices.resize(assimpMesh->mNumVertices);
  part->indices.resize(assimpMesh->mNumFaces * 3);

  for (unsigned i = 0; i < assimpMesh->mNumVertices; i++)
  {
    const auto& p = assimpMesh->mVertices[i];
    const auto& n = assimpMesh->mNormals[i];
    part->vertices[i].position = {p.x, p.y, p.z};
    part->vertices[i].normal = {n.x, n.y, n.z};
    if (assimpMesh->HasTextureCoords(0))
    {
      const auto& t1 = assimpMesh->mTextureCoords[0][i];
      part->vertices[i].texCoord = {t1.x, t1.y};
    }
    // Just set the bone weights to 0, just for safety
    part->vertices[i].boneIds = Vec4{0.f};
    part->vertices[i].boneWeights = Vec4{0.f};
  }

  for (unsigned i = 0; i < assimpMesh->mNumFaces; i++)
  {
    const auto& face = assimpMesh->mFaces[i];
    part->indices[i * 3] = face.mIndices[0];
    part->indices[i * 3 + 1] = face.mIndices[1];
    part->indices[i * 3 + 2] = face.mIndices[2];
  }

  if (!parseBones(mesh, part, assimpMesh))
    return false;

  part->ibo.bind();
  part->ibo.setData(part->indices.data(), part->indices.size() * sizeof(unsigned));
  part->vbo.bind();
  part->vbo.setData(part->vertices.data(), part->vertices.size() * sizeof(part->vertices[0]));
  part->vao.bind();
  for (auto l : VertexBones::Layout)
    part->vao.addVertexAttribute(&part->vbo, &part->ibo, l);
  part->vao.unbind();

  mesh.addObject(part);
  return true;
}

aw::Texture2D::WrapMode assimpWrapModeToAw(aiTextureMapMode mode)
{
  using WrapMode = aw::Texture2D::WrapMode;
  switch (mode)
  {
  case aiTextureMapMode_Wrap:
    return WrapMode::REPEAT;
  case aiTextureMapMode_Mirror:
    return WrapMode::MIRRORED_REPEAT;
  case aiTextureMapMode_Decal:
    return WrapMode::CLAMP_TO_BORDER;
  case aiTextureMapMode_Clamp:
    return WrapMode::CLAMP_TO_EDGE;
  default:
    return WrapMode::REPEAT;
  }
}

void outputTextureCount(const aiMaterial* assimpMat, const char* name, aiTextureType type)
{
  LogTemp() << name << ": " << assimpMat->GetTextureCount(type);
}

bool AssimpLoader::parseMaterial(aw::Mesh& mesh, const aiMaterial* assimpMat)
{
  // Diffuse textures
  // Load materialName
  aiString matName;
  if (assimpMat->Get(AI_MATKEY_NAME, matName) != AI_SUCCESS)
  {
    LogTemp() << "Material has no name!";
    return false;
  }
  LogTemp() << "Material name: " << matName.C_Str();
  Material mat(matName.C_Str());

  aiColor3D color;
  if (assimpMat->Get(AI_MATKEY_COLOR_DIFFUSE, color) == AI_SUCCESS)
  {
    mat.setDiffuseColor({color.r, color.g, color.b});
    LogTemp() << "Diffuse: " << mat.getDiffuseColor();
  }
  if (assimpMat->Get(AI_MATKEY_COLOR_AMBIENT, color) == AI_SUCCESS)
  {
    mat.setAmbientColor({color.r, color.g, color.b});
    LogTemp() << "Ambient: " << mat.getAmbientColor();
  }
  if (assimpMat->Get(AI_MATKEY_COLOR_SPECULAR, color) == AI_SUCCESS)
  {
    mat.setSpecularColor({color.r, color.g, color.b});
    LogTemp() << "Specular: " << mat.getSpecularColor();
  }

  // Load diffuse textures
  unsigned diffuseCount = assimpMat->GetTextureCount(aiTextureType_DIFFUSE);
  outputTextureCount(assimpMat, "Unkown: ", aiTextureType_NONE);
  outputTextureCount(assimpMat, "Diffuse: ", aiTextureType_DIFFUSE);
  outputTextureCount(assimpMat, "Ambient: ", aiTextureType_AMBIENT);
  outputTextureCount(assimpMat, "Other: ", aiTextureType_NONE);
  LogTemp() << "Diffuse count: " << diffuseCount;
  for (unsigned i = 0; i < diffuseCount; i++)
  {
    // unsigned int index, aiString *path, aiTextureMapping *mapping=NULL, unsigned int *uvindex=NULL, float
    // *blend=NULL, aiTextureOp *op=NULL, aiTextureMapMode *mapmode=NULL)
    aiString aPath;
    aiTextureMapping mapping = aiTextureMapping_UV;
    aiTextureOp op = aiTextureOp_Add;
    unsigned uvIndex;
    float blend;
    aiTextureMapMode mapMode;

    assimpMat->GetTexture(aiTextureType_DIFFUSE, i, &aPath, &mapping, &uvIndex, &blend, &op, &mapMode);
    std::string path(aPath.C_Str());
    if (mapping != aiTextureMapping_UV)
    {
      LogTemp() << "Only UV mapping is alowed for material!";
      return false;
    }
    aw::TextureSlot slot;
    slot.uvIndex = uvIndex;
    auto wrapMode = assimpWrapModeToAw(mapMode);
    slot.modeS = wrapMode;
    slot.modeT = wrapMode;
    slot.magFilter = aw::Texture2D::MagFilter::LINEAR;
    slot.minFilter = aw::Texture2D::MinFilter::LINEAR;

    auto posForwardSlash = path.find_last_of("/") + 1;
    auto posBackwardSlash = path.find_last_of("\\") + 1;
    auto pos = std::max(posForwardSlash, posBackwardSlash);

    auto texName = path.substr(pos);
    slot.texName = texName;
    LogTemp() << "Loading diffuse texture: " << texName;
    aw::AssetInputStream texFile("textures/meshes/" + texName);
    aw::Image img;
    if (!img.loadFromStream(texFile))
    {
      LogTemp() << "FAILED TO LOAD IMAGE";
      return false;
    }
    auto tex2D = std::make_shared<aw::Texture2D>();
    tex2D->bind();
    tex2D->loadFromImage(img);
    tex2D->setWrapModeS(slot.modeS);
    tex2D->setWrapModeT(slot.modeT);
    tex2D->setMinFilter(slot.minFilter);
    tex2D->setMagFilter(slot.magFilter);
    slot.texture2D = tex2D;
    mat.addDiffuseTexture(slot);
  }
  mesh.addMaterial(mat);
  return true;
}

bool AssimpLoader::parseBones(aw::Mesh& mesh, aw::MeshObject* object, const aiMesh* assimpMesh)
{
  for (unsigned i = 0; i < assimpMesh->mNumBones; i++)
  {
    const auto* bone = assimpMesh->mBones[i];
    std::string boneName(bone->mName.C_Str());
    int boneIndex = mesh.getBoneIndex(boneName);
    // Search if bone already mapped, otherwise add to mapping list
    if (boneIndex < 0)
    {
      boneIndex = mesh.addBone(boneName, aiMatrix4x4ToGlm(&bone->mOffsetMatrix));
    }
    // Add bone information to vertices
    for (unsigned j = 0; j < bone->mNumWeights; j++)
    {
      assert(object->vertices.size() > bone->mWeights[j].mVertexId);
      VertexBones& v = object->vertices[bone->mWeights[j].mVertexId];
      // Add to the first free weight slot
      for (unsigned k = 0; k < 4; k++)
      {
        if (v.boneWeights[k] <= 0.001f)
        {
          v.boneWeights[k] = bone->mWeights[j].mWeight;
          v.boneIds[k] = static_cast<float>(boneIndex);
          break;
        }
        else
        {
          if (k == 3)
          {
            int smallestIndex = 0;
            float smallestValue = v.boneWeights[0];
            for (unsigned l = 1; l < 4; l++)
            {
              if (smallestValue > v.boneWeights[l])
              {
                smallestIndex = l;
                smallestValue = v.boneWeights[l];
              }
            }
            if (smallestValue < bone->mWeights[j].mWeight)
            {
              v.boneWeights[smallestIndex] = bone->mWeights[j].mWeight;
              v.boneIds[smallestIndex] = static_cast<float>(boneIndex);
            }
          }
        }
      }
    }
  }
  return true;
}

std::shared_ptr<aw::MeshSkeleton> AssimpLoader::loadSkeleton()
{
  mBoneCount = 0;
  auto skeleton = std::make_shared<aw::MeshSkeleton>();
  bool result = parseSkeletonNode(skeleton->getRootNode(), mImporter.GetScene()->mRootNode);
  skeleton->setBoneCount(mBoneCount);
  if (result)
    return skeleton;
  return nullptr;
}

bool AssimpLoader::parseSkeletonNode(aw::MeshSkeletonNode& targetNode, const aiNode* node)
{
  mBoneCount++;
  targetNode.name = std::string(node->mName.C_Str());
  targetNode.transformation = aiMatrix4x4ToGlm(&node->mTransformation);

  targetNode.children.resize(node->mNumChildren);
  for (unsigned i = 0; i < node->mNumChildren; i++)
  {
    if (!parseSkeletonNode(targetNode.children[i], node->mChildren[i]))
      return false;
  }

  return true;
}

std::vector<std::unique_ptr<aw::MeshAnimation>> AssimpLoader::loadAnimations()
{
  std::vector<std::unique_ptr<aw::MeshAnimation>> result;
  const auto scene = getScene();
  if (!scene)
    return result;

  auto animCount = scene->mNumAnimations;
  for (unsigned i = 0; i < animCount; i++)
  {
    const auto* assimpAnimation = scene->mAnimations[i];

    LogTemp() << "Anim name: " << assimpAnimation->mName.C_Str() << ", duration: " << assimpAnimation->mDuration;
    LogTemp() << "Tick: " << assimpAnimation->mTicksPerSecond;
    LogTemp() << "Channel: " << assimpAnimation->mNumChannels;

    const auto channelCount = assimpAnimation->mNumChannels;
    MeshAnimationChannels channels(channelCount);
    for (unsigned j = 0; j < channelCount; j++)
    {
      const auto* assimpChannel = assimpAnimation->mChannels[j];
      auto& channel = channels[j];
      channel.boneName = assimpChannel->mNodeName.C_Str();
      const auto posKeyNum = assimpChannel->mNumPositionKeys;
      for (unsigned k = 0; k < posKeyNum; k++)
      {
        const auto& posKey = assimpChannel->mPositionKeys[k];
        channel.posKeys.push_back({static_cast<float>(posKey.mTime), aiVec3ToGlm(&posKey.mValue)});
      }
      const auto scaleKeyNum = assimpChannel->mNumScalingKeys;
      for (unsigned k = 0; k < scaleKeyNum; k++)
      {
        const auto& scaleKey = assimpChannel->mScalingKeys[k];
        channel.scaleKeys.push_back({static_cast<float>(scaleKey.mTime), aiVec3ToGlm(&scaleKey.mValue)});
      }
      const auto rotKeyNum = assimpChannel->mNumRotationKeys;
      for (unsigned k = 0; k < rotKeyNum; k++)
      {
        const auto& rotKey = assimpChannel->mRotationKeys[k];
        channel.rotKeys.push_back({static_cast<float>(rotKey.mTime), aiQuat3ToGlm(&rotKey.mValue)});
      }
    }
    result.push_back(std::make_unique<aw::MeshAnimation>(
        mFileName, assimpAnimation->mName.C_Str(), static_cast<float>(assimpAnimation->mDuration),
        static_cast<float>(assimpAnimation->mTicksPerSecond), channels));
  }
  // mScene->mAnimations[0]->mChannels[0]->mNodeName;
  return result;
}

const aiScene* AssimpLoader::getScene() const
{
  return mImporter.GetScene();
}
} // namespace aw
