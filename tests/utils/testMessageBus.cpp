#include <catch2/catch.hpp>

#include <aw/utils/messageBus/messageBus.hpp>

struct MessageA
{
  std::string msg;
};

struct MessageB
{
  std::string msg;
};

TEST_CASE("MessageBus")
{
  aw::msg::Bus bus;
  bus.broadcast(MessageA{"Hallo"});

  SECTION("One receiver")
  {
    INFO("Check if subscription safely works");
    MessageA message{"Message1"};
    MessageA received;
    {
      auto sub = bus.subscribeToChannel<MessageA>([&](const auto& msg) { received = msg; });
      bus.broadcast(message);
      CHECK(received.msg == message.msg);
    }
    received.msg = "";
    REQUIRE(received.msg != message.msg);
    bus.broadcast(message);
    INFO("Check if unsubscribe works on destructor");
    CHECK(received.msg != message.msg);
  }

  SECTION("Multiple message types")
  {
    MessageA messageA{"A"};
    MessageB messageB{"B"};
    MessageA recA;
    MessageB recB;
    {
      auto subA = bus.subscribeToChannel<MessageA>([&](const auto& msg) { recA = msg; });
      {
        auto subB = bus.subscribeToChannel<MessageB>([&](const auto& msg) { recB = msg; });
        bus.broadcast(messageA);
        bus.broadcast(messageB);
        CHECK(recA.msg == messageA.msg);
        CHECK(recB.msg == messageB.msg);
      }
      recA.msg = "";
      recB.msg = "";
      bus.broadcast(messageA);
      bus.broadcast(messageB);
      CHECK(recA.msg == messageA.msg);
      CHECK(recB.msg != messageB.msg);
    }
    recA.msg = "";
    recB.msg = "";
    bus.broadcast(messageA);
    bus.broadcast(messageB);
    CHECK(recA.msg != messageA.msg);
    CHECK(recB.msg != messageB.msg);
  }

  SECTION("Test out of order messages")
  {
    MessageA messageA{"A"};
    MessageB messageB{"B"};
    MessageA recA;
    MessageB recB;
    aw::msg::Bus bus2;
    auto subB = bus2.subscribeToChannel<MessageB>([&](const auto& msg) { recB = msg; });
    bus2.broadcast(messageB);
    CHECK(recB.msg == messageB.msg);

    bus2.broadcast(messageA);
    auto subA = bus2.subscribeToChannel<MessageA>([&](const auto& msg) { recA = msg; });
    bus2.broadcast(messageA);

    CHECK(recA.msg == messageA.msg);
  }
}

