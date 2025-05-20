#pragma once

#include "glad/gl.h"
#include "glfw/glfw3.h"
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"

namespace fox::gfx::api::gl
{
    using void_t     = GLvoid;
    using bool_t     = GLboolean;
    using char_t     = GLchar;
    using byte_t     = GLubyte;

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

    using enum_t     = GLenum;       //Enumerated constant value
    using sizei_t    = GLsizei;      //Sizes and dimensions (may not be negative)
    using size_t     = GLsizeiptr;   //Size in bytes
    using offset_t   = GLintptr;     //Offset in bytes
    using sync_t     = GLsync;       //Synchronization primitive
    using bitfield_t = GLbitfield;   //Bitwise combination of flags
    
    using count_t    = gl::uint32_t; //Number of elements
    using index_t    = gl::uint32_t; //Number of elements offset

    using time_t     = gl::uint64_t; //Duration in nanoseconds

    enum : gl::bool_t
    {
        False = GL_FALSE,
        True  = GL_TRUE,
    };
    


    enum class handle_t : gl::uint32_t {}; //OpenGL Object handle
    constexpr gl::handle_t DefaultFrameBuffer{};
    constexpr gl::handle_t NullObject{};

    class Object
    {
    public:
        Object(Object&& other) noexcept
        {
            m_handle = std::exchange(other.m_handle, gl::NullObject);
        }

        auto handle() const
        {
            return m_handle;
        }

        Object& operator=(Object&& other) noexcept
        {
            if (this != &other) m_handle = std::exchange(other.m_handle, m_handle);
            return *this;
        }

    protected:
        Object() = default;

        gl::handle_t m_handle{ gl::NullObject };
    };



    struct     range_t
    {
        explicit range_t(gl::count_t count, gl::index_t index = {})
            : count{ count }, index{ index } {}

        auto operator<=>(const range_t&) const = default;

        gl::count_t count{};
        gl::index_t index{};
    };
    struct byterange_t
    {
        explicit byterange_t(gl::size_t size, gl::offset_t offset = {})
            : size{ size }, offset{ offset } {}

        auto operator<=>(const byterange_t&) const = default;

        gl::size_t   size{};
        gl::offset_t offset{};
    };



    template<typename T, gl::uint32_t N> using Vector     = glm::vec<N, T, glm::packed_highp>;
    template<typename T, gl::uint32_t N> using Matrix     = glm::mat<N, N, T>;
                                         using Quaternion = glm::quat;

    using Vector1b = gl::Vector<gl::bool_t   , 1u>;
    using Vector2b = gl::Vector<gl::bool_t   , 2u>;
    using Vector3b = gl::Vector<gl::bool_t   , 3u>;
    using Vector4b = gl::Vector<gl::bool_t   , 4u>;

    using Vector1i = gl::Vector<gl::int32_t  , 1u>;
    using Vector2i = gl::Vector<gl::int32_t  , 2u>;
    using Vector3i = gl::Vector<gl::int32_t  , 3u>;
    using Vector4i = gl::Vector<gl::int32_t  , 4u>;

    using Vector1u = gl::Vector<gl::uint32_t , 1u>;
    using Vector2u = gl::Vector<gl::uint32_t , 2u>;
    using Vector3u = gl::Vector<gl::uint32_t , 3u>;
    using Vector4u = gl::Vector<gl::uint32_t , 4u>;

    using Vector1f = gl::Vector<gl::float32_t, 1u>;
    using Vector2f = gl::Vector<gl::float32_t, 2u>;
    using Vector3f = gl::Vector<gl::float32_t, 3u>;
    using Vector4f = gl::Vector<gl::float32_t, 4u>;

    using Vector1d = gl::Vector<gl::float64_t, 1u>;
    using Vector2d = gl::Vector<gl::float64_t, 2u>;
    using Vector3d = gl::Vector<gl::float64_t, 3u>;
    using Vector4d = gl::Vector<gl::float64_t, 4u>;

    using Vector1r = gl::Vector<gl::range_t  , 1u>;
    using Vector2r = gl::Vector<gl::range_t  , 2u>;
    using Vector3r = gl::Vector<gl::range_t  , 3u>;
    using Vector4r = gl::Vector<gl::range_t  , 4u>;

    using Matrix2f = gl::Matrix<gl::float32_t, 2u>;
    using Matrix3f = gl::Matrix<gl::float32_t, 3u>;
    using Matrix4f = gl::Matrix<gl::float32_t, 4u>;





    static void _debug_callback(gl::enum_t, gl::enum_t, gl::uint32_t, gl::enum_t, gl::sizei_t, const gl::char_t*, const void*) {}
    using debug_callback_t = decltype(_debug_callback);
}
