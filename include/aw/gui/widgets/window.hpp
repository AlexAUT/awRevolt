#pragma once

#include <aw/gui/widgets/bin.hpp>

#include <aw/utils/typeHelper/enumClassBitmask.hpp>

namespace aw::gui
{
class TextStyle;

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
  Window(const GUI& gui, std::string title, Style style = Style::Default);
  virtual ~Window() = default;

  virtual bool processEvent(const WindowEvent& event) override;
  virtual void render(Vec2 parentPos) override;

  void setTitle(std::string title);
  void setStyle(Style style);
  void setTitleTextStyle(const TextStyle* style);

  const std::string& getTitle() const { return mTitle; }
  Style getStyle() const { return mStyle; }
  const TextStyle& getTitleTextStyle() const { return *mTextStyle; }

  virtual void updateLayout() override;

private:
  bool hitTitleBar(Vec2 point);

  bool handleMovement(const WindowEvent& event);

private:
  std::string mTitle;
  Style mStyle;

  const TextStyle* mTextStyle;

  float mTitleBarHeight{0.f};
  bool mDrag{false};
  Vec2 mDrawOffset{0.f};
};

} // namespace aw::gui
ENABLE_BITMASK_OPERATORS(aw::gui::Window::Style);
