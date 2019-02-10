#include <aw/gui/widgets/label.hpp>

#include <aw/gui/gui.hpp>
#include <aw/gui/renderer/nanovgRenderer.hpp>

#include <glm/common.hpp>

namespace aw::gui
{
Label::Label(const GUI& gui, std::string text) : Widget(gui), mText(text)
{
  // Set minimal size
  updateLayout(aw::Vec2{0.f});
}

void Label::setText(std::string text)
{
  mText = std::move(text);
  invalidateLayout();
}

void Label::render()
{
  Widget::render();
  getGUI().getRenderer().render(*this);
}

void Label::setAlignment(Alignment alignment)
{
  mAlignment = alignment;
  invalidateLayout();
}

void Label::setAlignmentH(AlignmentH alignment)
{
  mAlignment.horizontal = alignment;
  invalidateLayout();
}

void Label::setAlignmentV(AlignmentV alignment)
{
  mAlignment.vertical = alignment;
  invalidateLayout();
}

void Label::updateLayout(aw::Vec2 parentPos)
{
  Widget::updateLayout(parentPos);
  // Update the cached minimum size
  // (textsize + padding) or prefered size
  mMinimumSize = getGUI().getRenderer().calculateTextSize(mText, getStyleClasses());
  mMinimumSize += getPadding().horizontalVertical();

  mMinimumSize = glm::max(mMinimumSize, getPreferedSize());
}

Vec2 Label::getMinimalSize() const
{
  return mMinimumSize;
}
} // namespace aw::gui
