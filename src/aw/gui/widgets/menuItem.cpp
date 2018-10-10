#include <aw/gui/widgets/menuItem.hpp>

#include <aw/gui/gui.hpp>
#include <aw/gui/style/textStyle.hpp>

namespace aw::gui
{
TextStyle defaultStyle{"sans", 10.f, Color(0.5f, 0.5f, 0.5f, 1.0f)};

MenuItem::MenuItem(const GUI& gui, std::string text) : Label(gui, std::move(text))
{
  setAlignment({AlignmentH::Center, AlignmentV::Middle});
  setPadding({4.f, 10.f});

  auto style = getGUI().getTextStyles().getStyle("menuItem");
  assert(style);
  setTextLayout(style);
}
}
