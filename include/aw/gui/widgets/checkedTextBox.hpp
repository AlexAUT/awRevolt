#pragma once

#include <aw/gui/widgets/textBox.hpp>

namespace aw::gui
{
class CheckedTextBox : public TextBox
{
public:
  CheckedTextBox(const aw::gui::GUI& gui, std::string text);
  virtual ~CheckedTextBox() = default;

  virtual void deselect(Vec2 mousePos = {}) override;
  virtual void changedText() override;

  void changeCheckWhileTyping(bool value) { mUpdateDuringTyping = value; }
  bool isTextValid() const { return mValid; }

  void setInvalidTextStyle(const TextStyle* invalidTextStyle) { mInvalidTextStyle = invalidTextStyle; }
  const TextStyle& getInvalidTextStyle() const { return *mInvalidTextStyle; }

  virtual const TextStyle* getCurrentTextStyle() const override;
  virtual void render(Vec2 parentPos) override;

protected:
  void changeValidState(bool valid) { mValid = valid; }
  virtual void updateValue() = 0;

private:
  bool mValid{true};
  bool mUpdateDuringTyping{true};

  const TextStyle* mInvalidTextStyle{nullptr};
};
} // namespace aw::gui
