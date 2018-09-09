#include <aw/graphics/3d/material.hpp>

namespace aw
{
Material::Material(std::string name) : mName(name)
{
}

void Material::setAmbientColor(Vec3 color)
{
  mAmbientColor = color;
}

Vec3 Material::getAmbientColor() const
{
  return mAmbientColor;
}

void Material::setDiffuseColor(Vec3 color)
{
  mDiffuseColor = color;
}

Vec3 Material::getDiffuseColor() const
{
  return mDiffuseColor;
}

void Material::setSpecularColor(Vec3 color)
{
  mSpecularColor = color;
}

Vec3 Material::getSpecularColor() const
{
  return mSpecularColor;
}

void Material::addDiffuseTexture(const TextureSlot& textureSlot)
{
  mDiffuseSlots.push_back(textureSlot);
}

void Material::addNormalTexture(const TextureSlot& textureSlot)
{
  mNormalSlots.push_back(textureSlot);
}

size_t Material::getDiffseSlotCount() const
{
  return mDiffuseSlots.size();
}

const TextureSlot& Material::getDiffuseSlot(unsigned index) const
{
  return mDiffuseSlots[index];
}

} // namespace aw
