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

public:
  MessageBus() = default;
  MessageBus(const MessageBus&) = delete;
  MessageBus operator=(const MessageBus&) = delete;

  template <typename EventType>
  typename Channel<EventType>::SubscriptionType subscribeToChannel(typename Channel<EventType>::Callback callback)
  {
    auto& channel = getAndCreateChannel<EventType>();
    return channel.subscribeSafely(std::move(callback));
  }

  template <typename EventType>
  int subscribeToChannelUnsafe(typename Channel<EventType>::Callback callback)
  {
    auto& channel = getAndCreateChannel<EventType>();
    return channel.subscribe(std::move(callback));
  }

  template <typename EventType>
  void unsubscribeFromChannel(int id)
  {
    auto* channel = getChannel<EventType>();
    if (channel)
      channel->unsubscribe(id);
  }

  template <typename EventType>
  void broadcast(const EventType& eventType) const
  {
    auto* channel = getChannel<EventType>();
    if (channel)
      channel->broadcast(eventType);
  }

private:
  template <typename EventType>
  Channel<EventType>& getAndCreateChannel()
  {
    using EventChannel = Channel<EventType>;
    auto* channel = getChannel<EventType>();

    if (!channel)
    {
      auto channelId = TypeIDs::getId<EventType>();
      while (mChannels.size() <= channelId)
        mChannels.emplace_back(nullptr);
      if (!mChannels[channelId])
        mChannels[channelId] = std::make_unique<EventChannel>();

      channel = static_cast<EventChannel*>(mChannels[channelId].get());
    }

    assert(channel);
    return *channel;
  }

  template <typename EventType>
  Channel<EventType>* getChannel() const
  {
    auto channelId = TypeIDs::getId<EventType>();
    if (channelId >= mChannels.size())
      return nullptr;
    using EventChannel = Channel<EventType>;
    return mChannels[channelId] ? static_cast<EventChannel*>(mChannels[channelId].get()) : nullptr;
  }

private:
  std::vector<std::unique_ptr<ChannelWrapper>> mChannels;
};
} // namespace aw
