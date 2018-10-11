#include <aw/gui/style/defaultStyles.hpp>

#include <aw/gui/gui.hpp>

namespace aw::gui
{
void applyTextStyles(TextStyleManager& manager);

void applyDefaultStyles(GUI& gui)
{
  applyTextStyles(gui.getTextStyles());
}

void applyTextStyles(TextStyleManager& styles)
{
  styles.addStyle("default", {"sans", 20.f, Color(0.8f, 0.8f, 0.8f, 1.0f)});
  styles.addStyle("menuItem", {"sans", 15.f, Color(0.8f, 0.8f, 0.8f, 1.0f)});
  styles.addStyle("headline", {"sans-bold", 30.f, Color{0.86f, 0.86f, 0.86f, 0.62f}});
}
}
