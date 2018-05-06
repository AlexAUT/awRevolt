#include <aw/graphics/core/vertexArrayObject.hpp>

#include <aw/opengl/opengl.hpp>

#include <cassert>

namespace aw
{
void VertexArrayObject::bind() const
{
  for (auto& bufferAttrib : mAttributes)
  {
    const auto& buffer = bufferAttrib.first;
    const auto& attrib = bufferAttrib.second;
    buffer->bind();
    glEnableVertexAttribArray(attrib.index);
    glVertexAttribPointer(attrib.index, attrib.size, attrib.type, attrib.normalized, attrib.stride, attrib.offset);
  }
}

void VertexArrayObject::unbind() const
{
  for (auto& bufferAttrib : mAttributes)
  {
    const auto& buffer = bufferAttrib.first;
    const auto& attrib = bufferAttrib.second;
    buffer->unbind();
    glDisableVertexAttribArray(attrib.index);
  }
}

void VertexArrayObject::addVertexAttribute(const BufferObject* buffer, VertexAttribute attribute)
{
  assert(!indexInUse(attribute.index) && "You cannot insert a vertex attribute with the same index more than once!");
  assert(buffer && "VertexAttribute should not have a nullptr as buffer!");
  mAttributes.push_back({buffer, attribute});
}

bool VertexArrayObject::indexInUse(int index) const
{
  for (auto& a : mAttributes)
  {
    if (a.second.index == index)
      return true;
  }
  return false;
}

} // namespace aw
