#include <aw/gui/widgets/bin.hpp>

#include <aw/gui/utils/eventConvert.hpp>

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
    return mChild->processEvent(localEvent);
  }
  return false;
}

void Bin::render(Vec2 parentPos)
{
  Widget::render(parentPos);
  if (mChild)
    mChild->render(getGlobalPosition());
}

void Bin::setChild(Widget::SPtr ptr)
{
  if (mChild)
    mChild->setParent(nullptr);

  mChild = std::move(ptr);
  if (mChild)
  {
    mChild->setParent(getSharedPtr());
    mChild->setSize(calculateChildSize());
    mChild->setRelativePosition(calculateChildRelPosition());
  }
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
