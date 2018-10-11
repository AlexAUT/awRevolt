#include <aw/gui/widgets/window.hpp>

#include <aw/gui/gui.hpp>
#include <aw/gui/renderer/nanovgRenderer.hpp>

#include <aw/engine/window.hpp>

namespace aw::gui
{
Window::Window(const GUI& gui, std::string title, Style style)
    : Bin(gui), mTitle(std::move(title)), mStyle(style), mTextStyle(getGUI().getTextStyles().getStyle("headline"))
{
}

bool Window::processEvent(const WindowEvent& event)
{
  bool usedEvent = false;

  if (static_cast<bool>(mStyle & Style::Moveable))
    usedEvent = handleMovement(event);

  if (!usedEvent)
    usedEvent = Bin::processEvent(event);

  return usedEvent;
}

void Window::render(Vec2 pos)
{
  Widget::render(pos);
  getGUI().getRenderer().render(*this);
  Bin::render(pos);
}
void Window::setTitle(std::string title)
{
  mTitle = std::move(title);
  invalidateLayout();
}

void Window::setStyle(Style style)
{
  mStyle = style;
  invalidateLayout();
}

void Window::setTitleTextStyle(const TextStyle* textStyle)
{
  assert(textStyle);
  mTextStyle = textStyle;
  invalidateLayout();
}

void Window::updateLayout()
{
  mTitleBarHeight = getGUI().getRenderer().calculateTextSize(mTitle, *mTextStyle).y;
  setPadding({mTitleBarHeight, 0.f, 0.f, 0.f});
  Bin::updateLayout();
}

bool Window::hitTitleBar(Vec2 point)
{
  auto pos = getRelativePosition();
  auto size = getSize();

  return (point.x >= pos.x && point.x < pos.x + size.x) && (point.y >= pos.y && point.y < pos.y + 30);
}

bool Window::handleMovement(const WindowEvent& event)
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
  return usedEvent;
}
} // namespace aw::gui
