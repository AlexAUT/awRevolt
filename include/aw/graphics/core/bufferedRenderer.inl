#pragma once

#include <aw/graphics/core/bufferedRenderer.hpp>

namespace aw
{
template <typename VertexType>
BufferedRenderer<VertexType>::BufferedRenderer(PrimitiveType primitiveType) : mRenderer(primitiveType)
{
  mVAO.addVertexAttributes(&mVBO, VertexType::Layout);
}

template <typename VertexType>
auto BufferedRenderer<VertexType>::allocate(size_t vertexCount) -> Iterator
{
  if (vertexCount == 0)
    return mCPUBuffer.end();

  auto oldSize = mCPUBuffer.size();
  mCPUBuffer.resize(mCPUBuffer.size() + vertexCount);
  mCPUVersion++;
  return std::next(mCPUBuffer.begin(), oldSize);
}

template <typename VertexType>
void BufferedRenderer<VertexType>::addVertex(VertexType vertex)
{
  mCPUBuffer.push_back(vertex);
  mCPUVersion++;
}

template <typename VertexType>
void BufferedRenderer<VertexType>::clear()
{
  mCPUBuffer.clear();
  mCPUVersion++;
}

template <typename VertexType>
void BufferedRenderer<VertexType>::render()
{
  if (mCPUVersion != mGPUVersion)
    updateGPUBuffer();

  mVAO.bind();
  mRenderer.renderArrays(0, mCPUBuffer.size());
  mVAO.unbind();
}

template <typename VertexType>
void BufferedRenderer<VertexType>::updateGPUBuffer()
{
  mGPUVersion = mCPUVersion;
  mVBO.bind();
  mVBO.setData(mCPUBuffer.data(), mCPUBuffer.size() * sizeof(VertexType));
  mVBO.unbind();
}

} // namespace aw
