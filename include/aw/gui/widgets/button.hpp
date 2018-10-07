#pragma once

#include <aw/gui/widgets/widget.hpp>

#include <string>

namespace aw::gui
{
class Button : public Widget
{
public:
  Button(const GUI& gui, std::string text) : Widget(gui), mText(std::move(text)) {}

  void render(Vec2 parentPos) override;

  void setText(std::string text) { mText = std::move(text); }
  const std::string& getText() const { return mText; }

private:
private:
  std::string mText;
};
} // namespace aw::gui
