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

std::ostream& operator<<(std::ostream& stream, const Vec2& vec);
std::ostream& operator<<(std::ostream& stream, const Vec2i& vec);
std::ostream& operator<<(std::ostream& stream, const Vec2u& vec);

std::ostream& operator<<(std::ostream& stream, const Vec3& vec);
std::ostream& operator<<(std::ostream& stream, const Vec3i& vec);

std::ostream& operator<<(std::ostream& stream, const Vec4& vec);
std::ostream& operator<<(std::ostream& stream, const Vec4i& vec);

} // namespace aw
