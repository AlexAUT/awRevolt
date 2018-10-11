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

  GUI(Vec2 screenSize) : mScreenSize{screenSize} {}

  void updateLayout();

  void update(float delta);
  bool processEvent(const WindowEvent& event);
  void render();

  void setScreenSize(Vec2 size);

  Screen::SPtr addScreen();
  const ScreenVector getScreens() const { return mScreens; }

  const NanovgRenderer& getRenderer() const { return mRenderer; }

  TextStyleManager& getTextStyles() { return mTextStyles; }
  const TextStyleManager& getTextStyles() const { return mTextStyles; }

  void setSelectedWidget(Widget::SPtr widget) const { mSelectedWidget = std::move(widget); }
  Widget* getSelectedWidget() const { return mSelectedWidget.get(); }

public:
private:
  void updateSize(const WindowEvent& event);

private:
  Vec2 mScreenSize{0.f};

  NanovgRenderer mRenderer;
  ScreenVector mScreens;

  TextStyleManager mTextStyles;

  mutable Widget::SPtr mSelectedWidget{nullptr};
};
} // namespace aw::gui
