#include <aw/gui/widgets/button.hpp>

#include <aw/gui/gui.hpp>
#include <aw/gui/renderer/nanovgRenderer.hpp>
#include <aw/utils/log.hpp>

#include <glm/common.hpp>

#include <cassert>

namespace aw::gui
{
Button::Button(const GUI& gui, std::string text)
    : Widget(gui), mText(std::move(text)), mTextLayout(getGUI().getTextStyles().getStyle("default"))
{
  assert(mTextLayout);
  setPadding({5.f});
}

void Button::render(Vec2 parentPos)
{
  Widget::render(parentPos);
  getGUI().getRenderer().render(*this);
}

void Button::setTextLayout(const TextStyle* layout)
{
  assert(layout);
  mTextLayout = layout;
  invalidateLayout();
}

void Button::updateLayout()
{
  Widget::updateLayout();
  // Update the cached minimum size
  // (textsize + padding) or prefered size
  mMinimumSize = getGUI().getRenderer().calculateTextSize(mText, *mTextLayout);
  LogTemp() << "mMinimumSize : " << mMinimumSize;
  auto& padding = getPadding();
  mMinimumSize.x += padding.left + padding.right;
  mMinimumSize.y += padding.top + padding.bottom;
  LogTemp() << "mMinimumSize after: " << mMinimumSize;

  mMinimumSize = glm::max(mMinimumSize, getPreferedSize());
}

Vec2 Button::getMinimalSize() const
{
  return mMinimumSize;
}
} // namespace aw::gui
