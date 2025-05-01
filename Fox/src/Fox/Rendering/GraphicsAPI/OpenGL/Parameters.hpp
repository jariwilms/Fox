#pragma once

#include "stdafx.hpp"

#include "Fox/Rendering/GraphicsAPI/OpenGL/Types.hpp"
#include "Fox/Rendering/GraphicsAPI/OpenGL/Flags.hpp"

namespace fox::gfx::api::gl
{
    using dispatch_t = std::variant<gl::Vector3u, gl::offset_t>;

    using TextureParameter = std::variant<glf::Texture::MinificationFilter, glf::Texture::MagnificationFilter, glf::Texture::Wrapping>;









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

    using clear_v = std::variant<color_p, depth_p, stencil_p, depthstencil_p>;
}