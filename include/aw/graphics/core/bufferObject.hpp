#pragma once

#include <aw/utils/types.hpp>

typedef unsigned GLenum;
typedef unsigned GLbitfield;

namespace aw
{

class BufferObject
{
public:
  BufferObject(GLenum type);
  BufferObject(GLenum type, GLbitfield usage);
  virtual ~BufferObject();

  BufferObject(const BufferObject&) = delete;
  BufferObject operator=(const BufferObject&) = delete;

  void setData(const void* data, unsigned size);
  void setSubData(void* data, unsigned size, ptrdiff offset);

  void bind() const;
  void unbind() const;

  unsigned getId() const;

private:
  unsigned mId;
  GLenum mType;
  GLbitfield mUsage;
};

} // namespace aw
