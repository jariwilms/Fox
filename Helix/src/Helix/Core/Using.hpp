#pragma once

#include <cstdint>

#include <glm/glm.hpp>

using bit        = bool;
using byte       = unsigned char;
using word       = unsigned short;
using dword      = unsigned int;
using qword      = unsigned long long;

using i8         = std::int8_t;
using i16        = std::int16_t;
using i32        = std::int32_t;
using i64        = std::int64_t;
using u8         = std::uint8_t;
using u16        = std::uint16_t;
using u32        = std::uint32_t;
using u64        = std::uint64_t;
using f32        = float;
using f64        = double;

using Vector1i   = glm::ivec1;
using Vector2i   = glm::ivec2;
using Vector3i   = glm::ivec3;
using Vector4i   = glm::ivec4;
using Vector1u   = glm::uvec1;
using Vector2u   = glm::uvec2;
using Vector3u   = glm::uvec3;
using Vector4u   = glm::uvec4;
using Vector1f   = glm::vec1;
using Vector2f   = glm::vec2;
using Vector3f   = glm::vec3;
using Vector4f   = glm::vec4;
//using Matrix1f   = Vector4f; //obv
using Matrix2f   = glm::mat2;
using Matrix3f   = glm::mat3;
using Matrix4f   = glm::mat4;
using Quaternion = glm::quat;

using t_hash     = size_t;
using Id         = u32;
