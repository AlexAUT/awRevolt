#include <aw/gui/widgets/tileContainer.hpp>

#include <cmath>

#include <glm/common.hpp>

namespace aw::gui
{
TileContainer::TileContainer(const GUI& gui, Vec2u tileSize) : Container(gui), mTileSize{tileSize} {}

void TileContainer::addChild(Widget::SPtr newChild)
{
  addChildAt(mChildren.size(), std::move(newChild));
}

void TileContainer::addChildAt(size_t index, Widget::SPtr newChild)
{
  assert(index <= mChildren.size());
  mChildren.insert(std::next(mChildren.begin(), index), newChild);
  mChildren[index]->setParent(getSharedPtr());
}

void TileContainer::addChildAfter(Widget* before, Widget::SPtr newChild)
{
  auto found = std::find_if(mChildren.begin(), mChildren.end(), [=](const auto& c) { return c.get() == before; });
  auto pos = std::distance(mChildren.begin(), found);
  if (found != mChildren.end())
    pos += 1;
  addChildAt(pos, newChild);
}

void TileContainer::removeAllChildren()
{
  mChildren.clear();
  invalidateLayout();
}

void TileContainer::updateLayout(Vec2 parentPos)
{
  auto width = getContentSize().x;
  int elementsPerRow = std::floor(width / mTileSize.x);
  if (elementsPerRow == 0)
    elementsPerRow = 1;

  auto freeSpace = std::fmod(width, mTileSize.x);
  auto spaceBetweenElements = mChildren.size() > 1 ? freeSpace / (mChildren.size() - 1) : freeSpace;

  auto cursor = getPadding().leftTop();
  int i = 0;
  for (auto& child : mChildren)
  {
    child->setSize(mTileSize);
    child->setRelativePosition(cursor);
    child->updateLayout(parentPos + getRelativePosition());
    cursor.x += mTileSize.x + spaceBetweenElements;
    if (++i == elementsPerRow)
    {
      cursor.x = getPadding().left;
      cursor.y += mTileSize.y;
      i = 0;
    }
  }

  float ySize = getPadding().bottom + cursor.y + mTileSize.y;
  mMinimalSizeCache = {getSize().x, ySize};

  Container::updateLayout(parentPos);
}

Vec2 TileContainer::getMinimalSize() const
{
  return glm::max(Container::getMinimalSize(), mMinimalSizeCache);
}

} // namespace aw::gui
