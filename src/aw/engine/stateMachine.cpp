#include <aw/engine/stateMachine.hpp>

namespace aw
{

void StateMachine::pushState(std::shared_ptr<State> stateToPush)
{
  mStatesToPush.push(stateToPush);
}

void StateMachine::popState()
{
  mPopStatesCount++;
}

void StateMachine::popAllStates()
{
  mPopAllStates = true;
}

void StateMachine::update(float delta)
{
  if (!mStateStack.empty())
    mStateStack.top()->update(delta);
}

void StateMachine::render()
{
  if (!mStateStack.empty())
    mStateStack.top()->render();

  while (!mStateStack.empty() && (mPopAllStates || mPopStatesCount > 0))
  {
    mStateStack.pop();
    mPopStatesCount--;
  }
  mPopAllStates = false;
  mPopStatesCount = 0;

  while (!mStatesToPush.empty())
  {
    mStateStack.push(mStatesToPush.front());
    mStatesToPush.pop();
  }
}

} // namespace aw
