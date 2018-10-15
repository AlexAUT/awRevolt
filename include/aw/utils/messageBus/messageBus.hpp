#pragma once

#include <aw/utils/typeHelper/typeCounter.hpp>

#include <functional>
#include <memory>
#include <vector>

namespace aw
{
class ChannelWrapper
{
public:
  virtual ~ChannelWrapper() = default;
};

template <typename Channel>
class [[nodiscard]] Subscription
{
public:
  Subscription() = delete;
  Subscription(Channel & channel, int id) : mChannel(channel), mId(id) {}
  Subscription(const Subscription&) = delete;
  Subscription& operator=(const Subscription) = delete;
  Subscription(Subscription && o) : mChannel(o.mChannel), mId(o.mId), mSubscribed(o.mSubscribed)
  {
    o.mSubscribed = false;
  }
  Subscription operator=(Subscription&& o) { return Subscription(o); }
  ~Subscription()
  {
    if (mSubscribed)
      mChannel.unsubscribe(mId);
  }

  void cancel()
  {
    if (mSubscribed)
    {
      mSubscribed = false;
      mChannel.unsubscribe(mId);
    }
  }

private:
  Channel& mChannel;
  int mId;
  bool mSubscribed{true};
};

template <typename EventType>
class Channel : public ChannelWrapper
{
public:
  using Callback = std::function<void(const EventType&)>;
  using SubscriptionType = Subscription<Channel>;

  int subscribe(Callback callback)
  {
    mListeners.emplace_back(std::make_pair(mCounter, std::move(callback)));
    return mCounter++;
  }

  SubscriptionType subscribeSafely(Callback callback) { return {*this, subscribe(std::move(callback))}; }

  void unsubscribe(int id)
  {
    for (auto& it : mListeners)
    {
      if (it.first == id)
      {
        std::swap(it, mListeners.back());
        mListeners.pop_back();
        return;
      }
    }
  }

  void broadcast(const EventType& event) const
  {
    for (auto& listener : mListeners)
      listener.second(event);
  }

private:
  std::vector<std::pair<int, Callback>> mListeners;
  int mCounter{1};
};

class MessageBus
{
public:
  using TypeIDs = TypeCounter<struct Anonym>;

  template <typename EventType>
  typename Channel<EventType>::SubscriptionType subscribeToChannel(typename Channel<EventType>::Callback callback)
  {
    auto channelId = mTypeIDs.getId<EventType>();
    if (mChannels.size() <= channelId)
      mChannels.resize(channelId + 1);

    using EventChannel = Channel<EventType>;
    if (!mChannels[channelId])
      mChannels[channelId] = std::make_unique<EventChannel>();

    return static_cast<EventChannel&>(*mChannels[channelId]).subscribeSafely(std::move(callback));
  }

  template <typename EventType>
  int subscribeToChannelUnsafe(typename Channel<EventType>::Callback callback)
  {
    auto channelId = mTypeIDs.getId<EventType>();
    if (mChannels.size() <= channelId)
      mChannels.resize(channelId + 1);

    using EventChannel = Channel<EventType>;
    if (!mChannels[channelId])
      mChannels[channelId] = std::make_unique<EventChannel>();

    return static_cast<EventChannel&>(*mChannels[channelId]).subscribe(std::move(callback));
  }

  template <typename EventType>
  void unsubscribeFromChannel(int id)
  {
    using EventChannel = Channel<EventType>;
    auto channelId = mTypeIDs.getId<EventType>();
    if (mChannels.size() > channelId || mChannels[channelId])
      static_cast<EventChannel&>(*mChannels[channelId]).unsubscribe(id);
  }

  template <typename EventType>
  void broadcast(const EventType& eventType) const
  {
    using EventChannel = Channel<EventType>;
    auto channelId = mTypeIDs.getId<EventType>();
    if (mChannels.size() > channelId && mChannels[channelId])
      static_cast<const EventChannel&>(*mChannels[channelId]).broadcast(eventType);
  }

private:
private:
  TypeIDs mTypeIDs;
  std::vector<std::unique_ptr<ChannelWrapper>> mChannels;
};
} // namespace aw
