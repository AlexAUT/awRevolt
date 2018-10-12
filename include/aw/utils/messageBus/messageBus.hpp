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

template <typename EventType>
class Channel : public ChannelWrapper
{
public:
  using Callback = std::function<void(const EventType&)>;

  int connect(Callback callback)
  {
    mListeners.emplace_back(std::make_pair(mCounter, std::move(callback)));
    return mCounter++;
  }

  void disconnect(int id)
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

  void broadcast(const EventType& event)
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
  int subscribeToChannel(typename Channel<EventType>::Callback callback)
  {
    auto channelId = mTypeIDs.getId<EventType>();
    if (mChannels.size() <= channelId)
      mChannels.resize(channelId + 1);

    using EventChannel = Channel<EventType>;
    if (!mChannels[channelId])
      mChannels[channelId] = std::make_unique<EventChannel>();

    return static_cast<EventChannel&>(*mChannels[channelId]).connect(std::move(callback));
  }

  template <typename EventType>
  void unsubscribeFromChannel(int id)
  {
    using EventChannel = Channel<EventType>;
    auto channelId = mTypeIDs.getId<EventType>();
    if (mChannels.size() > channelId || mChannels[channelId])
      static_cast<EventChannel&>(*mChannels[channelId]).disconnect(id);
  }

  template <typename EventType>
  void broadcast(const EventType& eventType)
  {
    using EventChannel = Channel<EventType>;
    auto channelId = mTypeIDs.getId<EventType>();
    if (mChannels.size() > channelId || mChannels[channelId])
      static_cast<EventChannel&>(*mChannels[channelId]).broadcast(eventType);
  }

private:
private:
  TypeIDs mTypeIDs;
  std::vector<std::unique_ptr<ChannelWrapper>> mChannels;
};
}
