#include <aw/graphics/core/vertexArrayObject.hpp>

#include <aw/opengl/opengl.hpp>

#include <aw/graphics/core/indicesBuffer.hpp>
#include <aw/graphics/core/vertexBuffer.hpp>

#include <cassert>

namespace aw
{
void VertexArrayObject::bind() const
{
  for (auto& bufferAttrib : mAttributes)
  {
    const auto& vbo = std::get<0>(bufferAttrib.first);
    if (vbo)
      vbo->bind();
    const auto& ibo = std::get<1>(bufferAttrib.first);
    if (ibo)
      ibo->bind();
    const auto& attrib = bufferAttrib.second;
    glEnableVertexAttribArray(attrib.index);
    glVertexAttribPointer(attrib.index, attrib.size, attrib.type, attrib.normalized, attrib.stride, attrib.offset);
  }
}

void VertexArrayObject::unbind() const
{
  for (auto& bufferAttrib : mAttributes)
  {
    const auto& vbo = std::get<0>(bufferAttrib.first);
    if (vbo)
      vbo->unbind();
    const auto& ibo = std::get<1>(bufferAttrib.first);
    if (ibo)
      ibo->unbind();
    const auto& attrib = bufferAttrib.second;
    glDisableVertexAttribArray(attrib.index);
  }
}

void VertexArrayObject::addVertexAttribute(const VertexBuffer* buffer, VertexAttribute attribute)
{
  addVertexAttribute(buffer, nullptr, attribute);
}

void VertexArrayObject::addVertexAttribute(const VertexBuffer* buffer, const IndicesBuffer* indices,
                                           VertexAttribute attribute)
{
  assert(!indexInUse(attribute.index) && "You cannot insert a vertex attribute with the same index more than once!");
  assert(buffer && "VertexAttribute should not have a nullptr as buffer!");
  mAttributes.push_back({{buffer, indices}, attribute});
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
