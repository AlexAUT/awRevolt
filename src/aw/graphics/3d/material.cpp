#include <aw/graphics/3d/material.hpp>

namespace aw
{
Material::Material(std::string name) : mName(name)
{
}

void Material::addDiffuseTexture(const TextureSlot& textureSlot)
{
  mDiffuseSlots.push_back(textureSlot);
}

void Material::addNormalTexture(const TextureSlot& textureSlot)
{
  mNormalSlots.push_back(textureSlot);
}

const TextureSlot& Material::getDiffuseSlot(unsigned index) const
{
  return mDiffuseSlots[index];
}

} // namespace aw
