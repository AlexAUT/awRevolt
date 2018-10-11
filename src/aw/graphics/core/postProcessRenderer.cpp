#include <aw/graphics/core/postProcessRenderer.hpp>

#include <aw/graphics/core/shaderProgram.hpp>
#include <aw/graphics/core/shaderStage.hpp>
#include <aw/graphics/core/texture2D.hpp>
#include <aw/graphics/core/vertex.hpp>

#include <aw/utils/file/assetInputStream.hpp>

#include <aw/opengl/opengl.hpp>

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
  AssetInputStream vShaderFile("shaders/postProcess.vert");
  ShaderStage vShader(ShaderStage::Vertex);
  vShader.loadFromStream(vShaderFile);

  AssetInputStream fShaderFile("shaders/postProcess.frag");
  ShaderStage fShader(ShaderStage::Fragment);
  fShader.loadFromStream(fShaderFile);

  mDefaultShader.bind();
  mDefaultShader.link(vShader, fShader);
  //  mDefaultShader.setUniform("postProcess_tex", 0);
  mDefaultShader.unbind();
}

} // namespace aw
