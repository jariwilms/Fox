export module fox.rendering.api.opengl.types;

import std;
import <glad/gl.h>;
import vendor.glm;

export namespace fox::gfx::api::gl
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





    template<typename T, gl::uint32_t N>
    using vector     = glm::vec<N, T, glm::packed_highp>;
    template<typename T, gl::uint32_t R, gl::uint32_t C = R>
    using matrix     = glm::mat<R, C, T>;
    template<typename T>
    using quaternion = glm::qua<T, glm::packed_highp>;



    using vector1b = gl::vector<gl::boolean_t, 1u>;
    using vector2b = gl::vector<gl::boolean_t, 2u>;
    using vector3b = gl::vector<gl::boolean_t, 3u>;
    using vector4b = gl::vector<gl::boolean_t, 4u>;

    using vector1i = gl::vector<gl::int32_t,   1u>;
    using vector2i = gl::vector<gl::int32_t,   2u>;
    using vector3i = gl::vector<gl::int32_t,   3u>;
    using vector4i = gl::vector<gl::int32_t,   4u>;

    using vector1u = gl::vector<gl::uint32_t,  1u>;
    using vector2u = gl::vector<gl::uint32_t,  2u>;
    using vector3u = gl::vector<gl::uint32_t,  3u>;
    using vector4u = gl::vector<gl::uint32_t,  4u>;

    using vector1f = gl::vector<gl::float32_t, 1u>;
    using vector2f = gl::vector<gl::float32_t, 2u>;
    using vector3f = gl::vector<gl::float32_t, 3u>;
    using vector4f = gl::vector<gl::float32_t, 4u>;

    using vector1d = gl::vector<gl::float64_t, 1u>;
    using vector2d = gl::vector<gl::float64_t, 2u>;
    using vector3d = gl::vector<gl::float64_t, 3u>;
    using vector4d = gl::vector<gl::float64_t, 4u>;

    using matrix2f = gl::matrix<gl::float32_t, 2u>;
    using matrix3f = gl::matrix<gl::float32_t, 3u>;
    using matrix4f = gl::matrix<gl::float32_t, 4u>;





    void _debug_callback(gl::enum_t, gl::enum_t, gl::uint32_t, gl::enum_t, gl::sizei_t, const gl::char_t*, const gl::void_t*);
    using debug_callback_t = decltype(_debug_callback);
}
