#include <aw/gui/gui.hpp>

#include <aw/engine/windowEvent.hpp>

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
  // Check for resize events
  updateSize(event);

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

void GUI::setScreenSize(Vec2 size)
{
  mScreenSize = size;
  for (auto& screen : mScreens)
    screen->setSize(mScreenSize);
}

Screen::SPtr GUI::addScreen()
{
  mScreens.push_back(std::make_shared<Screen>(*this, Vec2{0.f, 0.f}, mScreenSize));
  return mScreens.back();
}

void GUI::updateSize(const WindowEvent& event)
{
  if (event.type == WindowEvent::Resized)
  {
    setScreenSize(Vec2{event.size.width, event.size.height});
  }
}

} // namespace aw::gui
