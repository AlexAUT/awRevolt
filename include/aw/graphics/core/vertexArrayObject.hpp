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

  void addVertexAttribute(VertexAttribute attribute);

private:
  bool indexInUse(int index) const;

private:
  std::vector<VertexAttribute> mAttributes;
};

} // namespace aw
