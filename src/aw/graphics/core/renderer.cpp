#include <aw/graphics/core/renderer.hpp>

#include <aw/opengl/opengl.hpp>

#include <cassert>

namespace aw
{
// TODO: move them into opengl package
unsigned convertPrimitiveTypeToGL(PrimitiveType type);
unsigned convertIndicesTypeToGL(IndicesType type);

Renderer::Renderer(PrimitiveType pType) : mPrimitiveType(convertPrimitiveTypeToGL(pType)) {}

Renderer::Renderer(PrimitiveType pType, IndicesType iType) :
    mPrimitiveType(convertPrimitiveTypeToGL(pType)),
    mIndicesType(convertIndicesTypeToGL(iType))
{
}

void Renderer::setPrimitiveType(PrimitiveType type)
{
  mPrimitiveType = convertPrimitiveTypeToGL(type);
}

void Renderer::setIndicesType(IndicesType type)
{
  mIndicesType = convertIndicesTypeToGL(type);
}

void Renderer::renderArrays(int startOffset, int count) const
{
  GL_CHECK(glDrawArrays(static_cast<GLenum>(mPrimitiveType), startOffset, count));
}

void Renderer::renderElements(int count, const void* indicesOffset) const
{
  GL_CHECK(
      glDrawElements(static_cast<GLenum>(mPrimitiveType), count, static_cast<GLenum>(mIndicesType), indicesOffset));
}

unsigned convertPrimitiveTypeToGL(PrimitiveType type)
{
  using Type = PrimitiveType;
  switch (type)
  {
  case Type::Triangles:
    return GL_TRIANGLES;
  case Type::TriangleFan:
    return GL_TRIANGLE_FAN;
  case Type::TriangleStrip:
    return GL_TRIANGLE_STRIP;
  case Type::Points:
    return GL_POINTS;
  case Type::Lines:
    return GL_LINES;
  case Type::LineLoop:
    return GL_LINE_LOOP;
  case Type::LineStrip:
    return GL_LINE_STRIP;
  default:
    assert("You should never come here when using the enum class correctly");
    return GL_TRIANGLES;
  }
}

unsigned convertIndicesTypeToGL(IndicesType type)
{
  using Type = IndicesType;
  switch (type)
  {
  case Type::UnsignedInt:
    return GL_UNSIGNED_INT;
  case Type::UnsignedShort:
    return GL_UNSIGNED_SHORT;
  case Type::UnsignedByte:
    return GL_UNSIGNED_BYTE;
  default:
    assert("You should never come here when using the enum class correctly");
    return GL_UNSIGNED_INT;
  }
}

} // namespace aw
