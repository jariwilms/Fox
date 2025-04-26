#pragma once

#include "glad/gl.h"
#include "glfw/glfw3.h"
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"

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

    using size_t     = GLsizei;     //Sizes and dimensions (should not be negative)
    using enum_t     = GLenum;      //Enumerated value of constants
    using sizeptr_t  = GLsizeiptr;  //Buffer size   in bytes
    using intptr_t   = GLintptr;    //Buffer offset in bytes
    using sync_t     = GLsync;      //Synchronization primitive
    using bitfield_t = GLbitfield;  //Value containing one or more flags

    using byte_t     = gl::uint8_t;

    enum : gl::bool_t
    {
        False = GL_FALSE,
        True  = GL_TRUE,
    };
    


    //Strong aliases
    enum class handle_t : gl::uint32_t {}; //Alias for OpenGL Object handles
    enum class query_t  : gl::uint32_t {}; //Alias for OpenGL Query  handles
    enum class format_t : gl::enum_t   {}; //Alias for OpenGL Binary Formats

    constexpr gl::handle_t NullObject{};



    //Vector types
    template<typename T, gl::int32_t N> using Vector     = glm::vec<N, T, glm::packed_highp>;
    template<typename T, gl::int32_t N> using Matrix     = glm::mat<N, N, T>;
                                        using Quaternion = glm::quat;

    using Vector1b   = gl::Vector<gl::bool_t,    1>;
    using Vector2b   = gl::Vector<gl::bool_t,    2>;
    using Vector3b   = gl::Vector<gl::bool_t,    3>;
    using Vector4b   = gl::Vector<gl::bool_t,    4>;

    using Vector1i   = gl::Vector<gl::int32_t,   1>;
    using Vector2i   = gl::Vector<gl::int32_t,   2>;
    using Vector3i   = gl::Vector<gl::int32_t,   3>;
    using Vector4i   = gl::Vector<gl::int32_t,   4>;

    using Vector1u   = gl::Vector<gl::uint32_t,  1>;
    using Vector2u   = gl::Vector<gl::uint32_t,  2>;
    using Vector3u   = gl::Vector<gl::uint32_t,  3>;
    using Vector4u   = gl::Vector<gl::uint32_t,  4>;
    
    using Vector1f   = gl::Vector<gl::float32_t, 1>;
    using Vector2f   = gl::Vector<gl::float32_t, 2>;
    using Vector3f   = gl::Vector<gl::float32_t, 3>;
    using Vector4f   = gl::Vector<gl::float32_t, 4>;
    
    using Vector1d   = gl::Vector<gl::float64_t, 1>;
    using Vector2d   = gl::Vector<gl::float64_t, 2>;
    using Vector3d   = gl::Vector<gl::float64_t, 3>;
    using Vector4d   = gl::Vector<gl::float64_t, 4>;
    
    using Matrix2f   = gl::Matrix<gl::float32_t, 2>;
    using Matrix3f   = gl::Matrix<gl::float32_t, 3>;
    using Matrix4f   = gl::Matrix<gl::float32_t, 4>;



    //Size and Range Types
    template<typename T, gl::uint32_t N>
    struct Dimensions
    {
        gl::Vector<T, N> origin;
        gl::Vector<T, N> extent;
    };

    template<typename T> using Line   = Dimensions<T, 1>;
    template<typename T> using Area   = Dimensions<T, 2>;
    template<typename T> using Volume = Dimensions<T, 3>;

    template<typename T>
    struct Range
    {
        T min{};
        T max{};
    };
}
