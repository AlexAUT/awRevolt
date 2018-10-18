#include <aw/gui/widgets/textBox.hpp>

#include <aw/engine/windowEvent.hpp>
#include <aw/gui/gui.hpp>
#include <aw/gui/renderer/nanovgRenderer.hpp>

#include <aw/utils/log.hpp>

namespace aw::gui
{
TextBox::TextBox(const GUI& gui, std::string text)
    : Widget(gui), mText(std::move(text)), mTextStyle(gui.getTextStyles().getStyle("default"))
{
  assert(mTextStyle);
  setSelectable(true);
  setPadding({3.f});
}

void TextBox::setText(std::string text)
{
  mText = std::move(text);
  invalidateLayout();

  setSelectable(true);
}

bool TextBox::processEvent(const WindowEvent& event)
{
  bool usedEvent = false;
  // Check if mouse pressed hit textBox
  if (isInState(State::Selected))
  {
    // Check if text input occured
    if (event.type == WindowEvent::TextEntered)
    {
      auto unicode = event.text.unicode;
      LogTemp() << "Unicode: " << unicode;
      if (unicode > 30 && (unicode < 127 || unicode > 159))
        addCharacterAtCursor(sf::String(event.text.unicode).toAnsiString().front());
      else if (unicode == '\b')
        removeAtCursor(1);
      else if (unicode == 127)
      {
        if (static_cast<size_t>(getCursorPosition()) < mText.size())
        {
          setCursorPosition(getCursorPosition() + 1);
          removeAtCursor(1);
        }
      }
      usedEvent = true;
    }
    // Check for Escape, left, right
    if (event.type == WindowEvent::KeyPressed)
    {
      if (event.key.code == sf::Keyboard::Left)
        setCursorPosition(getCursorPosition() - 1);
      else if (event.key.code == sf::Keyboard::Right)
        setCursorPosition(getCursorPosition() + 1);

      usedEvent = true;
    }
  }

  return Widget::processEvent(event) || usedEvent;
}

void TextBox::update(float delta)
{
  if (isInState(State::Selected))
  {
    mCursorTimer += delta;
    if (mCursorTimer > mCursorBlinkRate)
    {
      mCursorTimer -= mCursorBlinkRate;
      mShowCursor = !mShowCursor;
    }
  }
}

void TextBox::render(Vec2 parentPos)
{
  Widget::render(parentPos);
  getGUI().getRenderer().render(*this);
}

void TextBox::removeAtCursor(unsigned numToRemove)
{
  if (mCursorPosition != 0 && !mText.empty())
  {
    auto removeAt = std::min(static_cast<size_t>(mCursorPosition - 1), mText.size() - 1);
    mText.erase(removeAt, numToRemove);
    mCursorPosition--;
  }
}

void TextBox::addCharacterAtCursor(char c)
{
  if (mCursorPosition > static_cast<int>(mText.size()))
    mText.push_back(c);
  mText.insert(static_cast<size_t>(mCursorPosition), 1, c);
  mCursorPosition++;
}

void TextBox::select(Vec2 clickPos)
{
  Widget::select(clickPos);
  LogTemp() << "Text box selected!" << isInState(State::Selected);
  if (isInState(State::Selected))
  {
    mCursorPosition = getGUI().getRenderer().calculateCursorPosition(*this, clickPos - getRelativePosition());
    mCursorTimer = 0.f;
    mShowCursor = true;
  }
}

void TextBox::setCursorPosition(int position)
{
  mCursorTimer = 0.f;
  mShowCursor = true;
  mCursorPosition = std::max(std::min(position, static_cast<int>(mText.size())), 0);
}

void TextBox::setTextStyle(const TextStyle* textStyle)
{
  assert(textStyle);
  mTextStyle = textStyle;
  invalidateLayout();
}

void TextBox::updateLayout()
{
  auto textSize = getGUI().getRenderer().calculateTextSize("A", *mTextStyle);
  mMinimalSize.x = std::max(getPreferedSize().x, textSize.x * mMinWidthInCharacter);
  mMinimalSize.y = std::max(getPreferedSize().y, textSize.y);

  mMinimalSize.x += getPadding().left + getPadding().right;
  mMinimalSize.y += getPadding().top + getPadding().bottom;

  Widget::updateLayout();
}

Vec2 TextBox::getMinimalSize() const
{
  return mMinimalSize;
}
} // namespace aw::gui
