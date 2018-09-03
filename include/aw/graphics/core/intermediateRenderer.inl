#pragma once

#include <aw/graphics/core/intermediateRenderer.hpp>

#include <aw/opengl/opengl.hpp>

#include <cassert>

namespace aw
{
template <typename VertexType>
IntermediateRenderer<VertexType>::IntermediateRenderer(size_t bufferCount) : mBuffer(bufferCount)
{
  assert(bufferCount > 0);
  mVBO.bind();
  mVBO.setData(nullptr, bufferCount * sizeof(VertexType));
  mVBO.unbind();
  mVAO.addVertexAttributes(&mVBO, VertexType::Layout);
}
template <typename VertexType>
void IntermediateRenderer<VertexType>::addVertex(const VertexType& vertex)
{
  mBuffer[mBufferCursor++] = vertex;
}

template <typename VertexType>
bool IntermediateRenderer<VertexType>::addVertices(const VertexType* begin, const VertexType* end)
{
  auto size = end - begin;
  if (size > mBuffer.size())
    return false;
  if (size > (mBuffer.size() - mBufferCursor))
    render();
  std::copy(begin, end, &mBuffer[mBufferCursor]);
  mBufferCursor += size;
  return true;
}

template <typename VertexType>
VertexType* IntermediateRenderer<VertexType>::allocateVertexSpace(size_t vertexCount)
{
  if (vertexCount > mBuffer.size())
    return nullptr;
  if (vertexCount > (mBuffer.size() - mBufferCursor))
    render();
  auto* segment = &mBuffer[mBufferCursor];
  mBufferCursor += vertexCount;
  return segment;
}

template <typename VertexType>
void IntermediateRenderer<VertexType>::clear()
{
  mBufferCursor = 0;
}

template <typename VertexType>
void IntermediateRenderer<VertexType>::render()
{
  mVAO.bind();

  mVBO.bind();
  mVBO.setSubData(mBuffer.data(), mBufferCursor * sizeof(VertexType), 0);
  mVBO.unbind();

  GL_CHECK(glDrawArrays(GL_TRIANGLES, 0, mBufferCursor));

  mVAO.unbind();
  mBufferCursor = 0;
}

template <typename VertexType>
size_t IntermediateRenderer<VertexType>::getBufferSize() const
{
  return mBuffer.size();
}

} // namespace aw
