#pragma once

#include <aw/utils/math/vector.hpp>

#include <nanovg.h>

namespace aw::gui
{
class NanovgRenderer
{
public:
  NanovgRenderer();
  ~NanovgRenderer();

  void beginFrame();
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
