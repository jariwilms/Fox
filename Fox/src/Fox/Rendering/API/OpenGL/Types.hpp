#pragma once

#include "glad/gl.h"
#include "glfw/glfw3.h"
#include "glm/glm.hpp"

namespace fox::gfx::api::gl
{
    //Fundamental types
    using bool_t     = GLboolean;
    using char_t     = GLchar;
    using int8_t     = GLbyte;
    using uint8_t    = GLubyte;
    using int16_t    = GLshort;
    using uint16_t   = GLushort;
    using int32_t    = GLint;
    using uint32_t   = GLuint;
    using int64_t    = GLint64;
    using uint64_t   = GLuint64;
    using float16_t  = GLhalf;
    using float32_t  = GLfloat;
    using float64_t  = GLdouble;

    using size_t     = GLsizei;    //Sizes and dimensions (may not be negative)
    using enum_t     = GLenum;     //Enumerated value of constants
    using sizeptr_t  = GLsizeiptr; //Buffer size in bytes
    using intptr_t   = GLintptr;   //Buffer offset in bytes
    using sync_t     = GLsync;     //Synchronization primitive
    using bitfield_t = GLbitfield; //Value containing one or more flags



    //Vector types
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



    //Strong aliases
    enum class handle_t : gl::uint32_t {}; //Alias for OpenGL  Object handles
    enum class query_t  : gl::uint32_t {}; //Alias for OpenGL  Query  handles
    enum class index_t  : gl::uint32_t {}; //Alias for binding point  indices



    enum : gl::bool_t
    {
        False = GL_FALSE,
        True  = GL_TRUE,
    };
    enum : gl::uint32_t
    {
        NullObject = gl::uint32_t{}, 
    };
}
