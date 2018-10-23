#pragma once

namespace aw
{
class Renderer
{
public:
  enum class PrimitiveType
  {
    Points,
    LineStrip,
    LineLoop,
    Lines,
    TriangleStrip,
    TriangleFan,
    Triangles,
  };

  enum class IndicesType
  {
    UnsignedByte,
    UnsignedShort,
    UnsignedInt,
  };

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
