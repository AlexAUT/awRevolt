#pragma once

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

  const Settings& getSettings() const;

private:
  void handleEvents();
  void update(float delta);
  void render();

private:
  Settings mSettings;
  Window mWindow;

  bool mRunning;
};

} // namespace aw
