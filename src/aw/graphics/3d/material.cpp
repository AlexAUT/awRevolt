#include <aw/graphics/3d/material.hpp>

#include <aw/graphics/core/shaderProgram.hpp>

namespace aw
{
void Material::assignToShader(const Material& material, const ShaderProgram& shader, std::string_view uniformName)
{
  shader.bind();

  shader.setUniform("diffuseColor", material.getDiffuseColor());
  shader.setUniform("ambientColor", material.getAmbientColor());
  shader.setUniform("specularColor", Vec4(material.getSpecularColor(), 10));
  shader.setUniform("enableDiffuseTex", material.getDiffseSlotCount() > 0);

  if (material.getDiffseSlotCount() > 0)
    material.getDiffuseSlot(0).texture2D->bind();
  shader.setUniform("enableDecalTex", material.getDiffseSlotCount() > 1);
  if (material.getDiffseSlotCount() > 1)
    material.getDiffuseSlot(1).texture2D->bind(1);
}

Material::Material(std::string name) : mName(name) {}

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
