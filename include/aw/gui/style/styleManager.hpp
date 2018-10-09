#pragma once

#include <unordered_map>

#include <memory>

namespace aw::gui
{
template <typename StyleType>
class StyleManager
{
public:
  using ElementUPtr = std::unique_ptr<StyleType>;

public:
  StyleManager();
  // Does not override (returns false if already present)
  bool addStyle(std::string name, const StyleType& element);
  // Does always insert/update the style
  void updateStyle(const std::string& name, const StyleType& element);

  const StyleType* getStyle(const std::string& name) const;

private:
private:
  std::unordered_map<std::string, ElementUPtr> mStyles;
};

template <typename StyleType>
StyleManager<StyleType>::StyleManager()
{
  addStyle("default", StyleType::defaultInstance());
}

template <typename StyleType>
bool StyleManager<StyleType>::addStyle(std::string name, const StyleType& element)
{
  auto result = mStyles.insert(std::make_pair(std::move(name), std::make_unique<StyleType>(element)));
  return result.second;
}

template <typename StyleType>
void StyleManager<StyleType>::updateStyle(const std::string& name, const StyleType& element)
{
  auto found = mStyles.find(name);
  if (found != mStyles.end())
    *found->second = element;
  else
    addStyle(name, element);
}

template <typename StyleType>
const StyleType* StyleManager<StyleType>::getStyle(const std::string& name) const
{
  auto found = mStyles.find(name);
  if (found != mStyles.end())
    return found->second.get();
  return nullptr;
}
} // namespace aw::gui
