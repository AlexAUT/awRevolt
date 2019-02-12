#pragma once

#include <aw/gui/style/padding.hpp>
#include <aw/gui/widgets/widget.hpp>
#include <aw/utils/types.hpp>

#include <string>

namespace aw::gui
{
struct TextStyle;

class Button : public Widget
{
public:
  AW_GUI_CLASS_NAME(Button)

  Button(const GUI& gui, std::string text);

  void render() override;

  void setText(std::string text) { mText = std::move(text); }
  const std::string& getText() const { return mText; }

  virtual void updateLayout(aw::Vec2 parentPos) override;
  virtual Vec2 getMinimalSize() const override;

private:
private:
  std::string mText;
  Vec2 mMinimumSize{0.f};
};
} // namespace aw::gui
