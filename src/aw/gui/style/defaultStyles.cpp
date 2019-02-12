#include <aw/gui/style/defaultStyles.hpp>

namespace aw::gui
{
void addDefaultElementStyles(StyleManager& styles);

StyleManager getDefaultTextStyles()
{
  StyleManager styles;

  StyleTemplate s;
  s.fontName = "sans";
  s.fontSize = 15.f;
  s.fontColor = Color{0.8f, 0.8f, 0.8f, 1.0f};
  styles.add("defaultFont", s);

  s = StyleTemplate();
  s.fontName = "sans";
  s.fontSize = 15.f;
  s.fontColor = Color{0.4f, 0.4f, 0.4f, 1.0f};
  styles.add("defaultMuted", s);

  s = StyleTemplate();
  s.fontName = "sans";
  s.fontSize = 15.f;
  s.fontColor = Color{0.8f, 0.1f, 0.1f, 1.0f};
  styles.add("defaultFail", s);

  s = StyleTemplate();
  s.fontName = "sans";
  s.fontSize = 12.f;
  s.fontColor = Color{0.8f, 0.8f, 0.8f, 1.0f};
  styles.add("menuItem", s);

  s = StyleTemplate();
  s.fontName = "sans-bold";
  s.fontSize = 25.f;
  s.fontColor = Color{0.86, 0.86f, 0.86f, 0.62f};
  styles.add("headline", s);

  s = StyleTemplate();
  s.fontName = "icon";
  s.fontSize = 22.f;
  s.fontColor = Color{1.f, 1.f, 1.f, 1.f};
  styles.add("icon", s);

  s = StyleTemplate();
  s.fontName = "icon";
  s.fontSize = 50.f;
  s.fontColor = Color{1.f, 1.f, 1.f, 1.f};
  styles.add("fileIcon", s);

  addDefaultElementStyles(styles);

  s = StyleTemplate();
  s.backgroundColor = Color{0.4f, 0.4f, 0.4f, 1.f};
  styles.add("folderViewEntry .hover", s);

  styles.add("fileViewEntry .hover", s);

  s = StyleTemplate();
  s.backgroundColor = Color{0.1f, 0.1f, 0.3f, 1.f};
  styles.add("folderViewEntry .select", s);

  s = StyleTemplate();
  s.backgroundColor = Color{1.f, 0.5f, 0.5f, 1.f};
  s.fontColor = Color{0.f, 0.f, 0.f, 0.8f};
  styles.add("contextMenuEntry .hover", s);

  return styles;
}

void addDefaultElementStyles(StyleManager& styles)
{
  auto menuItem = styles.getCopy("defaultFont");
  styles.add("#MenuItem", menuItem);

  auto menuSubItem = styles.getCopy("defaultFont");
  styles.add("#MenuSubItem", menuSubItem);

  auto label = styles.getCopy("defaultFont");
  styles.add("#Label", label);

  auto transparent = StyleTemplate();
  transparent.backgroundColor = Color{0.f, 0.f, 0.f, 0.f};
  styles.add("#LinearContainer", transparent);
  styles.add("#TileContainer", transparent);
  styles.add("#Menu", transparent);

  auto panel = StyleTemplate();
  panel.backgroundColor = Color{0.109f, 0.117f, 0.1333f, 0.753f};
  styles.add("#Panel", panel);

  auto contextMenu = StyleTemplate();
  contextMenu.backgroundColor = Color{0.3, 0.3, 0.35, 1.f};
  styles.add("#ContextMenu", contextMenu);

  auto menu = styles.getCopy("#Panel");
  styles.add("#Panlel", panel);
}
} // namespace aw::gui
