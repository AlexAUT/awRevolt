#pragma once

#include <aw/gui/style/padding.hpp>
#include <aw/gui/utils/signal.hpp>
#include <aw/utils/color.hpp>
#include <aw/utils/math/vector.hpp>

#include <bitset>
#include <functional>
#include <memory>

#include <aw/engine/windowEventForward.hpp>

namespace aw::gui
{
class GUI;

#define AW_GUI_CLASS_NAME(name)                                                                                        \
  virtual const std::string& getElementId() const override                                                             \
                                                                                                                       \
  {                                                                                                                    \
    static std::string id = "#" #name;                                                                                 \
    return id;                                                                                                         \
  }

class Widget : public std::enable_shared_from_this<Widget>
{
public:
  // Define it here manually, because of the override keyword, in child classes use the macro above
  virtual const std::string& getElementId() const
  {
    static std::string id = "#Widget";
    return id;
  }
  using SPtr = std::shared_ptr<Widget>;
  using CSPtr = std::shared_ptr<const Widget>;
  using WPtr = std::weak_ptr<Widget>;

  enum class State
  {
    Hovered = 0,
    Selected = 1,
    Pressed = 2,
    // Do not use count and it should always be last (needed until we finally get reflection)
    _COUNT = 3
  };

  using Signal = aw::gui::Signal<void(Widget&)>;
  using MousePosSignal = aw::gui::Signal<void(Widget&, Vec2)>;

public:
  Widget(const GUI& gui) : mGUI(gui) {}
  virtual ~Widget() = default;

  SPtr getSharedPtr() { return shared_from_this(); }
  CSPtr getConstSharedPtr() { return shared_from_this(); }

  virtual bool processEvent(const WindowEvent& event);
  virtual void update(float delta) {}
  virtual void render() { assert(!isLayoutDirty()); }

  const GUI& getGUI() const { return mGUI; }

  void addStyleClass(std::string styleClass);
  void addStyleClass(std::string styleClass, size_t pos);
  void removeStyleClass(std::string_view styleClass);
  bool hasStyleClass(std::string_view styleClass);
  const std::vector<std::string> getStyleClasses() const { return mStyleClasses; }

  void setPreferedSize(Vec2 size);
  void setPadding(Padding padding);
  void changeState(State state, bool value);
  void enableState(State state);
  void disableState(State state);
  void setSelectable(bool value) { mSelectable = value; }
  void setDeselectableByMouseEvent(bool value) { mDeselectByEvents = value; }
  void setIgnoreEvents(bool value) { mIgnoreEvents = value; }
  void setConsumeClickOnDeselect(bool value) { mConsumeClickOnDeselect = value; }

  WPtr getParent() const { return mParent; }
  Vec2 getSize() const { return mSize; }
  Vec2 getContentSize() const { return mSize - getPadding().horizontalVertical(); }
  Vec2 getPreferedSize() const { return mPreferedSize; }
  Vec2 getRelativePosition() const { return mRelativePosition; }
  Vec2 getGlobalPosition() const { return mGlobalPosition; }
  const Padding& getPadding() const { return mPadding; }

  bool isLayoutDirty() const { return mIsLayoutDirty; }
  virtual void updateLayout(aw::Vec2 parentPos)
  {
    setGlobalPosition(parentPos + getRelativePosition());
    mIsLayoutDirty = false;
  }
  virtual Vec2 getMinimalSize() const { return mPreferedSize + mPadding.horizontalVertical(); }

  bool isLocalPointOnWidget(Vec2 point)
  {
    return (point.x >= mRelativePosition.x && point.x < (mRelativePosition.x + mSize.x) &&
            point.y >= mRelativePosition.y && point.y < (mRelativePosition.y + mSize.y));
  }

  bool isInState(State state) const { return mState.test(static_cast<size_t>(state)); }
  unsigned getCombinedState() const { return static_cast<unsigned>(mState.to_ulong()); }

public:
  // These should be called by the layouter, calling them may result in wrong rendering
  void setParent(WPtr parent);
  void clearParent();

  void setSize(Vec2 size);
  void setRelativePosition(Vec2 pos);
  void setGlobalPosition(Vec2 pos);

  virtual void invalidateLayout();

public:
  // Callback (expose them directly to the user)
  MousePosSignal onSelect;
  MousePosSignal onDeselect;
  MousePosSignal onMouseEnter;
  MousePosSignal onMouseLeft;
  MousePosSignal onMouseMoved;
  MousePosSignal onClick;
  MousePosSignal onRightClick;

private:
  const GUI& mGUI;
  WPtr mParent{};

  std::vector<std::string> mStyleClasses;

  std::bitset<3> mState;

  bool mIsLayoutDirty{true};

  bool mSelectable{false};
  bool mDeselectByEvents{true};
  bool mIgnoreEvents{false};
  bool mConsumeClickOnDeselect{false};
  Vec2 mPreferedSize{0.f};
  Vec2 mSize{0.f};

  Vec2 mRelativePosition{0.f};
  mutable Vec2 mGlobalPosition{0.f};

  Padding mPadding;

  // Event stuff
public:
  virtual void select(Vec2 mousePos = {})
  {
    if (mSelectable && !isInState(State::Selected))
    {
      enableState(State::Selected);
      onSelect(*this, mousePos);
    }
  }
  virtual void deselect(Vec2 mousePos = {})
  {
    if (isInState(State::Selected))
    {
      disableState(State::Selected);
      onDeselect(*this, mousePos);
    }
  }
  virtual void mouseEntered(Vec2 mousePos)
  {
    enableState(State::Hovered);
    onMouseEnter(*this, mousePos);
  }
  virtual void mouseLeft(Vec2 mousePos)
  {
    disableState(State::Hovered);
    onMouseLeft(*this, mousePos);
  }
  virtual void mouseMoved(Vec2 mousePos)
  {
    enableState(State::Hovered); // Safety reasons
    onMouseMoved(*this, mousePos);
  }
  virtual void clicked(Vec2 mousePos) { onClick(*this, mousePos); }
  virtual void rightClicked(Vec2 mousePos) { onRightClick(*this, mousePos); }
};
} // namespace aw::gui
