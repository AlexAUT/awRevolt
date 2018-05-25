#pragma once

#include <aw/graphics/core/shaderProgram.hpp>
#include <aw/graphics/core/vertexArrayObject.hpp>
#include <aw/graphics/core/vertexBuffer.hpp>

namespace aw
{
class Texture2D;

class PostProcessRenderer
{
public:
  PostProcessRenderer(const PostProcessRenderer&) = delete;
  PostProcessRenderer operator=(const PostProcessRenderer) = delete;

  static void render();
  static void render(const Texture2D& tex);

private:
  PostProcessRenderer();

  void loadDefaultShader();
  static PostProcessRenderer& getInstance();

private:
  VertexArrayObject mVAO;
  VertexBuffer mVBO;
  bool mShaderLoaded{false};
  ShaderProgram mDefaultShader;
};
} // namespace aw
