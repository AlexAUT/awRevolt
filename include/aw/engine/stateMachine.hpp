#pragma once

#include <aw/engine/state.hpp>

#include <memory>
#include <queue>
#include <stack>

namespace aw
{
class StateMachine
{
public:
  void pushState(std::shared_ptr<State> newState);
  void popState();
  void popAllStates();

  void update(float delta);
  void render();

private:
private:
  std::stack<std::shared_ptr<State>> mStateStack;
  std::queue<std::shared_ptr<State>> mStatesToPush;
  int mPopStatesCount{0};
  bool mPopAllStates{false};
};
} // namespace aw
