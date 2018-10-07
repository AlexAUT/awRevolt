#include <aw/gui/widgets/container.hpp>

#include <aw/gui/utils/eventConvert.hpp>

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
  for (auto& child : mChildren)
  {
    if (child->processEvent(localEvent))
      return true;
  }

  return false;
}

void Container::updateLayout()
{
  if (!isLayoutDirty())
    return;

  for (auto& child : mChildren)
    child->updateLayout();

  Widget::updateLayout();
}

void Container::invalidLayout()
{
  if (isLayoutDirty())
    return;

  Widget::invalidLayout();
  for (auto& child : mChildren)
    child->invalidLayout();
}
} // namespace aw::gui
