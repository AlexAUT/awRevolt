#pragma once

#include <string>
#include <vector>

#include <aw/gui/style/alignment.hpp>
#include <aw/gui/style/padding.hpp>
#include <aw/gui/style/textStyle.hpp>
#include <aw/utils/log.hpp>
#include <aw/utils/math/vector.hpp>

#include <nanovg.h>

namespace aw::gui
{

// Adopted from https://github.com/memononen/nanovg/blob/master/example/demo.c
NVGcolor convertColor(Color color);
NVGalign convertAlignment(Alignment align);
int isBlack(NVGcolor col);
// static char* cpToUTF8(int cp, char* str);
void applyTextStyle(NVGcontext* vg, const TextStyle& style);

Vec2 getTextSize(NVGcontext* vg, const std::string& text, const TextStyle& style);

void drawButton(NVGcontext* vg, int preicon, const char* text, float x, float y, float w, float h, NVGcolor col);
void drawEditBoxBase(NVGcontext* vg, float x, float y, float w, float h);
void drawEditBox(NVGcontext* vg, const char* text, float x, float y, float w, float h);
void drawEditBoxCursor(NVGcontext* vg, const std::string& text, float x, float y, float w, float h, int cursorPos);

void drawRoundedRect(NVGcontext* vg, Vec2 pos, Vec2 size, float radius, Color fillColor, float dropShadowSize = 0.f);
void drawText(NVGcontext* vg, const std::string& text, Vec2 pos, Vec2 containerSize, const TextStyle& style,
              Alignment align, Padding padding);
void drawTextBlurred(NVGcontext* vg, const std::string& text, Vec2 pos, Vec2 containerSize, const TextStyle& style,
                     Alignment align, Padding padding);
void drawHeaderHighlight(NVGcontext* vg, Vec2 pos, Vec2 size, Color color, float cornerRadius);

NVGcolor convertColor(Color color)
{
  return {{{color.r, color.g, color.b, color.a}}};
}

NVGalign convertAlignment(Alignment align)
{
  int alignment = 0;
  switch (align.horizontal)
  {
  case AlignmentH::Left:
    alignment |= NVG_ALIGN_LEFT;
    break;
  case AlignmentH::Center:
    alignment |= NVG_ALIGN_CENTER;
    break;
  case AlignmentH::Right:
    alignment |= NVG_ALIGN_RIGHT;
    break;
  }
  switch (align.vertical)
  {
  case AlignmentV::Top:
    alignment |= NVG_ALIGN_TOP;
    break;
  case AlignmentV::Middle:
    alignment |= NVG_ALIGN_MIDDLE;
    break;
  case AlignmentV::Bottom:
    alignment |= NVG_ALIGN_BOTTOM;
    break;
  }

  return static_cast<NVGalign>(alignment);
}

int isBlack(NVGcolor col)
{
  if (col.r == 0.0f && col.g == 0.0f && col.b == 0.0f && col.a == 0.0f)
  {
    return 1;
  }
  return 0;
}

static char* cpToUTF8(int cp, char* str)
{
  int n = 0;
  if (cp < 0x80)
    n = 1;
  else if (cp < 0x800)
    n = 2;
  else if (cp < 0x10000)
    n = 3;
  else if (cp < 0x200000)
    n = 4;
  else if (cp < 0x4000000)
    n = 5;
  else if (cp <= 0x7fffffff)
    n = 6;
  str[n] = '\0';
  switch (n)
  {
  case 6:
    str[5] = static_cast<char>(0x80 | (cp & 0x3f));
    cp = cp >> 6;
    cp |= 0x4000000;
  case 5:
    str[4] = static_cast<char>(0x80 | (cp & 0x3f));
    cp = cp >> 6;
    cp |= 0x200000;
  case 4:
    str[3] = static_cast<char>(0x80 | (cp & 0x3f));
    cp = cp >> 6;
    cp |= 0x10000;
  case 3:
    str[2] = static_cast<char>(0x80 | (cp & 0x3f));
    cp = cp >> 6;
    cp |= 0x800;
  case 2:
    str[1] = static_cast<char>(0x80 | (cp & 0x3f));
    cp = cp >> 6;
    cp |= 0xc0;
  case 1:
    str[0] = static_cast<char>(cp);
  }
  return str;
}

void applyTextStyle(NVGcontext* vg, const TextStyle& style)
{
  nvgFontSize(vg, style.fontSize);
  nvgFontFace(vg, style.fontName.c_str());
  nvgFillColor(vg, convertColor(style.fontColor));
}

Vec2 getTextSize(NVGcontext* vg, const std::string& text, const TextStyle& style)
{
  applyTextStyle(vg, style);
  float bounds[4];
  nvgTextBounds(vg, 0.f, 0.f, text.c_str(), text.c_str() + text.size(), bounds);
  return {bounds[2] - bounds[0], bounds[3] - bounds[1]};
}

void drawButton(NVGcontext* vg, int preicon, const char* text, float x, float y, float w, float h, NVGcolor col)
{
  NVGpaint bg;
  float cornerRadius = 4.0f;

  bg = nvgLinearGradient(vg, x, y, x, y + h, nvgRGBA(255, 255, 255, isBlack(col) ? 16 : 32),
                         nvgRGBA(0, 0, 0, isBlack(col) ? 16 : 32));
  nvgBeginPath(vg);
  nvgRoundedRect(vg, x + 1, y + 1, w - 2, h - 2, cornerRadius - 1);
  if (!isBlack(col))
  {
    nvgFillColor(vg, col);
    nvgFill(vg);
  }
  nvgFillPaint(vg, bg);
  nvgFill(vg);

  nvgBeginPath(vg);
  nvgRoundedRect(vg, x + 0.5f, y + 0.5f, w - 1, h - 1, cornerRadius - 0.5f);
  nvgStrokeColor(vg, nvgRGBA(0, 0, 0, 48));
  nvgStroke(vg);
}

void drawEditBoxBase(NVGcontext* vg, float x, float y, float w, float h)
{
  NVGpaint bg;
  // Edit
  bg = nvgBoxGradient(vg, x + 1, y + 1 + 1.5f, w - 2, h - 2, 3, 4, nvgRGBA(255, 255, 255, 32), nvgRGBA(32, 32, 32, 32));
  nvgBeginPath(vg);
  nvgRoundedRect(vg, x, y, w, h, 4 - 1);
  nvgFillPaint(vg, bg);
  nvgFill(vg);

  nvgBeginPath(vg);
  nvgRoundedRect(vg, x - 0.5f, y - 0.5f, w + 1, h + 1, 4 - 0.5f);
  nvgStrokeColor(vg, nvgRGBA(0, 0, 0, 48));
  nvgStroke(vg);
}

void drawEditBoxCursor(NVGcontext* vg, const std::string& text, float x, float y, float w, float h, int cursorPos)
{
  float cursorX;
  if (text.empty())
  {
    cursorX = x + h * 0.3f;
  }
  else
  {
    static std::vector<NVGglyphPosition> positions;
    positions.resize(text.size());
    nvgTextGlyphPositions(vg, x + h * 0.3f, y + h * 0.5f, text.c_str(), text.c_str() + text.size(), positions.data(),
                          static_cast<int>(cursorPos + 1));

    if (static_cast<size_t>(cursorPos) < text.size())
      cursorX = positions[static_cast<size_t>(cursorPos)].minx - 2.f;
    else
      cursorX = positions.back().maxx - 2.f;
  }

  nvgFontSize(vg, 25.0f);
  nvgFontFace(vg, "sans");
  nvgFillColor(vg, nvgRGBA(255, 255, 255, 64));
  nvgTextAlign(vg, NVG_ALIGN_LEFT | NVG_ALIGN_MIDDLE);
  nvgText(vg, cursorX, y + h * 0.5f, "|", nullptr);
}

void drawRoundedRect(NVGcontext* vg, Vec2 pos, Vec2 size, float radius, Color fillColor, float dropShadowSize)
{
  nvgBeginPath(vg);
  nvgRoundedRect(vg, pos.x, pos.y, size.x, size.y, radius);
  nvgFillColor(vg, convertColor(fillColor));
  //	nvgFillColor(vg, nvgRGBA(0,0,0,128));
  nvgFill(vg);

  if (dropShadowSize > 0.f)
  {
    // Drop shadow
    auto shadowPaint = nvgBoxGradient(vg, pos.x, pos.y + 2, size.x, size.y, radius * 2, 10, nvgRGBA(0, 0, 0, 128),
                                      nvgRGBA(0, 0, 0, 0));
    nvgBeginPath(vg);
    float nOffset = dropShadowSize * 0.25f;
    float xPOffset = dropShadowSize * 0.5f;
    float yPOffset = dropShadowSize * 0.75f;
    nvgRect(vg, pos.x - nOffset, pos.y - nOffset, size.x + xPOffset, size.y + yPOffset);
    nvgRoundedRect(vg, pos.x, pos.y, size.x, size.y, radius);
    nvgPathWinding(vg, NVG_HOLE);
    nvgFillPaint(vg, shadowPaint);
    nvgFill(vg);
  }
}

void drawText(NVGcontext* vg, const std::string& text, Vec2 pos, Vec2 containerSize, const TextStyle& style,
              Alignment align, Padding padding)
{
  applyTextStyle(vg, style);
  nvgTextAlign(vg, convertAlignment(align));

  if (align.horizontal == AlignmentH::Left)
    pos.x += padding.left;
  else if (align.horizontal == AlignmentH::Center)
    pos.x += padding.left + ((containerSize.x - padding.left - padding.right) * 0.5f);
  else if (align.horizontal == AlignmentH::Right)
    pos.x += containerSize.x - padding.right;

  if (align.vertical == AlignmentV::Top)
    pos.y += padding.top;
  else if (align.vertical == AlignmentV::Middle)
    pos.y += padding.left + ((containerSize.y - padding.left - padding.right) * 0.5f);
  else if (align.vertical == AlignmentV::Bottom)
    pos.y += containerSize.y - padding.bottom;

  nvgText(vg, pos.x, pos.y, text.c_str(), nullptr);
}

void drawTextBlurred(NVGcontext* vg, const std::string& text, Vec2 pos, Vec2 containerSize, const TextStyle& style,
                     Alignment align, Padding padding)
{
  applyTextStyle(vg, style);
  nvgTextAlign(vg, convertAlignment(align));

  if (align.horizontal == AlignmentH::Left)
    pos.x += padding.left;
  else if (align.horizontal == AlignmentH::Center)
    pos.x += padding.left + ((containerSize.x - padding.left - padding.right) * 0.5f);
  else if (align.horizontal == AlignmentH::Right)
    pos.x += containerSize.x - padding.right;

  if (align.vertical == AlignmentV::Top)
    pos.y += padding.top;
  else if (align.vertical == AlignmentV::Middle)
    pos.y += padding.left + ((containerSize.y - padding.left - padding.right) * 0.5f);
  else if (align.vertical == AlignmentV::Bottom)
    pos.y += containerSize.y - padding.bottom;

  nvgFontBlur(vg, 2);
  nvgFillColor(vg, nvgRGBA(0, 0, 0, 128));
  nvgText(vg, pos.x, pos.y, text.c_str(), nullptr);

  nvgFontBlur(vg, 0);
  nvgFillColor(vg, convertColor(style.fontColor));
  nvgText(vg, pos.x, pos.y, text.c_str(), nullptr);
}

void drawHeaderHighlight(NVGcontext* vg, Vec2 pos, Vec2 size, Color color, float cornerRadius)
{
  // Header
  auto headerPaint =
      nvgLinearGradient(vg, pos.x, pos.y, pos.x, pos.y + 15, nvgRGBA(255, 255, 255, 8), nvgRGBA(0, 0, 0, 16));
  nvgBeginPath(vg);
  nvgFillColor(vg, convertColor(color));
  nvgRoundedRect(vg, pos.x + 1, pos.y + 1, size.x - 2, size.y, cornerRadius - 1);
  nvgFillPaint(vg, headerPaint);
  nvgFill(vg);
  nvgBeginPath(vg);
  nvgMoveTo(vg, pos.x + 0.5f, pos.y + 0.5f + size.y);
  nvgLineTo(vg, pos.x + 0.5f + size.x - 1, pos.y + 0.5f + size.y);
  nvgStrokeColor(vg, nvgRGBA(0, 0, 0, 32));
  nvgStroke(vg);
}

} // namespace aw::gui
