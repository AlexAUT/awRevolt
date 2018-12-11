#include <aw/gui/widgets/typedTextBox.hpp>

#include <aw/gui/gui.hpp>

namespace aw::gui
{
TypedTextBox::TypedTextBox(const aw::gui::GUI& gui, std::string text) :
    TextBox(gui, text),
    mInvalidTextStyle(gui.getTextStyles().getStyle("defaultFail"))
{
}

void TypedTextBox::deselect(Vec2 mousePos)
{
  if (!mUpdateDuringTyping)
    updateValue();

  TextBox::deselect(mousePos);
}
void TypedTextBox::changedText()
{
  if (mUpdateDuringTyping)
    updateValue();
}

const TextStyle* TypedTextBox::getCurrentTextStyle() const
{
  if (!isTextValid())
    return mInvalidTextStyle;
  return TextBox::getCurrentTextStyle();
}

void TypedTextBox::render(Vec2 parentPos)
{
  assert(!isLayoutDirty());
  Widget::render(parentPos);
  getGUI().getRenderer().render(*this);
}

} // namespace aw::gui
