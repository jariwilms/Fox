#pragma once

#include <stdafx.hpp>

#include <glad/gl.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace fox::gfx::api::gl
{
    using void_t     = GLvoid      ;
    using bool_t     = bool        ; //Fundamental
    using boolean_t  = GLboolean   ; //Unsigned char
    using char_t     = GLchar      ;
    using byte_t     = GLubyte     ;

    using int8_t     = GLbyte      ;
    using uint8_t    = GLubyte     ;
    using int16_t    = GLshort     ;
    using uint16_t   = GLushort    ;
    using int32_t    = GLint       ;
    using uint32_t   = GLuint      ;
    using int64_t    = GLint64     ;
    using uint64_t   = GLuint64    ;
    using float16_t  = GLhalf      ;
    using float32_t  = GLfloat     ;
    using float64_t  = GLdouble    ;

    using enum_t     = GLenum      ; //Enumerated constant
    using sizei_t    = GLsizei     ; //Sizes and dimensions (may not be negative)
    using size_t     = GLsizeiptr  ; //Number of bytes
    using offset_t   = GLintptr    ; //Number of bytes offset
    using count_t    = gl::uint32_t; //Number of elements
    using index_t    = gl::uint32_t; //Number of elements offset
    using sync_t     = GLsync      ; //Synchronization primitive
    using bitfield_t = GLbitfield  ; //Bitwise combination of flags
    using time_t     = gl::uint64_t; //Duration in nanoseconds

    using pointer_t  = gl::void_t* ; //Generic pointer type

    enum : gl::bool_t
    {
        False = GL_FALSE,
        True  = GL_TRUE,
    };
    
    enum class handle_t  : gl::uint32_t {};
    enum class binding_t : gl::index_t  {};
    enum class key_t     : gl::uint64_t {};





    template<typename T, gl::uint32_t N> using Vector     = glm::vec<N, T, glm::packed_highp>;
    template<typename T, gl::uint32_t N> using Matrix     = glm::mat<N, N, T>;
                                         using Quaternion = glm::quat;

    using Vector1b = gl::Vector<gl::boolean_t, 1u>;
    using Vector2b = gl::Vector<gl::boolean_t, 2u>;
    using Vector3b = gl::Vector<gl::boolean_t, 3u>;
    using Vector4b = gl::Vector<gl::boolean_t, 4u>;

    using Vector1i = gl::Vector<gl::int32_t,   1u>;
    using Vector2i = gl::Vector<gl::int32_t,   2u>;
    using Vector3i = gl::Vector<gl::int32_t,   3u>;
    using Vector4i = gl::Vector<gl::int32_t,   4u>;

    using Vector1u = gl::Vector<gl::uint32_t,  1u>;
    using Vector2u = gl::Vector<gl::uint32_t,  2u>;
    using Vector3u = gl::Vector<gl::uint32_t,  3u>;
    using Vector4u = gl::Vector<gl::uint32_t,  4u>;

    using Vector1f = gl::Vector<gl::float32_t, 1u>;
    using Vector2f = gl::Vector<gl::float32_t, 2u>;
    using Vector3f = gl::Vector<gl::float32_t, 3u>;
    using Vector4f = gl::Vector<gl::float32_t, 4u>;

    using Vector1d = gl::Vector<gl::float64_t, 1u>;
    using Vector2d = gl::Vector<gl::float64_t, 2u>;
    using Vector3d = gl::Vector<gl::float64_t, 3u>;
    using Vector4d = gl::Vector<gl::float64_t, 4u>;

    using Matrix2f = gl::Matrix<gl::float32_t, 2u>;
    using Matrix3f = gl::Matrix<gl::float32_t, 3u>;
    using Matrix4f = gl::Matrix<gl::float32_t, 4u>;





    template<typename T, gl::uint32_t N>
    struct region_t
    {
        constexpr region_t(const gl::Vector<T, N>& extent = {}, const gl::Vector<T, N>& origin = {})
            : extent{ extent }, origin{ origin } {}

        auto operator==(const region_t&) const -> gl::bool_t = default;

        gl::Vector<T, N> extent{};
        gl::Vector<T, N> origin{};
    };
    struct range_t
    {
        constexpr range_t(gl::count_t count = {}, gl::index_t index = {})
            : count{ count }, index{ index } {}

        auto operator==(const range_t&) const -> gl::bool_t = default;

        gl::count_t count{};
        gl::index_t index{};
    };
    struct byterange_t
    {
        constexpr byterange_t(gl::size_t size = {}, gl::offset_t offset = {})
            : size{ size }, offset{ offset } {}

        auto operator==(const byterange_t&) const -> gl::bool_t = default;

        gl::size_t   size{};
        gl::offset_t offset{};
    };

    using length_t      = gl::region_t<gl::uint32_t, 1u>;
    using area_t        = gl::region_t<gl::uint32_t, 2u>;
    using volume_t      = gl::region_t<gl::uint32_t, 3u>;
    using hypervolume_t = gl::region_t<gl::uint32_t, 4u>; //Yes, this exists

    using lock_t        = std::tuple<gl::range_t, gl::sync_t>;

    template<typename... T>
    class proxy_t
    {
    public:
        template<typename U> requires (std::is_convertible_v<U, T> && ...)
        constexpr proxy_t(U&&  value )
            : pack{ std::make_tuple(static_cast<T>(std::forward<U>(value))...) } {}
        constexpr proxy_t(T... values)
            : pack{ std::make_tuple(values...) } {}

        template<typename Fn>
        void apply(Fn&& function)
        {
            std::apply([function](auto&&... value) { ((function(value)), ...); }, pack);
        }

        std::tuple<T...> pack;
    };





    static void _debug_callback(gl::enum_t, gl::enum_t, gl::uint32_t, gl::enum_t, gl::sizei_t, const gl::char_t*, const gl::void_t*) {}
    using debug_callback_t = decltype(_debug_callback);
}
