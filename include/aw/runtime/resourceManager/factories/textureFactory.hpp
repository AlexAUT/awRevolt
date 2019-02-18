#pragma once

#include <aw/graphics/core/texture2D.hpp>
#include <aw/runtime/resourceManager/resourceDatabase.hpp>
#include <aw/runtime/resourceManager/resourceFactory.hpp>
#include <aw/runtime/resourceManager/resourcePtr.hpp>
#include <aw/runtime/resourceManager/resourceRegistry.hpp>

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
  using Registry = ResourceRegistry<Texture2D>;
  using ResourcePointer = ResourcePtr<Texture2D>;

public:
  ResourcePointer create(Registry& registry, ResourceDatabase& dataBase, const Path& path);

private:
private:
};
} // namespace aw::factories
