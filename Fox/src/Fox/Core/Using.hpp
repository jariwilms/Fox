#pragma once

#include <cstdint>

#include <glm/glm.hpp>

namespace fox
{
	using bool_t    = bool;
	using char_t    = char;          //Not equal to signed char apparently
	using int8_t    = std::int8_t;
	using uint8_t   = std::uint8_t;
	using int16_t   = std::int16_t;
	using uint16_t  = std::uint16_t;
	using int32_t   = std::int32_t;
	using uint32_t  = std::uint32_t;
	using int64_t   = std::int64_t;
	using uint64_t  = std::uint64_t;
	using float32_t = float;
	using float64_t = double;

	using byte       = uint8_t;
	using word       = uint16_t;
	using dword      = uint32_t;
	using qword      = uint64_t;

	using size_t     = std::size_t;   //Offset in bytes
	using hash_t     = fox::size_t;   
	using count_t    = fox::uint32_t; //Number of elements
	using offset_t   = fox::uint32_t; //Number of elements offset

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
	using Matrix2f   = glm::mat2;
	using Matrix3f   = glm::mat3;
	using Matrix4f   = glm::mat4;
	using Quaternion = glm::quat;

	enum Id : fox::uint32_t {};
}
