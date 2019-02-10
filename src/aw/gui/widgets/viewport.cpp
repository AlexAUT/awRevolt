#include <aw/gui/widgets/viewport.hpp>

#include <aw/engine/windowEvent.hpp>
#include <aw/gui/gui.hpp>
#include <aw/gui/utils/eventConvert.hpp>

#include <glm/common.hpp>

namespace aw::gui
{
Viewport::Viewport(const GUI& gui) : Widget(gui) {}

bool Viewport::processEvent(const aw::WindowEvent& event)
{
  auto usedEvent = Widget::processEvent(event);
  if (mChild)
  {
    auto childEvent = convertToLocalEvent(event, *this);
    switch (childEvent.type)
    {
    case WindowEvent::MouseMoved:
      if (!isLocalPointOnWidget({event.mouseMove.x, event.mouseMove.y}))
      {
        childEvent.mouseMove.y = -mVerticalOffset - 1;
        childEvent.mouseMove.x = -mVerticalOffset - 1;
      }
      break;
    case WindowEvent::MouseButtonPressed:
    case WindowEvent::MouseButtonReleased:
      if (!isLocalPointOnWidget({event.mouseButton.x, event.mouseButton.y}))
      {
        childEvent.mouseButton.y = -mVerticalOffset - 1;
        childEvent.mouseButton.x = -mVerticalOffset - 1;
      }
      break;
    case WindowEvent::MouseWheelScrolled:
      if (!isLocalPointOnWidget({event.mouseWheelScroll.x, event.mouseWheelScroll.y}))
      {
        childEvent.mouseWheelScroll.y = -mVerticalOffset - 1;
        childEvent.mouseWheelScroll.x = -mVerticalOffset - 1;
      }
      break;
    default:
      break;
    }

    usedEvent = mChild->processEvent(childEvent) || usedEvent;
  }

  return usedEvent;
}

void Viewport::render()
{
  getGUI().getRenderer().pushViewport(getGlobalPosition() + getPadding().leftTop(),
                                      getSize() - getPadding().horizontalVertical());
  if (mChild)
    mChild->render();
  getGUI().getRenderer().popViewport();
}

void Viewport::updateLayout(Vec2 parentPos)
{
  if (!isLayoutDirty())
    return;

  Widget::updateLayout(parentPos);

  if (mChild)
  {
    mChild->setRelativePosition(getPadding().leftTop() - Vec2{mHorizontalOffset, mVerticalOffset});
    auto childSize = glm::max(getSize() - getPadding().horizontalVertical(), mChild->getMinimalSize());
    mChild->setSize(childSize);
    mChild->updateLayout(parentPos);
  }

  Widget::updateLayout(parentPos);
}

void Viewport::setChild(Widget::SPtr child)
{
  if (mChild == child)
    return;

  if (mChild)
    mChild->clearParent();

  mChild = std::move(child);
  mChild->setParent(getSharedPtr());
}

void Viewport::setHorizontalOffset(float value)
{
  mHorizontalOffset = value;
  invalidateLayout();
}

void Viewport::setVerticalOffset(float value)
{
  mVerticalOffset = value;
  invalidateLayout();
}

void Viewport::invalidateLayout()
{
  Widget::invalidateLayout();
  if (mChild)
    mChild->invalidateLayout();
}

} // namespace aw::gui
