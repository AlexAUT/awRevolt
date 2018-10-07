#include <aw/gui/renderer/nanovgRenderer.hpp>

#include "nanovgDrawHelper.hpp"

#include <aw/gui/widgets/widgets.hpp>
#include <aw/opengl/opengl.hpp>
#include <aw/utils/log.hpp>

#include <nanovg_gl.h>

#include <cassert>

namespace aw::gui
{
NanovgRenderer::NanovgRenderer() : mContext(nvgCreateGL3(NVG_STENCIL_STROKES | NVG_DEBUG))
{
  assert(mContext);

  nvgCreateFont(mContext, "sans", "assets/fonts/Roboto-Regular.ttf");
  nvgCreateFont(mContext, "sans-bold", "assets/fonts/Roboto-Bold.ttf");
}

NanovgRenderer::~NanovgRenderer()
{
  if (mContext)
    nvgDeleteGL3(mContext);
}

void NanovgRenderer::beginFrame()
{
  nvgBeginFrame(mContext, 800.f, 600.f, 1.f);
}

void NanovgRenderer::endFrame()
{
  nvgEndFrame(mContext);
}

template <>
void NanovgRenderer::render(const Window& window)
{
  auto pos = window.getGlobalPosition();
  auto size = window.getSize();
  drawWindow(mContext, window.getTitle().c_str(), pos.x, pos.y, size.x, size.y);
}
} // namespace aw::gui
