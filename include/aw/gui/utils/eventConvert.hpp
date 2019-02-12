#pragma once

#include <aw/engine/windowEvent.hpp>
#include <aw/gui/widgets/widget.hpp>

namespace aw::gui
{

inline WindowEvent convertToLocalEvent(const WindowEvent& event, const Widget& widget)
{
  auto localEvent = event;
  switch (event.type)
  {
  case WindowEvent::MouseMoved:
    localEvent.mouseMove.x -= static_cast<int>(widget.getRelativePosition().x);
    localEvent.mouseMove.y -= static_cast<int>(widget.getRelativePosition().y);
    break;
  case WindowEvent::MouseButtonPressed:
  case WindowEvent::MouseButtonReleased:
    localEvent.mouseButton.x -= static_cast<int>(widget.getRelativePosition().x);
    localEvent.mouseButton.y -= static_cast<int>(widget.getRelativePosition().y);
    break;
  case WindowEvent::MouseWheelScrolled:
    localEvent.mouseWheelScroll.x -= static_cast<int>(widget.getRelativePosition().x);
    localEvent.mouseWheelScroll.y -= static_cast<int>(widget.getRelativePosition().y);
    break;
  default:
    break;
  }

  return localEvent;
}

inline WindowEvent convertToLocalEventFromGlobal(const WindowEvent& event, const Widget& widget)
{
  auto localEvent = event;
  switch (event.type)
  {
  case WindowEvent::MouseMoved:
    localEvent.mouseMove.x -= static_cast<int>(widget.getGlobalPosition().x);
    localEvent.mouseMove.y -= static_cast<int>(widget.getGlobalPosition().y);
    break;
  case WindowEvent::MouseButtonPressed:
  case WindowEvent::MouseButtonReleased:
    localEvent.mouseButton.x -= static_cast<int>(widget.getGlobalPosition().x);
    localEvent.mouseButton.y -= static_cast<int>(widget.getGlobalPosition().y);
    break;
  case WindowEvent::MouseWheelScrolled:
    localEvent.mouseWheelScroll.x -= static_cast<int>(widget.getGlobalPosition().x);
    localEvent.mouseWheelScroll.y -= static_cast<int>(widget.getGlobalPosition().y);
    break;
  default:
    break;
  }

  return localEvent;
}
} // namespace aw::gui
