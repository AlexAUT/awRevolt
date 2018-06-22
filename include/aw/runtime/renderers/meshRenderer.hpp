#pragma once

#include <vector>

namespace aw
{
class MeshNode;
class Camera;
class ShaderProgram;
class DirectionalLight;
class Texture2D;

class MeshRenderer
{
public:
  void registerMesh(const MeshNode* mesh);

  void renderShadowMap(const Camera& camera, const ShaderProgram& shader, const DirectionalLight& light) const;
  void renderForwardPass(const Camera& camera, const Camera& lightCam, const Texture2D& shadowMap,
                         ShaderProgram& shader, const DirectionalLight& light) const;

private:
private:
  std::vector<const MeshNode*> mMeshes;
};
} // namespace aw
