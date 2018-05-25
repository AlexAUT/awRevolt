#pragma once

typedef unsigned GLenum;

namespace aw
{
class RenderBuffer
{
public:
  RenderBuffer();
  ~RenderBuffer();

  void create(unsigned width, unsigned height);
  void create(unsigned width, unsigned height, GLenum type);

  void bind() const;
  void unbind() const;

  unsigned getId() const;

private:
private:
  unsigned mRenderBuffer{0};
};

} // namespace aw
