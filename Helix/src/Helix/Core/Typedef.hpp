#pragma once

#include <glm/glm.hpp>

using byte  = unsigned char;
using word  = unsigned short;
using dword = unsigned int;
using qword = unsigned long long;

enum class FundamentalType
{
    Void, 

    Bool, 

    Byte,     UnsignedByte, 
    Short,    UnsignedShort, 
    Int,      UnsignedInt, 
    Long,     UnsignedLong, 
    LongLong, UnsignedLongLong, 

    Float, 
    Double, 
};

using Vector2i = glm::ivec2;
using Vector3i = glm::ivec3;
using Vector4i = glm::ivec4;
using Vector2u = glm::uvec2;
using Vector3u = glm::uvec3;
using Vector4u = glm::uvec4;
using Vector2f = glm::vec2;
using Vector3f = glm::vec3;
using Vector4f = glm::vec4;
using Matrix2f = glm::mat2;
using Matrix3f = glm::mat3;
using Matrix4f = glm::mat4;
using Quaternion = glm::quat;

using t_hash = size_t;
using Id = unsigned int;
