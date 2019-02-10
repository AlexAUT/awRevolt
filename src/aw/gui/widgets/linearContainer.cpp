#include <aw/gui/widgets/linearContainer.hpp>

#include <aw/utils/types.hpp>

#include <glm/common.hpp>

#include <numeric>

namespace aw::gui
{
void LinearContainer::addChild(Widget::SPtr widget, float weight)
{
  addChildAt(mChildren.size(), widget, weight);
}

void LinearContainer::addChildAt(size_t index, Widget::SPtr newChild, float weight)
{
  assert(index <= mChildren.size());
  mWeights.insert(std::next(mWeights.begin(), index), weight);
  mChildren.insert(std::next(mChildren.begin(), index), newChild);
  mChildren[index]->setParent(getSharedPtr());

  updateMinimalSize();
}

void LinearContainer::addChildAfter(Widget* before, Widget::SPtr newChild, float weight)
{
  auto found = std::find_if(mChildren.begin(), mChildren.end(), [=](const auto& c) { return c.get() == before; });
  auto pos = std::distance(mChildren.begin(), found);
  if (found != mChildren.end())
    pos += 1;
  addChildAt(pos, newChild, weight);
}

bool LinearContainer::removeChild(Widget* toRemove)
{
  for (auto i = 0lu; i < mChildren.size(); i++)
  {
    auto* child = mChildren[i].get();
    if (child == toRemove)
    {
      child->clearParent();
      invalidateLayout();
      mChildren.erase(std::next(mChildren.begin(), i));
      mWeights.erase(std::next(mWeights.begin(), i));
      return true;
    }
  }
  return false;
}

void LinearContainer::setSpaceBetweenElements(float space)
{
  mSpaceBetweenElements = space;
  invalidateLayout();
}

void LinearContainer::updateLayout(aw::Vec2 parentPos)
{
  if (!isLayoutDirty())
    return;

  Container::updateLayout(parentPos);

  auto dynamicAxis = static_cast<int>(mOrientation);
  auto staticAxis = dynamicAxis ^ 1;

  auto freeSpace = getContentSize()[dynamicAxis];
  auto staticAxisValue = getContentSize()[staticAxis];

  // In the first pass try to give everyone their minimal size + spaceBetween
  for (auto& child : mChildren)
    freeSpace -= (child->getMinimalSize()[dynamicAxis] + mSpaceBetweenElements);
  // Since there are only n-1 edges between elements we need to add spacing again
  freeSpace += mSpaceBetweenElements;

  // Subtract the outer padding from the freespace and from the static axis size
  auto outerDynamicPadding = getDynamicAxisPadding();
  auto outerStaticPadding = getStaticAxisPadding();

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
    child->updateLayout(parentPos + getRelativePosition());

    cursor += childSize[dynamicAxis] + mSpaceBetweenElements;
  }
  Container::updateLayout(parentPos);

  updateMinimalSize();
}

Vec2 LinearContainer::getMinimalSize() const
{
  return mMinimalSizeCache;
}

Vec2 LinearContainer::getDynamicAxisPadding() const
{
  if (mOrientation == Orientation::Horizontal)
    return {getPadding().left, getPadding().right};
  else
    return {getPadding().top, getPadding().bottom};
}

Vec2 LinearContainer::getStaticAxisPadding() const
{
  if (mOrientation == Orientation::Vertical)
    return {getPadding().left, getPadding().right};
  else
    return {getPadding().top, getPadding().bottom};
}

void LinearContainer::updateMinimalSize()
{
  auto dynamicAxis = static_cast<int>(mOrientation);
  auto staticAxis = dynamicAxis ^ 1;

  // Subtract the outer padding from the freespace and from the static axis size
  auto outerDynamicPadding = getDynamicAxisPadding();
  auto outerStaticPadding = getStaticAxisPadding();
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
} // namespace aw::gui
