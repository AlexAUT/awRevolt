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
NanovgRenderer::NanovgRenderer() : mContext(nvgCreateGL3(NVG_STENCIL_STROKES)) //| NVG_DEBUG))
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

void NanovgRenderer::beginFrame(Vec2 windowResolution)
{
  nvgBeginFrame(mContext, windowResolution.x, windowResolution.y, 1.f);
  glViewport(0, 0, static_cast<int>(windowResolution.x), static_cast<int>(windowResolution.y));
}

void NanovgRenderer::endFrame()
{
  nvgEndFrame(mContext);
}

template <>
void NanovgRenderer::render(const Panel& panel) const
{
  auto pos = panel.getGlobalPosition();
  auto size = panel.getSize();

  Color bgColor{28 / 255.f, 30 / 255.f, 34 / 255.f, 192 / 255.f};
  float dropShadowSize = 20.f;

  drawRoundedRect(mContext, pos, size, 4.f, bgColor, dropShadowSize);
}

template <>
void NanovgRenderer::render(const Window& window) const
{
  auto pos = window.getGlobalPosition();
  auto size = window.getSize();
  // Window
  Color bgColor{28 / 255.f, 30 / 255.f, 34 / 255.f, 192 / 255.f};
  float dropShadowSize = 40.f;
  drawRoundedRect(mContext, pos, size, 3.f, bgColor, dropShadowSize);

  // Header
  drawHeaderHighlight(mContext, pos, {size.x, 30.f}, bgColor, 3.f);

  drawTextBlurred(mContext, window.getTitle(), pos, {size.x, 30.f}, window.getTitleTextStyle(),
                  {AlignmentH::Center, AlignmentV::Middle}, Padding{0.f});
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

  using namespace aw::gui;
  const auto a = Alignment{AlignmentH::Center, AlignmentV::Middle};
  const auto p = Padding(0.f);
  drawText(mContext, button.getText(), pos, size, button.getTextLayout(), a, p);
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

  drawEditBoxBase(mContext, pos.x, pos.y, size.x, size.y);

  // To counter the drop shadow, otherwise the text looks too high and not centered
  pos.y += 1;
  pos.x += textBox.getPadding().left;
  // size -= Vec2{p.left + p.right, p.top + p.bottom};
  using namespace aw::gui;
  const auto& textStyle = *textBox.getTextStyle();
  drawText(mContext, text, pos, size, textStyle, {AlignmentH::Left, AlignmentV::Middle}, {});

  if (textBox.shouldRenderCursor())
  {
    drawEditBoxCursor(mContext, textStyle, text.c_str(), pos.x, pos.y, size.x, size.y, textBox.getCursorPosition());
  }
}

template <>
void NanovgRenderer::render(const Menu& menu) const
{
  auto pos = menu.getGlobalPosition();
  auto size = menu.getSize();
  const Color color{28 / 255.f, 30 / 255.f, 34 / 255.f, 255 / 255.f};

  drawRoundedRect(mContext, pos, size, 0.f, color);
  drawHeaderHighlight(mContext, pos, size, color, 0.f);
}

template <>
void NanovgRenderer::render(const MenuItem& menuItem) const
{
  if (menuItem.isInState(Widget::State::Selected))
  {
    auto pos = menuItem.getGlobalPosition();
    auto size = menuItem.getSize();
    const Color color{28 / 255.f, 30 / 255.f, 255 / 255.f, 255 / 255.f};

    auto lineThickness = size.y * 0.1f;
    pos.y += (size.y - lineThickness) - 2;
    size.y = lineThickness;

    drawRoundedRect(mContext, pos, size, 0.f, color);
  }
  render(static_cast<const Label&>(menuItem));
}

template <>
void NanovgRenderer::render(const MenuSubItem& menuSubItem) const
{
  using State = Widget::State;
  if (menuSubItem.isInState(State::Hovered) || menuSubItem.isInState(State::Selected))
  {
    auto pos = menuSubItem.getGlobalPosition();
    auto size = menuSubItem.getSize();
    const Color color{28 / 255.f, 30 / 255.f, 255 / 255.f, 255 / 255.f};
    drawRoundedRect(mContext, pos, size, 3.f, color);
    drawHeaderHighlight(mContext, pos, size, color, 0.f);
  }
  render(static_cast<const Label&>(menuSubItem));
}

template <>
void NanovgRenderer::render(const ListItem& listItem) const
{
  using State = Widget::State;
  if (listItem.isInState(State::Hovered) || listItem.isInState(State::Selected))
  {
    auto pos = listItem.getGlobalPosition();
    auto size = listItem.getSize();
    Color color{28 / 255.f, 30 / 255.f, 255 / 255.f, 255 / 255.f};
    if (!listItem.isInState(State::Selected))
      color.shade(0.25f);

    drawRoundedRect(mContext, pos, size, 3.f, color);
    drawHeaderHighlight(mContext, pos, size, color, 0.f);
  }
  render(static_cast<const Label&>(listItem));
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
  {
    if (positions[i].maxx >= relativePoint.x)
    {
      auto span = positions[i].maxx - positions[i].minx;
      if (relativePoint.x <= (positions[i].minx + (0.5 * span)))
        return static_cast<int>(i);
      return static_cast<int>(i) + 1;
    }
  }
  return static_cast<int>(text.size());
}
} // namespace aw::gui
