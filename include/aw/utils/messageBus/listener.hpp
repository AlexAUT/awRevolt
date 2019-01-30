#pragma once

#include <aw/utils/messageBus/messageBus.hpp>

namespace aw::msg
{
template <typename HostClass, typename EventType>
class Listener
{
public:
  Listener(msg::Bus& bus) :
      mSubscription(bus.subscribeToChannel<EventType>([this](const auto& event) {
        auto* instance = static_cast<HostClass*>(this);
        instance->receive(event);
      }))
  {
  }

private:
private:
  typename msg::Channel<EventType>::SubscriptionType mSubscription;
};
} // namespace aw::msg
