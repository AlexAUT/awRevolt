#include <aw/gui/style/styleManager.hpp>

namespace aw::gui
{
bool StyleManager::addStyle(std::string name, const StyleTemplate& element)
{
  auto result = mStyles.insert(std::make_pair(std::move(name), std::move(element)));
  return result.second;
}

void StyleManager::updateStyle(const std::string& name, const StyleTemplate& element)
{
  auto found = mStyles.find(name);
  if (found != mStyles.end())
    found->second = element;
  else
    addStyle(name, element);
}

const StyleTemplate* StyleManager::getStyle(const std::string& name) const
{
  auto found = mStyles.find(name);
  if (found != mStyles.end())
    return &found->second;
  return nullptr;
}
} // namespace aw::gui
