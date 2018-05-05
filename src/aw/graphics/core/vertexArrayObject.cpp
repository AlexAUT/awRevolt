#include <aw/graphics/core/vertexArrayObject.hpp>

#include <aw/opengl/opengl.hpp>

#include <cassert>

namespace aw
{
void VertexArrayObject::bind() const
{
  for (auto& attribute : mAttributes)
  {
    attribute.buffer->bind();
    glEnableVertexAttribArray(attribute.index);
    glVertexAttribPointer(attribute.index, attribute.size, attribute.type, attribute.normalized, attribute.stride,
                          attribute.offset);
  }
}

void VertexArrayObject::unbind() const
{
  for (auto& attribute : mAttributes)
  {
    attribute.buffer->unbind();
    glDisableVertexAttribArray(attribute.index);
  }
}

void VertexArrayObject::addVertexAttribute(VertexAttribute attribute)
{
  assert(!indexInUse(attribute.index) && "You cannot insert a vertex attribute with the same index more than once!");
  assert(attribute.buffer && "VertexAttribute should not have a nullptr as buffer!");
  mAttributes.push_back(attribute);
}

bool VertexArrayObject::indexInUse(int index) const
{
  for (auto& a : mAttributes)
  {
    if (a.index == index)
      return true;
  }
  return false;
}

} // namespace aw
