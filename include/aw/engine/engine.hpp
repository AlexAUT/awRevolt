#pragma once

#include <aw/engine/runtime/stateMachine.hpp>
#include <aw/engine/settings.hpp>
#include <aw/engine/window.hpp>
#include <aw/runtime/resourceManager/resourceManager.hpp>
#include <aw/utils/messageBus/messageBus.hpp>
#include <aw/utils/time/clock.hpp>

namespace aw
{

class Engine
{
public:
  Engine(aw::Settings settings = aw::Settings::loadFromFile());
  Engine(const Engine&) = delete;
  Engine operator=(const Engine&) = delete;

  int run();

  void terminate(int returnCode = 0);

  msg::Bus& getMessageBus() { return mMsgBus; }
  const msg::Bus& getMessageBus() const { return mMsgBus; }
  const Settings& getSettings() const { return mSettings; }
  StateMachine& getStateMachine() { return mStateMachine; }
  const StateMachine& getStateMachine() const { return mStateMachine; }
  Window& getWindow() { return mWindow; }
  const Window& getWindow() const { return mWindow; }
  ResourceManager& getResourceManager() { return mResourceManager; }
  const ResourceManager& getResourceManager() const { return mResourceManager; }

private:
  void handleEvents();
  void update(float delta);
  void render();

private:
  msg::Bus mMsgBus;
  Settings mSettings;
  StateMachine mStateMachine;
  Window mWindow;
  ResourceManager mResourceManager;

  Clock mUpdateTimer;

  bool mRunning;
  int mReturnCode{0};
};

} // namespace aw
