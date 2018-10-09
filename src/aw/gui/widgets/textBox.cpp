#include <aw/gui/widgets/textBox.hpp>

#include <aw/engine/windowEvent.hpp>
#include <aw/gui/gui.hpp>
#include <aw/gui/renderer/nanovgRenderer.hpp>

#include <aw/utils/log.hpp>

namespace aw::gui
{
void TextBox::setText(std::string text)
{
  mText = std::move(text);
  invalidLayout();
}

bool TextBox::processEvent(const WindowEvent& event)
{
  // Check if mouse pressed hit textBox
  if (event.type == WindowEvent::MouseButtonPressed)
  {
    if (event.mouseButton.button == sf::Mouse::Left)
    {
      LogTemp() << "Check pointer : " << event.mouseButton.x << "," << event.mouseButton.y;
      Vec2 mousePos = {event.mouseButton.x, event.mouseButton.y};
      if (isLocalPointOnWidget(mousePos))
      {
        select(mousePos);
        return true;
      }
      else
        mSelected = false;
    }
  }
  if (mSelected)
  {
    // Check if text input occured
    if (event.type == WindowEvent::TextEntered)
    {
      auto unicode = event.text.unicode;
      if (unicode == '\b')
        removeAtCursor(1);
      if (unicode > 30 && (unicode < 127 || unicode > 159))
        addCharacterAtCursor(sf::String(event.text.unicode).toAnsiString().front());
    }
    // Check for Escape, left, right
    if (event.type == WindowEvent::KeyPressed)
    {
      if (event.key.code == sf::Keyboard::Escape)
        deselect();
      else if (event.key.code == sf::Keyboard::Left)
        setCursorPosition(getCursorPosition() - 1);
      else if (event.key.code == sf::Keyboard::Right)
        setCursorPosition(getCursorPosition() + 1);
    }
  }

  return false;
}

void TextBox::update(float delta)
{
  if (mSelected)
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

void TextBox::select()
{
  // Select at last character (size if always last character
  select(getSize());
}

void TextBox::select(Vec2 clickPos)
{
  mSelected = true;
  LogTemp() << "Click pos: " << clickPos << " - " << getRelativePosition();
  mCursorPosition = getGUI().getRenderer().calculateCursorPosition(*this, clickPos - getRelativePosition());
  mCursorTimer = 0.f;
  mShowCursor = true;
}

void TextBox::setCursorPosition(int position)
{
  mCursorTimer = 0.f;
  mShowCursor = true;
  mCursorPosition = std::max(std::min(position, static_cast<int>(mText.size())), 0);
}
}
