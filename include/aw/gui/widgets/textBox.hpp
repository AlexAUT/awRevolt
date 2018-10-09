#pragma once

#include <aw/gui/widgets/widget.hpp>

namespace aw::gui
{
class TextBox : public Widget
{
public:
  TextBox(const GUI& gui) : Widget(gui) {}

  void setText(std::string text);
  const std::string& getText() const { return mText; }

  virtual bool processEvent(const WindowEvent& event) override;
  virtual void update(float delta) override;
  virtual void render(Vec2 parentPos) override;

  void removeAtCursor(unsigned numToRemove);
  void addCharacterAtCursor(char c);

  void deselect() { mSelected = false; }
  void select();
  void select(Vec2 relativeClickPosition);

  void setCursorPosition(int position);

  bool shouldRenderCursor() const { return mSelected && mShowCursor; }
  int getCursorPosition() const { return mCursorPosition; }

private:
private:
  bool mSelected{false};
  int mCursorPosition;
  float mCursorBlinkRate{0.5f};
  float mCursorTimer{0.f};
  bool mShowCursor;

  std::string mText;
};
}
