#pragma once

#include <aw/gui/style/padding.hpp>
#include <aw/utils/math/vector.hpp>

#include <bitset>
#include <functional>
#include <memory>

#include <aw/engine/windowEventForward.hpp>

namespace aw::gui
{
class GUI;

class Widget : public std::enable_shared_from_this<Widget>
{
public:
  using SPtr = std::shared_ptr<Widget>;
  using CSPtr = std::shared_ptr<const Widget>;

  enum class State
  {
    Hovered = 0,
    Pressed = 1,
    Selected = 2,
  };

  using Callback = std::function<void(const Widget&)>;

public:
  Widget(const GUI& gui) : mGUI(gui) {}
  virtual ~Widget() = default;

  SPtr getSharedPtr() { return shared_from_this(); }
  CSPtr getConstSharedPtr() { return shared_from_this(); }

  virtual bool processEvent(const WindowEvent& event);
  virtual void update(float delta) {}
  virtual void render(Vec2 parentPos) { setGlobalPosition(getRelativePosition() + parentPos); }

  const GUI& getGUI() const { return mGUI; }

  void setPreferedSize(Vec2 size);
  void setPadding(Padding padding);
  void changeState(State state, bool value) { mState.set(static_cast<size_t>(state), value); }
  void enableState(State state) { mState.set(static_cast<size_t>(state)); }
  void disableState(State state) { mState.reset(static_cast<size_t>(state)); }
  void setSelectable(bool value) { mSelectable = value; }
  void setConsumeEvent(bool value) { mConsumeEvent = value; }
  void setConsumeClickOnDeselect(bool value) { mConsumeClickOnDeselect = value; }

  SPtr getParent() const { return mParent; }
  Vec2 getSize() const { return mSize; }
  Vec2 getPreferedSize() const { return mPreferedSize; }
  Vec2 getRelativePosition() const { return mRelativePosition; }
  Vec2 getGlobalPosition() const { return mGlobalPosition; }
  const Padding& getPadding() const { return mPadding; }

  bool isLayoutDirty() const { return mIsLayoutDirty; }
  virtual void updateLayout() { mIsLayoutDirty = false; }
  virtual Vec2 getMinimalSize() const { return mPreferedSize; }

  bool isLocalPointOnWidget(Vec2 point)
  {
    return (point.x > mRelativePosition.x && point.x < (mRelativePosition.x + mSize.x) &&
            point.y > mRelativePosition.y && point.y < (mRelativePosition.y + mSize.y));
  }

  bool isInState(State state) const { return mState.test(static_cast<size_t>(state)); }

public:
  // These should be called by the layouter, calling them may result in wrong rendering
  void setParent(SPtr parent);

  void setSize(Vec2 size);
  void setRelativePosition(Vec2 pos);
  void setGlobalPosition(Vec2 pos);

  virtual void invalidateLayout();

public:
  // Callback (expose them directly to the user)
  Callback onSelect;
  Callback onDeselect;
  Callback onMouseEnter;
  Callback onMouseLeft;
  Callback onMouseMoved;
  Callback onClick;

private:
  const GUI& mGUI;
  SPtr mParent{nullptr};

  std::bitset<3> mState;

  bool mIsLayoutDirty{true};

  bool mSelectable{false};
  bool mConsumeEvent{true};
  bool mConsumeClickOnDeselect{false};
  Vec2 mPreferedSize{0.f};
  Vec2 mSize{0.f};

  Vec2 mRelativePosition{0.f};
  mutable Vec2 mGlobalPosition{0.f};

  Padding mPadding;

  // Event stuff
public:
  virtual void select(Vec2 mousePos)
  {
    if (mSelectable)
      enableState(State::Selected);
    if (onSelect)
      onSelect(*this);
  }
  virtual void deselect(Vec2 mousePos)
  {
    disableState(State::Selected);
    if (onDeselect)
      onDeselect(*this);
  }
  virtual void mouseEntered(Vec2 mousePos)
  {
    enableState(State::Hovered);
    if (onMouseEnter)
      onMouseEnter(*this);
  }
  virtual void mouseLeft(Vec2 mousePos)
  {
    disableState(State::Hovered);
    if (onMouseLeft)
      onMouseLeft(*this);
  }
  virtual void mouseMoved(Vec2 mousePos)
  {
    enableState(State::Hovered); // Safety reasons
    if (onMouseMoved)
      onMouseMoved(*this);
  }
  virtual void clicked(Vec2 mousePos)
  {
    if (onClick)
      onClick(*this);
  }
};
} // namespace aw::gui
