#pragma once

#include <aw/gui/widgets/widget.hpp>

#include <aw/gui/style/alignment.hpp>

#include <string>

namespace aw::gui
{
struct TextStyle;

class Label : public Widget
{
public:
  AW_GUI_CLASS_NAME(Label)
  using SPtr = std::shared_ptr<Label>;

public:
  Label(const GUI& gui, std::string text);
  virtual ~Label() = default;

  void setText(std::string text);
  const std::string& getText() const { return mText; }

  virtual void render() override;

  void setAlignment(Alignment alignment);
  void setAlignmentH(AlignmentH alignment);
  void setAlignmentV(AlignmentV alignment);

  Alignment getAlignment() const { return mAlignment; }
  AlignmentH getAlignmentH() const { return mAlignment.horizontal; }
  AlignmentV getAlignmentV() const { return mAlignment.vertical; }

  virtual void updateLayout(aw::Vec2 parentPos) override;
  virtual Vec2 getMinimalSize() const override;

private:
private:
  std::string mText;
  Alignment mAlignment;

  Vec2 mMinimumSize{0.f};
};
} // namespace aw::gui
