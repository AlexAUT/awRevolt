#include <aw/runtime/resourceManager/factories/textureFactory.hpp>

#include <aw/graphics/core/image.hpp>
#include <aw/utils/file/fileInputStream.hpp>
#include <aw/utils/file/path.hpp>
#include <aw/utils/log.hpp>

DEFINE_LOG_CATEGORIES(TextureFactory, "Texture Factory");

namespace aw::factories
{
auto TextureFactory::create(const Path& path) -> TypePtr
{
  aw::Image img;
  if (!img.load(path))
  {
    LogErrorTextureFactory() << "Failed to load mesh texture: " << path;
    return nullptr;
  }
  auto tex2D = std::make_shared<aw::Texture2D>();
  tex2D->bind();
  tex2D->loadFromImage(img);
  tex2D->unbind();
  return tex2D;
}

} // namespace aw::factories
