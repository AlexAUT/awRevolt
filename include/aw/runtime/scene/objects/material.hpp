#pragma once

#include <aw/graphics/core/texture2D.hpp>
#include <aw/runtime/resourceManager/resourcePtr.hpp>
#include <aw/utils/color.hpp>

#include <vector>

namespace aw
{
struct TextureSlot
{
  enum class Type
  {
    Diffuse,
    Normal,
  };

  Type type;
  ResourcePtr<Texture2D> texture;
  unsigned uvIndex;
  Texture2D::MinFilter minFilter;
  Texture2D::MagFilter magFilter;
  Texture2D::WrapMode modeS;
  Texture2D::WrapMode modeT;

  template <class Archive>
  void save(Archive& archive) const;
};

struct Material
{
  aw::Color ambientColor;
  aw::Color diffuseColor;
  aw::Color specularColor;

  std::vector<TextureSlot> textureSlots;

  template <class Archive>
  void save(Archive& archive) const;
};

#ifndef CEREAL_NVP
#define CEREAL_NVP(x)
#endif
template <typename Archive>
void TextureSlot::save(Archive& archive) const
{
  archive(CEREAL_NVP(type));
  archive(CEREAL_NVP(texture.id));
  archive(CEREAL_NVP(minFilter));
  archive(CEREAL_NVP(magFilter));
  archive(CEREAL_NVP(modeS));
  archive(CEREAL_NVP(modeT));
}

template <typename Archive>
void Material::save(Archive& archive) const
{
  archive(CEREAL_NVP(ambientColor));
  archive(CEREAL_NVP(diffuseColor));
  archive(CEREAL_NVP(specularColor));
  archive(CEREAL_NVP(textureSlots));
}
} // namespace aw
