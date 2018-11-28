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

  SECTION("Assign and check if present")
  {
    e1.assign<Component>();
    REQUIRE(e1.has<Component>());
    REQUIRE(*e1.get<Component>() == Component());
  }
}

TEST_CASE("Add and remove component")
{
  // testAddAndRemove<TransformDirectManaged>();
  // testAddAndRemove<TransformIndirectManaged>();
}
