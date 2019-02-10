#include <aw/gui/style/defaultStyles.hpp>

namespace aw::gui
{
StyleManager getDefaultTextStyles()
{
  StyleManager styles;

  StyleTemplate s;
  s.fontName = "sans";
  s.fontSize = 15.f;
  s.fontColor = Color{0.8f, 0.8f, 0.8f, 1.0f};
  s.backgroundColor = Color{0.f, 0.f, 0.f, 0.f};
  styles.addStyle("default", s);

  s = StyleTemplate();
  s.fontName = "sans";
  s.fontSize = 15.f;
  s.fontColor = Color{0.4f, 0.4f, 0.4f, 1.0f};
  styles.addStyle("defaultMuted", s);

  s = StyleTemplate();
  s.fontName = "sans";
  s.fontSize = 15.f;
  s.fontColor = Color{0.8f, 0.1f, 0.1f, 1.0f};
  styles.addStyle("defaultFail", s);

  s = StyleTemplate();
  s.fontName = "sans";
  s.fontSize = 12.f;
  s.fontColor = Color{0.8f, 0.8f, 0.8f, 1.0f};
  styles.addStyle("menuItem", s);

  s = StyleTemplate();
  s.fontName = "sans-bold";
  s.fontSize = 25.f;
  s.fontColor = Color{0.86, 0.86f, 0.86f, 0.62f};
  styles.addStyle("headline", s);

  s = StyleTemplate();
  s.fontName = "icon";
  s.fontSize = 22.f;
  s.fontColor = Color{1.f, 1.f, 1.f, 1.f};
  styles.addStyle("icon", s);

  s = StyleTemplate();
  s.fontName = "icon";
  s.fontSize = 50.f;
  s.fontColor = Color{1.f, 1.f, 1.f, 1.f};
  styles.addStyle("fileIcon", s);

  s = StyleTemplate();
  s.backgroundColor = Color{0.4f, 0.4f, 0.4f, 1.f};
  styles.addStyle("folderViewEntry hover", s);

  styles.addStyle("fileViewEntry hover", s);

  s = StyleTemplate();
  s.backgroundColor = Color{0.1f, 0.1f, 0.3f, 1.f};
  styles.addStyle("folderViewEntry select", s);

  return styles;
}
} // namespace aw::gui
