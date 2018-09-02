#pragma once

#include <aw/utils/types.hpp>

#include <aw/utils/log.hpp>
#include <aw/utils/spatial/AABB.hpp>
#include <aw/utils/spatial/AABBIntersectors.hpp>

#include <array>
#include <cassert>
#include <functional>
#include <memory>
#include <vector>

namespace aw
{
template <typename ChildType, typename Intersector>
class Octree
{
public:
  typedef std::unique_ptr<Octree> UPtr;

public:
  Octree(AABB bBox, size_t maxElementsPerCell = 10, size_t maxDepth = 5);

  void addElement(ChildType element, Intersector intersector);

  void traverse(const std::function<void(ChildType)>& callback, AABB boundsToCheck,
                Intersector intersector = Intersector());

private:
  void split();

private:
  AABB mBounds;
  size_t mMaxElements;
  size_t mMaxDepth;

  std::vector<ChildType> mElements;

  bool mSplit{false};
  std::array<Octree::UPtr, 8> mChildNodes{nullptr};
};

template <typename ChildType, typename Intersector>
Octree<ChildType, Intersector>::Octree(AABB bBox, size_t maxElementsPerCell, size_t maxDepth)
    : mBounds(bBox), mMaxElements(maxElementsPerCell), mMaxDepth(maxDepth)
{
}

template <typename ChildType, typename Intersector>
void Octree<ChildType, Intersector>::addElement(ChildType element, Intersector intersector)
{
  assert(intersector(mBounds, element));

  // Insert directly
  if (!mSplit && (mMaxDepth == 0 || mElements.size() < mMaxElements))
  {
    mElements.push_back(element);
    return;
  }

  // We need to split or just test against already present childs
  if (!mSplit)
    split();

  // Check for every child
  for (int x = 0; x < 2; x++)
  {
    for (int y = 0; y < 2; y++)
    {
      for (int z = 0; z < 2; z++)
      {
        int index = (x << 2) | (y << 1) | z;
        if (intersector(mChildNodes[index]->mBounds, element))
          mChildNodes[index]->addElement(element, intersector);
      }
    }
  }
}

template <typename ChildType, typename Intersector>
void Octree<ChildType, Intersector>::split()
{
  auto center = mBounds.getCenter();
  auto extend = mBounds.getExtend();
  // Create the 8 childs
  for (int x = 0; x < 2; x++)
  {
    for (int y = 0; y < 2; y++)
    {
      for (int z = 0; z < 2; z++)
      {
        int index = (x << 2) | (y << 1) | z;
        Vec3 offset{x - 0.5f, y - 0.5f, z - 0.5f};
        Vec3 childCenter = center + extend * offset;
        Vec3 childExtend = extend * 0.5f;
        AABB childBounds{childCenter, childExtend};

        mChildNodes[index] = std::make_unique<Octree<ChildType, Intersector>>(childBounds, mMaxElements, mMaxDepth - 1);
      }
    }
  }
  mSplit = true;
  // Add existing elements again (this will insert them into the new childs)
  for (auto& it : mElements)
    addElement(it, Intersector());
  // The nodes are not stored in the childs
  std::vector<ChildType>().swap(mElements);
}

template <typename ChildType, typename Intersector>
void Octree<ChildType, Intersector>::traverse(const std::function<void(ChildType)>& callback, AABB boundsToCheck,
                                              Intersector intersector)
{
  if (!AABBAABBIntersector()(mBounds, boundsToCheck))
    return;

  if (mSplit)
  {
    for (auto& child : mChildNodes)
      child->traverse(callback, boundsToCheck);
  }
  else
  {
    for (auto element : mElements)
    {
      if (Intersector()(boundsToCheck, element))
        callback(element);
    }
  }
}

} // namespace aw
