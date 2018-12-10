#pragma once

#include <aw/graphics/core/texture2D.hpp>
#include <aw/utils/math/vector.hpp>
#include <aw/utils/types.hpp>

#include <memory>
#include <string>
#include <vector>

namespace aw
{
class ShaderProgram;

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
  static void assignToShader(const Material& material, const ShaderProgram& shader, std::string_view uniformName);

public:
  explicit Material(std::string name);

  void addDiffuseTexture(const TextureSlot& textureSlot);
  void addNormalTexture(const TextureSlot& textureSlot);

  void setAmbientColor(Vec3 color);
  Vec3 getAmbientColor() const;

  void setDiffuseColor(Vec3 color);
  Vec3 getDiffuseColor() const;

  void setSpecularColor(Vec3 color);
  Vec3 getSpecularColor() const;

  size_t getDiffseSlotCount() const;
  const TextureSlot& getDiffuseSlot(unsigned index) const;

private:
private:
  std::string mName;

  Vec3 mAmbientColor{0.f, 0.f, 0.f};
  Vec3 mDiffuseColor{0.f, 0.f, 0.f};
  Vec3 mSpecularColor{0.f, 0.f, 0.f};

  std::vector<TextureSlot> mDiffuseSlots;
  std::vector<TextureSlot> mNormalSlots;
};
} // namespace aw
