#pragma once

#include <aw/utils/math/vector.hpp>

#include <SFML/Window/Event.hpp>
#include <SFML/Window/Window.hpp>

#include <functional>
#include <memory>
#include <vector>

namespace aw
{

class Settings;

typedef sf::Event WindowEvent;

class Window
{
public:
  typedef std::function<void(const WindowEvent& event)> EventCallback;
  typedef unsigned EventListenerID;

public:
  Window(const Settings& settings);

  void handleEvents(/*const EventHandlers& eventHandlers*/);
  void swapBuffers();
  void applySettings(const Settings& settings);

  EventListenerID registerEventListener(EventCallback callback);
  void unregisterEventListener(EventListenerID id);

  sf::Window& getSFMLWindow();
  const sf::Window& getSFMLWindow() const;
  Vec2u getSize() const;

private:
  void loadOpenGLFunctions();

private:
  sf::Window mWindow;

  unsigned mListenerID{0};
  std::vector<std::pair<int, EventCallback>> mEventListeners;
};

} // namespace aw
