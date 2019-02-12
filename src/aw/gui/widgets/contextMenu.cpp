#include <aw/gui/widgets/contextMenu.hpp>

#include <aw/engine/windowEvent.hpp>
#include <aw/gui/gui.hpp>
#include <aw/gui/widgets/label.hpp>

namespace aw::gui
{
ContextMenu::ContextMenu(const GUI& gui) :
    Panel(gui),
    mChildContainer(std::make_shared<LinearContainer>(gui, Orientation::Vertical))
{
  setPadding({10.f, 5.f});
}

void ContextMenu::open(Vec2 anchorPoint)
{
  getGUI().setSelectedWidget(getSharedPtr());
  updateLayout(anchorPoint);
}

void ContextMenu::close()
{
  getGUI().setSelectedWidget(nullptr);
}

void ContextMenu::addItem(std::string id, std::string text)
{
  addItemAt(std::move(id), std::move(text), mChildContainer->getChildren().size());
}

void ContextMenu::addItemAt(std::string id, std::string text, size_t pos)
{
  if (!getChild())
    setChild(mChildContainer);

  // Create child label
  auto newEntry = std::make_shared<Label>(getGUI(), std::move(text));
  newEntry->addStyleClass("contextMenuEntry");
  newEntry->setPadding({5.f, 10.f});

  newEntry->onClick.connect([this, id](auto, auto) { onItemClicked(id); });

  mChildContainer->addChildAt(pos, newEntry);
}

float calcSpawnPos(float clickPos, float screenDim, float size)
{
  if (screenDim - clickPos - size > 0)
  {
    // Spawn to the right/bottom
    return clickPos;
  }
  else if (clickPos - size > 0)
  {
    // Spawn to the left/top
    return clickPos - size;
  }
  else
  {
    // Spawn in the middle (always leaning to right/bottom)
    return screenDim - size;
  }
}

bool ContextMenu::processEvent(const WindowEvent& event)
{
  auto usedEvent = Panel::processEvent(event);
  if (!usedEvent)
  {
    // If the user presses escape close context menu
    if (event.type == WindowEvent::KeyPressed)
    {
      if (event.key.code == sf::Keyboard::Escape)
      {
        close();
        usedEvent = true;
      }
    }
    else if (event.type == WindowEvent::MouseButtonPressed)
    {
      if (!isLocalPointOnWidget({event.mouseButton.x, event.mouseButton.y}))
      {
        close();
        usedEvent = true;
      }
    }
  }

  return usedEvent;
}

void ContextMenu::updateLayout(Vec2 parentPos)
{
  Panel::updateLayout(parentPos);
  // Now calculate spawn position:
  auto screenSize = getGUI().getScreenSize();
  auto minSize = getMinimalSize();
  setSize(minSize);

  Vec2 spawnPosition{calcSpawnPos(parentPos.x, screenSize.x, minSize.x),
                     calcSpawnPos(parentPos.y, screenSize.y, minSize.y)};
  invalidateLayout();
  Panel::updateLayout(spawnPosition);
}
} // namespace aw::gui
