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
}; // namespace aw::gui

using TextStyleManager = StyleManager<TextStyle>;
} // namespace aw::gui
