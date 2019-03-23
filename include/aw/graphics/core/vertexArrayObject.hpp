#pragma once

#include <aw/config.hpp>

#include <aw/graphics/core/vertexAttribute.hpp>
#include <aw/graphics/core/vertexLayout.hpp>

#include <tuple>
#include <vector>

namespace aw
{

class VertexBuffer;
class IndicesBuffer;

class VertexArrayObject
{
public:
  using DrawBufferBindings = std::tuple<const VertexBuffer*, const IndicesBuffer*>;
  using BindPair = std::pair<DrawBufferBindings, VertexAttribute>;

public:
#ifdef AW_USE_GL
  VertexArrayObject();
  ~VertexArrayObject();
#else
  VertexArrayObject() = default;
#endif
  VertexArrayObject(const VertexArrayObject&) = delete;
  VertexArrayObject operator=(const VertexArrayObject&) = delete;

  void bind() const;
  void unbind() const;

  void addVertexAttribute(const VertexBuffer* buffer, VertexAttribute attribute);
  void addVertexAttribute(const VertexBuffer* buffer, const IndicesBuffer* indices, VertexAttribute attribute);

  template <size_t T>
  void addVertexAttributes(const VertexBuffer* buffer, const VertexLayout<T>& layout);

private:
  bool indexInUse(unsigned index) const;

  void applyVertexAttribute(const BindPair& bufferAttribute) const;

private:
  std::vector<BindPair> mAttributes;
#ifdef AW_USE_GL
  unsigned mVAOHandle;
#endif
};

template <size_t T>
void VertexArrayObject::addVertexAttributes(const VertexBuffer* buffer, const VertexLayout<T>& layout)
{
  for (const auto& a : layout)
    addVertexAttribute(buffer, a);
}

} // namespace aw
