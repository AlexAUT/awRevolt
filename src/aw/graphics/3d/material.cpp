#include <aw/graphics/3d/material.hpp>

#include <aw/graphics/core/shaderProgram.hpp>
#include <aw/opengl/opengl.hpp>

namespace aw
{
Texture2D* getFallbackTexture()
{
  auto init = []() {
    Texture2D* tex = new Texture2D();
    uint8 color[] = {255, 20, 147};
    tex->bind();
    tex->load(&color, 1, 1, PixelFormat::RGB8);
    tex->unbind();
    return tex;
  };
  static Texture2D* tex = init();
  return tex;
}

void Material::assignToShader(const Material& material, const ShaderProgram& shader, std::string_view uniformName)
{
  shader.bind();

  shader.setUniform("diffuseColor", material.getDiffuseColor());
  shader.setUniform("ambientColor", material.getAmbientColor());
  shader.setUniform("specularColor", Vec4(material.getSpecularColor(), 10));
  shader.setUniform("enableDiffuseTex", material.getDiffseSlotCount() > 0);

  if (material.getDiffseSlotCount() > 0)
  {
    auto* tex = material.getDiffuseSlot(0).texture2D.get();
    if (!tex)
      tex = getFallbackTexture();
    tex->bind();
  }
  shader.setUniform("enableDecalTex", material.getDiffseSlotCount() > 1);
  if (material.getDiffseSlotCount() > 1)
  {
    auto* tex = material.getDiffuseSlot(1).texture2D.get();
    if (!tex)
      tex = getFallbackTexture();
    tex->bind(1);
  }
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
