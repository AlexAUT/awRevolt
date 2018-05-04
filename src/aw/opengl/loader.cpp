#include <aw/opengl/loader.hpp>

#include <aw/opengl/impl/gl_core_4_5.hpp>

#include <aw/utils/log.hpp>

DEFINE_LOG_CATEGORY(OpenGLLoaderW, aw::log::Warning, OpenGL_Loader)
DEFINE_LOG_CATEGORY(OpenGLLoaderD, aw::log::Debug, OpenGL_Loader)

namespace aw
{
namespace opengl
{

void init()
{
#ifdef AW_USE_OPENGL
  auto result = gl::sys::LoadFunctions();
  if (result.GetNumMissing() > 0)
  {
    LogOpenGLLoaderW() << "Failed to load opengl pointers! Failed function: " << result.GetNumMissing();
  }
  else
  {
    LogOpenGLLoaderD() << "Opengl version " << gl::sys::GetMajorVersion() << "." << gl::sys::GetMinorVersion()
                       << " loaded!";
  }
#endif
}

} // namespace opengl
} // namespace aw
