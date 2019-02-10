#pragma once

#include <aw/graphics/core/indicesType.hpp>
#include <aw/graphics/core/primitiveType.hpp>

namespace aw
{
class Renderer
{
public:
  Renderer(PrimitiveType primitiveType);
  Renderer(PrimitiveType type, IndicesType indicesType);

  void setPrimitiveType(PrimitiveType type);
  void setIndicesType(IndicesType type);

  void renderArrays(int startOffset, int count) const;
  void renderElements(int count, const void* indicesOffset = nullptr) const;

private:
private:
  unsigned mPrimitiveType;
  unsigned mIndicesType;
};
} // namespace aw
