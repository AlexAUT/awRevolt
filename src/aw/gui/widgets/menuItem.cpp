#include <aw/gui/widgets/menuItem.hpp>

#include <aw/gui/gui.hpp>
#include <aw/gui/style/textStyle.hpp>
#include <aw/gui/utils/eventConvert.hpp>
#include <aw/gui/widgets/menu.hpp>

#include <aw/utils/log.hpp>

namespace aw::gui
{
TextStyle defaultStyle{"sans", 10.f, Color(0.5f, 0.5f, 0.5f, 1.0f)};

MenuItem::MenuItem(const GUI& gui, Menu& menu, std::string text, bool isSubElement)
    : Label(gui, std::move(text)), mMenu(menu), mIsSubElement(isSubElement),
      mChildContainer(std::make_shared<LinearContainer>(gui, Orientation::Vertical))
{
  setAlignment({AlignmentH::Center, AlignmentV::Middle});
  setPadding({4.f, 10.f});

  auto style = getGUI().getTextStyles().getStyle("menuItem");
  assert(style);
  setTextLayout(style);
}

MenuSubItem::SPtr MenuItem::addSubEntry(const std::string& text)
{
  auto newChild = std::make_shared<MenuSubItem>(getGUI(), mMenu, text, true);

  mChildContainer->addChild(newChild, 0.f);
  newChild->invalidateLayout();
  mChildContainer->updateLayout();
  mChildContainer->setSize(mChildContainer->getMinimalSize());
  mChildContainer->updateLayout();
  invalidateLayout();

  return newChild;
}

bool MenuItem::processEvent(const WindowEvent& event)
{
  if (isInState(State::Selected))
  {
    auto localEvent = convertToLocalEvent(event, *this);
    if (mChildContainer->processEvent(localEvent))
      return true;
  }
  return Label::processEvent(event);
}

void MenuItem::render(Vec2 parentPos)
{
  Label::render(parentPos);
}

void MenuItem::updateLayout()
{
  Label::updateLayout();

  // calculate child container position
  auto pos = getSize();
  pos.x = 0;
  mChildContainer->setRelativePosition(pos);
  mChildContainer->updateLayout();
}

void MenuItem::select(Vec2 mousePos)
{
  mMenu.setSelectedChild(this, this);
  LogTemp() << "I am now in charge: " << this;
}

void MenuItem::deselect(Vec2 mousePos)
{
  mMenu.setSelectedChild(nullptr, this);
}
}
