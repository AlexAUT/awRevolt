#pragma once

#include <aw/utils/math/vector.hpp>

#include <SFML/Window/Window.hpp>

#include <memory>
#include <vector>

namespace aw
{

class EventHandler;
class Settings;

class Window
{
public:
  Window(const Settings& settings);

  typedef std::vector<std::unique_ptr<EventHandler>> EventHandlers;
  void handleEvents(/*const EventHandlers& eventHandlers*/);
  void swapBuffers();

  void applySettings(const Settings& settings);

  sf::Window& getSFMLWindow();
  const sf::Window& getSFMLWindow() const;
  Vec2u getSize() const;

private:
  void loadOpenGLFunctions();

private:
  sf::Window mWindow;
};

} // namespace aw
