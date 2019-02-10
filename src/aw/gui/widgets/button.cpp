#include <aw/gui/widgets/button.hpp>

#include <aw/gui/gui.hpp>
#include <aw/gui/renderer/nanovgRenderer.hpp>
#include <aw/utils/log.hpp>

#include <glm/common.hpp>

#include <cassert>

namespace aw::gui
{
Button::Button(const GUI& gui, std::string text) : Widget(gui), mText(std::move(text))
{
  setPadding({5.f});
}

void Button::render()
{
  Widget::render();
  getGUI().getRenderer().render(*this);
}

void Button::updateLayout(aw::Vec2 parentPos)
{
  Widget::updateLayout(parentPos);
  // Update the cached minimum size
  // (textsize + padding) or prefered size
  mMinimumSize = getGUI().getRenderer().calculateTextSize(mText, getStyleClasses());
  auto& padding = getPadding();
  mMinimumSize.x += padding.left + padding.right;
  mMinimumSize.y += padding.top + padding.bottom;

  mMinimumSize = glm::max(mMinimumSize, getPreferedSize());
}

Vec2 Button::getMinimalSize() const
{
  return mMinimumSize;
}
} // namespace aw::gui
