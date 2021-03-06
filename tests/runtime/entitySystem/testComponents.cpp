#include <catch2/catch.hpp>

//#include <aw/runtime/entitySystem/directComponentManager.hpp>
#include <aw/runtime/entitySystem/entitySystem.hpp>

#include "components.hpp"

template <typename Transform>
void testComponentAdd()
{
  using namespace aw::ecs;

  EntitySystem entitySystem;
  Entity e = entitySystem.createEntity();

  SECTION("Add component default constructed")
  {
    e.add<Transform>();
    REQUIRE(e.has<Transform>());
  }

  SECTION("Add component value constructed")
  {
    Transform transform{1.f, 2.f};
    e.add<Transform>(transform);
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
    e.add<Transform>(transform.x, transform.y);
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

TEST_CASE("Component add (direct)")
{
  testComponentAdd<TransformDirectManaged>();
}
TEST_CASE("Component add (indirect)")
{
  testComponentAdd<TransformIndirectManaged>();
}

template <typename Transform>
void testModifyingComponent()
{
  using namespace aw::ecs;
  EntitySystem entitySystem;
  Entity e = entitySystem.createEntity();

  Transform transform{1.f, 2.f};
  e.add<Transform>(transform);

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
    REQUIRE(e.add<Transform>(newTrans));
    REQUIRE(e.has<Transform>());
    REQUIRE(*e.get<Transform>() == newTrans);

    REQUIRE(e.remove<Transform>());
    REQUIRE(!e.has<Transform>());
    REQUIRE(!e.remove<Transform>());
    REQUIRE(!e.has<Transform>());
  }
}

TEST_CASE("Modifying component (direct)")
{
  testModifyingComponent<TransformDirectManaged>();
}
TEST_CASE("Modifying component (indirect)")
{
  testModifyingComponent<TransformIndirectManaged>();
}

template <typename Transform, typename Motion>
void testMultipleComponents()
{
  using namespace aw::ecs;

  EntitySystem entitySystem;
  Entity e = entitySystem.createEntity();

  Transform refTransform{1.f, 2.f};
  e.add<Transform>(refTransform);

  Motion refMotion{3.f, 4.f};
  e.add<Motion>(refMotion);

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
TEST_CASE("Multiple components (direct/direct)")
{
  testMultipleComponents<TransformDirectManaged, MotionDirectManaged>();
}
TEST_CASE("Multiple components (direct/indirect)")
{
  testMultipleComponents<TransformDirectManaged, MotionIndirectManaged>();
}
TEST_CASE("Multiple components (indirect/direct)")
{
  testMultipleComponents<TransformIndirectManaged, MotionDirectManaged>();
}
TEST_CASE("Multiple components (indirect/indirect)")
{
  testMultipleComponents<TransformIndirectManaged, MotionIndirectManaged>();
}
