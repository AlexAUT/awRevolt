#include <aw/gui/widgets/widget.hpp>

namespace aw::gui
{
void Widget::setParent(SPtr parent)
{
  if (mParent == parent)
    return;

  mParent = std::move(parent);
  invalidLayout();
}

void Widget::setPreferedSize(Vec2 size)
{
  if (mPreferedSize == size)
    return;
  mPreferedSize = size;
  invalidLayout();
}

void Widget::setSize(Vec2 size)
{
  if (mSize == size)
    return;
  mSize = size;
  invalidLayout();
}

void Widget::setRelativePosition(Vec2 pos)
{
  if (mRelativePosition == pos)
    return;
  mRelativePosition = pos;
  invalidLayout();
}

void Widget::setGlobalPosition(Vec2 pos)
{
  mGlobalPosition = pos;
}

void Widget::invalidLayout()
{
  if (isLayoutDirty())
    return;

  mIsLayoutDirty = true;
  if (mParent)
    mParent->invalidLayout();
}
} // namespace aw::gui
