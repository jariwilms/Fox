#pragma once

#include <glm/glm.hpp>

using byte       = unsigned char;
using word       = unsigned short;
using dword      = unsigned int;
using qword      = unsigned long long;

using i8         = std::int8_t;
using i16        = std::int16_t;
using i32        = std::int32_t;
using i64        = std::int64_t;
using ui8        = std::uint8_t;
using ui16       = std::uint16_t;
using ui32       = std::uint32_t;
using ui64_t     = std::uint64_t;

using Vector2i   = glm::ivec2;
using Vector3i   = glm::ivec3;
using Vector4i   = glm::ivec4;
using Vector2u   = glm::uvec2;
using Vector3u   = glm::uvec3;
using Vector4u   = glm::uvec4;
using Vector2f   = glm::vec2;
using Vector3f   = glm::vec3;
using Vector4f   = glm::vec4;
using Matrix2f   = glm::mat2;
using Matrix3f   = glm::mat3;
using Matrix4f   = glm::mat4;
using Quaternion = glm::quat;

using t_hash     = size_t;
using Id         = unsigned int;
