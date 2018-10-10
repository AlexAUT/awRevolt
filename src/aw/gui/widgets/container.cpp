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
  return mMinimalSizeCache;
}

void Container::invalidateLayout()
{
  if (isLayoutDirty())
    return;

  Widget::invalidateLayout();
  for (auto& child : mChildren)
    child->invalidateLayout();

  // Update the minimal size cache
  mMinimalSizeCache = Vec2{0.f};
  for (auto& child : mChildren)
    mMinimalSizeCache += child->getMinimalSize();
  mMinimalSizeCache = glm::max(mMinimalSizeCache, Widget::getMinimalSize());
}
} // namespace aw::gui
