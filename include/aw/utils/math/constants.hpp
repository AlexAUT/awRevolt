#pragma once

#include <glm/gtc/constants.hpp>

namespace aw
{
namespace constantsF
{
constexpr float PI = glm::pi<float>();
constexpr float PI_2 = PI / 2.f;
constexpr float PI_4 = PI / 4.f;

constexpr float TO_RAD = PI / 180.f;
constexpr float TO_DEG = 180.f / PI;
} // namespace constantsF

namespace constatsD
{
constexpr double PI = glm::pi<double>();
constexpr double PI_2 = PI / 2.0;
constexpr double PI_4 = PI / 4.0;

constexpr double TO_RAD = PI / 180.0;
constexpr double TO_DEG = 180.0 / PI;
} // namespace constatsD
} // namespace aw
