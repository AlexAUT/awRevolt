#pragma once

#include <aw/gui/widgets/label.hpp>

namespace aw::gui
{
class MenuItem : public Label
{
public:
  MenuItem(const GUI& gui, std::string text);
  virtual ~MenuItem() = default;

private:
private:
};
} // namespace aw::gui
