#pragma once

#include <aw/gui/utils/signal.hpp>
#include <aw/gui/widgets/linearContainer.hpp>
#include <aw/gui/widgets/panel.hpp>

namespace aw::gui
{
class ContextMenu : public aw::gui::Panel
{
public:
  using SPtr = std::shared_ptr<ContextMenu>;
  AW_GUI_CLASS_NAME(ContextMenu)

  using ItemClickedSignal = aw::gui::Signal<void(std::string)>;

public:
  ContextMenu(const GUI& gui);

  void open(Vec2 clickPos);
  void close();

  void addItem(std::string id, std::string text);
  void addItemAt(std::string id, std::string text, size_t pos);

  virtual bool processEvent(const WindowEvent& event) override;

  virtual void updateLayout(Vec2 parentPos) override;

  ItemClickedSignal onItemClicked;

private:
private:
  LinearContainer::SPtr mChildContainer;
};
} // namespace aw::gui
