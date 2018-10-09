#pragma once

#include <aw/gui/widgets/widget.hpp>
#include <aw/utils/types.hpp>

#include <bitset>
#include <functional>
#include <string>

namespace aw::gui
{
class Button : public Widget
{
public:
  enum class State
  {
    Hovered = 0,
    Pressed = 1
  };

  using Callback = std::function<void(const Button&)>;

public:
  Button(const GUI& gui, std::string text) : Widget(gui), mText(std::move(text)) {}

  virtual bool processEvent(const WindowEvent& event) override;
  void render(Vec2 parentPos) override;

  void setText(std::string text) { mText = std::move(text); }
  const std::string& getText() const { return mText; }

  void changeState(State state, bool value) { mState.set(static_cast<size_t>(state), value); }
  void enableState(State state) { mState.set(static_cast<size_t>(state)); }
  void disableState(State state) { mState.reset(static_cast<size_t>(state)); }

  bool isInState(State state) const { return mState.test(static_cast<size_t>(state)); }

private:
private:
  std::string mText;
  std::bitset<2> mState;

  Callback mOnClick;
};
} // namespace aw::gui
