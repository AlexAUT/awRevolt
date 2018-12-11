#pragma once

#include <aw/gui/widgets/label.hpp>

#include <string>

namespace aw::gui
{
class ListItem : public Label
{
public:
  using SPtr = std::shared_ptr<ListItem>;

public:
  ListItem(const GUI& gui, std::string text, std::string id);
  virtual ~ListItem() = default;

  virtual void render(Vec2 parentPos) override;

  std::string_view getId() const { return mId; }

private:
  std::string mId;
};
} // namespace aw::gui
