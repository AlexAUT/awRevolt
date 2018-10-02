#include <aw/engine/window.hpp>

#include <aw/engine/settings.hpp>
#include <aw/opengl/opengl.hpp>

#include <aw/utils/log.hpp>

#include <SFML/Window/Event.hpp>

#include <chrono>
#include <thread>

namespace aw
{

Window::Window(const Settings& settings)
{
  applySettings(settings);
}

void Window::handleEvents(/*const EventHandlers& eventHandlers*/)
{
  sf::Event event;
  while (mWindow.pollEvent(event))
  {
    if (event.type == sf::Event::LostFocus || event.type == sf::Event::MouseLeft)
      mHasFocus = false;
    if (event.type == sf::Event::GainedFocus || event.type == sf::Event::MouseEntered)
      mHasFocus = true;
    for (auto& callback : mEventListeners)
      callback.second(event);
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

  LogTemp() << "Grab cursor: " << settings.grabCursor;
  mWindow.setMouseCursorGrabbed(settings.grabCursor);
  mWindow.setMouseCursorVisible(settings.cursorVisible);

#ifdef AW_ANDROID
  // We need to wait for the EGL context to be created, otherwise opengl calls will fail silently!
  std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  handleEvents();
  mWindow.display();
#endif
}

Window::EventListenerID Window::registerEventListener(EventCallback callback)
{
  mEventListeners.push_back({mListenerID, callback});
  return mListenerID++;
}

void Window::unregisterEventListener(EventListenerID id)
{
  for (auto it = mEventListeners.begin(); it != mEventListeners.end(); it++)
  {
    if (it->first == id)
    {
      *it = *(mEventListeners.end() - 1);
      mEventListeners.pop_back();
      break;
    }
  }
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

bool Window::hasFocus() const
{
  return mHasFocus;
}

} // namespace aw
