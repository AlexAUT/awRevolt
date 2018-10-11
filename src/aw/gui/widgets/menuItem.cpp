#include <aw/gui/widgets/menuItem.hpp>

#include <aw/gui/gui.hpp>
#include <aw/gui/style/textStyle.hpp>
#include <aw/gui/utils/eventConvert.hpp>
#include <aw/gui/widgets/menu.hpp>

namespace aw::gui
{
TextStyle defaultStyle{"sans", 10.f, Color(0.5f, 0.5f, 0.5f, 1.0f)};

MenuItem::MenuItem(const GUI& gui, Menu& menu, std::string text)
    : Label(gui, std::move(text)), mMenu(menu), mChildPanel(std::make_shared<Panel>(gui)),
      mChildContainer(std::make_shared<LinearContainer>(gui, Orientation::Vertical))
{
  mChildPanel->setChild(mChildContainer);

  setAlignment({AlignmentH::Center, AlignmentV::Middle});
  setPadding({4.f, 10.f});

  setSelectable(true);
  setConsumeClickOnDeselect(true);

  auto style = getGUI().getTextStyles().getStyle("menuItem");
  assert(style);
  setTextLayout(style);
}

MenuSubItem::SPtr MenuItem::addSubEntry(const std::string& text)
{
  auto newChild = std::make_shared<MenuSubItem>(getGUI(), mMenu, text);

  mChildContainer->addChild(newChild, 0.f);
  newChild->invalidateLayout();
  mChildPanel->updateLayout();
  mChildPanel->setSize(mChildContainer->getMinimalSize());
  mChildPanel->updateLayout();
  invalidateLayout();

  return newChild;
}

bool MenuItem::processEvent(const WindowEvent& event)
{
  if (isInState(State::Selected))
  {
    auto localEvent = convertToLocalEvent(event, *this);
    if (mChildPanel->processEvent(localEvent))
      return true;
  }
  return Label::processEvent(event);
}

void MenuItem::render(Vec2 parentPos)
{
  Widget::render(parentPos);
  getGUI().getRenderer().render(*this);

  if (isInState(State::Selected))
  {
    getGUI().getRenderer().render(*this);
    mChildPanel->render(getGlobalPosition());
  }
}

void MenuItem::updateLayout()
{
  Label::updateLayout();

  // calculate child container position
  auto pos = getSize();
  pos.x = 0;
  mChildPanel->setRelativePosition(pos);
  mChildPanel->updateLayout();
}

void MenuItem::select(Vec2 mousePos)
{
  Widget::select(mousePos);
  mMenu.setSelectedChild(this, this);
}

void MenuItem::deselect(Vec2 mousePos)
{
  Widget::deselect(mousePos);
  mMenu.setSelectedChild(nullptr, this);
}

void MenuItem::mouseEntered(Vec2 mousePos)
{
  Widget::mouseEntered(mousePos);
  // Check if some menu entry is select, if yes, steal it from him
  if (mMenu.getSelectedChild())
  {
    mMenu.getSelectedChild()->deselect({0.f, 0.f});
    select({0.f, 0.f});
  }
}
} // namespace aw::gui
