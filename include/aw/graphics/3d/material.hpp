#pragma once

#include <aw/graphics/core/texture2D.hpp>
#include <aw/utils/math/vector.hpp>
#include <aw/utils/types.hpp>

#include <memory>
#include <string>
#include <vector>

namespace aw
{

struct TextureSlot
{
  std::string texName;
  std::shared_ptr<Texture2D> texture2D;
  unsigned uvIndex;
  Texture2D::MinFilter minFilter;
  Texture2D::MagFilter magFilter;
  Texture2D::WrapMode modeS;
  Texture2D::WrapMode modeT;
};

class Material
{
public:
  explicit Material(std::string name);

  void addDiffuseTexture(const TextureSlot& textureSlot);
  void addNormalTexture(const TextureSlot& textureSlot);

  void setDiffuseColor(Vec3 color);
  Vec3 getDiffuseColor() const;

  size_t getDiffseSlotCount() const;
  const TextureSlot& getDiffuseSlot(unsigned index) const;

private:
private:
  std::string mName;

  Vec3 mDiffuseColor{1.f, 1.f, 1.f};

  std::vector<TextureSlot> mDiffuseSlots;
  std::vector<TextureSlot> mNormalSlots;
};
} // namespace aw
