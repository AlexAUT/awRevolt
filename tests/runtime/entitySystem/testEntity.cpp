#include <catch2/catch.hpp>

#include <aw/runtime/entitySystem/entitySystem.hpp>

TEST_CASE("Default constructed entity should always be invalid")
{
  aw::Entity e;
  REQUIRE(!e.isValid());
}

TEST_CASE("Entity simple lifetime")
{
  aw::EntitySystem entitySystem;
  auto entity = entitySystem.createEntity();
  INFO("First entity of the system should never fail");
  REQUIRE(entity.isValid());

  SECTION("An valid entity should be invalid after destroy")
  {
    SECTION("Calling destroy on entity itself")
    {
      REQUIRE(entity.isValid());
      REQUIRE(entity.destroy());
      REQUIRE(!entity.isValid());
    }
    SECTION("Calling destroy via entity system")
    {
      REQUIRE(entity.isValid());
      REQUIRE(entitySystem.destroyEntity(entity));
      REQUIRE(!entity.isValid());
    }
  }

  SECTION("Destroy an invalid entity should leave it invalid and return false")
  {
    entity.destroy();
    REQUIRE(!entity.isValid());
    SECTION("On entity itself")
    {
      REQUIRE(!entity.destroy());
      REQUIRE(!entity.isValid());
    }
    SECTION("On system")
    {
      REQUIRE(!entitySystem.destroyEntity(entity));
      REQUIRE(!entity.isValid());
    }
  }
}

TEST_CASE("Multiple entities lifetimes")
{
  aw::EntitySystem system;
  auto e1 = system.createEntity();
  auto e2 = system.createEntity();

  REQUIRE(e1.isValid());
  REQUIRE(e2.isValid());

  SECTION("Kill one should not kill the other")
  {
    REQUIRE(e1.destroy());
    REQUIRE(!e1.isValid());
    REQUIRE(e2.isValid());
  }
  SECTION("Kill the second should not the kill the first")
  {
    REQUIRE(e2.destroy());
    REQUIRE(!e2.isValid());
    REQUIRE(e1.isValid());
  }
}
