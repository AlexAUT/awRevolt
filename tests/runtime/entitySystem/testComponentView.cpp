#include <catch2/catch.hpp>

#include <aw/runtime/entitySystem/entitySystem.hpp>
#include <aw/runtime/entitySystem/indirectComponentManager.hpp>

#include "components.hpp"

template <typename Transform, typename Motion>
void testSingleComponentView()
{
  using namespace aw::ecs;

  EntitySystem system;

  SECTION("Create view")
  {
    auto view = system.getView<Transform>();
    REQUIRE(!view.end());
  }

  SECTION("No entity with component")
  {
    int found = 0;
    for ([[maybe_unused]] auto comp : system.getView<Transform>())
      found++;
    REQUIRE(found == 0);
  }

  auto e1 = system.createEntity();
  e1.assign<Transform>(1.f, 2.f);

  SECTION("One entity with one component")
  {
    int counter = 0;
    for (auto comp : system.getView<Transform>())
    {
      CHECK(std::get<0>(comp).get() == e1.get<Transform>().get());
      counter++;
      CHECK(counter == 1);
    }
    REQUIRE(counter == 1);
  }

  SECTION("No entity with component but with other component")
  {
    int found = 0;
    for ([[maybe_unused]] auto comp : system.getView<Motion>())
      found++;
    REQUIRE(found == 0);
  }

  e1.assign<Motion>(3.f, 4.f);
  SECTION("View on two components single entity")
  {
    int counter = 0;
    for (auto comp : system.getView<Transform, Motion>())
    {
      CHECK(std::get<0>(comp).get() == e1.get<Transform>().get());
      CHECK(std::get<1>(comp).get() == e1.get<Motion>().get());
      counter++;
      REQUIRE(counter == 1);
    }
    REQUIRE(counter == 1);
  }

  auto e2 = system.createEntity();
  e2.assign<Transform>();
  SECTION("Two entities one shared component and one only by one")
  {
    SECTION("View on shared component")
    {
      int counter = 0;
      for ([[maybe_unused]] auto comp : system.getView<Transform>())
      {
        counter++;
      }
      CHECK(counter == 2);
    }

    SECTION("View on not shared component")
    {
      int counter = 0;
      for ([[maybe_unused]] auto comp : system.getView<Motion>())
        counter++;
      REQUIRE(counter == 1);
    }

    SECTION("View on both components")
    {
      int counter = 0;
      for ([[maybe_unused]] auto comp : system.getView<Transform, Motion>())
        counter++;
      REQUIRE(counter == 1);
    }
  }

  e2.assign<Motion>();
  SECTION("View two components multiple entities")
  {
    int counter = 0;
    for ([[maybe_unused]] auto comp : system.getView<Transform, Motion>())
      counter++;
    REQUIRE(counter == 2);
  }
}

TEST_CASE("Single component (Direct/Direct)")
{
  testSingleComponentView<TransformDirectManaged, MotionIndirectManaged>();
}
TEST_CASE("Single component (Direct/Indirect)")
{
  testSingleComponentView<TransformDirectManaged, MotionDirectManaged>();
}
TEST_CASE("Single component (Indirect/Direct)")
{
  testSingleComponentView<TransformIndirectManaged, MotionDirectManaged>();
}
TEST_CASE("Single component (Indirect/Indirect)")
{
  testSingleComponentView<TransformIndirectManaged, MotionIndirectManaged>();
}

template <typename Transform, typename Motion>
void testUpdateComponentsWithView()
{
  using namespace aw::ecs;
  EntitySystem system;

  auto e1 = system.createEntity();
  auto e2 = system.createEntity();
  e2.assign<Motion>(5.f, 0.f);
  e1.assign<Transform>(1.f, 1.f);
  e1.assign<Motion>(1.f, 2.f);
  e2.assign<Transform>(10.f, 10.f);

  for (auto transMotion : system.getView<Motion, Transform>())
  {
    auto& [motion, trans] = transMotion;
    trans->x += motion->vX;
    trans->y += motion->vY;
  }
  REQUIRE(e1.get<Transform>()->x == 2.f);
  REQUIRE(e1.get<Transform>()->y == 3.f);
  REQUIRE(e2.get<Transform>()->x == 15.f);
  REQUIRE(e2.get<Transform>()->y == 10.f);
}

TEST_CASE("Updated components with view (Direct/Direct)")
{
  testUpdateComponentsWithView<TransformDirectManaged, MotionDirectManaged>();
}
TEST_CASE("Updated components with view (Direct/Indirect)")
{
  testUpdateComponentsWithView<TransformDirectManaged, MotionIndirectManaged>();
}
TEST_CASE("Updated components with view (Indirect/Direct)")
{
  testUpdateComponentsWithView<TransformIndirectManaged, MotionDirectManaged>();
}
TEST_CASE("Updated components with view (Indirect/Indirect)")
{
  testUpdateComponentsWithView<TransformIndirectManaged, MotionIndirectManaged>();
}
