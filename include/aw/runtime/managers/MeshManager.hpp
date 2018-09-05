#pragma once

#include <memory>
#include <string>
#include <unordered_map>

#include <aw/graphics/3d/mesh.hpp>

namespace aw
{

typedef std::unordered_map<std::string, std::unique_ptr<Mesh>> MeshManager;

} // namespace aw
