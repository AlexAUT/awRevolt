#pragma once

#include <aw/gui/widgets/textBox.hpp>

#include <regex>
#include <sstream>

namespace aw::gui
{
class TypedTextBox : public TextBox
{
public:
  TypedTextBox(const aw::gui::GUI& gui, std::string text);
  virtual ~TypedTextBox() = default;

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

class TextBoxFloat final : public TypedTextBox
{
public:
  TextBoxFloat(const aw::gui::GUI& gui, float value) : TypedTextBox(gui, std::to_string(value)) {}
  ~TextBoxFloat() = default;

  float getValue() const { return mValue; }

protected:
  void updateValue() override
  {
    std::regex regex("[+-]?(?=[.]?[0-9])[0-9]*(?:[.][0-9]*)?(?:[Ee][+-]?[0-9]+)?");
    auto match = std::regex_match(getText(), regex);
    changeValidState(match);
    if (match)
    {
      mValue = std::stof(getText().c_str());
    }
  }

private:
  float mValue;

}; // namespace aw::gui

} // namespace aw::gui
