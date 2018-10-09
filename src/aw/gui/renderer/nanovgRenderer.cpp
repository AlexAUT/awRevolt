#include <aw/gui/renderer/nanovgRenderer.hpp>

#include "nanovgDrawHelper.hpp"

#include <aw/gui/style/textStyle.hpp>
#include <aw/gui/widgets/widgets.hpp>
#include <aw/opengl/opengl.hpp>
#include <aw/utils/color.hpp>
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

Vec2 NanovgRenderer::calculateTextSize(const std::string& text, const TextStyle& style) const
{
  return getTextSize(mContext, text, style);
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
void NanovgRenderer::render(const Window& window) const
{
  auto pos = window.getGlobalPosition();
  auto size = window.getSize();
  drawWindow(mContext, window.getTitle().c_str(), pos.x, pos.y, size.x, size.y);
}

void tintColor(NVGcolor& color, float amount)
{
  color.r = color.r - color.r * amount;
  color.g = color.g - color.g * amount;
  color.b = color.b - color.b * amount;
}

void shadeColor(NVGcolor& color, float amount)
{
  color.r = color.r + (1.f - color.r) * amount;
  color.g = color.g + (1.f - color.g) * amount;
  color.b = color.b + (1.f - color.b) * amount;
}

template <>
void NanovgRenderer::render(const Button& button) const
{
  auto pos = button.getGlobalPosition();
  auto size = button.getSize();
  NVGcolor color = nvgRGBA(0, 96, 128, 255);
  using State = Button::State;
  if (button.isInState(State::Pressed))
    tintColor(color, 0.25f);
  else if (button.isInState(State::Hovered))
    shadeColor(color, 0.1f);
  drawButton(mContext, 0, button.getText().c_str(), pos.x, pos.y, size.x, size.y, color);
}

template <>
void NanovgRenderer::render(const Label& label) const
{
  auto pos = label.getGlobalPosition();
  auto size = label.getSize();

  drawText(mContext, label.getText(), pos, size, label.getTextLayout(), label.getAlignment(), label.getPadding());
}

template <>
void NanovgRenderer::render(const TextBox& textBox) const
{
  auto pos = textBox.getGlobalPosition();
  auto size = textBox.getSize();
  const auto& text = textBox.getText();

  drawEditBox(mContext, text.c_str(), pos.x, pos.y, size.x, size.y);

  if (textBox.shouldRenderCursor())
  {
    drawEditBoxCursor(mContext, text.c_str(), pos.x, pos.y, size.x, size.y, textBox.getCursorPosition());
  }
}

template <>
int NanovgRenderer::calculateCursorPosition(const TextBox& textBox, Vec2 relativePoint) const
{
  const auto& text = textBox.getText();
  if (text.empty())
    return 0;

  static std::vector<NVGglyphPosition> positions;
  positions.resize(text.size());

  auto size = textBox.getSize();

  nvgFontSize(mContext, 20.0f);
  nvgFontFace(mContext, "sans");
  nvgTextAlign(mContext, NVG_ALIGN_LEFT | NVG_ALIGN_MIDDLE);
  nvgTextGlyphPositions(mContext, size.y * 0.3f, size.y * 0.5f, text.c_str(), text.c_str() + text.size(),
                        positions.data(), (int)text.size());

  for (unsigned i = 0; i < text.size(); i++)
    LogTemp() << text[i] << " = " << positions[i].minx << ", " << positions[i].maxx;
  for (unsigned i = 0; i < text.size(); i++)
  {
    if (positions[i].maxx >= relativePoint.x)
    {
      LogTemp() << "Inside character: " << i;
      auto span = positions[i].maxx - positions[i].minx;
      if (relativePoint.x <= (positions[i].minx + (0.5 * span)))
        return static_cast<int>(i);
      return static_cast<int>(i) + 1;
    }
  }
  return static_cast<int>(text.size());
}
} // namespace aw::gui
