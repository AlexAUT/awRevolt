#include <aw/gui/gui.hpp>

namespace aw::gui
{
void GUI::updateLayout()
{
  for (auto& screen : mScreens)
    screen->updateLayout();
}

void GUI::update(float delta)
{
  for (auto& screen : mScreens)
    screen->update(delta);
}

bool GUI::processEvent(const WindowEvent& event)
{
  if (mSelectedWidget)
  {
    return mSelectedWidget->processEvent(event);
  }

  for (auto& screen : mScreens)
  {
    screen->updateLayout();
    if (screen->processEvent(event))
      return true;
  }

  return false;
}

void GUI::render()
{
  mRenderer.beginFrame();
  for (auto& screen : mScreens)
  {
    updateLayout();
    screen->render({0.f, 0.f});
  }
  if (mSelectedWidget)
  {
    Vec2 parentPos{0.f, 0.f};
    if (mSelectedWidget->getParent())
      parentPos = mSelectedWidget->getParent()->getGlobalPosition();
    mSelectedWidget->render(parentPos);
  }
  mRenderer.endFrame();
}

Screen::SPtr GUI::addScreen(Vec2 pos, Vec2 size)
{
  mScreens.push_back(std::make_shared<Screen>(*this, pos, size));
  return mScreens.back();
}
} // namespace aw::gui
