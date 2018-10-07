#pragma once

#include <aw/gui/renderer/nanovgRenderer.hpp>
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

  void update(float delta);
  bool processEvent(const WindowEvent& event);
  void render();

  Screen::SPtr addScreen(Vec2 pos, Vec2 size);
  const ScreenVector getScreens() const { return mScreens; }

public:
private:
private:
  NanovgRenderer mRenderer;
  ScreenVector mScreens;
};
} // namespace aw::gui
