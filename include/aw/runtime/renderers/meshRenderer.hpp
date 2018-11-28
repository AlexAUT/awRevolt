#pragma once

#include <vector>

namespace aw
{
class SceneNode;
class Scene;
class MeshNode;
class Camera;
class ShaderProgram;
struct DirectionalLight;
class Texture2D;

class MeshRenderer
{
public:
  void analyzeScene(const aw::Scene& scene);

  void registerMesh(const MeshNode* mesh);

  void renderForwardPass(const Camera& camera, ShaderProgram& shader);

  void renderShadowMap(const Camera& camera, const ShaderProgram& shader, const DirectionalLight& light) const;
  void renderForwardPassWithShadow(const Camera& camera, const Camera& lightCam, const Texture2D& shadowMap,
                                   ShaderProgram& shader, const DirectionalLight& light) const;

private:
private:
  std::vector<const MeshNode*> mMeshes;
};
} // namespace aw
