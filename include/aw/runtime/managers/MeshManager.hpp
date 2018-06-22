#pragma once

#include <memory>
#include <string>
#include <unordered_map>

namespace aw
{
class Mesh;

typedef std::unordered_map<std::string, std::unique_ptr<Mesh>> MeshManager;

} // namespace aw
