#include <aw/gui/widgets/window.hpp>

#include <aw/gui/gui.hpp>
#include <aw/gui/renderer/nanovgRenderer.hpp>

#include <aw/engine/window.hpp>

namespace aw::gui
{
bool Window::processEvent(const WindowEvent& event)
{
  bool usedEvent = false;
  if (mDrag)
  {
    if (event.type == WindowEvent::MouseButtonReleased)
    {
      if (event.mouseButton.button == sf::Mouse::Left)
      {
        if (mDrag)
        {
          auto point = Vec2(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y));
          setRelativePosition(point + mDrawOffset);
          mDrag = false;
          usedEvent = true;
        }
      }
    }

    if (event.type == WindowEvent::MouseMoved)
    {
      auto point = Vec2(static_cast<float>(event.mouseMove.x), static_cast<float>(event.mouseMove.y));
      setRelativePosition(point + mDrawOffset);
      usedEvent = true;
    }
  }
  else if (event.type == WindowEvent::MouseButtonPressed)
  {
    if (event.mouseButton.button == sf::Mouse::Left)
    {
      auto point = Vec2(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y));
      if (hitTitleBar(point))
      {
        mDrag = true;
        mDrawOffset = getRelativePosition() - point;
        usedEvent = true;
      }
    }
  }

  if (!usedEvent)
    usedEvent = Bin::processEvent(event);

  if (!usedEvent)
    (void)event; // TODO: check if the click was on the window body, because we should still eat that event, or
                 // implement it inside Bin

  return usedEvent;
}

void Window::render(Vec2 pos)
{
  Widget::render(pos);
  getGUI().getRenderer().render(*this);
  Bin::render(pos);
}

bool Window::hitTitleBar(Vec2 point)
{
  auto pos = getRelativePosition();
  auto size = getSize();

  return (point.x >= pos.x && point.x < pos.x + size.x) && (point.y >= pos.y && point.y < pos.y + 30);
}

} // namespace aw::gui
