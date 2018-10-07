#pragma once

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

private:
private:
  NVGcontext* mContext{nullptr};
};
} // namespace aw::gui
