#pragma once

import std;

import fox.rendering.api.opengl.flags;
import fox.rendering.api.opengl.types;

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
        std::variant<std::array<gl::int32_t  , 4u>, 
                     std::array<gl::uint32_t , 4u>, 
                     std::array<gl::float32_t, 4u>> value{}; 
    };
    struct minimum_lod
    { 
        gl::float32_t value{}; 
    };
    struct maximum_lod
    { 
        gl::float32_t value{}; 
    };
    struct depth_stencil_mode
    {
        glf::Texture::BaseFormat value{};
    };
    struct base_level
    {
        gl::uint32_t value{};
    };
    struct lod_bias
    {
        gl::float32_t value{};
    };
    struct maximum_anisotropy
    {
        gl::float32_t value{};
    };
    struct maximum_level
    {
        gl::uint32_t value{};
    };
    struct swizzle_r
    {
        glf::Texture::Swizzle value{};
    };
    struct swizzle_g
    {
        glf::Texture::Swizzle value{};
    };
    struct swizzle_b
    {
        glf::Texture::Swizzle value{};
    };
    struct swizzle_a
    {
        glf::Texture::Swizzle value{};
    };
    struct swizzle_rgba
    {
        std::array<glf::Texture::Swizzle, 4> value{};
    };
    struct fade_threshold_size
    {
        gl::float32_t value{};
    };
    struct sprite_coordinate_origin
    {
        glf::Point::Origin value{};
    };
    struct patch_vertices
    {
        gl::uint32_t value{};
    };
    struct patch_default_outer_level
    {
        std::array<gl::float32_t, 4u> value{};
    };
    struct patch_default_inner_level
    {
        std::array<gl::float32_t, 4u> value{};
    };



    using dispatch_v          = std::variant<gl::Vector3u, gl::offset_t>;
    using texture_parameter_v = std::variant<
                                    glp::compare_function    , glp::compare_mode, 
                                    glp::base_level          , glp::maximum_level, 
                                    glp::border_color        , 
                                    glp::depth_stencil_mode  , 
                                    glp::magnification_filter, glp::minification_filter, glp::maximum_anisotropy, 
                                    glp::wrapping_s          , glp::wrapping_t         , glp::wrapping_r, 
                                    glp::swizzle_r           , glp::swizzle_g          , glp::swizzle_b , glp::swizzle_a, glp::swizzle_rgba, 
                                    glp::maximum_lod         , glp::minimum_lod        , glp::lod_bias>;
    using clear_v             = std::variant<glp::color_index, glp::depth, glp::stencil, glp::depthstencil>;
    using point_parameter_v   = std::variant<glp::fade_threshold_size, glp::sprite_coordinate_origin>;
    using sampler_parameter_v = std::variant<
                                    glp::magnification_filter, glp::minification_filter, 
                                    glp::maximum_lod         , glp::minimum_lod        , 
                                    glp::wrapping_s          , glp::wrapping_t         , glp::wrapping_r, 
                                    glp::border_color        , 
                                    glp::compare_mode        , glp::compare_function>;
    using patch_parameter_v   = std::variant<glp::patch_vertices, glp::patch_default_outer_level, glp::patch_default_inner_level>;
}
