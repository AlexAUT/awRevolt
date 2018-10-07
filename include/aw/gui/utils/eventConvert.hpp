#pragma once

#include <aw/engine/windowEvent.hpp>
#include <aw/gui/widgets/widget.hpp>

namespace aw::gui
{

inline WindowEvent convertToLocalEvent(const WindowEvent& event, const Widget& widget)
{
  auto localEvent = event;
  if (event.type == WindowEvent::MouseMoved)
  {
    localEvent.mouseMove.x -= static_cast<int>(widget.getRelativePosition().x);
    localEvent.mouseMove.y -= static_cast<int>(widget.getRelativePosition().y);
  }
  if (event.type == WindowEvent::MouseButtonPressed || event.type == WindowEvent::MouseButtonReleased)
  {
    localEvent.mouseButton.x -= static_cast<int>(widget.getRelativePosition().x);
    localEvent.mouseButton.y -= static_cast<int>(widget.getRelativePosition().y);
  }

  return localEvent;
}
} // namespace aw::gui
