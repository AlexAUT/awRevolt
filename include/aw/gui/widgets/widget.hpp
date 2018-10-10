#pragma once

#include <aw/utils/math/vector.hpp>

#include <bitset>
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

  SPtr getParent() const { return mParent; }
  Vec2 getSize() const { return mSize; }
  Vec2 getPreferedSize() const { return mPreferedSize; }
  Vec2 getRelativePosition() const { return mRelativePosition; }
  Vec2 getGlobalPosition() const { return mGlobalPosition; }

  bool isLayoutDirty() const { return mIsLayoutDirty; }
  virtual void updateLayout() { mIsLayoutDirty = false; }
  virtual Vec2 getMinimalSize() const { return mPreferedSize; }

  bool isLocalPointOnWidget(Vec2 point)
  {
    return (point.x > mRelativePosition.x && point.x < (mRelativePosition.x + mSize.x) &&
            point.y > mRelativePosition.y && point.y < (mRelativePosition.y + mSize.y));
  }

  void changeState(State state, bool value) { mState.set(static_cast<size_t>(state), value); }
  void enableState(State state) { mState.set(static_cast<size_t>(state)); }
  void disableState(State state) { mState.reset(static_cast<size_t>(state)); }

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
  Callback onMouseEnter;
  Callback onMouseLeft;
  Callback onMouseMoved;
  Callback onClick;

private:
  const GUI& mGUI;
  SPtr mParent{nullptr};

  std::bitset<3> mState;

  bool mIsLayoutDirty{true};

  Vec2 mPreferedSize{0.f};
  Vec2 mSize{0.f};

  Vec2 mRelativePosition{0.f};
  Vec2 mGlobalPosition{0.f};

  // Event stuff
public:
  virtual void select(Vec2 mousePos)
  {
    if (onSelect)
      onSelect(*this);
  }
  virtual void mouseEntered(Vec2 mousePos)
  {
    if (onMouseEnter)
      onMouseEnter(*this);
  }
  virtual void mouseLeft(Vec2 mousePos)
  {
    if (onMouseLeft)
      onMouseLeft(*this);
  }
  virtual void mouseMoved(Vec2 mousePos)
  {
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
