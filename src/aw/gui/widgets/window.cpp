#include <aw/gui/widgets/window.hpp>

#include <aw/gui/gui.hpp>
#include <aw/gui/renderer/nanovgRenderer.hpp>

#include <aw/engine/window.hpp>

namespace aw::gui
{
bool Window::processEvent(const WindowEvent& event)
{
  auto pressLeft = event.type == WindowEvent::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left;
  if (pressLeft)
  {
    auto point = Vec2(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y));
    if (hitTitleBar(point))
    {
      mDrag = true;
      mDrawOffset = getRelativePosition() - point;
      return true;
    }
  }

  auto releaseLeft = event.type == WindowEvent::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left;
  if (mDrag && releaseLeft)
  {
    auto point = Vec2(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y));
    setRelativePosition(point + mDrawOffset);
    mDrag = false;
    return true;
  }

  if (mDrag && event.type == WindowEvent::MouseMoved)
  {
    auto point = Vec2(static_cast<float>(event.mouseMove.x), static_cast<float>(event.mouseMove.y));
    setRelativePosition(point + mDrawOffset);
    return true;
  }

  return false;
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
