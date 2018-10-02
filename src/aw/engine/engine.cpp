#include <aw/engine/engine.hpp>

#include <aw/utils/log.hpp>

#include <chrono>
#include <thread>

namespace aw
{
Engine::Engine(aw::Settings settings) : mSettings(settings), mWindow(mSettings), mRunning(true)
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
#ifdef AW_ANDROID
    if (!mWindow.hasFocus() && mSettings.sleepOnFocusLossAndroid > 0)
    {
      LogTemp() << "In background sleep for " << mSettings.sleepOnFocusLossAndroid << " sec!";
      const auto sleepDuration = std::chrono::seconds(mSettings.sleepOnFocusLossAndroid);
      std::this_thread::sleep_for(sleepDuration);
    }
#endif
  }
  return mReturnCode;
}

void Engine::terminate(int returnCode)
{
  mRunning = false;
  mReturnCode = returnCode;
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
#ifdef AW_ANDROID
  if (!mWindow.hasFocus())
    return;
#endif
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
