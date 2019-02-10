#pragma once

#include <functional>
#include <vector>

namespace aw::gui
{
template <typename Signature>
class Signal;

template <typename ReturnValue, typename... Args>
class Signal<ReturnValue(Args...)>
{
public:
  using Id = int;
  using Function = std::function<ReturnValue(const Args&...)>;
  using IdFunctionPair = std::pair<int, Function>;

public:
  Id connect(Function func)
  {
    Id newId = mListeners.empty() ? 1 : mListeners.back().first;
    mListeners.emplace_back(newId, std::move(func));
    return newId;
  }

  void disconnect(Id toRemove)
  {
    auto found = std::find(mListeners.begin(), mListeners.end(), [=](auto& e) { return toRemove == e.first; });
    if (found != mListeners.end())
      mListeners.erase(found);
  }

  void operator()(const Args&... args)
  {
    for (auto& listener : mListeners)
      listener.second(args...);
  }

private:
private:
  std::vector<IdFunctionPair> mListeners;
};
} // namespace aw::gui
