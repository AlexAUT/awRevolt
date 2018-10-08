#pragma once

#include <memory>
#include <string>
#include <unordered_map>

namespace aw
{
class Mesh;

using MeshManager = std::unordered_map<std::string, std::unique_ptr<Mesh>>;

} // namespace aw
