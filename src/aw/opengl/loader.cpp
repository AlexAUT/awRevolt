#include <aw/opengl/loader.hpp>

#include <aw/opengl/opengl.hpp>

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
  if (ogl_LoadFunctions() == ogl_LOAD_FAILED)
  {
    LogOpenGLLoaderW() << "Failed to load opengl pointers!";
  }
#endif
}

} // namespace opengl
} // namespace aw
