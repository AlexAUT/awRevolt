#include <aw/gui/gui.hpp>

#include <aw/engine/windowEvent.hpp>
#include <aw/gui/utils/eventConvert.hpp>

namespace aw::gui
{
void GUI::updateLayout()
{
  for (auto& screen : mScreens)
    screen->updateLayout(aw::Vec2{0.f});
}

void GUI::update(float delta)
{
  for (auto& screen : mScreens)
    screen->update(delta);
}

bool GUI::receive(const WindowEvent& event)
{
  // Check for resize events
  updateSize(event);

  if (mSelectedWidget)
  {
    auto localEvent = convertToLocalEventFromGlobal(event, *mSelectedWidget);
    return mSelectedWidget->processEvent(localEvent);
  }

  updateLayout();
  for (auto& screen : mScreens)
  {
    if (screen->processEvent(event))
      return true;
  }

  return false;
}

void GUI::render()
{
  mRenderer.beginFrame(mScreenSize);
  for (auto& screen : mScreens)
  {
    updateLayout();
    screen->render();
  }
  if (mSelectedWidget)
  {
    mSelectedWidget->render();
  }
  mRenderer.endFrame();
}

void GUI::setScreenSize(Vec2 size)
{
  mScreenSize = size;
  for (auto& screen : mScreens)
  {
    screen->setSize(mScreenSize);
  }

  updateLayout();
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
