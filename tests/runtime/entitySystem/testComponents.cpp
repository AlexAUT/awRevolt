#include <catch2/catch.hpp>

#include <aw/runtime/entitySystem/directComponentManager.hpp>
#include <aw/runtime/entitySystem/entitySystem.hpp>

struct Transform
{
  float x, y;

  bool operator==(const Transform& rhs) const { return x == rhs.x && y == rhs.y; }

  using Manager = aw::ecs::DirectComponentManager<Transform>;
};

struct Motion
{
  float vX, vY;

  bool operator==(const Motion& rhs) const { return vX == rhs.vX && vY == rhs.vY; }

  using Manager = aw::ecs::DirectComponentManager<Motion>;
};

TEST_CASE("Component add")
{
  using namespace aw::ecs;

  EntitySystem entitySystem;
  Entity e = entitySystem.createEntity();

  SECTION("Add component default constructed")
  {
    e.assign<Transform>();
    REQUIRE(e.has<Transform>());
  }

  SECTION("Add component value constructed")
  {
    Transform transform{1.f, 2.f};
    e.assign<Transform>(transform);
    REQUIRE(e.has<Transform>());

    SECTION("Check if component is created with custom constructor")
    {
      auto comp = e.get<Transform>();
      REQUIRE(comp);
      REQUIRE(comp.get());

      REQUIRE(*comp == transform);
      REQUIRE(&comp.get()->x == &comp->x);
    }
  }

  SECTION("Add component custom custructed")
  {
    Transform transform{1.f, 2.f};
    e.assign<Transform>(transform.x, transform.y);
    REQUIRE(e.has<Transform>());

    SECTION("Check if component is created with custom constructor")
    {
      auto comp = e.get<Transform>();
      REQUIRE(comp);
      REQUIRE(comp.get());

      REQUIRE(*comp == transform);
      REQUIRE(&comp.get()->x == &comp->x);
    }
  }
}

TEST_CASE("Modifying component")
{
  using namespace aw::ecs;
  EntitySystem entitySystem;
  Entity e = entitySystem.createEntity();

  Transform transform{1.f, 2.f};
  e.assign<Transform>(transform);

  SECTION("Change component")
  {
    auto comp = e.get<Transform>();
    REQUIRE(comp);
    comp->x = 10.f;
    comp->y = 12.f;

    comp = e.get<Transform>();
    REQUIRE(comp);
    REQUIRE(comp->x == 10.f);
    REQUIRE(comp->y == 12.f);
  }
  SECTION("Remove component")
  {
    REQUIRE(e.remove<Transform>());
    REQUIRE(!e.remove<Transform>());
  }

  SECTION("Add again after delete")
  {
    REQUIRE(e.remove<Transform>());
    Transform newTrans{100.f, 100.f};
    REQUIRE(e.assign<Transform>(newTrans));
    REQUIRE(e.has<Transform>());
    REQUIRE(*e.get<Transform>() == newTrans);

    REQUIRE(e.remove<Transform>());
    REQUIRE(!e.has<Transform>());
    REQUIRE(!e.remove<Transform>());
    REQUIRE(!e.has<Transform>());
  }
}

TEST_CASE("Multiple components")
{
  using namespace aw::ecs;

  EntitySystem entitySystem;
  Entity e = entitySystem.createEntity();

  Transform refTransform{1.f, 2.f};
  e.assign<Transform>(refTransform);

  Motion refMotion{3.f, 4.f};
  e.assign<Motion>(refMotion);

  REQUIRE(e.has<Transform>());
  REQUIRE(e.has<Motion>());
  REQUIRE(*e.get<Transform>() == refTransform);
  REQUIRE(*e.get<Motion>() == refMotion);

  SECTION("Remove first one")
  {
    REQUIRE(e.remove<Transform>());
    REQUIRE(!e.has<Transform>());
    REQUIRE(e.has<Motion>());
    REQUIRE(!e.remove<Transform>());
    REQUIRE(!e.has<Transform>());
    REQUIRE(e.has<Motion>());
  }
  SECTION("Remove second one")
  {
    REQUIRE(e.remove<Motion>());
    REQUIRE(!e.has<Motion>());
    REQUIRE(e.has<Transform>());
    REQUIRE(!e.remove<Motion>());
    REQUIRE(!e.has<Motion>());
    REQUIRE(e.has<Transform>());
  }
}
