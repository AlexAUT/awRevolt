#include <aw/gui/widgets/linearContainer.hpp>

#include <aw/utils/types.hpp>

#include <glm/common.hpp>

#include <numeric>

namespace aw::gui
{
void LinearContainer::addChild(Widget::SPtr widget, float weight)
{
  mWeights.push_back(weight);
  mChildren.push_back(std::move(widget));
  mChildren.back()->setParent(getSharedPtr());
}

void LinearContainer::setSpaceBetweenElements(float space)
{
  mSpaceBetweenElements = space;
  invalidateLayout();
}

void LinearContainer::setOuterPadding(Padding padding)
{
  mOuterPadding = padding;
  invalidateLayout();
}

void LinearContainer::updateLayout()
{
  if (!isLayoutDirty())
    return;

  Container::updateLayout();

  auto dynamicAxis = static_cast<int>(mOrientation);
  auto staticAxis = dynamicAxis ^ 1;

  auto freeSpace = getSize()[dynamicAxis];
  auto staticAxisValue = getSize()[staticAxis];

  // In the first pass try to give everyone their minimal size + spaceBetween
  for (auto& child : mChildren)
    freeSpace -= (child->getMinimalSize()[dynamicAxis] + mSpaceBetweenElements);
  // Since there are only n-1 edges between elements we need to add spacing again
  freeSpace += mSpaceBetweenElements;

  // Subtract the outer padding from the freespace and from the static axis size
  auto outerDynamicPadding = getOuterDynamicAxisPadding();
  auto outerStaticPadding = getOuterStaticAxisPadding();

  freeSpace -= (outerDynamicPadding[0] + outerDynamicPadding[1]);
  staticAxisValue -= (outerStaticPadding[0] + outerStaticPadding[1]);

  freeSpace = std::max(0.f, freeSpace);

  // Used to calculate the share of each element of the remaining free space
  auto weightSum = std::accumulate(mWeights.begin(), mWeights.end(), 0.f);

  // Now share the space which is still free
  auto cursor = outerDynamicPadding[0];
  for (size_t i = 0; i < mChildren.size(); i++)
  {
    auto& child = mChildren[i];
    auto share = weightSum > 0.f ? freeSpace * (mWeights[i] / weightSum) : 0.f;
    assert(share >= 0.f);
    // Calculate new size
    auto childSize = child->getMinimalSize();
    childSize[dynamicAxis] += share;
    childSize[staticAxis] = staticAxisValue;
    child->setSize(childSize);
    // Calculate new relative position
    Vec2 pos;
    pos[dynamicAxis] = cursor;
    pos[staticAxis] = outerStaticPadding[0];
    child->setRelativePosition(pos);
    // Tell the child to update his own layout
    child->updateLayout();

    cursor += childSize[dynamicAxis] + mSpaceBetweenElements;
  }
  Container::updateLayout();

  // Update minimal size cache
  mMinimalSizeCache = Vec2{0.f};
  for (auto& child : mChildren)
  {
    auto size = child->getMinimalSize();
    mMinimalSizeCache[dynamicAxis] += size[dynamicAxis] + mSpaceBetweenElements;
    mMinimalSizeCache[staticAxis] = std::max(mMinimalSizeCache[staticAxis], size[staticAxis]);
  }
  mMinimalSizeCache[dynamicAxis] -= mSpaceBetweenElements; // same as above
  mMinimalSizeCache[dynamicAxis] += (outerDynamicPadding[0] + outerDynamicPadding[1]);
  mMinimalSizeCache[staticAxis] += (outerStaticPadding[0] + outerStaticPadding[1]);
  mMinimalSizeCache = glm::max(mMinimalSizeCache, getPreferedSize());
}

Vec2 LinearContainer::getMinimalSize() const
{
  return mMinimalSizeCache;
}

Vec2 LinearContainer::getOuterDynamicAxisPadding() const
{
  if (mOrientation == Orientation::Horizontal)
    return {mOuterPadding.left, mOuterPadding.right};
  else
    return {mOuterPadding.top, mOuterPadding.bottom};
}

Vec2 LinearContainer::getOuterStaticAxisPadding() const
{
  if (mOrientation == Orientation::Vertical)
    return {mOuterPadding.left, mOuterPadding.right};
  else
    return {mOuterPadding.top, mOuterPadding.bottom};
}
} // namespace aw::gui
