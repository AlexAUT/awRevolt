#pragma once

#include <aw/engine/runtime/stateMachine.hpp>
#include <aw/engine/settings.hpp>
#include <aw/engine/window.hpp>

namespace aw
{

class Engine
{
public:
  Engine();
  Engine(const Engine&) = delete;
  Engine operator=(const Engine&) = delete;

  int run();

  void terminate();

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
  Settings mSettings;
  StateMachine mStateMachine;
  Window mWindow;

  bool mRunning;
};

} // namespace aw
