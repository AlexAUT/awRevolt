#pragma once

#include <aw/gui/renderer/nanovgRenderer.hpp>
#include <aw/gui/style/defaultStyles.hpp>
#include <aw/gui/style/styleManager.hpp>
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

  GUI(Vec2 screenSize, StyleManager styles = getDefaultTextStyles()) :
      mScreenSize{screenSize},
      mRenderer{*this},
      mStyles(std::move(styles))
  {
  }

  void updateLayout();

  void update(float delta);
  bool receive(const WindowEvent& event);
  void render();

  void setScreenSize(Vec2 size);
  Vec2 getScreenSize() const { return mScreenSize; }

  Screen::SPtr addScreen();
  const ScreenVector getScreens() const { return mScreens; }

  NanovgRenderer& getRenderer() const { return const_cast<NanovgRenderer&>(mRenderer); }

  StyleManager& getStyles() { return mStyles; }
  const StyleManager& getStyles() const { return mStyles; }

  void setSelectedWidget(Widget::SPtr widget) const { mSelectedWidget = std::move(widget); }
  Widget* getSelectedWidget() const { return mSelectedWidget.get(); }

public:
private:
  void updateSize(const WindowEvent& event);

private:
  Vec2 mScreenSize{0.f};

  NanovgRenderer mRenderer;
  ScreenVector mScreens;

  StyleManager mStyles;

  mutable Widget::SPtr mSelectedWidget{nullptr};
};
} // namespace aw::gui
