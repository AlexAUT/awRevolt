#include <aw/graphics/core/postProcessRenderer.hpp>
#include <aw/graphics/core/shaderProgram.hpp>
#include <aw/graphics/core/shaderStage.hpp>
#include <aw/graphics/core/texture2D.hpp>
#include <aw/graphics/core/vertex.hpp>
#include <aw/opengl/opengl.hpp>
#include <aw/utils/file/path.hpp>
#include <aw/utils/log.hpp>

DEFINE_LOG_CATEGORIES(PostProcess, "Postprocess-renderer");

namespace aw
{
PostProcessRenderer::PostProcessRenderer()
{
  VertexPosTex vertices[4] = {
      {{-1.f, -1.f, 0.f}, {0.f, 0.f}},
      {{1.f, -1.f, 0.f}, {1.f, 0.f}},
      {{-1.f, 1.f, 0.f}, {0.f, 1.f}},
      {{1.f, 1.f, 0.f}, {1.f, 1.f}},
  };
  mVBO.bind();
  mVBO.setData(vertices, sizeof(vertices));

  mVAO.bind();
  mVAO.addVertexAttributes(&mVBO, VertexPosTex::Layout);
  mVAO.unbind();
}

void PostProcessRenderer::render(const Texture2D& texture)
{
  auto& instance = PostProcessRenderer::getInstance();
  if (!instance.mShaderLoaded)
    instance.loadDefaultShader();
  instance.mDefaultShader.bind();
  texture.bind();
  render();
}

void PostProcessRenderer::render()
{
  const auto& instance = PostProcessRenderer::getInstance();
  instance.mVAO.bind();
  GL_CHECK(glDrawArrays(GL_TRIANGLE_STRIP, 0, 4));
  instance.mVAO.unbind();
}

PostProcessRenderer& PostProcessRenderer::getInstance()
{
  static PostProcessRenderer* instance = new PostProcessRenderer();
  return *instance;
}

void PostProcessRenderer::loadDefaultShader()
{
  auto vShader = ShaderStage::loadFromPath(ShaderStage::Vertex, createAssetPath("shaders/postProcess.vert"));
  auto fShader = ShaderStage::loadFromPath(ShaderStage::Fragment, createAssetPath("shaders/postProcess.frag"));

  if (vShader && fShader)
  {
    mDefaultShader.bind();
    mDefaultShader.link(*vShader, *fShader);
    mDefaultShader.unbind();
  }
}

} // namespace aw
