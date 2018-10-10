#include <aw/gui/widgets/label.hpp>

#include <aw/gui/gui.hpp>
#include <aw/gui/renderer/nanovgRenderer.hpp>
#include <aw/utils/log.hpp>

#include <glm/common.hpp>

namespace aw::gui
{
Label::Label(const GUI& gui, std::string text)
    : Widget(gui), mText(text), mTextLayout(getGUI().getTextStyles().getStyle("default"))
{
  assert(mTextLayout);
}

void Label::setText(std::string text)
{
  mText = std::move(text);
  invalidateLayout();
}

void Label::setTextLayout(const TextStyle* layout)
{
  assert(layout);
  mTextLayout = layout;
  invalidateLayout();
}

void Label::render(Vec2 parentPos)
{
  assert(!isLayoutDirty());
  Widget::render(parentPos);
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

void Label::setPadding(Padding padding)
{
  mPadding = padding;
  invalidateLayout();
}

void Label::updateLayout()
{
  Widget::updateLayout();
  // Update the cached minimum size
  // (textsize + padding) or prefered size
  mMinimumSize = getGUI().getRenderer().calculateTextSize(mText, *mTextLayout);
  mMinimumSize.x += mPadding.left + mPadding.right;
  mMinimumSize.y += mPadding.top + mPadding.bottom;

  mMinimumSize = glm::max(mMinimumSize, getPreferedSize());
}

Vec2 Label::getMinimalSize() const
{
  return mMinimumSize;
}
} // namespace aw::gui
