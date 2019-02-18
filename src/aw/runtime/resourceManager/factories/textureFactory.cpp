#include <aw/runtime/resourceManager/factories/textureFactory.hpp>

#include <aw/graphics/core/image.hpp>
#include <aw/utils/file/fileInputStream.hpp>
#include <aw/utils/file/path.hpp>
#include <aw/utils/log.hpp>

DEFINE_LOG_CATEGORIES(TextureFactory, "Texture Factory");

namespace aw::factories
{
auto TextureFactory::create(ResourceRegistry<Texture2D>& registry, ResourceDatabase& db, const Path& path)
    -> ResourcePointer
{
  // Check if database has already the path entry
  if (db.has(path.asString()))
  {
    auto id = db.get(path.asString());
    auto ptr = registry.get(id);
    if (ptr)
      return ptr;
  }

  // Create new database entry
  auto id = db.newResource(path.asString());

  //
  aw::Image img;
  if (!img.load(path))
  {
    LogErrorTextureFactory() << "Failed to load mesh texture: " << path;
    return {id, nullptr};
  }
  auto tex2D = std::make_shared<aw::Texture2D>();
  tex2D->bind();
  tex2D->load(img);
  tex2D->unbind();
  return {id, tex2D};
}

} // namespace aw::factories
