#pragma once

#include <aw/engine/runtime/stateMachine.hpp>
#include <aw/engine/settings.hpp>
#include <aw/engine/window.hpp>

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

  MessageBus& getMessageBus() { return mMsgBus; }
  const MessageBus& getMessageBus() const { return mMsgBus; }
  const Settings& getSettings() const;
  StateMachine& getStateMachine();
  const StateMachine& getStateMachine() const;
  Window& getWindow();
  const Window& getWindow() const;

private:
  void handleEvents();
  void update(float delta);
  void render();

private:
  MessageBus mMsgBus;
  Settings mSettings;
  StateMachine mStateMachine;
  Window mWindow;

  Clock mUpdateTimer;

  bool mRunning;
  int mReturnCode{0};
};

} // namespace aw
