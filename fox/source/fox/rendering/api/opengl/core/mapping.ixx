export module fox.rendering.api.opengl.mapping;

import std;
import fox.rendering.api.opengl.flags;
import fox.rendering.api.opengl.types;
import fox.rendering.api.opengl.utility;
import fox.rendering.base.buffer;
import fox.rendering.base.cubemap;
import fox.rendering.base.pipeline;
import fox.rendering.base.query;
import fox.rendering.base.render_buffer;
import fox.rendering.base.render_state;
import fox.rendering.base.shader;
import fox.rendering.base.texture;
import fox.rendering.base.vertex_array;
import fox.rendering.base.frame_buffer;

export namespace fox::gfx::api::gl
{
    template<typename T>
    constexpr auto map_type             () -> gl::vertex_array_attribute_type_e
    {
        if constexpr (std::is_same_v<std::remove_cvref_t<T>, gl::int8_t   >) return gl::vertex_array_attribute_type_e::byte            ;
        if constexpr (std::is_same_v<std::remove_cvref_t<T>, gl::uint8_t  >) return gl::vertex_array_attribute_type_e::unsigned_byte   ;
        if constexpr (std::is_same_v<std::remove_cvref_t<T>, gl::int16_t  >) return gl::vertex_array_attribute_type_e::short_          ;
        if constexpr (std::is_same_v<std::remove_cvref_t<T>, gl::uint16_t >) return gl::vertex_array_attribute_type_e::unsigned_short  ;
        if constexpr (std::is_same_v<std::remove_cvref_t<T>, gl::int32_t  >) return gl::vertex_array_attribute_type_e::integer         ;
        if constexpr (std::is_same_v<std::remove_cvref_t<T>, gl::uint32_t >) return gl::vertex_array_attribute_type_e::unsigned_integer;
        if constexpr (std::is_same_v<std::remove_cvref_t<T>, gl::float32_t>) return gl::vertex_array_attribute_type_e::float_          ;
        if constexpr (std::is_same_v<std::remove_cvref_t<T>, gl::float64_t>) return gl::vertex_array_attribute_type_e::double_         ;
    }

