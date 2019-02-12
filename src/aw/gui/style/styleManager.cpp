#include <aw/gui/style/styleManager.hpp>

namespace aw::gui
{
bool StyleManager::add(std::string name, const StyleTemplate& element)
{
  auto result = mStyles.insert(std::make_pair(std::move(name), std::move(element)));
  return result.second;
}

void StyleManager::update(const std::string& name, const StyleTemplate& element)
{
  auto found = mStyles.find(name);
  if (found != mStyles.end())
    found->second = element;
  else
    add(name, element);
}

const StyleTemplate* StyleManager::get(const std::string& name) const
{
  auto found = mStyles.find(name);
  if (found != mStyles.end())
    return &found->second;
  return nullptr;
}

StyleTemplate StyleManager::getCopy(const std::string& name) const
{
  auto* style = get(name);
  if (style)
    return *style;
  return {};
}
} // namespace aw::gui
