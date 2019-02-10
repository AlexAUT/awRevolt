#include <aw/gui/widgets/widget.hpp>

#include <aw/engine/windowEvent.hpp>

namespace aw::gui
{
namespace priv
{
const char* stateToString(Widget::State state)
{
  switch (state)
  {
  case Widget::State::Hovered:
    return "hover";
  case Widget::State::Pressed:
    return "press";
  case Widget::State::Selected:
    return "select";
  default:
    return "";
  }
}
} // namespace priv
bool Widget::processEvent(const WindowEvent& event)
{
  if (!mConsumeEvent)
    return false;

  bool usedEvent = false;
  if (event.type == WindowEvent::MouseMoved)
  {
    Vec2 mousePos{event.mouseButton.x, event.mouseButton.y};
    bool hit = isLocalPointOnWidget({event.mouseMove.x, event.mouseMove.y});
    if (hit)
    {
      bool entered = !isInState(State::Hovered);
      if (entered)
        mouseEntered(mousePos);
      else
        mouseMoved(mousePos);
      usedEvent = true;
    }
    else if (isInState(State::Hovered))
      mouseLeft(mousePos);
  }
  else if (event.type == WindowEvent::MouseButtonPressed)
  {
    if (event.mouseButton.button == sf::Mouse::Left)
    {
      Vec2 mousePos{event.mouseButton.x, event.mouseButton.y};
      if (isLocalPointOnWidget(mousePos))
      {
        enableState(State::Pressed);
        select(mousePos);
        usedEvent = true;
      }
      else if (mDeselectByEvents && isInState(State::Selected))
      {
        deselect(mousePos);
        usedEvent = usedEvent | mConsumeClickOnDeselect;
      }
    }
  }
  else if (event.type == WindowEvent::MouseButtonReleased)
  {
    if (event.mouseButton.button == sf::Mouse::Left)
    {
      Vec2 mousePos{event.mouseButton.x, event.mouseButton.y};
      if (isInState(State::Pressed) && isLocalPointOnWidget(mousePos))
      {
        clicked(mousePos);
        usedEvent = true;
      }

      disableState(State::Pressed);
    }
  }
  else if (event.type == WindowEvent::KeyPressed)
  {
    if (mDeselectByEvents && isInState(State::Selected) && event.key.code == sf::Keyboard::Escape)
    {
      deselect({0.f, 0.f});
      usedEvent = true;
    }
  }

  return usedEvent;
}
void Widget::addStyleClass(std::string styleClass)
{
  addStyleClass(std::move(styleClass), mStyleClasses.size());
}

void Widget::addStyleClass(std::string styleClass, size_t pos)
{
  if (!hasStyleClass(styleClass))
  {
    mStyleClasses.insert(std::next(mStyleClasses.begin(), pos), std::move(styleClass));
  }
}

void Widget::removeStyleClass(std::string_view styleClass)
{
  auto found = std::find(mStyleClasses.begin(), mStyleClasses.end(), styleClass);
  if (found != mStyleClasses.end())
    mStyleClasses.erase(found);
}

bool Widget::hasStyleClass(std::string_view styleClass)
{
  auto found = std::find(mStyleClasses.begin(), mStyleClasses.end(), styleClass);
  return found != mStyleClasses.end();
}

void Widget::setParent(WPtr parent)
{
  auto oldParent = mParent.lock();
  auto newParent = parent.lock();
  if (oldParent == newParent)
    return;

  mParent = std::move(parent);
  invalidateLayout();
  // Since invalid layout skips if it is already dirty, we need to apply it on the new parent manually here, not nice
  // but avoids doing it every time in invalidateLayout
  if (newParent)
    newParent->invalidateLayout();
}

void Widget::clearParent()
{
  mParent = {};
  invalidateLayout();
}

void Widget::setPreferedSize(Vec2 size)
{
  if (mPreferedSize == size)
    return;
  mPreferedSize = size;
  invalidateLayout();
}

void Widget::setPadding(Padding padding)
{
  mPadding = padding;
  invalidateLayout();
}

void Widget::changeState(State state, bool value)
{
  if (value)
    enableState(state);
  else
    disableState(state);
}
void Widget::enableState(State state)
{
  mState.set(static_cast<size_t>(state));
  addStyleClass(priv::stateToString(state));
}
void Widget::disableState(State state)
{
  mState.reset(static_cast<size_t>(state));
  removeStyleClass(priv::stateToString(state));
}

void Widget::setSize(Vec2 size)
{
  if (mSize == size)
    return;
  mSize = size;
  invalidateLayout();
}

void Widget::setRelativePosition(Vec2 pos)
{
  if (mRelativePosition == pos)
    return;
  mRelativePosition = pos;
  invalidateLayout();
}

void Widget::setGlobalPosition(Vec2 pos)
{
  mGlobalPosition = pos;
}

void Widget::invalidateLayout()
{
  if (isLayoutDirty())
    return;

  mIsLayoutDirty = true;
  auto parent = mParent.lock();
  if (parent)
    parent->invalidateLayout();
}
} // namespace aw::gui
