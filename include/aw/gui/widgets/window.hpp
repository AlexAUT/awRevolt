#pragma once

#include <aw/gui/widgets/bin.hpp>

#include <aw/utils/typeHelper/enumClassBitmask.hpp>

namespace aw::gui
{
struct TextStyle;

class Window : public Bin
{
public:
  enum class Style
  {
    None = 0,
    Moveable = 1,
    Default = Moveable,
  };

public:
  Window(const GUI& gui, std::string title, Window::Style style = Window::Style::Default);
  virtual ~Window() = default;

  virtual bool processEvent(const WindowEvent& event) override;
  virtual void render() override;

  void setTitle(std::string title);
  void setStyle(Style style);

  const std::string& getTitle() const { return mTitle; }
  Style getStyle() const { return mStyle; }

  virtual void updateLayout(aw::Vec2 parentPos) override;

private:
  bool hitTitleBar(Vec2 point);

  bool handleMovement(const WindowEvent& event);

private:
  std::string mTitle;
  Style mStyle;

  float mTitleBarHeight{0.f};
  bool mDrag{false};
  Vec2 mDrawOffset{0.f};
};

} // namespace aw::gui
ENABLE_BITMASK_OPERATORS(aw::gui::Window::Style);
