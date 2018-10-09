#pragma once

#include <string>
#include <vector>

#include <aw/utils/log.hpp>

#include <nanovg.h>

// Adopted from https://github.com/memononen/nanovg/blob/master/example/demo.c

void drawWindow(NVGcontext* vg, const char* title, float x, float y, float w, float h);
void drawButton(NVGcontext* vg, int preicon, const char* text, float x, float y, float w, float h, NVGcolor col);
void drawEditBoxBase(NVGcontext* vg, float x, float y, float w, float h);
void drawEditBox(NVGcontext* vg, const char* text, float x, float y, float w, float h);

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

void drawWindow(NVGcontext* vg, const char* title, float x, float y, float w, float h)
{
  float cornerRadius = 3.0f;
  NVGpaint shadowPaint;
  NVGpaint headerPaint;

  nvgSave(vg);
  //	nvgClearState(vg);

  // Window
  nvgBeginPath(vg);
  nvgRoundedRect(vg, x, y, w, h, cornerRadius);
  nvgFillColor(vg, nvgRGBA(28, 30, 34, 192));
  //	nvgFillColor(vg, nvgRGBA(0,0,0,128));
  nvgFill(vg);

  // Drop shadow
  shadowPaint = nvgBoxGradient(vg, x, y + 2, w, h, cornerRadius * 2, 10, nvgRGBA(0, 0, 0, 128), nvgRGBA(0, 0, 0, 0));
  nvgBeginPath(vg);
  nvgRect(vg, x - 10, y - 10, w + 20, h + 30);
  nvgRoundedRect(vg, x, y, w, h, cornerRadius);
  nvgPathWinding(vg, NVG_HOLE);
  nvgFillPaint(vg, shadowPaint);
  nvgFill(vg);

  // Header
  headerPaint = nvgLinearGradient(vg, x, y, x, y + 15, nvgRGBA(255, 255, 255, 8), nvgRGBA(0, 0, 0, 16));
  nvgBeginPath(vg);
  nvgRoundedRect(vg, x + 1, y + 1, w - 2, 30, cornerRadius - 1);
  nvgFillPaint(vg, headerPaint);
  nvgFill(vg);
  nvgBeginPath(vg);
  nvgMoveTo(vg, x + 0.5f, y + 0.5f + 30);
  nvgLineTo(vg, x + 0.5f + w - 1, y + 0.5f + 30);
  nvgStrokeColor(vg, nvgRGBA(0, 0, 0, 32));
  nvgStroke(vg);

  nvgFontSize(vg, 30.0f);
  nvgFontFace(vg, "sans-bold");
  nvgTextAlign(vg, NVG_ALIGN_CENTER | NVG_ALIGN_MIDDLE);

  nvgFontBlur(vg, 2);
  nvgFillColor(vg, nvgRGBA(0, 0, 0, 128));
  nvgText(vg, x + w / 2, y + 16 + 1, title, nullptr);

  nvgFontBlur(vg, 0);
  nvgFillColor(vg, nvgRGBA(220, 220, 220, 160));
  nvgText(vg, x + w / 2, y + 16, title, nullptr);

  nvgRestore(vg);
}

void drawButton(NVGcontext* vg, int preicon, const char* text, float x, float y, float w, float h, NVGcolor col)
{
  NVGpaint bg;
  char icon[8];
  float cornerRadius = 4.0f;
  float tw = 0, iw = 0;

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

  nvgFontSize(vg, 20.0f);
  nvgFontFace(vg, "sans-bold");
  tw = nvgTextBounds(vg, 0, 0, text, nullptr, nullptr);
  if (preicon != 0)
  {
    nvgFontSize(vg, h * 1.3f);
    nvgFontFace(vg, "icons");
    iw = nvgTextBounds(vg, 0, 0, cpToUTF8(preicon, icon), nullptr, nullptr);
    iw += h * 0.15f;
  }

  if (preicon != 0)
  {
    nvgFontSize(vg, h * 1.3f);
    nvgFontFace(vg, "icons");
    nvgFillColor(vg, nvgRGBA(255, 255, 255, 96));
    nvgTextAlign(vg, NVG_ALIGN_LEFT | NVG_ALIGN_MIDDLE);
    nvgText(vg, x + w * 0.5f - tw * 0.5f - iw * 0.75f, y + h * 0.5f, cpToUTF8(preicon, icon), nullptr);
  }

  nvgFontSize(vg, 20.0f);
  nvgFontFace(vg, "sans-bold");
  nvgTextAlign(vg, NVG_ALIGN_LEFT | NVG_ALIGN_MIDDLE);
  nvgFillColor(vg, nvgRGBA(0, 0, 0, 160));
  nvgText(vg, x + w * 0.5f - tw * 0.5f + iw * 0.25f, y + h * 0.5f - 1, text, nullptr);
  nvgFillColor(vg, nvgRGBA(255, 255, 255, 160));
  nvgText(vg, x + w * 0.5f - tw * 0.5f + iw * 0.25f, y + h * 0.5f, text, nullptr);
}

void drawEditBoxBase(NVGcontext* vg, float x, float y, float w, float h)
{
  NVGpaint bg;
  // Edit
  bg = nvgBoxGradient(vg, x + 1, y + 1 + 1.5f, w - 2, h - 2, 3, 4, nvgRGBA(255, 255, 255, 32), nvgRGBA(32, 32, 32, 32));
  nvgBeginPath(vg);
  nvgRoundedRect(vg, x + 1, y + 1, w - 2, h - 2, 4 - 1);
  nvgFillPaint(vg, bg);
  nvgFill(vg);

  nvgBeginPath(vg);
  nvgRoundedRect(vg, x + 0.5f, y + 0.5f, w - 1, h - 1, 4 - 0.5f);
  nvgStrokeColor(vg, nvgRGBA(0, 0, 0, 48));
  nvgStroke(vg);
}

void drawEditBox(NVGcontext* vg, const char* text, float x, float y, float w, float h)
{
  drawEditBoxBase(vg, x, y, w, h);

  nvgFontSize(vg, 20.0f);
  nvgFontFace(vg, "sans");
  nvgFillColor(vg, nvgRGBA(255, 255, 255, 64));
  nvgTextAlign(vg, NVG_ALIGN_LEFT | NVG_ALIGN_MIDDLE);
  nvgText(vg, x + h * 0.3f, y + h * 0.5f, text, nullptr);
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
