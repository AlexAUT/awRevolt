#include <aw/gui/widgets/checkedTextBox.hpp>

#include <aw/gui/gui.hpp>

namespace aw::gui
{
CheckedTextBox::CheckedTextBox(const aw::gui::GUI& gui, std::string text) :
    TextBox(gui, text),
    mInvalidTextStyle(gui.getTextStyles().getStyle("defaultFail"))
{
}

void CheckedTextBox::deselect(Vec2 mousePos)
{
  if (!mUpdateDuringTyping)
    updateValue();

  TextBox::deselect(mousePos);
}
void CheckedTextBox::changedText()
{
  if (mUpdateDuringTyping)
    updateValue();
  TextBox::changedText();
}

const TextStyle* CheckedTextBox::getCurrentTextStyle() const
{
  if (!isTextValid())
    return mInvalidTextStyle;
  return TextBox::getCurrentTextStyle();
}

void CheckedTextBox::render(Vec2 parentPos)
{
  assert(!isLayoutDirty());
  Widget::render(parentPos);
  getGUI().getRenderer().render(*this);
}

} // namespace aw::gui
