#pragma once

#include <memory>
#include <string>
#include <unordered_map>

namespace aw
{
class Texture2D;

typedef std::unordered_map<std::string, std::unique_ptr<Texture2D>> TextureManager;

} // namespace aw
