#include <aw/gui/widgets/bin.hpp>

#include <aw/gui/utils/eventConvert.hpp>

#include <glm/common.hpp>

namespace aw::gui
{
void Bin::update(float delta)
{
  if (mChild)
    mChild->update(delta);
}

bool Bin::processEvent(const WindowEvent& event)
{
  if (mChild)
  {
    auto localEvent = convertToLocalEvent(event, *this);
    if (mChild->processEvent(localEvent))
      return true;
  }
  return Widget::processEvent(event);
}

void Bin::render(Vec2 parentPos)
{
  Widget::render(parentPos);
  if (mChild)
    mChild->render(getGlobalPosition());
}

void Bin::updateLayout()
{
  if (!isLayoutDirty())
    return;

  if (mChild)
  {
    mChild->setSize(calculateChildSize());
    mChild->setRelativePosition(calculateChildRelPosition());
    mChild->updateLayout();
  }
  Widget::updateLayout();
}

Vec2 Bin::getMinimalSize() const
{
  auto padding = getPadding();
  Vec2 advance{padding.left + padding.right, padding.top + padding.bottom};
  if (mChild)
    return glm::max(mChild->getMinimalSize(), Widget::getMinimalSize()) + advance;
  return Widget::getMinimalSize() + advance;
}

void Bin::setChild(Widget::SPtr ptr)
{
  if (mChild == ptr)
    return;

  if (mChild)
    mChild->setParent(nullptr);

  mChild = std::move(ptr);
  if (mChild)
    mChild->setParent(getSharedPtr());
}

Vec2 Bin::calculateChildRelPosition() const
{
  return {getPadding().left, getPadding().top};
}

Vec2 Bin::calculateChildSize() const
{
  auto size = getSize();
  auto& padding = getPadding();
  return {size.x - padding.left - padding.right, size.y - padding.top - padding.bottom};
}
} // namespace aw::gui
