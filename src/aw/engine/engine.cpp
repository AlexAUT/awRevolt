#include <aw/engine/engine.hpp>

namespace aw
{
Engine::Engine() : mSettings(priv::loadSettings()), mWindow(mSettings), mRunning(true)
{
}

int Engine::run()
{
  mUpdateTimer.restart();
  while (mRunning)
  {
    handleEvents();
    update(mUpdateTimer.restart<Seconds>());
    render();
  }
  return 0;
}

void Engine::terminate()
{
  mRunning = false;
}

void Engine::handleEvents()
{
  mWindow.handleEvents();
}

void Engine::update(float delta)
{
  mStateMachine.update(delta);
}

void Engine::render()
{
  mStateMachine.render();

  mWindow.getSFMLWindow().display();
}

const Settings& Engine::getSettings() const
{
  return mSettings;
}

StateMachine& Engine::getStateMachine()
{
  return mStateMachine;
}

const StateMachine& Engine::getStateMachine() const
{
  return mStateMachine;
}

Window& Engine::getWindow()
{
  return mWindow;
}

const Window& Engine::getWindow() const
{
  return mWindow;
}

} // namespace aw
