#pragma once

#include <aw/graphics/core/vertexAttribute.hpp>

#include <tuple>
#include <vector>

namespace aw
{

class VertexBuffer;
class IndicesBuffer;

class VertexArrayObject
{
public:
  VertexArrayObject() = default;
  VertexArrayObject(const VertexArrayObject&) = delete;
  VertexArrayObject operator=(const VertexArrayObject&) = delete;

  void bind() const;
  void unbind() const;

  void addVertexAttribute(const VertexBuffer* buffer, VertexAttribute attribute);
  void addVertexAttribute(const VertexBuffer* buffer, const IndicesBuffer* indices, VertexAttribute attribute);

private:
  bool indexInUse(int index) const;

private:
  typedef std::tuple<const VertexBuffer*, const IndicesBuffer*> DrawBufferBindings;
  std::vector<std::pair<DrawBufferBindings, const VertexAttribute>> mAttributes;
};

} // namespace aw
