#include <aw/gui/widgets/container.hpp>

#include <aw/gui/utils/eventConvert.hpp>

#include <glm/common.hpp>

namespace aw::gui
{
void Container::update(float delta)
{
  for (auto& child : mChildren)
    child->update(delta);
}

void Container::render(Vec2 pos)
{
  Widget::render(pos);

  for (auto& child : mChildren)
    child->render(getGlobalPosition());
}

bool Container::processEvent(const WindowEvent& event)
{
  auto localEvent = convertToLocalEvent(event, *this);
  auto usedEvent = false;
  for (auto& child : mChildren)
  {
    usedEvent = child->processEvent(localEvent) || usedEvent;
  }

  return usedEvent || Widget::processEvent(event);
}

void Container::updateLayout()
{
  if (!isLayoutDirty())
    return;

  for (auto& child : mChildren)
    child->updateLayout();

  Widget::updateLayout();
}

void Container::invalidateLayout()
{
  if (isLayoutDirty())
    return;

  Widget::invalidateLayout();
  for (auto& child : mChildren)
    child->invalidateLayout();
}
} // namespace aw::gui
