#pragma once

#include <aw/engine/windowEventForward.hpp>
#include <aw/utils/color.hpp>
#include <aw/utils/math/vector.hpp>

#include <SFML/Window/Event.hpp>
#include <SFML/Window/Window.hpp>

#include <functional>
#include <limits>
#include <memory>
#include <vector>

namespace aw
{
struct Settings;
namespace msg
{
class Bus;
}

class Window
{
public:
  typedef std::function<void(const WindowEvent& event)> EventCallback;
  typedef unsigned EventListenerID;

  enum class ClearType : unsigned
  {
    Color = 1,
    Depth = 2,
    Stencil = 4,
    All = std::numeric_limits<unsigned>::max()
  };

public:
  Window(const Settings& settings, const msg::Bus& bus);
  void handleEvents(/*const EventHandlers& eventHandlers*/);
  void clear(ClearType target = ClearType::All);
  void swapBuffers();
  void applySettings(const Settings& settings);

  sf::Window& getSFMLWindow();
  const sf::Window& getSFMLWindow() const;
  Vec2u getSize() const;
  float getAspectRatio() const;

  bool hasFocus() const;

  void setClearColor(aw::Color color);

private:
  const msg::Bus& mMessageBus;

  sf::Window mWindow;
  bool mHasFocus{true};
};

} // namespace aw
