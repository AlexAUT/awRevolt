#pragma once

#include <aw/gui/widgets/bin.hpp>

namespace aw::gui
{
class Window : public Bin
{
public:
  Window(const GUI& gui, std::string title) : Bin(gui, {32.f, 2.f, 2.f, 2.f}), mTitle(std::move(title)) {}
  virtual ~Window() = default;

  virtual bool processEvent(const WindowEvent& event) override;
  virtual void render(Vec2 parentPos) override;

  void setTitle(std::string title) { mTitle = std::move(title); }

  const std::string& getTitle() const { return mTitle; }

private:
  bool hitTitleBar(Vec2 point);

private:
  std::string mTitle;

  bool mDrag{false};
  Vec2 mDrawOffset{0.f};
};

} // namespace aw::gui
