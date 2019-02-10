#include <aw/gui/widgets/bin.hpp>

#include <aw/gui/utils/eventConvert.hpp>

#include <glm/common.hpp>

namespace aw::gui
{
void Bin::update(float delta)
{
  if (mChild)
    mChild->update(delta);
}

bool Bin::processEvent(const WindowEvent& event)
{
  auto usedByChild = false;
  if (mChild)
  {
    auto localEvent = convertToLocalEvent(event, *this);
    usedByChild = mChild->processEvent(localEvent);
  }
  // Also update bin
  return Widget::processEvent(event) || usedByChild;
}

void Bin::render()
{
  Widget::render();
  if (mChild)
    mChild->render();
}

void Bin::updateLayout(aw::Vec2 parentPos)
{
  if (!isLayoutDirty())
    return;

  if (mChild)
  {
    mChild->setSize(calculateChildSize());
    mChild->setRelativePosition(calculateChildRelPosition());
    mChild->updateLayout(parentPos + getRelativePosition());
  }
  Widget::updateLayout(parentPos);
}

Vec2 Bin::getMinimalSize() const
{
  auto pad = getPadding().horizontalVertical();
  if (mChild)
    return glm::max(mChild->getMinimalSize() + pad, Widget::getMinimalSize());
  return Widget::getMinimalSize();
}

void Bin::setChild(Widget::SPtr ptr)
{
  if (mChild == ptr)
    return;

  if (mChild)
    mChild->clearParent();

  mChild = std::move(ptr);
  if (mChild)
    mChild->setParent(getSharedPtr());
}

void Bin::invalidateLayout()
{
  Widget::invalidateLayout();
  if (mChild)
    mChild->invalidateLayout();
}

Vec2 Bin::calculateChildRelPosition() const
{
  return getPadding().leftTop();
}

Vec2 Bin::calculateChildSize() const
{
  return getContentSize();
}
} // namespace aw::gui
