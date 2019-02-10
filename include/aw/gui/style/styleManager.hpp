#pragma once

#include <aw/gui/style/style.hpp>

#include <memory>
#include <optional>
#include <unordered_map>

namespace aw::gui
{
class StyleManager
{
public:
  // Does not override (returns false if already present)
  bool addStyle(std::string name, const StyleTemplate& element);
  // Does always insert/update the style
  void updateStyle(const std::string& name, const StyleTemplate& element);

  const StyleTemplate* getStyle(const std::string& name) const;

private:
private:
  std::unordered_map<std::string, StyleTemplate> mStyles;
};
} // namespace aw::gui
