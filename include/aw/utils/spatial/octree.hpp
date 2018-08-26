#pragma once

#include <aw/utils/bBox.hpp>
#include <aw/utils/types.hpp>

#include <aw/utils/log.hpp>
#include <aw/utils/spatial/boxCell.hpp>

#include <array>
#include <cassert>
#include <vector>

namespace aw
{
template <typename ChildType, typename Intersector>
class Octree
{
public:
  Octree(BBox bBox, size_t maxElementsPerCell = 10, size_t maxDepth = 5);

  void addElement(ChildType* element, Intersector intersector);

private:
private:
  BBox mBounds;
  size_t mMaxElements;
  size_t mMaxDepth;

  std::vector<ChildType*> mElements;

  std::array<Octree*, 8> mChildNodes{nullptr};
};

template <typename ChildType, typename Intersector>
Octree<ChildType, Intersector>::Octree(BBox bBox, size_t maxElementsPerCell, size_t maxDepth)
    : mBounds(bBox), mMaxElements(maxElementsPerCell), mMaxDepth(maxDepth)
{
}

template <typename ChildType, typename Intersector>
void Octree<ChildType, Intersector>::addElement(ChildType* element, Intersector intersector)
{
  assert(element);
  assert(intersector(mBounds, *element));

  // Insert directly into childs if maxDepth = 0 or smaller than max elements
  if (mMaxDepth <= 0 || mElements.size() < (mMaxElements - 1))
  {
    mElements.push_back(element);
  }

  for (int x = 0; x < 2; x++)
  {
    for (int y = 0; y < 2; y++)
    {
      for (int z = 0; z < 2; z++)
      {
        int index = 0;
        index |= x;
        index |= y << 1;
        index |= z << 2;
        LogTemp() << "Index: " << index;
      }
    }
  }
}

} // namespace aw
