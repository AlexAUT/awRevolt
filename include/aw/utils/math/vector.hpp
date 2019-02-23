#pragma once

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

#include <ostream>

namespace aw
{

typedef glm::vec2 Vec2;
typedef glm::bvec2 Vec2b;
typedef glm::ivec2 Vec2i;
typedef glm::uvec2 Vec2u;
typedef glm::dvec2 Vec2d;

typedef glm::vec3 Vec3;
typedef glm::bvec3 Vec3b;
typedef glm::ivec3 Vec3i;
typedef glm::uvec3 Vec3u;
typedef glm::dvec3 Vec3d;

typedef glm::vec4 Vec4;
typedef glm::bvec3 Vec3b;
typedef glm::ivec4 Vec4i;
typedef glm::uvec4 Vec4u;
typedef glm::dvec4 Vec4d;
} // namespace aw

// Serialize function for all glm vectors
namespace glm
{
#ifndef CEREAL_NVP
#define CEREAL_NVP(x)
#endif
template <class Archive, glm::length_t length, typename VectorType, qualifier precesion>
void serialize(Archive& archive, vec<length, VectorType, precesion>& vec)
{
  if constexpr (length >= 1)
    archive(CEREAL_NVP(vec.x));
  if constexpr (length >= 2)
    archive(CEREAL_NVP(vec.y));
  if constexpr (length >= 3)
    archive(CEREAL_NVP(vec.z));
  if constexpr (length >= 4)
    archive(CEREAL_NVP(vec.x));
}

} // namespace glm

std::ostream& operator<<(std::ostream& stream, const aw::Vec2& vec);
std::ostream& operator<<(std::ostream& stream, const aw::Vec2i& vec);
std::ostream& operator<<(std::ostream& stream, const aw::Vec2u& vec);

std::ostream& operator<<(std::ostream& stream, const aw::Vec3& vec);
std::ostream& operator<<(std::ostream& stream, const aw::Vec3i& vec);

std::ostream& operator<<(std::ostream& stream, const aw::Vec4& vec);
std::ostream& operator<<(std::ostream& stream, const aw::Vec4i& vec);
