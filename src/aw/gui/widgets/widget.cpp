#include <aw/gui/widgets/widget.hpp>

namespace aw::gui
{
void Widget::setParent(SPtr parent)
{
  if (mParent == parent)
    return;

  mParent = std::move(parent);
  invalidateLayout();
  // Since invalid layout skips if it is already dirty, we need to apply it on the new parent manually here, not nice
  // but avoids doing it every time in invalidateLayout
  if (mParent)
    mParent->invalidateLayout();
}

void Widget::setPreferedSize(Vec2 size)
{
  if (mPreferedSize == size)
    return;
  mPreferedSize = size;
  invalidateLayout();
}

void Widget::setSize(Vec2 size)
{
  if (mSize == size)
    return;
  mSize = size;
  invalidateLayout();
}

void Widget::setRelativePosition(Vec2 pos)
{
  if (mRelativePosition == pos)
    return;
  mRelativePosition = pos;
  invalidateLayout();
}

void Widget::setGlobalPosition(Vec2 pos)
{
  mGlobalPosition = pos;
}

void Widget::invalidateLayout()
{
  if (isLayoutDirty())
    return;

  mIsLayoutDirty = true;
  if (mParent)
    mParent->invalidateLayout();
}
} // namespace aw::gui
