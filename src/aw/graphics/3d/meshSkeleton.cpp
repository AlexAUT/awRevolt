#include <aw/graphics/3d/meshSkeleton.hpp>

namespace aw
{
MeshSkeletonNode& MeshSkeleton::getRootNode()
{
  return mRootNode;
}

const MeshSkeletonNode& MeshSkeleton::getRootNode() const
{
  return mRootNode;
}

void MeshSkeleton::setBoneCount(unsigned count)
{
  mBoneCount = count;
}

unsigned MeshSkeleton::getBoneCount() const
{
  return mBoneCount;
}

} // namespace aw
