#pragma once

#include "Types.hpp"
#include "Flags.hpp"

namespace fox::gfx::api::glp
{
    struct color_index
    {
        gl::uint32_t                                           index{};
        std::variant<gl::Vector4i, gl::Vector4u, gl::Vector4f> color{};
    };
    struct depth
    {
        std::variant<gl::int32_t, gl::uint32_t, gl::float32_t> value{};
    };
    struct stencil
    {
        std::variant<gl::int32_t, gl::uint32_t, gl::float32_t> value{};
    };
    struct depthstencil
    {
        gl::float32_t depth{};
        gl::int32_t   stencil{};
    };
    struct framebuffer
    {
        gl::handle_t                 frameBuffer{};
        glf::FrameBuffer::Attachment attachment{};
    };

    struct compare_mode
    { 
        glf::Texture::CompareMode value{}; 
    };
    struct compare_function     
    { 
        glf::Texture::CompareFunction value{}; 
    };
    struct magnification_filter 
    { 
        glf::Texture::MagnificationFilter value{}; 
    };
    struct minification_filter  
    { 
        glf::Texture::MinificationFilter value{}; 
    };
    struct wrapping_s           
    { 
        glf::Texture::Wrapping value{}; 
    };
    struct wrapping_t           
    { 
        glf::Texture::Wrapping value{}; 
    };
    struct wrapping_r           
    { 
        glf::Texture::Wrapping value{}; 
    };
    struct border_color         
    { 
        std::variant<std::array<gl::int32_t  , 4>, 
                     std::array<gl::uint32_t , 4>, 
                     std::array<gl::float32_t, 4>> value{}; 
    };
    struct minimum_lod_p
    { 
        gl::float32_t value{}; 
    };
    struct maximum_lod_p
    { 
        gl::float32_t value{}; 
    };



    using dispatch_t          = std::variant<gl::Vector3u, gl::offset_t>;
    using texture_parameter_t = std::variant<glp::minification_filter, glp::magnification_filter, glp::wrapping_s, glp::wrapping_t, glp::wrapping_r, glp::border_color>;
    using clear_t             = std::variant<glp::color_index, glp::depth, glp::stencil, glp::depthstencil>;
    using framebuffer_t       = std::variant<framebuffer, glf::FrameBuffer::Source>;
    using point_parameter_t   = std::variant<gl::float32_t, glf::Point::Parameter>;
    using sampler_parameter_t = std::variant<
                                    magnification_filter, minification_filter, 
                                    maximum_lod_p       , minimum_lod_p      , 
                                    wrapping_s          , wrapping_t         , wrapping_r, 
                                    border_color        , 
                                    compare_mode        , compare_function>;
}
