#pragma once

#ifdef AW_USE_OPENGL
#include <aw/opengl/impl/gl_core_4_5.hpp>
#endif
#ifdef AW_USE_GLES
#include <GLES2/gl2.h>
#endif
#include <stdexcept>

namespace aw
{

#define vOffsetof(struct_, member_) reinterpret_cast<const void*>(offsetof(struct_, member_))

class GLException : public std::runtime_error
{
public:
  explicit GLException(const char* message);
  explicit GLException(const std::string& message);
};

namespace opengl
{

namespace priv
{
GLenum glCheckError(const char* file, int line);
}
} // namespace opengl
} // namespace aw

#define GL_CHECK(x)                                                                                                    \
  x;                                                                                                                   \
  aw::opengl::priv::glCheckError(__FILE__, __LINE__);
