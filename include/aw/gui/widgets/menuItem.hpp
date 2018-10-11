#pragma once

#include <aw/gui/widgets/label.hpp>

#include <aw/gui/widgets/linearContainer.hpp>
#include <aw/gui/widgets/menuSubItem.hpp>
#include <aw/gui/widgets/panel.hpp>

namespace aw::gui
{
class Menu;

class MenuItem : public Label
{
public:
  using SPtr = std::shared_ptr<MenuItem>;

public:
  MenuItem(const GUI& gui, Menu& menu, std::string text, bool isSubElement = false);
  virtual ~MenuItem() = default;

  MenuSubItem::SPtr addSubEntry(const std::string& text);

  bool isSubEntry() const { return mIsSubElement; }

  const LinearContainer& getChildContainer() const { return *mChildContainer; }

  virtual bool processEvent(const WindowEvent& event) override;
  virtual void render(Vec2 parentPos) override;
  virtual void updateLayout() override;

  virtual void select(Vec2 mousePos) override;
  virtual void deselect(Vec2 mousePos) override;

private:
private:
  Menu& mMenu;

  bool mIsSubElement{false};
  bool mShowChilds{false};

  Panel::SPtr mChildPanel;
  LinearContainer::SPtr mChildContainer;
};
} // namespace aw::gui
