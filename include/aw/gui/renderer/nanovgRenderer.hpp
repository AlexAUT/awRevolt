#pragma once

#include <aw/gui/style/style.hpp>
#include <aw/utils/math/vector.hpp>

#include <nanovg.h>

#include <map>
#include <stack>
#include <string>
#include <vector>

namespace aw::gui
{
class GUI;
class Widget;

class NanovgRenderer
{
private:
  struct Viewport
  {
    aw::Vec2 leftTop;
    aw::Vec2 size;
  };

public:
  NanovgRenderer(GUI& gui);
  ~NanovgRenderer();

  Vec2 calculateTextSize(const std::string& text, const std::vector<std::string>& styleClasses) const;

  void beginFrame(Vec2 windowResolution);
  void endFrame();

  int setZOrder(int zOrder);

  void pushViewport(aw::Vec2 leftTop, aw::Vec2 size);
  void popViewport();

  template <typename WidgetType>
  void render(const WidgetType& widget) const;

  template <typename WidgetType>
  int calculateCursorPosition(const WidgetType& widget, Vec2 relativePoint) const;

private:
  void resetViewport();
  void activateViewport(Viewport& viewport);

  const Style& getStyle(const Widget&) const;
  const Style& getStyle(const std::vector<std::string>& styleClasses) const;

private:
  const GUI& mGUI;
  NVGcontext* mContext{nullptr};
  int mZOrder{0};
  std::stack<Viewport> mViewportStack;

  mutable std::map<std::vector<std::string>, Style> mStyleCache;
};
} // namespace aw::gui
