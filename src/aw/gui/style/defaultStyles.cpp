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
  styles.addStyle("defaultMuted", {"sans", 20.f, Color(0.4f, 0.4f, 0.4f, 1.0f)});
  styles.addStyle("defaultFail", {"sans", 20.f, Color(0.8f, 0.1f, 0.1f, 1.0f)});
  styles.addStyle("menuItem", {"sans", 15.f, Color(0.8f, 0.8f, 0.8f, 1.0f)});
  styles.addStyle("headline", {"sans-bold", 30.f, Color{0.86f, 0.86f, 0.86f, 0.62f}});
} // namespace aw::gui
} // namespace aw::gui
