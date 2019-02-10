#include <aw/gui/widgets/checkedTextBox.hpp>

#include <aw/gui/gui.hpp>

namespace aw::gui
{
CheckedTextBox::CheckedTextBox(const aw::gui::GUI& gui, std::string text) : TextBox(gui, text) {}

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

void CheckedTextBox::render()
{
  assert(!isLayoutDirty());
  Widget::render();
  getGUI().getRenderer().render(*this);
}

} // namespace aw::gui
