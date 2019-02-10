#pragma once

#include <aw/gui/widgets/widget.hpp>

namespace aw::gui
{
struct TextStyle;

class TextBox : public Widget
{
public:
  TextBox(const GUI& gui, std::string text = "");

  void setText(std::string text);
  const std::string& getText() const { return mText; }

  virtual bool processEvent(const WindowEvent& event) override;
  virtual void update(float delta) override;
  virtual void render() override;

  void removeAtCursor(unsigned numToRemove);
  void addCharacterAtCursor(char c);

  virtual void select(Vec2 relativeClickPosition) override;

  void setCursorPosition(int position);

  bool shouldRenderCursor() const { return isInState(State::Selected) && mShowCursor; }
  int getCursorPosition() const { return mCursorPosition; }

  virtual void updateLayout(aw::Vec2 parentPos) override;
  virtual Vec2 getMinimalSize() const override;

public:
  Widget::Signal onTextChange;

protected:
  virtual void changedText();

private:
  std::string mText;

  int mCursorPosition;
  float mCursorBlinkRate{0.5f};
  float mCursorTimer{0.f};
  bool mShowCursor;

  int mMinWidthInCharacter{6};
  Vec2 mMinimalSize{0.f};
};
} // namespace aw::gui
