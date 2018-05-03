#pragma once

#include <aw/utils/math/vector.hpp>

#include <string>

namespace aw
{

struct Settings
{
  std::string applicationName{"Aw Engine"};
  Vec2u resolution{800, 600};
  unsigned bitsPerPixel{32};
  unsigned depthBits{16};
  unsigned stencilBits{8};
  unsigned antialiasing{0};
  unsigned openglMajor{4};
  unsigned openglMinor{3};
  bool coreContext{true};
  bool debugContext{false};
  bool vsync{true};
  unsigned frameLimit{0};
  bool grabCursor{false};
  bool cursorVisible{true};
};

void logSettings(const Settings& settings);

namespace priv
{
Settings loadSettings();
bool saveSettings(const Settings& settings);
} // namespace priv
} // namespace aw
