#include <catch2/catch.hpp>

#include <aw/runtime/entitySystem/directComponentManager.hpp>
#include <aw/runtime/entitySystem/entity.hpp>
#include <aw/runtime/entitySystem/entitySystem.hpp>
#include <aw/runtime/entitySystem/indirectComponentManager.hpp>

#include "components.hpp"

// Note: remind that the component manager is defined as a typedef inside the component

template <typename Component>
void testAddAndRemove()
{
  using namespace aw::ecs;

  EntitySystem system;
  auto e1 = system.createEntity();

  SECTION("Assign")
  {
    e1.add<Component>();
    REQUIRE(e1.has<Component>());
    REQUIRE(*e1.get<Component>() == Component());
  }
  SECTION("Assign and remove")
  {
    e1.add<Component>();
    e1.remove<Component>();
    REQUIRE(!e1.has<Component>());
  }

  SECTION("Add, remove and add again")
  {
    e1.add<Component>();
    e1.remove<Component>();
    e1.add<Component>();
    REQUIRE(e1.has<Component>());
    REQUIRE(*e1.get<Component>() == Component());
  }

  auto e2 = system.createEntity();
  SECTION("Multiple components add, remove, add")
  {
    e1.add<Component>();
    e2.add<Component>(1.f, 2.f);
    REQUIRE(e1.has<Component>());
    REQUIRE(*e1.get<Component>() == Component());
    REQUIRE(e2.has<Component>());
    REQUIRE(*e2.get<Component>() == Component{1.f, 2.f});

    e1.remove<Component>();
    REQUIRE(!e1.has<Component>());
    REQUIRE(e2.has<Component>());
    REQUIRE(*e2.get<Component>() == Component{1.f, 2.f});

    e1.add<Component>(3.f, 4.f);
    REQUIRE(e1.has<Component>());
    REQUIRE(*e1.get<Component>() == Component{3.f, 4.f});
    REQUIRE(e2.has<Component>());
    REQUIRE(*e2.get<Component>() == Component{1.f, 2.f});

    e2.remove<Component>();
    REQUIRE(e1.has<Component>());
    REQUIRE(*e1.get<Component>() == Component{3.f, 4.f});
    REQUIRE(!e2.has<Component>());

    e1.remove<Component>();
    REQUIRE(!e1.has<Component>());
    REQUIRE(!e2.has<Component>());
  }
}

TEST_CASE("Add and remove component, DirectComponentManager")
{
  testAddAndRemove<TransformDirectManaged>();
}
TEST_CASE("Add and remove component, IndirectComponentManager")
{
  testAddAndRemove<TransformIndirectManaged>();
}
