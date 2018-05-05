#include <aw/engine/engine.hpp>
#include <aw/opengl/opengl.hpp>

namespace aw
{
Engine::Engine() : mSettings(priv::loadSettings()), mWindow(mSettings), mRunning(true)
{
  glClearColor(0.f, 0.8f, 0.25f, 1.0f);
}

int Engine::run()
{
  while (mRunning)
  {
    handleEvents();
    update(0);
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
  //  glClearColor(0.f, 0.25f, 0.8f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

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
