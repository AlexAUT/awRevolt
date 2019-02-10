#pragma once

#include <aw/gui/widgets/label.hpp>

namespace aw::gui
{
class Menu;

class MenuSubItem : public Label
{
public:
  using SPtr = std::shared_ptr<MenuSubItem>;

public:
  MenuSubItem(const GUI& gui, Menu& menu, std::string text);

  virtual void render() override;

private:
private:
  Menu& mMenu;
};
} // namespace aw::gui
