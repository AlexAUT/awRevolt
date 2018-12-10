#pragma once

#include <aw/graphics/core/geometry.hpp>
#include <aw/graphics/core/renderer.hpp>
#include <aw/graphics/core/vertexArrayObject.hpp>
#include <aw/graphics/core/vertexBuffer.hpp>
#include <aw/utils/spatial/AABB.hpp>
#include <aw/utils/types.hpp>

#include <vector>

namespace aw
{
template <typename VertexType_>
class PrimitiveRenderer
{
public:
  using VertexType = VertexType_;
  using VertexContainer = std::vector<VertexType>;
  using Iterator = typename VertexContainer::iterator;
  using PrimitiveType = Renderer::PrimitiveType;

public:
  PrimitiveRenderer(PrimitiveType primitiveType = PrimitiveType::Triangles);

  Iterator allocate(size_t count);

  void clear();
  void render();

private:
private:
  VertexContainer mCPUBuffer;
  size_t mGPUBufferSize{0};
  VertexBuffer mGPUBuffer;

  VertexArrayObject mVAO;
  Renderer mRenderer;
};

template <typename VertexType>
PrimitiveRenderer<VertexType>::PrimitiveRenderer(PrimitiveType primitiveType) : mRenderer(primitiveType)
{
  mVAO.bind();
  mVAO.addVertexAttributes(&mGPUBuffer, VertexType::Layout);
  mVAO.unbind();
}

template <typename VertexType>
auto PrimitiveRenderer<VertexType>::allocate(size_t count) -> Iterator
{
  auto currentSize = mCPUBuffer.size();
  mCPUBuffer.resize(currentSize + count);
  return mCPUBuffer.begin() + currentSize;
}

template <typename VertexType>
void PrimitiveRenderer<VertexType>::clear()
{
  mCPUBuffer.clear();
}

template <typename VertexType>
void PrimitiveRenderer<VertexType>::render()
{
  if (mCPUBuffer.empty())
    return;

  mGPUBuffer.bind();
  if (mGPUBufferSize < mCPUBuffer.size())
  {
    mGPUBuffer.setData(mCPUBuffer.data(), sizeof(VertexType) * mCPUBuffer.size());
    mGPUBufferSize = mCPUBuffer.size();
  }
  else
  {
    mGPUBuffer.setSubData(mCPUBuffer.data(), sizeof(VertexType) * mCPUBuffer.size(), 0);
  }
  mGPUBuffer.unbind();

  mVAO.bind();

  mRenderer.renderArrays(0, mCPUBuffer.size());
  mVAO.unbind();
}
} // namespace aw
