#include <aw/graphics/core/vertexArrayObject.hpp>

#include <aw/config.hpp>
#include <aw/graphics/core/indicesBuffer.hpp>
#include <aw/graphics/core/vertexBuffer.hpp>
#include <aw/opengl/opengl.hpp>

#include <cassert>

namespace aw
{
#ifdef AW_USE_GL
VertexArrayObject::VertexArrayObject()
{
  GL_CHECK(glGenVertexArrays(1, &mVAOHandle));
}

VertexArrayObject::~VertexArrayObject()
{
  GL_CHECK(glDeleteVertexArrays(1, &mVAOHandle));
}
#endif
void VertexArrayObject::bind() const
{
#ifdef AW_USE_GL
  GL_CHECK(glBindVertexArray(mVAOHandle));
#else
  for (auto& bufferAttrib : mAttributes)
  {
    applyVertexAttribute(bufferAttrib);
  }
#endif
}

void VertexArrayObject::unbind() const
{
#ifdef AW_USE_GL
  GL_CHECK(glBindVertexArray(0));
#else
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
#endif
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
#ifdef AW_USE_GL
  bind();
  applyVertexAttribute(mAttributes.back());
#endif
}

bool VertexArrayObject::indexInUse(unsigned index) const
{
  for (auto& a : mAttributes)
  {
    if (a.second.index == index)
      return true;
  }
  return false;
}

void VertexArrayObject::applyVertexAttribute(const BindPair& attribute) const
{
  const auto& vbo = std::get<0>(attribute.first);
  if (vbo)
    vbo->bind();
  const auto& ibo = std::get<1>(attribute.first);
  if (ibo)
    ibo->bind();
  const auto& attrib = attribute.second;
  glEnableVertexAttribArray(attrib.index);
  glVertexAttribPointer(attrib.index, attrib.size, attrib.type, attrib.normalized, attrib.stride, attrib.offset);
}

} // namespace aw
