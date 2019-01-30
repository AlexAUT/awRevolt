#include <aw/engine/window.hpp>

#include <aw/engine/settings.hpp>
#include <aw/engine/windowEvent.hpp>
#include <aw/opengl/opengl.hpp>
#include <aw/utils/log.hpp>
#include <aw/utils/messageBus/messageBus.hpp>

#include <chrono>
#include <thread>

namespace aw
{

Window::Window(const Settings& settings, const msg::Bus& bus) : mMessageBus(bus)
{
  applySettings(settings);
}

void Window::handleEvents(/*const EventHandlers& eventHandlers*/)
{
  WindowEvent event;
  while (mWindow.pollEvent(event))
  {
    if (event.type == sf::Event::LostFocus || event.type == sf::Event::MouseLeft)
      mHasFocus = false;
    if (event.type == sf::Event::GainedFocus || event.type == sf::Event::MouseEntered)
      mHasFocus = true;

    mMessageBus.broadcast<WindowEvent>(event);
  }
}

void Window::clear(ClearType targets)
{
  unsigned val = static_cast<unsigned>(targets);
  GLbitfield toClear = (val & static_cast<unsigned>(ClearType::Color) ? GL_COLOR_BUFFER_BIT : GL_NONE) |
                       (val & static_cast<unsigned>(ClearType::Depth) ? GL_DEPTH_BUFFER_BIT : GL_NONE) |
                       (val & static_cast<unsigned>(ClearType::Stencil) ? GL_STENCIL_BUFFER_BIT : GL_NONE);
  GL_CHECK(glClear(toClear));
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

#ifdef AW_ANDROID
  // We need to wait for the EGL context to be created, otherwise opengl calls will fail silently!
  std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  handleEvents();
  mWindow.display();
#endif
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

float Window::getAspectRatio() const
{
  auto size = mWindow.getSize();
  return static_cast<float>(size.x) / static_cast<float>(size.y);
}

bool Window::hasFocus() const
{
  return mHasFocus;
}

void Window::setClearColor(aw::Color color)
{
  GL_CHECK(glClearColor(color.r, color.g, color.b, color.a));
}

} // namespace aw
