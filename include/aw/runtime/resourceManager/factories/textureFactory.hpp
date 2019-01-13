#pragma once

#include <aw/graphics/core/texture2D.hpp>
#include <aw/runtime/resourceManager/resourceFactory.hpp>

namespace aw
{
class Path;
}

namespace aw::factories
{
class TextureFactory : public ResourceFactory<TextureFactory, Texture2D>
{
public:
  using TypePtr = std::shared_ptr<Texture2D>;

public:
  TypePtr create(const Path& path);

private:
private:
};
} // namespace aw::factories
