#pragma once

#include <aw/gui/style/style.hpp>
#include <aw/gui/widgets/widget.hpp>
#include <aw/utils/math/vector.hpp>

#include <nanovg/nanovg.h>

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
public:
  using StateMap = std::map<int, Style>;
  using StyleMap = std::map<std::vector<std::string>, StateMap>;

private:
  struct Viewport
  {
    aw::Vec2 leftTop;
    aw::Vec2 size;
  };

public:
  NanovgRenderer(GUI& gui);
  ~NanovgRenderer();

  Vec2 calculateTextSize(const std::string& text, const Widget& widget);
  Vec2 calculateTextSize(const std::string& text, const std::string& elementId,
                         const std::vector<std::string>& styleClasses) const;

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

private:
  const GUI& mGUI;
  NVGcontext* mContext{nullptr};
  int mZOrder{0};
  std::stack<Viewport> mViewportStack;

  // Cache for each #element styles
  mutable std::map<std::string, StyleMap> mElementStyleCache;
};
} // namespace aw::gui
