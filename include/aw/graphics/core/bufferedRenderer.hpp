#pragma once

#include <aw/graphics/core/renderer.hpp>
#include <aw/graphics/core/vertexArrayObject.hpp>
#include <aw/graphics/core/vertexBuffer.hpp>
#include <aw/utils/types.hpp>

#include <vector>

namespace aw
{
template <typename VertexType>
class BufferedRenderer
{
public:
  using Container = std::vector<VertexType>;
  using Iterator = typename Container::iterator;

public:
  BufferedRenderer(PrimitiveType primitiveType);

  BufferedRenderer(const BufferedRenderer&) = delete;
  BufferedRenderer& operator=(const BufferedRenderer&) = delete;

  // Allocates reqested amount of vertices and returns a span to it
  // do not store this pointer after initial use! use the change functions to alter vertices afterwards
  Iterator allocate(size_t vertexCount);
  // Use this if you want to add just a few vertices, use allocate for more
  void addVertex(VertexType vertex);

  void clear();
  void render();

private:
  void updateGPUBuffer();

private:
  Renderer mRenderer;

  std::vector<VertexType> mCPUBuffer;
  VertexBuffer mVBO;
  VertexArrayObject mVAO;

  size_t mCPUVersion{1};
  size_t mGPUVersion{0};
};
} // namespace aw

#include <aw/graphics/core/bufferedRenderer.inl>
