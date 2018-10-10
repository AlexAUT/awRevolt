#pragma once

#include <aw/gui/renderer/nanovgRenderer.hpp>
#include <aw/gui/style/textStyle.hpp>
#include <aw/gui/widgets/screen.hpp>
#include <aw/utils/math/vector.hpp>

#include <memory>
#include <vector>

namespace aw::gui
{
class GUI
{
public:
  using ScreenVector = std::vector<Screen::SPtr>;

  void updateLayout();

  void update(float delta);
  bool processEvent(const WindowEvent& event);
  void render();

  Screen::SPtr addScreen(Vec2 pos, Vec2 size);
  const ScreenVector getScreens() const { return mScreens; }

  const NanovgRenderer& getRenderer() const { return mRenderer; }

  TextStyleManager& getTextStyles() { return mTextStyles; }
  const TextStyleManager& getTextStyles() const { return mTextStyles; }

  void setSelectedWidget(Widget::SPtr widget) const { mSelectedWidget = std::move(widget); }
  Widget* getSelectedWidget() const { return mSelectedWidget.get(); }

public:
private:
private:
  NanovgRenderer mRenderer;
  ScreenVector mScreens;

  TextStyleManager mTextStyles;

  mutable Widget::SPtr mSelectedWidget{nullptr};
};
} // namespace aw::gui
