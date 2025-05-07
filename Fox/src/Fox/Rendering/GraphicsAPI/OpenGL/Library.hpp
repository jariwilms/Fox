#pragma once

#include "stdafx.hpp"
#include "Flags.hpp"

namespace fox::gfx::api::gl
{
    template<typename T>
    static constexpr auto to_underlying(T value) noexcept
    {
        return static_cast<std::underlying_type_t<T>>(value);
    }
    template<typename T>
    static constexpr auto to_underlying_ptr(T* value)
    {
        return reinterpret_cast<std::underlying_type_t<T>*>(value);
    }
    template<typename T>
    static constexpr auto to_underlying_ptr(const T* value)
    {
        return reinterpret_cast<const std::underlying_type_t<T>*>(value);
    }





    struct color_p
    {
        gl::uint32_t                                           index{};
        std::variant<gl::Vector4i, gl::Vector4u, gl::Vector4f> color{};
    };
    struct depth_p
    {
        std::variant<gl::int32_t, gl::uint32_t, gl::float32_t> value{};
    };
    struct stencil_p
    {
        std::variant<gl::int32_t, gl::uint32_t, gl::float32_t> value{};
    };
    struct depthstencil_p
    {
        gl::float32_t depth{};
        gl::int32_t   stencil{};
    };

    struct framebuffer_p
    {
        gl::handle_t                 frameBuffer{};
        glf::FrameBuffer::Attachment attachment{};
    };

    using dispatch_v    = std::variant<gl::Vector3u, gl::offset_t>;
    using texture_v     = std::variant<glf::Texture::MinificationFilter, glf::Texture::MagnificationFilter, glf::Texture::Wrapping>;
    using clear_v       = std::variant<gl::color_p, gl::depth_p, gl::stencil_p, gl::depthstencil_p>;
    using framebuffer_v = std::variant<framebuffer_p, glf::FrameBuffer::Source>;





    template<typename T>
    concept arithmetic_type_c =
        (
            std::is_same_v<T, gl::int8_t>    || 
            std::is_same_v<T, gl::uint8_t>   || 
            std::is_same_v<T, gl::int16_t>   || 
            std::is_same_v<T, gl::uint16_t>  || 
            std::is_same_v<T, gl::int32_t>   || 
            std::is_same_v<T, gl::uint32_t>  || 
            std::is_same_v<T, gl::int64_t>   || 
            std::is_same_v<T, gl::uint64_t>  || 
            std::is_same_v<T, gl::float16_t> ||
            std::is_same_v<T, gl::float32_t> || 
            std::is_same_v<T, gl::float64_t>
        );

    template<glf::Texture::Target T, glf::Texture::Target U>
    concept valid_texture_view_c = 
        (T == glf::Texture::Target::_1D                 && (U == glf::Texture::Target::_1D            || U == glf::Texture::Target::_1DArray)                                                                                              ) ||
        (T == glf::Texture::Target::_2D                 && (U == glf::Texture::Target::_2D            || U == glf::Texture::Target::_2DArray)                                                                                              ) ||
        (T == glf::Texture::Target::_3D                 && (U == glf::Texture::Target::_3D)                                                                                                                                                ) ||
        (T == glf::Texture::Target::CubeMap             && (U == glf::Texture::Target::CubeMap        || U == glf::Texture::Target::_2D                 || U == glf::Texture::Target::_2DArray || U == glf::Texture::Target::CubeMapArray) ) ||
        (T == glf::Texture::Target::Rectangle           && (U == glf::Texture::Target::Rectangle)                                                                                                                                          ) ||
        (T == glf::Texture::Target::_1DArray            && (U == glf::Texture::Target::_1D            || U == glf::Texture::Target::_1DArray)                                                                                              ) ||
        (T == glf::Texture::Target::_2DArray            && (U == glf::Texture::Target::_2D            || U == glf::Texture::Target::_2DArray)                                                                                              ) ||
        (T == glf::Texture::Target::CubeMapArray        && (U == glf::Texture::Target::_2D            || U == glf::Texture::Target::_2DArray            || U == glf::Texture::Target::CubeMap  || U == glf::Texture::Target::CubeMapArray) ) ||
        (T == glf::Texture::Target::_2DMultisample      && (U == glf::Texture::Target::_2DMultisample || U == glf::Texture::Target::_2DMultisampleArray)                                                                                   ) ||
        (T == glf::Texture::Target::_2DMultisampleArray && (U == glf::Texture::Target::_2DMultisample || U == glf::Texture::Target::_2DMultisampleArray));
}
