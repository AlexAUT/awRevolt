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
  bool add(std::string name, const StyleTemplate& element);
  // Does always insert/update the style
  void update(const std::string& name, const StyleTemplate& element);

  const StyleTemplate* get(const std::string& name) const;
  StyleTemplate getCopy(const std::string& name) const;

private:
private:
  std::unordered_map<std::string, StyleTemplate> mStyles;
};
} // namespace aw::gui
