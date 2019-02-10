#include <aw/gui/widgets/scrollableBin.hpp>

#include <aw/engine/windowEvent.hpp>
#include <aw/gui/gui.hpp>
#include <aw/gui/utils/eventConvert.hpp>

#include <glm/common.hpp>

namespace aw::gui
{
ScrollableBin::ScrollableBin(const GUI& gui) : Viewport(gui), mViewport(std::make_shared<Viewport>(gui)) {}

bool ScrollableBin::processEvent(const aw::WindowEvent& event)
{
  auto localEvent = convertToLocalEvent(event, *this);
  auto usedEvent = mViewport->processEvent(localEvent);
  usedEvent = Widget::processEvent(event) || usedEvent;

  if (!usedEvent)
  {
    auto child = mViewport->getChild();
    if (child)
    {
      if (event.type == aw::WindowEvent::MouseWheelScrolled)
      {
        if (isLocalPointOnWidget({event.mouseWheelScroll.x, event.mouseWheelScroll.y}))
        {
          auto scroll = mViewport->getVertialOffset() - 10 * event.mouseWheelScroll.delta;
          mViewport->setVerticalOffset(glm::min(child->getSize().y - getContentSize().y, glm::max(0.f, scroll)));
        }
      }
    }
  }

  return usedEvent;
}

void ScrollableBin::render()
{
  mViewport->render();
}

void ScrollableBin::setChild(Widget::SPtr widget)
{
  mViewport->setParent(getSharedPtr());
  mViewport->setChild(widget);
}

void ScrollableBin::updateLayout(Vec2 parentPos)
{
  Widget::updateLayout(parentPos);
  mViewport->setRelativePosition(getPadding().leftTop());
  mViewport->setSize(getContentSize());
  mViewport->updateLayout(getGlobalPosition());
}

void ScrollableBin::invalidateLayout()
{
  Widget::invalidateLayout();
  if (mViewport)
    mViewport->invalidateLayout();
}
} // namespace aw::gui
