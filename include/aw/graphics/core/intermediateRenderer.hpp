#pragma once

#include <aw/utils/types.hpp>

#include <aw/graphics/core/renderer.hpp>
#include <aw/graphics/core/vertexArrayObject.hpp>
#include <aw/graphics/core/vertexBuffer.hpp>

namespace aw
{
template <typename VertexType>
class IntermediateRenderer
{
public:
  IntermediateRenderer(size_t bufferCount = 512 * sizeof(VertexType));

  void addVertex(const VertexType& vertex);
  bool addVertices(const VertexType* begin, const VertexType* end);

  VertexType* allocateVertexSpace(size_t vertexCount);

  void clear();
  void render();

  size_t getBufferSize() const;

private:
private:
  VertexArrayObject mVAO;
  VertexBuffer mVBO;

  std::vector<VertexType> mBuffer;
  size_t mBufferCursor{0};

  Renderer mRenderer;
};

} // namespace aw

#include <aw/graphics/core/intermediateRenderer.inl>
