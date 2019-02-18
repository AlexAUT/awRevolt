#pragma once

#include <aw/utils/messageBus/messageBus.hpp>

namespace aw::msg
{
template <typename HostClass, typename... EventTypes>
class Listener
{
public:
  Listener(msg::Bus& bus) :
      mSubscriptions({bus.subscribeToChannel<EventTypes>([this](const auto& event) {
        auto* instance = static_cast<HostClass*>(this);
        instance->receive(event);
      })...})
  {
  }

private:
private:
  std::tuple<typename msg::Channel<EventTypes>::SubscriptionType...> mSubscriptions;
};
} // namespace aw::msg
