#pragma once

#include <aw/utils/math/matrix.hpp>
#include <aw/utils/types.hpp>

#include <memory>
#include <string>
#include <vector>

namespace aw
{
class MeshSkeletonNode
{
public:
  std::string name;
  Mat4 transformation;

  std::vector<MeshSkeletonNode> children;

private:
private:
};
} // namespace aw
