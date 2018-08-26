#pragma once

#include <aw/utils/bBox.hpp>
#include <aw/utils/math/vector.hpp>
#include <aw/utils/types.hpp>

#include <array>
#include <memory>
#include <vector>

namespace aw
{
template <typename ChildType>
class BoxCell
{
public:
  BoxCell(const BBox& bounds);

  void addChild(ChildType* child);
  void removeChild(ChildType* toRemove);
  size_t getChildCount() const;

  void split();

private:
private:
  BBox mBounds;

  BoxCell* parent{nullptr};
  std::array<std::unique_ptr<BoxCell*>, 8> mChildCells{nullptr};
  std::vector<ChildType*> mChildren;
};

template <typename ChildType>
BoxCell<ChildType>::BoxCell(const BBox& bounds) : mBounds(bounds)
{
}

template <typename ChildType>
void BoxCell<ChildType>::addChild(ChildType* child)
{
  mChildren.push_back(child);
}

template <typename ChildType>
void BoxCell<ChildType>::removeChild(ChildType* toRemove)
{
  for (size_t i = 0; i < mChildren.size(); i++)
  {
    if (mChildren[i] == toRemove)
    {
      mChildren.erase(i);
      return;
    }
  }
}

template <typename ChildType>
size_t BoxCell<ChildType>::getChildCount() const
{
  return mChildren.size();
}

template <typename ChildType>
void BoxCell<ChildType>::split()
{
}

} // namespace aw
