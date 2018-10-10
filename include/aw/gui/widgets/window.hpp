#pragma once

#include <aw/gui/widgets/bin.hpp>

#include <aw/utils/enumClassBitmask.hpp>

namespace aw::gui
{
class Window : public Bin
{
public:
  enum class Style
  {
    None = 0,
    Titlebar = 1,
    Moveable = 2,
    Default = Titlebar | Moveable,
  };

public:
  Window(const GUI& gui, std::string title, Style style = Style::Default)
      : Bin(gui, {32.f, 2.f, 2.f, 2.f}), mTitle(std::move(title)), mStyle(style)
  {
  }
  virtual ~Window() = default;

  virtual bool processEvent(const WindowEvent& event) override;
  virtual void render(Vec2 parentPos) override;

  void setTitle(std::string title);
  void setStyle(Style style);

  const std::string& getTitle();
  Style getStyle();

  virtual void updateLayout();

private:
  bool hitTitleBar(Vec2 point);

  bool handleMovement(const WindowEvent& event);

private:
  std::string mTitle;
  Style mStyle;

  bool mDrag{false};
  Vec2 mDrawOffset{0.f};
};

} // namespace aw::gui
ENABLE_BITMASK_OPERATORS(aw::gui::Window::Style);
