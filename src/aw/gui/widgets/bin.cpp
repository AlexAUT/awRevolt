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
  if (mChild)
  {
    auto localEvent = convertToLocalEvent(event, *this);
    if (mChild->processEvent(localEvent))
      return true;
  }
  return Widget::processEvent(event);
}

void Bin::render(Vec2 parentPos)
{
  Widget::render(parentPos);
  if (mChild)
    mChild->render(getGlobalPosition());
}

void Bin::updateLayout()
{
  if (!isLayoutDirty())
    return;

  if (mChild)
  {
    mChild->setSize(calculateChildSize());
    mChild->setRelativePosition(calculateChildRelPosition());
    mChild->updateLayout();
  }
  Widget::updateLayout();
}

Vec2 Bin::getMinimalSize() const
{
  if (mChild)
    return glm::max(mChild->getMinimalSize(), Widget::getMinimalSize());
  return Widget::getMinimalSize();
}

void Bin::setChild(Widget::SPtr ptr)
{
  if (mChild == ptr)
    return;

  if (mChild)
    mChild->setParent(nullptr);

  mChild = std::move(ptr);
  if (mChild)
    mChild->setParent(getSharedPtr());
}

void Bin::setPadding(Padding padding)
{
  mPadding = padding;
  invalidateLayout();
}

Vec2 Bin::calculateChildRelPosition() const
{
  return {mPadding.left, mPadding.top};
}

Vec2 Bin::calculateChildSize() const
{
  auto size = getSize();
  return {size.x - mPadding.left - mPadding.right, size.y - mPadding.top - mPadding.bottom};
}
} // namespace aw::gui
