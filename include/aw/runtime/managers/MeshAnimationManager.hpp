#pragma once

#include <memory>
#include <string>
#include <unordered_map>

namespace aw
{
class MeshAnimation;

typedef std::unordered_map<std::string, std::unique_ptr<MeshAnimation>> MeshAnimationManager;

} // namespace aw
