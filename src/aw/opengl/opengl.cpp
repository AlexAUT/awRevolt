#include <aw/opengl/opengl.hpp>

#include <aw/utils/log.hpp>

DEFINE_LOG_CATEGORY(OpenGLE, aw::log::Error, Opengl)

namespace aw
{

GLException::GLException(const char* message) : std::runtime_error(message)
{
}

GLException::GLException(const std::string& message) : std::runtime_error(message)
{
}

namespace opengl
{
namespace priv
{
GLenum glCheckError(const char* file, int line)
{
  GLenum errorCode;
  while ((errorCode = glGetError()) != GL_NO_ERROR)
  {
    std::string message;
    switch (errorCode)
    {
    case GL_INVALID_ENUM:
      message = "INVALID_ENUM";
      break;
    case GL_INVALID_VALUE:
      message = "INVALID_VALUE";
      break;
    case GL_INVALID_OPERATION:
      message = "INVALID_OPERATION";
      break;
#ifdef GL_STACK_OVERFLOW
    case GL_STACK_OVERFLOW:
      message = "STACK_OVERFLOW";
      break;
#endif
#ifdef GL_STACK_UNDERFLOW
    case GL_STACK_UNDERFLOW:
      message = "STACK_UNDERFLOW";
      break;
#endif
    case GL_OUT_OF_MEMORY:
      message = "OUT_OF_MEMORY";
      break;
#ifdef GL_INVALID_FRAMEBUFFER_OPERATION
    case GL_INVALID_FRAMEBUFFER_OPERATION:
      message = "INVALID_FRAMEBUFFER_OPERATION";
      break;
#endif
    default:
      message = "UNKNOWN OPENGL ERROR, CODE: " + std::to_string(errorCode);
    }
    message += " in " + std::string(file) + ":" + std::to_string(line);
    LogOpenGLE() << message;
    throw GLException(message);
  }
  return GL_NO_ERROR;
}

} // namespace priv
} // namespace opengl
} // namespace aw
