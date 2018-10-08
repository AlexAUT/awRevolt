#include <aw/gui/widgets/linearContainer.hpp>

#include <aw/utils/types.hpp>

#include <numeric>

namespace aw::gui
{
void LinearContainer::addChild(Widget::SPtr widget, float weight)
{
  mWeights.push_back(weight);
  mChildren.push_back(std::move(widget));
  mChildren.back()->setParent(getSharedPtr());
}

void LinearContainer::updateLayout()
{
  if (!isLayoutDirty())
    return;

  Container::updateLayout();

  auto weightSum = std::accumulate(mWeights.begin(), mWeights.end(), 0.f);

  auto dynamicAxis = static_cast<int>(mOrientation);
  auto staticAxis = dynamicAxis ^ 1;

  auto freeSpace = getSize()[dynamicAxis];
  auto staticAxisValue = getSize()[staticAxis];

  // In the first pass try to give everyone their minimal size
  for (auto& child : mChildren)
    freeSpace -= child->getMinimalSize()[dynamicAxis];

  // Now share the space which is still free
  auto cursor = 0.f;
  for (size_t i = 0; i < mChildren.size(); i++)
  {
    auto& child = mChildren[i];
    auto share = weightSum > 0.f ? freeSpace * (mWeights[i] / weightSum) : 0.f;
    // Calculate new size
    auto childSize = child->getMinimalSize();
    childSize[dynamicAxis] += freeSpace * share;
    childSize[staticAxis] = staticAxisValue;
    child->setSize(childSize);
    // Calculate new relative position
    Vec2 pos;
    pos[dynamicAxis] = cursor;
    pos[staticAxis] = 0.f;
    child->setRelativePosition(pos);

    cursor += childSize[dynamicAxis];
  }
}
}