    auto map_texture_format_base        (api::Texture::format_e format) -> gl::texture_base_format_e
    {
        switch (format)
        {
            using enum api::Texture::format_e;

            case r8_unorm    :
            case r16_unorm   :
            case r8_snorm    :
            case r16_snorm   :
            case r16_float   :
            case r32_float   : return gl::texture_base_format_e::r;
            
            case rg8_unorm   :
            case rg16_unorm  :
            case rg8_snorm   :
            case rg16_snorm  :
            case rg16_float  :
            case rg32_float  : return gl::texture_base_format_e::rg;
            
            case rgb8_unorm  :
            case rgb16_unorm :
            case rgb8_snorm  :
            case rgb16_snorm :
            case rgb8_srgb   :
            case rgb16_float :
            case rgb32_float : return gl::texture_base_format_e::rgb;
            
            case rgba8_unorm :
            case rgba16_unorm:
            case rgba8_snorm :
            case rgba16_snorm:
            case rgba8_srgb  :
            case rgba16_float:
            case rgba32_float: return gl::texture_base_format_e::rgba;
            
            case d16_unorm   :
            case d24_unorm   :
            case d32_float   : return gl::texture_base_format_e::d;
            
            case s8_uint     : return gl::texture_base_format_e::s;

            default: throw std::invalid_argument{ "Invalid format!" };
        }
    }
    auto map_texture_format             (api::Texture::format_e format) -> gl::texture_format_e
    {
        switch (format)
        {
            using enum api::Texture::format_e;

            case r8_unorm         : return gl::texture_format_e::r8_unorm;
            case rg8_unorm        : return gl::texture_format_e::rg8_unorm;
            case rgb8_unorm       : return gl::texture_format_e::rgb8_unorm;
            case rgba8_unorm      : return gl::texture_format_e::rgba8_unorm;
            case r16_unorm        : return gl::texture_format_e::r16_unorm;
            case rg16_unorm       : return gl::texture_format_e::rg16_unorm;
            case rgb16_unorm      : return gl::texture_format_e::rgb16_unorm;
            case rgba16_unorm     : return gl::texture_format_e::rgba16_unorm;
            case r8_snorm         : return gl::texture_format_e::r8_snorm;
            case rg8_snorm        : return gl::texture_format_e::rg8_snorm;
            case rgb8_snorm       : return gl::texture_format_e::rgb8_snorm;
            case rgba8_snorm      : return gl::texture_format_e::rgba8_snorm;
            case r16_snorm        : return gl::texture_format_e::r16_snorm;
            case rg16_snorm       : return gl::texture_format_e::rg16_snorm;
            case rgb16_snorm      : return gl::texture_format_e::rgb16_snorm;
            case rgba16_snorm     : return gl::texture_format_e::rgba16_snorm;
            case rgb8_srgb        : return gl::texture_format_e::rgb8_srgb;
            case rgba8_srgb       : return gl::texture_format_e::rgba8_srgb;
            case r16_float        : return gl::texture_format_e::r16_float;
            case rg16_float       : return gl::texture_format_e::rg16_float;
            case rgb16_float      : return gl::texture_format_e::rgb16_float;
            case rgba16_float     : return gl::texture_format_e::rgba16_float;
            case r32_float        : return gl::texture_format_e::r32_float;
            case rg32_float       : return gl::texture_format_e::rg32_float;
            case rgb32_float      : return gl::texture_format_e::rgb32_float;
            case rgba32_float     : return gl::texture_format_e::rgba32_float;
            case d16_unorm        : return gl::texture_format_e::d16_unorm;
            case d24_unorm        : return gl::texture_format_e::d24_unorm;
            case d32_float        : return gl::texture_format_e::d32_float;
            case d24_unorm_s8_uint: return gl::texture_format_e::d24_unorm_s8_uint;
            case d32_float_s8_uint: return gl::texture_format_e::d32_float_s8_uint;
            case s8_uint          : return gl::texture_format_e::s8_uint;

            default: throw std::invalid_argument{ "Invalid format!" };
        }
    }
    auto map_texture_format_type        (api::Texture::format_e format) -> gl::pixel_data_type_e
    {
        switch (format)
        {
            using enum api::Texture::format_e;

            case r8_unorm    :
            case rg8_unorm   :
            case rgb8_unorm  :
            case rgba8_unorm :  return gl::pixel_data_type_e::unsigned_byte_;

            case r16_unorm   :
            case rg16_unorm  :
            case rgb16_unorm :
            case rgba16_unorm: return gl::pixel_data_type_e::unsigned_short_;

            case r8_snorm    :
            case rg8_snorm   :
            case rgb8_snorm  :
            case rgba8_snorm : return gl::pixel_data_type_e::byte_;

            case r16_snorm   :
            case rg16_snorm  :
            case rgb16_snorm :
            case rgba16_snorm: return gl::pixel_data_type_e::short_;

            case rgb8_srgb   :
            case rgba8_srgb  : return gl::pixel_data_type_e::unsigned_byte_;
            
            case r16_float   :
            case rg16_float  :
            case rgb16_float :
            case rgba16_float: return gl::pixel_data_type_e::half_float_;
            
            case r32_float   :
            case rg32_float  :
            case rgb32_float :
            case rgba32_float: return gl::pixel_data_type_e::float_;
            
            default: throw std::invalid_argument{ "Invalid format!" };
        }
    }
    auto map_texture_min_filter         (api::Texture::filter_e filter) -> gl::texture_minification_filter_e
    {
        switch (filter)
        {
            using enum api::Texture::filter_e;

            case none     : return gl::texture_minification_filter_e::nearest;
            case nearest  : return gl::texture_minification_filter_e::nearest_mipmap_nearest;
            case bilinear : return gl::texture_minification_filter_e::linear_mipmap_nearest;
            case trilinear: return gl::texture_minification_filter_e::linear_mipmap_linear;

            default: throw std::invalid_argument{ "Invalid filter!" };
        }
    }
    auto map_texture_mag_filter         (api::Texture::filter_e filter) -> gl::texture_magnification_filter_e
    {
        switch (filter)
        {
            using enum api::Texture::filter_e;

            case none     : return gl::texture_magnification_filter_e::nearest;
            case nearest  : return gl::texture_magnification_filter_e::nearest;
            case bilinear : return gl::texture_magnification_filter_e::linear;
            case trilinear: return gl::texture_magnification_filter_e::linear;

            default: throw std::invalid_argument{ "Invalid filter!" };
        }
    }
    auto map_texture_wrapping           (api::Texture::wrapping_e wrapping) -> gl::texture_wrapping_e
    {
        switch (wrapping)
        {
            using enum api::Texture::wrapping_e;

            case clamp_to_edge         : return gl::texture_wrapping_e::clamp_to_edge;
            case clamp_to_border       : return gl::texture_wrapping_e::clamp_to_border;
            case repeat                : return gl::texture_wrapping_e::repeat;
            case mirrored_repeat       : return gl::texture_wrapping_e::mirrored_repeat;
            case mirrored_clamp_to_edge: return gl::texture_wrapping_e::mirrored_clamp_to_edge;

            default: throw std::invalid_argument{ "Invalid wrapping!" };
        }
    }
    auto map_render_buffer_format       (api::render_buffer::format_e format) -> gl::render_buffer_format_e
    {
        switch (format)
        {
            using enum api::render_buffer::format_e;

            case r8_unorm         : return gl::render_buffer_format_e::r8;
            case rg8_unorm        : return gl::render_buffer_format_e::rg8;
            case rgb8_unorm       : return gl::render_buffer_format_e::rgb8;
            case rgba8_unorm      : return gl::render_buffer_format_e::rgba8;
            case rgba8_srgb       : return gl::render_buffer_format_e::rgba8_srgb;
            case d16_unorm        : return gl::render_buffer_format_e::d16_unorm;
            case d24_unorm        : return gl::render_buffer_format_e::d24_unorm;
            case d32_float        : return gl::render_buffer_format_e::d32_float;
            case d24_unorm_s8_uint: return gl::render_buffer_format_e::d24_unorm_s8_uint;
            case d32_float_s8_uint: return gl::render_buffer_format_e::d32_float_s8_uint;
            case s8_uint          : return gl::render_buffer_format_e::s8_uint;

            default: throw std::invalid_argument{ "Invalid format!" };
        }
    }
    auto map_cubemap_texture_format_base(api::cubemap::format_e format) -> gl::texture_base_format_e
    {
        switch (format)
        {
            using enum api::cubemap::format_e;

            case r8_unorm    :
            case r16_unorm   :
            case r8_snorm    :
            case r16_snorm   :
            case r16_float   :
            case r32_float   : return gl::texture_base_format_e::r;
            
            case rg8_unorm   :
            case rg16_unorm  :
            case rg8_snorm   :
            case rg16_snorm  :
            case rg16_float  :
            case rg32_float  : return gl::texture_base_format_e::rg;
            
            case rgb8_unorm  :
            case rgb16_unorm :
            case rgb8_snorm  :
            case rgb16_snorm :
            case rgb8_srgb   :
            case rgb16_float :
            case rgb32_float : return gl::texture_base_format_e::rgb;
            
            case rgba8_unorm :
            case rgba16_unorm:
            case rgba8_snorm :
            case rgba16_snorm:
            case rgba8_srgb  :
            case rgba16_float:
            case rgba32_float: return gl::texture_base_format_e::rgba;
            
            case d16_unorm   :
            case d24_unorm   :
            case d32_float   : return gl::texture_base_format_e::d;
            
            case s8_uint     : return gl::texture_base_format_e::s;

            default: throw std::invalid_argument{ "Invalid format!" };
        }
    }
    auto map_cubemap_texture_format     (api::cubemap::format_e format) -> gl::texture_format_e
    {
        switch (format)
        {
            using enum api::cubemap::format_e;

            case r8_unorm         : return gl::texture_format_e::r8_unorm;
            case rg8_unorm        : return gl::texture_format_e::rg8_unorm;
            case rgb8_unorm       : return gl::texture_format_e::rgb8_unorm;
            case rgba8_unorm      : return gl::texture_format_e::rgba8_unorm;
            
            case r16_unorm        : return gl::texture_format_e::r16_unorm;
            case rg16_unorm       : return gl::texture_format_e::rg16_unorm;
            case rgb16_unorm      : return gl::texture_format_e::rgb16_unorm;
            case rgba16_unorm     : return gl::texture_format_e::rgba16_unorm;
            
            case r8_snorm         : return gl::texture_format_e::r8_snorm;
            case rg8_snorm        : return gl::texture_format_e::rg8_snorm;
            case rgb8_snorm       : return gl::texture_format_e::rgb8_snorm;
            case rgba8_snorm      : return gl::texture_format_e::rgba8_snorm;
            
            case r16_snorm        : return gl::texture_format_e::r16_snorm;
            case rg16_snorm       : return gl::texture_format_e::rg16_snorm;
            case rgb16_snorm      : return gl::texture_format_e::rgb16_snorm;
            case rgba16_snorm     : return gl::texture_format_e::rgba16_snorm;
            
            case rgb8_srgb        : return gl::texture_format_e::rgb8_srgb;
            case rgba8_srgb       : return gl::texture_format_e::rgba8_srgb;
            
            case r16_float        : return gl::texture_format_e::r16_float;
            case rg16_float       : return gl::texture_format_e::rg16_float;
            case rgb16_float      : return gl::texture_format_e::rgb16_float;
            case rgba16_float     : return gl::texture_format_e::rgba16_float;
            
            case r32_float        : return gl::texture_format_e::r32_float;
            case rg32_float       : return gl::texture_format_e::rg32_float;
            case rgb32_float      : return gl::texture_format_e::rgb32_float;
            case rgba32_float     : return gl::texture_format_e::rgba32_float;
            
            case d16_unorm        : return gl::texture_format_e::d16_unorm;
            case d24_unorm        : return gl::texture_format_e::d24_unorm;
            case d32_float        : return gl::texture_format_e::d32_float;
            
            case d24_unorm_s8_uint: return gl::texture_format_e::d24_unorm_s8_uint;
            case d32_float_s8_uint: return gl::texture_format_e::d32_float_s8_uint;
            
            case s8_uint          : return gl::texture_format_e::s8_uint;

            default: throw std::invalid_argument{ "Invalid format!" };
        }
    }
    auto map_cubemap_texture_format_type(api::cubemap::format_e format) -> gl::pixel_data_type_e
    {
        switch (format)
        {
            using enum api::cubemap::format_e;

            case r8_unorm    :
            case rg8_unorm   :
            case rgb8_unorm  :
            case rgba8_unorm : return gl::pixel_data_type_e::unsigned_byte_;

            case r16_unorm   :
            case rg16_unorm  :
            case rgb16_unorm :
            case rgba16_unorm: return gl::pixel_data_type_e::unsigned_short_;

            case r8_snorm    :
            case rg8_snorm   :
            case rgb8_snorm  :
            case rgba8_snorm : return gl::pixel_data_type_e::byte_;

            case r16_snorm   :
            case rg16_snorm  :
            case rgb16_snorm :
            case rgba16_snorm: return gl::pixel_data_type_e::short_;

            case rgb8_srgb   :
            case rgba8_srgb  : return gl::pixel_data_type_e::unsigned_byte_;

            case r16_float   :
            case rg16_float  :
            case rgb16_float :
            case rgba16_float: return gl::pixel_data_type_e::half_float_;

            case r32_float   :
            case rg32_float  :
            case rgb32_float :
            case rgba32_float: return gl::pixel_data_type_e::float_;
            
            default: throw std::invalid_argument{ "Invalid format!" };
        }
    }
    auto map_frame_buffer_target        (api::frame_buffer::target_e  target) -> gl::frame_buffer_target_e
    {
        switch (target)
        {
            using enum api::frame_buffer::target_e;

            case read : return gl::frame_buffer_target_e::read;
            case write: return gl::frame_buffer_target_e::write;

            default: throw std::invalid_argument{ "Invalid target!" };
        }
    }
    auto map_frame_buffer_attachment    (api::frame_buffer::attachment_e attachment) -> gl::frame_buffer_attachment_e
    {
        switch (attachment)
        {
            using enum api::frame_buffer::attachment_e;

            case color0      : return gl::frame_buffer_attachment_e::color0; 
            case color1      : return gl::frame_buffer_attachment_e::color1; 
            case color2      : return gl::frame_buffer_attachment_e::color2; 
            case color3      : return gl::frame_buffer_attachment_e::color3; 
            case color4      : return gl::frame_buffer_attachment_e::color4; 
            case color5      : return gl::frame_buffer_attachment_e::color5; 
            case color6      : return gl::frame_buffer_attachment_e::color6; 
            case color7      : return gl::frame_buffer_attachment_e::color7; 

            case depth       : return gl::frame_buffer_attachment_e::depth;
            case stencil     : return gl::frame_buffer_attachment_e::stencil;
            case depth_stencil: return gl::frame_buffer_attachment_e::depth_stencil;

            default: throw std::invalid_argument{ "Invalid attachment!" };
        }
    }
    auto map_program_stage              (api::shader::stage_e stage_e) -> gl::program_stage_e
    {
        switch (stage_e)
        {
            using enum api::shader::stage_e;

            case vertex                 : return gl::program_stage_e::vertex;
            case tessellation_control   : return gl::program_stage_e::tessellation_control;
            case tessellation_evaluation: return gl::program_stage_e::tessellation_evaluation;
            case geometry               : return gl::program_stage_e::geometry;
            case fragment               : return gl::program_stage_e::fragment;
            case compute                : return gl::program_stage_e::compute;

            default: throw std::invalid_argument{ "Invalid stage!" };
        }
    }                                                                      
    auto map_shader_type                (api::shader::stage_e stage_e) -> gl::shader_type_e
    {
        switch (stage_e)
        {
            using enum api::shader::stage_e;

            case vertex                 : return gl::shader_type_e::vertex;
            case tessellation_control   : return gl::shader_type_e::tessellation_control;
            case tessellation_evaluation: return gl::shader_type_e::tessellation_evaluation;
            case geometry               : return gl::shader_type_e::geometry;
            case fragment               : return gl::shader_type_e::fragment;
            case compute                : return gl::shader_type_e::compute;

            default: throw std::invalid_argument{ "Invalid stage!" };
        }
    }
    auto map_query_target               (api::query::target_e target) -> gl::query_target_e
    {
        switch (target)
        {
            using enum api::query::target_e;

            case any_samples_passed                        : return gl::query_target_e::any_samples_passed;
            case any_samples_passed_conservative           : return gl::query_target_e::any_samples_passed_conservative;
            case clipping_input_primitives                 : return gl::query_target_e::clipping_input_primitives;
            case clipping_output_primitives                : return gl::query_target_e::clipping_output_primitives;
            case compute_shader_invocations                : return gl::query_target_e::compute_shader_invocations;
            case fragment_shader_invocations               : return gl::query_target_e::fragment_shader_invocations;
            case geometry_shader_invocations               : return gl::query_target_e::geometry_shader_invocations;
            case geometry_shader_primitives_emitted        : return gl::query_target_e::geometry_shader_primitives_emitted;
            case primitives_generated                      : return gl::query_target_e::primitives_generated;
            case primitives_submitted                      : return gl::query_target_e::primitives_submitted;
            case samples_passed                            : return gl::query_target_e::samples_passed;
            case tessellation_control_shader_patches       : return gl::query_target_e::tessellation_control_shader_patches;
            case tessellation_evaluation_shader_invocations: return gl::query_target_e::tessellation_evaluation_shader_invocations;
            case time_elapsed                              : return gl::query_target_e::time_elapsed;
            case timestamp                                 : return gl::query_target_e::timestamp;
            case transform_feedback_overflow               : return gl::query_target_e::transform_feedback_overflow;
            case transform_feedback_primitives_written     : return gl::query_target_e::transform_feedback_primitives_written;
            case transform_feedback_stream_overflow        : return gl::query_target_e::transform_feedback_stream_overflow;
            case vertex_shader_invocations                 : return gl::query_target_e::vertex_shader_invocations;
            case vertices_submitted                        : return gl::query_target_e::vertices_submitted;

            default: throw std::invalid_argument{ "Invalid target!" };
        }
    }
    auto map_depth_function             (api::render_state::depth_function_e depthFunction) -> gl::depth_function_e
    {
        switch (depthFunction)
        {
            using enum api::render_state::depth_function_e;

            case always      : return gl::depth_function_e::always;
            case never       : return gl::depth_function_e::never;
            case equal       : return gl::depth_function_e::equal;
            case notequal    : return gl::depth_function_e::not_equal;
            case less        : return gl::depth_function_e::less;
            case greater     : return gl::depth_function_e::greater;
            case lessequal   : return gl::depth_function_e::less_equal;
            case greaterequal: return gl::depth_function_e::greater_equal;

            default: throw std::invalid_argument{ "Invalid function!" };
        }
    }
    auto map_culling_face               (api::render_state::face_culling_e cullingFace) -> gl::culling_facet_e
    {
        switch (cullingFace)
        {
            using enum api::render_state::face_culling_e;

            case front     : return gl::culling_facet_e::front;
            case back      : return gl::culling_facet_e::back;
            case front_back: return gl::culling_facet_e::front_back;

            default: throw std::invalid_argument{ "Invalid face!" };
        }
    }
}
