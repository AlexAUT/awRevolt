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
  while ((errorCode = gl::GetError()) != gl::NO_ERROR_)
  {
    std::string message;
    switch (errorCode)
    {
    case gl::INVALID_ENUM:
      message = "INVALID_ENUM";
      break;
    case gl::INVALID_VALUE:
      message = "INVALID_VALUE";
      break;
    case gl::INVALID_OPERATION:
      message = "INVALID_OPERATION";
      break;
    case gl::STACK_OVERFLOW:
      message = "STACK_OVERFLOW";
      break;
    case gl::STACK_UNDERFLOW:
      message = "STACK_UNDERFLOW";
      break;
    case gl::OUT_OF_MEMORY:
      message = "OUT_OF_MEMORY";
      break;
    case gl::INVALID_FRAMEBUFFER_OPERATION:
      message = "INVALID_FRAMEBUFFER_OPERATION";
      break;
    default:
      message = "UNKNOWN OPENGL ERROR, CODE: " + std::to_string(errorCode);
    }
    message += " in " + std::string(file) + ":" + std::to_string(line);
    LogOpenGLE() << message;
    throw GLException(message);
  }
  return gl::NO_ERROR_;
}

} // namespace priv
} // namespace opengl
} // namespace aw
