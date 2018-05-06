#pragma once

#include <aw/graphics/core/vertexAttribute.hpp>

#include <vector>

namespace aw
{

class VertexArrayObject
{
public:
  VertexArrayObject() = default;
  VertexArrayObject(const VertexArrayObject&) = delete;
  VertexArrayObject operator=(const VertexArrayObject&) = delete;

  void bind() const;
  void unbind() const;

  void addVertexAttribute(const BufferObject* buffer, VertexAttribute attribute);

private:
  bool indexInUse(int index) const;

private:
  std::vector<std::pair<const BufferObject*, const VertexAttribute>> mAttributes;
};

} // namespace aw
