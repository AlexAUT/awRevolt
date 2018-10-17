#pragma once

#include <aw/graphics/core/geometry.hpp>
#include <aw/graphics/core/vertexArrayObject.hpp>
#include <aw/graphics/core/vertexBuffer.hpp>
#include <aw/opengl/opengl.hpp>
#include <aw/utils/spatial/AABB.hpp>
#include <aw/utils/types.hpp>

#include <vector>

namespace aw
{
template <typename VertexType>
class PrimitiveRenderer
{
public:
  using VertexContainer = std::vector<VertexType>;

public:
  template <typename Primitive>
  void addPrimitive(Primitive& p);

  void clear();
  void render();

private:
private:
  VertexContainer mCPUBuffer;
  size_t mGPUBufferSize{0};
  VertexBuffer mGPUBuffer;

  VertexArrayObject mVAO;
};

template <typename Primitive>
void addPrimitive(const aw::AABB& p)
{
  geo::cube<Primitive>(p.getCenter(), p.getSize());
}

template <typename VertexType>
void PrimitiveRenderer<VertexType>::clear()
{
  mCPUBuffer.clear();
}

template <typename VertexType>
void PrimitiveRenderer<VertexType>::render()
{
  if (mGPUBufferSize < mCPUBuffer.size())
  {
    mGPUBuffer.setData(mCPUBuffer.data(), sizeof(VertexType) * mCPUBuffer.size());
    mGPUBufferSize = mCPUBuffer.size();
  }
  else
    mGPUBuffer.setSubData(mCPUBuffer.data(), sizeof(VertexType) * mCPUBuffer.size(), 0);

  mVAO.bind();
  GL_CHECK(glDrawArrays(GL_TRIANGLES, 0, mCPUBuffer.size()));
}
} // namespace aw
