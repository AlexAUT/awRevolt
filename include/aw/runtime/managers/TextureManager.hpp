#pragma once

#include <memory>
#include <string>
#include <unordered_map>

#include <aw/graphics/core/texture2D.hpp>

namespace aw
{
typedef std::unordered_map<std::string, std::unique_ptr<Texture2D>> TextureManager;

} // namespace aw
