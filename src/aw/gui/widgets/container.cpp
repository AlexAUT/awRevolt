#include <aw/gui/gui.hpp>
#include <aw/gui/utils/eventConvert.hpp>
#include <aw/gui/widgets/container.hpp>

#include <glm/common.hpp>

namespace aw::gui
{
void Container::update(float delta)
{
  for (auto& child : mChildren)
    child->update(delta);
}

void Container::render()
{
  Widget::render();

  getGUI().getRenderer().render(*this);

  for (auto& child : mChildren)
    child->render();
}

bool Container::processEvent(const WindowEvent& event)
{
  auto localEvent = convertToLocalEvent(event, *this);
  auto usedEvent = false;
  // No range based loop, because events may change the children
  for (size_t i = 0; i < mChildren.size(); i++)
  {
    usedEvent = mChildren[i]->processEvent(localEvent) || usedEvent;
  }

  return Widget::processEvent(event) || usedEvent;
}

void Container::updateLayout(aw::Vec2 parentPos)
{
  if (!isLayoutDirty())
    return;

  for (auto& child : mChildren)
    child->updateLayout(parentPos + getRelativePosition());

  // We need to clear invalid state...
  Widget::updateLayout(parentPos);
}

void Container::invalidateLayout()
{
  Widget::invalidateLayout();
  for (auto& child : mChildren)
    child->invalidateLayout();
}
} // namespace aw::gui
