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
  Button(const GUI& gui, std::string text);

  void render(Vec2 parentPos) override;

  void setText(std::string text) { mText = std::move(text); }
  const std::string& getText() const { return mText; }

  void setTextLayout(const TextStyle* layout);
  const TextStyle& getTextLayout() const { return *mTextLayout; }

  virtual void updateLayout() override;
  virtual Vec2 getMinimalSize() const override;

private:
private:
  std::string mText;

  const TextStyle* mTextLayout{nullptr};
  Vec2 mMinimumSize{0.f};
};
} // namespace aw::gui
