#include <aw/gui/gui.hpp>

namespace aw::gui
{
void GUI::update(float delta)
{
  for (auto& screen : mScreens)
    screen->update(delta);
}

bool GUI::processEvent(const WindowEvent& event)
{
  auto consumed = false;
  for (auto& screen : mScreens)
  {
    if (screen->processEvent(event))
      return true;
  }

  return false;
}

void GUI::render()
{
  mRenderer.beginFrame();
  for (auto& screen : mScreens)
    screen->render(mRenderer, {0.f, 0.f});
  mRenderer.endFrame();
}

Screen::SPtr GUI::addScreen(Vec2 pos, Vec2 size)
{
  mScreens.push_back(std::make_shared<Screen>(pos, size));
  return mScreens.back();
}
} // namespace aw::gui
