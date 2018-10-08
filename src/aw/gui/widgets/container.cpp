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

  Widget::updateLayout();

  for (auto& child : mChildren)
    child->updateLayout();
}

Vec2 Container::getMinimalSize() const
{
  if (isLayoutDirty())
  {
    Vec2 childSizes{0.f};
    for (auto& child : mChildren)
      childSizes += child->getMinimalSize();
    mMinimalSizeCache = glm::max(childSizes, Widget::getMinimalSize());
  }
  return mMinimalSizeCache;
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
