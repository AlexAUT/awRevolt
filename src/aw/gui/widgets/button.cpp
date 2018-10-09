#include <aw/gui/widgets/button.hpp>

#include <aw/engine/windowEvent.hpp>
#include <aw/gui/gui.hpp>
#include <aw/gui/renderer/nanovgRenderer.hpp>

namespace aw::gui
{
bool Button::processEvent(const WindowEvent& event)
{
  bool usedEvent = false;
  if (event.type == WindowEvent::MouseMoved)
  {
    bool hit = isLocalPointOnWidget({event.mouseMove.x, event.mouseMove.y});
    changeState(State::Hovered, hit);
    usedEvent = usedEvent || hit;
  }
  if (event.type == WindowEvent::MouseButtonPressed)
  {
    if (event.mouseButton.button == sf::Mouse::Left)
    {
      if (isLocalPointOnWidget({event.mouseButton.x, event.mouseButton.y}))
      {
        changeState(State::Pressed, true);
        usedEvent = true;
      }
    }
  }
  if (event.type == WindowEvent::MouseButtonReleased)
  {
    if (event.mouseButton.button == sf::Mouse::Left)
    {
      if (mOnClick && isLocalPointOnWidget({event.mouseButton.x, event.mouseButton.y}))
        mOnClick(*this);

      usedEvent = isInState(State::Pressed);
      changeState(State::Pressed, false);
    }
  }
  return usedEvent;
}

void Button::render(Vec2 parentPos)
{
  Widget::render(parentPos);
  getGUI().getRenderer().render(*this);
}
} // namespace aw::gui
