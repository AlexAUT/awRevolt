#pragma once

#include <aw/graphics/3d/meshSkeletonNode.hpp>

#include <aw/utils/math/matrix.hpp>
#include <aw/utils/math/vector.hpp>

namespace aw
{

class MeshSkeleton
{
public:
  MeshSkeleton() = default;
  MeshSkeleton(const MeshSkeleton&) = delete;
  MeshSkeleton operator=(const MeshSkeleton&) = delete;

  MeshSkeletonNode& getRootNode();
  const MeshSkeletonNode& getRootNode() const;

  void setBoneCount(unsigned count);
  unsigned getBoneCount() const;

private:
private:
  unsigned mBoneCount{0};
  MeshSkeletonNode mRootNode;
};

} // namespace aw
