#pragma once

#include <aw/config.hpp>

#ifdef AW_USE_OPENGL
#include <aw/opengl/impl/gl.hpp>
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
GLenum glCheckError(const char* stmt, const char* file, int line);

} // namespace priv
} // namespace opengl
} // namespace aw

#ifdef _DEBUG
#define GL_CHECK(stmt)                                                                                                 \
  do                                                                                                                   \
  {                                                                                                                    \
    stmt;                                                                                                              \
    aw::opengl::priv::glCheckError(#stmt, __FILE__, __LINE__);                                                         \
  } while (false)
#else
#define GL_CHECK(stmt) stmt
#endif
