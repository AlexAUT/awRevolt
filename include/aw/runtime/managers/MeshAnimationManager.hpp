#pragma once

#include <memory>
#include <string>
#include <unordered_map>

namespace aw
{
class MeshAnimation;

using MeshAnimationManager = std::unordered_map<std::string, std::unique_ptr<MeshAnimation>>;

} // namespace aw
