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





    struct compare_mode_p         { glf::Texture::CompareMode         value{}; };
    struct compare_function_p     { glf::Texture::CompareFunction     value{}; };
    struct magnification_filter_p { glf::Texture::MagnificationFilter value{}; };
    struct minification_filter_p  { glf::Texture::MinificationFilter  value{}; };
    struct wrapping_s_p           { glf::Texture::Wrapping            value{}; };
    struct wrapping_t_p           { glf::Texture::Wrapping            value{}; };
    struct wrapping_r_p           { glf::Texture::Wrapping            value{}; };
    struct border_color_p         { std::variant<std::array<gl::int32_t  , 4>, 
                                                 std::array<gl::uint32_t , 4>, 
                                                 std::array<gl::float32_t, 4>> value{}; };
    struct minimum_lod_p          { gl::float32_t                     value{}; };
    struct maximum_lod_p          { gl::float32_t                     value{}; };



    using dispatch_v          = std::variant<gl::Vector3u, gl::offset_t>;
    using texture_parameter_v = std::variant<gl::minification_filter_p, gl::magnification_filter_p, gl::wrapping_s_p, gl::wrapping_t_p, gl::wrapping_r_p, gl::border_color_p>;
    using clear_v             = std::variant<gl::color_p, gl::depth_p, gl::stencil_p, gl::depthstencil_p>;
    using framebuffer_v       = std::variant<framebuffer_p, glf::FrameBuffer::Source>;
    using point_parameter_v   = std::variant<gl::float32_t, glf::Point::Parameter>;


    using sampler_parameter_v = std::variant<
                                    magnification_filter_p, minification_filter_p, 
                                    maximum_lod_p         , minimum_lod_p        , 
                                    wrapping_s_p          , wrapping_t_p         , wrapping_r_p, 
                                    border_color_p        , 
                                    compare_mode_p     , compare_function_p>;
}
