#include <aw/engine/window.hpp>

#include <aw/engine/settings.hpp>
#include <aw/opengl/loader.hpp>

#include <SFML/Window/Event.hpp>

namespace aw
{

Window::Window(const Settings& settings)
{
  applySettings(settings);
  loadOpenGLFunctions();
}

void Window::handleEvents(/*const EventHandlers& eventHandlers*/)
{
  sf::Event event;
  while (mWindow.pollEvent(event))
  {
    // for (auto& handler : eventHandlers)
    //  handler->processWindowEvent(event);
  }
}

void Window::swapBuffers()
{
  mWindow.display();
}

void Window::applySettings(const Settings& settings)
{
  sf::VideoMode videoMode{
      settings.resolution.x,
      settings.resolution.y,
      settings.bitsPerPixel,
  };

  sf::ContextSettings contextSettings{settings.depthBits,
                                      settings.stencilBits,
                                      settings.antialiasing,
                                      settings.openglMajor,
                                      settings.openglMinor,
                                      static_cast<unsigned>(sf::ContextSettings::Default |
                                                            (settings.coreContext ? sf::ContextSettings::Core : 0) |
                                                            (settings.debugContext ? sf::ContextSettings::Debug : 0))};

  mWindow.create(videoMode, settings.applicationName, sf::Style::Default, contextSettings);
  if (settings.vsync)
    mWindow.setVerticalSyncEnabled(true);
  else
    mWindow.setFramerateLimit(settings.frameLimit);

  mWindow.setMouseCursorGrabbed(settings.grabCursor);
  mWindow.setMouseCursorVisible(settings.cursorVisible);
}

sf::Window& Window::getSFMLWindow()
{
  return mWindow;
}

const sf::Window& Window::getSFMLWindow() const
{
  return mWindow;
}

Vec2u Window::getSize() const
{
  auto size = mWindow.getSize();
  return {static_cast<unsigned>(size.x), static_cast<unsigned>(size.y)};
}

void Window::loadOpenGLFunctions()
{
  opengl::init();
}

} // namespace aw
