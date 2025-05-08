#pragma once

#include "Types.hpp"
#include "Flags.hpp"

namespace fox::gfx::api::gl
{
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

    using  minification_p  = glf::Texture::MinificationFilter;
    using  magnification_p = glf::Texture::MagnificationFilter;
    struct wrapping_s_p    { glf::Texture::Wrapping       wrapping{}; };
    struct wrapping_t_p    { glf::Texture::Wrapping       wrapping{}; };
    struct wrapping_r_p    { glf::Texture::Wrapping       wrapping{}; };
    struct border_color_p  { std::array<gl::float32_t, 4> color   {}; };

    using dispatch_v    = std::variant<gl::Vector3u, gl::offset_t>;
    using texture_v     = std::variant<gl::minification_p, gl::magnification_p, gl::wrapping_s_p, gl::wrapping_t_p, gl::wrapping_r_p, gl::border_color_p>;
    using clear_v       = std::variant<gl::color_p, gl::depth_p, gl::stencil_p, gl::depthstencil_p>;
    using framebuffer_v = std::variant<framebuffer_p, glf::FrameBuffer::Source>;

}
