#pragma once

namespace aw
{

class StateMachine;

class State
{
public:
  State(StateMachine& stateMachine);
  virtual ~State() = default;

  virtual void update(float delta) = 0;
  virtual void render() = 0;

private:
private:
  StateMachine& mStateMachine;
};

} // namespace aw
