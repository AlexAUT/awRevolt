#include <aw/gui/widgets/container.hpp>

#include <aw/engine/window.hpp>

namespace aw::gui
{
void Container::update(float delta)
{
  for (auto& child : mChildren)
    child->update(delta);
}

void Container::render(NanovgRenderer& renderer, Vec2 pos)
{
  Widget::render(renderer, pos);

  auto localPos = pos - getRelativePosition();
  for (auto& child : mChildren)
    child->render(renderer, localPos);
}

bool Container::processEvent(const WindowEvent& event)
{
  auto localEvent = event;
  if (event.type == WindowEvent::MouseMoved)
  {
    localEvent.mouseMove.x -= static_cast<int>(getRelativePosition().x);
    localEvent.mouseMove.y -= static_cast<int>(getRelativePosition().y);
  }
  if (event.type == WindowEvent::MouseButtonPressed || event.type == WindowEvent::MouseButtonReleased)
  {
    localEvent.mouseButton.x -= static_cast<int>(getRelativePosition().x);
    localEvent.mouseButton.y -= static_cast<int>(getRelativePosition().y);
  }

  for (auto& child : mChildren)
  {
    if (child->processEvent(localEvent))
      return true;
  }

  return false;
}
} // namespace aw::gui
