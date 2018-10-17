#pragma once

#include <aw/utils/math/vector.hpp>

#include <nanovg.h>

#include <string>

namespace aw::gui
{
class TextStyle;

class NanovgRenderer
{
public:
  NanovgRenderer();
  ~NanovgRenderer();

  Vec2 calculateTextSize(const std::string& text, const TextStyle& style) const;

  void beginFrame(Vec2 windowResolution);
  void endFrame();

  template <typename WidgetType>
  void render(const WidgetType& widget) const;

  template <typename WidgetType>
  int calculateCursorPosition(const WidgetType& widget, Vec2 relativePoint) const;

private:
private:
  NVGcontext* mContext{nullptr};
};
} // namespace aw::gui
