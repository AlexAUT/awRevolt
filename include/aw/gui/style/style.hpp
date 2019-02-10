#pragma once

#include <aw/utils/color.hpp>

#include <optional>
#include <string>

namespace aw::gui
{
struct StyleTemplate
{
  // Body
  std::optional<Color> backgroundColor{};
  // Text
  std::optional<std::string> fontName{};
  std::optional<float> fontSize{};
  std::optional<Color> fontColor{};
};

struct Style
{
  // Body
  Color backgroundColor;
  // Text
  std::string fontName;
  float fontSize;
  Color fontColor;

  Style& operator+=(const StyleTemplate& styleTemplate);
};

} // namespace aw::gui
