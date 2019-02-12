#pragma once

#include <aw/gui/widgets/label.hpp>

#include <string>

namespace aw::gui
{
class ListItem : public Label
{
public:
  AW_GUI_CLASS_NAME(ListItem)
  using SPtr = std::shared_ptr<ListItem>;

public:
  ListItem(const GUI& gui, std::string text, std::string id);
  virtual ~ListItem() = default;

  virtual void render() override;

  std::string_view getId() const { return mId; }

private:
  std::string mId;
};
} // namespace aw::gui
