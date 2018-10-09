#pragma once

#include <aw/gui/style/styleManager.hpp>
#include <aw/utils/color.hpp>

#include <string>

namespace aw::gui
{
struct TextStyle
{
  std::string fontName;
  float fontSize;
  Color fontColor;

  static TextStyle defaultInstance() { return {"sans", 20.f, Color(0.8f, 0.8f, 0.8f, 1.0f)}; }
}; // namespace aw::gui

using TextStyleManager = StyleManager<TextStyle>;
} // namespace aw::gui
