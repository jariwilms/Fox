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

    auto map_texture_format_base        (api::Texture::Format format) -> gl::texture_base_format_e
    {
        switch (format)
        {
            using enum api::Texture::Format;

            case R8_UNORM    :
            case R16_UNORM   :
            case R8_SNORM    :
            case R16_SNORM   :
            case R16_FLOAT   :
            case R32_FLOAT   : return gl::texture_base_format_e::r;
            
            case RG8_UNORM   :
            case RG16_UNORM  :
            case RG8_SNORM   :
            case RG16_SNORM  :
            case RG16_FLOAT  :
            case RG32_FLOAT  : return gl::texture_base_format_e::rg;
            
            case RGB8_UNORM  :
            case RGB16_UNORM :
            case RGB8_SNORM  :
            case RGB16_SNORM :
            case RGB8_SRGB   :
            case RGB16_FLOAT :
            case RGB32_FLOAT : return gl::texture_base_format_e::rgb;
            
            case RGBA8_UNORM :
            case RGBA16_UNORM:
            case RGBA8_SNORM :
            case RGBA16_SNORM:
            case RGBA8_SRGB  :
            case RGBA16_FLOAT:
            case RGBA32_FLOAT: return gl::texture_base_format_e::rgba;
            
            case D16_UNORM   :
            case D24_UNORM   :
            case D32_FLOAT   : return gl::texture_base_format_e::d;
            
            case S8_UINT     : return gl::texture_base_format_e::s;

            default: throw std::invalid_argument{ "Invalid format!" };
        }
    }
    auto map_texture_format             (api::Texture::Format format) -> gl::texture_format_e
    {
        switch (format)
        {
            using enum api::Texture::Format;

            case R8_UNORM         : return gl::texture_format_e::r8_unorm;
            case RG8_UNORM        : return gl::texture_format_e::rg8_unorm;
            case RGB8_UNORM       : return gl::texture_format_e::rgb8_unorm;
            case RGBA8_UNORM      : return gl::texture_format_e::rgba8_unorm;
            case R16_UNORM        : return gl::texture_format_e::r16_unorm;
            case RG16_UNORM       : return gl::texture_format_e::rg16_unorm;
            case RGB16_UNORM      : return gl::texture_format_e::rgb16_unorm;
            case RGBA16_UNORM     : return gl::texture_format_e::rgba16_unorm;
            case R8_SNORM         : return gl::texture_format_e::r8_snorm;
            case RG8_SNORM        : return gl::texture_format_e::rg8_snorm;
            case RGB8_SNORM       : return gl::texture_format_e::rgb8_snorm;
            case RGBA8_SNORM      : return gl::texture_format_e::rgba8_snorm;
            case R16_SNORM        : return gl::texture_format_e::r16_snorm;
            case RG16_SNORM       : return gl::texture_format_e::rg16_snorm;
            case RGB16_SNORM      : return gl::texture_format_e::rgb16_snorm;
            case RGBA16_SNORM     : return gl::texture_format_e::rgba16_snorm;
            case RGB8_SRGB        : return gl::texture_format_e::rgb8_srgb;
            case RGBA8_SRGB       : return gl::texture_format_e::rgba8_srgb;
            case R16_FLOAT        : return gl::texture_format_e::r16_float;
            case RG16_FLOAT       : return gl::texture_format_e::rg16_float;
            case RGB16_FLOAT      : return gl::texture_format_e::rgb16_float;
            case RGBA16_FLOAT     : return gl::texture_format_e::rgba16_float;
            case R32_FLOAT        : return gl::texture_format_e::r32_float;
            case RG32_FLOAT       : return gl::texture_format_e::rg32_float;
            case RGB32_FLOAT      : return gl::texture_format_e::rgb32_float;
            case RGBA32_FLOAT     : return gl::texture_format_e::rgba32_float;
            case D16_UNORM        : return gl::texture_format_e::d16_unorm;
            case D24_UNORM        : return gl::texture_format_e::d24_unorm;
            case D32_FLOAT        : return gl::texture_format_e::d32_float;
            case D24_UNORM_S8_UINT: return gl::texture_format_e::d24_unorm_s8_uint;
            case D32_FLOAT_S8_UINT: return gl::texture_format_e::d32_float_s8_uint;
            case S8_UINT          : return gl::texture_format_e::s8_uint;

            default: throw std::invalid_argument{ "Invalid format!" };
        }
    }
    auto map_texture_format_type        (api::Texture::Format format) -> gl::pixel_data_type_e
    {
        switch (format)
        {
            using enum api::Texture::Format;

            case R8_UNORM    :
            case RG8_UNORM   :
            case RGB8_UNORM  :
            case RGBA8_UNORM :  return gl::pixel_data_type_e::unsigned_byte_;

            case R16_UNORM   :
            case RG16_UNORM  :
            case RGB16_UNORM :
            case RGBA16_UNORM: return gl::pixel_data_type_e::unsigned_short_;

            case R8_SNORM    :
            case RG8_SNORM   :
            case RGB8_SNORM  :
            case RGBA8_SNORM : return gl::pixel_data_type_e::byte_;

            case R16_SNORM   :
            case RG16_SNORM  :
            case RGB16_SNORM :
            case RGBA16_SNORM: return gl::pixel_data_type_e::short_;

            case RGB8_SRGB   :
            case RGBA8_SRGB  : return gl::pixel_data_type_e::unsigned_byte_;
            
            case R16_FLOAT   :
            case RG16_FLOAT  :
            case RGB16_FLOAT :
            case RGBA16_FLOAT: return gl::pixel_data_type_e::half_float_;
            
            case R32_FLOAT   :
            case RG32_FLOAT  :
            case RGB32_FLOAT :
            case RGBA32_FLOAT: return gl::pixel_data_type_e::float_;
            
            default: throw std::invalid_argument{ "Invalid format!" };
        }
    }
    auto map_texture_min_filter         (api::Texture::Filter filter) -> gl::texture_minification_filter_e
    {
        switch (filter)
        {
            using enum api::Texture::Filter;

            case None     : return gl::texture_minification_filter_e::nearest;
            case Nearest  : return gl::texture_minification_filter_e::nearest_mipmap_nearest;
            case Bilinear : return gl::texture_minification_filter_e::linear_mipmap_nearest;
            case Trilinear: return gl::texture_minification_filter_e::linear_mipmap_linear;

            default: throw std::invalid_argument{ "Invalid filter!" };
        }
    }
    auto map_texture_mag_filter         (api::Texture::Filter filter) -> gl::texture_magnification_filter_e
    {
        switch (filter)
        {
            using enum api::Texture::Filter;

            case None     : return gl::texture_magnification_filter_e::nearest;
            case Nearest  : return gl::texture_magnification_filter_e::nearest;
            case Bilinear : return gl::texture_magnification_filter_e::linear;
            case Trilinear: return gl::texture_magnification_filter_e::linear;

            default: throw std::invalid_argument{ "Invalid filter!" };
        }
    }
    auto map_texture_wrapping           (api::Texture::Wrapping wrapping) -> gl::texture_wrapping_e
    {
        switch (wrapping)
        {
            using enum api::Texture::Wrapping;

            case ClampToEdge        : return gl::texture_wrapping_e::clamp_to_edge;
            case ClampToBorder      : return gl::texture_wrapping_e::clamp_to_border;
            case Repeat             : return gl::texture_wrapping_e::repeat;
            case MirroredRepeat     : return gl::texture_wrapping_e::mirrored_repeat;
            case MirroredClampToEdge: return gl::texture_wrapping_e::mirrored_clamp_to_edge;

            default: throw std::invalid_argument{ "Invalid wrapping!" };
        }
    }
    auto map_render_buffer_format       (api::render_buffer::Format format) -> gl::render_buffer_format_e
    {
        switch (format)
        {
            using enum api::render_buffer::Format;

            case R8_UNORM         : return gl::render_buffer_format_e::r8;
            case RG8_UNORM        : return gl::render_buffer_format_e::rg8;
            case RGB8_UNORM       : return gl::render_buffer_format_e::rgb8;
            case RGBA8_UNORM      : return gl::render_buffer_format_e::rgba8;
            case RGBA8_SRGB       : return gl::render_buffer_format_e::rgba8_srgb;
            case D16_UNORM        : return gl::render_buffer_format_e::d16_unorm;
            case D24_UNORM        : return gl::render_buffer_format_e::d24_unorm;
            case D32_FLOAT        : return gl::render_buffer_format_e::d32_float;
            case D24_UNORM_S8_UINT: return gl::render_buffer_format_e::d24_unorm_s8_uint;
            case D32_FLOAT_S8_UINT: return gl::render_buffer_format_e::d32_float_s8_uint;
            case S8_UINT          : return gl::render_buffer_format_e::s8_uint;

            default: throw std::invalid_argument{ "Invalid format!" };
        }
    }
    auto map_cubemap_texture_format_base(api::cubemap::Format format) -> gl::texture_base_format_e
    {
        switch (format)
        {
            using enum api::cubemap::Format;

            case R8_UNORM    :
            case R16_UNORM   :
            case R8_SNORM    :
            case R16_SNORM   :
            case R16_FLOAT   :
            case R32_FLOAT   : return gl::texture_base_format_e::r;
            
            case RG8_UNORM   :
            case RG16_UNORM  :
            case RG8_SNORM   :
            case RG16_SNORM  :
            case RG16_FLOAT  :
            case RG32_FLOAT  : return gl::texture_base_format_e::rg;
            
            case RGB8_UNORM  :
            case RGB16_UNORM :
            case RGB8_SNORM  :
            case RGB16_SNORM :
            case RGB8_SRGB   :
            case RGB16_FLOAT :
            case RGB32_FLOAT : return gl::texture_base_format_e::rgb;
            
            case RGBA8_UNORM :
            case RGBA16_UNORM:
            case RGBA8_SNORM :
            case RGBA16_SNORM:
            case RGBA8_SRGB  :
            case RGBA16_FLOAT:
            case RGBA32_FLOAT: return gl::texture_base_format_e::rgba;
            
            case D16_UNORM   :
            case D24_UNORM   :
            case D32_FLOAT   : return gl::texture_base_format_e::d;
            
            case S8_UINT     : return gl::texture_base_format_e::s;

            default: throw std::invalid_argument{ "Invalid format!" };
        }
    }
    auto map_cubemap_texture_format     (api::cubemap::Format format) -> gl::texture_format_e
    {
        switch (format)
        {
            using enum api::cubemap::Format;

            case R8_UNORM         : return gl::texture_format_e::r8_unorm;
            case RG8_UNORM        : return gl::texture_format_e::rg8_unorm;
            case RGB8_UNORM       : return gl::texture_format_e::rgb8_unorm;
            case RGBA8_UNORM      : return gl::texture_format_e::rgba8_unorm;
            
            case R16_UNORM        : return gl::texture_format_e::r16_unorm;
            case RG16_UNORM       : return gl::texture_format_e::rg16_unorm;
            case RGB16_UNORM      : return gl::texture_format_e::rgb16_unorm;
            case RGBA16_UNORM     : return gl::texture_format_e::rgba16_unorm;
            
            case R8_SNORM         : return gl::texture_format_e::r8_snorm;
            case RG8_SNORM        : return gl::texture_format_e::rg8_snorm;
            case RGB8_SNORM       : return gl::texture_format_e::rgb8_snorm;
            case RGBA8_SNORM      : return gl::texture_format_e::rgba8_snorm;
            
            case R16_SNORM        : return gl::texture_format_e::r16_snorm;
            case RG16_SNORM       : return gl::texture_format_e::rg16_snorm;
            case RGB16_SNORM      : return gl::texture_format_e::rgb16_snorm;
            case RGBA16_SNORM     : return gl::texture_format_e::rgba16_snorm;
            
            case RGB8_SRGB        : return gl::texture_format_e::rgb8_srgb;
            case RGBA8_SRGB       : return gl::texture_format_e::rgba8_srgb;
            
            case R16_FLOAT        : return gl::texture_format_e::r16_float;
            case RG16_FLOAT       : return gl::texture_format_e::rg16_float;
            case RGB16_FLOAT      : return gl::texture_format_e::rgb16_float;
            case RGBA16_FLOAT     : return gl::texture_format_e::rgba16_float;
            
            case R32_FLOAT        : return gl::texture_format_e::r32_float;
            case RG32_FLOAT       : return gl::texture_format_e::rg32_float;
            case RGB32_FLOAT      : return gl::texture_format_e::rgb32_float;
            case RGBA32_FLOAT     : return gl::texture_format_e::rgba32_float;
            
            case D16_UNORM        : return gl::texture_format_e::d16_unorm;
            case D24_UNORM        : return gl::texture_format_e::d24_unorm;
            case D32_FLOAT        : return gl::texture_format_e::d32_float;
            
            case D24_UNORM_S8_UINT: return gl::texture_format_e::d24_unorm_s8_uint;
            case D32_FLOAT_S8_UINT: return gl::texture_format_e::d32_float_s8_uint;
            
            case S8_UINT          : return gl::texture_format_e::s8_uint;

            default: throw std::invalid_argument{ "Invalid format!" };
        }
    }
    auto map_cubemap_texture_format_type(api::cubemap::Format format) -> gl::pixel_data_type_e
    {
        switch (format)
        {
            using enum api::cubemap::Format;

            case R8_UNORM    :
            case RG8_UNORM   :
            case RGB8_UNORM  :
            case RGBA8_UNORM : return gl::pixel_data_type_e::unsigned_byte_;

            case R16_UNORM   :
            case RG16_UNORM  :
            case RGB16_UNORM :
            case RGBA16_UNORM: return gl::pixel_data_type_e::unsigned_short_;

            case R8_SNORM    :
            case RG8_SNORM   :
            case RGB8_SNORM  :
            case RGBA8_SNORM : return gl::pixel_data_type_e::byte_;

            case R16_SNORM   :
            case RG16_SNORM  :
            case RGB16_SNORM :
            case RGBA16_SNORM: return gl::pixel_data_type_e::short_;

            case RGB8_SRGB   :
            case RGBA8_SRGB  : return gl::pixel_data_type_e::unsigned_byte_;

            case R16_FLOAT   :
            case RG16_FLOAT  :
            case RGB16_FLOAT :
            case RGBA16_FLOAT: return gl::pixel_data_type_e::half_float_;

            case R32_FLOAT   :
            case RG32_FLOAT  :
            case RGB32_FLOAT :
            case RGBA32_FLOAT: return gl::pixel_data_type_e::float_;
            
            default: throw std::invalid_argument{ "Invalid format!" };
        }
    }
    auto map_frame_buffer_target        (api::frame_buffer::Target  target) -> gl::frame_buffer_target_e
    {
        switch (target)
        {
            using enum api::frame_buffer::Target;

            case Read : return gl::frame_buffer_target_e::read;
            case Write: return gl::frame_buffer_target_e::write;

            default: throw std::invalid_argument{ "Invalid target!" };
        }
    }
    auto map_frame_buffer_attachment    (api::frame_buffer::Attachment attachment) -> gl::frame_buffer_attachment_e
    {
        switch (attachment)
        {
            using enum api::frame_buffer::Attachment;

            case Color0      : return gl::frame_buffer_attachment_e::color0; 
            case Color1      : return gl::frame_buffer_attachment_e::color1; 
            case Color2      : return gl::frame_buffer_attachment_e::color2; 
            case Color3      : return gl::frame_buffer_attachment_e::color3; 
            case Color4      : return gl::frame_buffer_attachment_e::color4; 
            case Color5      : return gl::frame_buffer_attachment_e::color5; 
            case Color6      : return gl::frame_buffer_attachment_e::color6; 
            case Color7      : return gl::frame_buffer_attachment_e::color7; 

            case Depth       : return gl::frame_buffer_attachment_e::depth;
            case Stencil     : return gl::frame_buffer_attachment_e::stencil;
            case DepthStencil: return gl::frame_buffer_attachment_e::depth_stencil;

            default: throw std::invalid_argument{ "Invalid attachment!" };
        }
    }
    auto map_program_stage              (api::shader::Stage stage) -> gl::program_stage_e
    {
        switch (stage)
        {
            using enum api::shader::Stage;

            case Vertex                : return gl::program_stage_e::vertex;
            case TessellationControl   : return gl::program_stage_e::tessellation_control;
            case TessellationEvaluation: return gl::program_stage_e::tessellation_evaluation;
            case Geometry              : return gl::program_stage_e::geometry;
            case Fragment              : return gl::program_stage_e::fragment;
            case Compute               : return gl::program_stage_e::compute;

            default: throw std::invalid_argument{ "Invalid stage!" };
        }
    }                                                                      
    auto map_shader_type                (api::shader::Stage stage) -> gl::shader_type_e
    {
        switch (stage)
        {
            using enum api::shader::Stage;

            case Vertex                : return gl::shader_type_e::vertex;
            case TessellationControl   : return gl::shader_type_e::tessellation_control;
            case TessellationEvaluation: return gl::shader_type_e::tessellation_evaluation;
            case Geometry              : return gl::shader_type_e::geometry;
            case Fragment              : return gl::shader_type_e::fragment;
            case Compute               : return gl::shader_type_e::compute;

            default: throw std::invalid_argument{ "Invalid stage!" };
        }
    }
    auto map_query_target               (api::Query::Target target) -> gl::query_target_e
    {
        switch (target)
        {
            using enum api::Query::Target;

            case AnySamplesPassed                        : return gl::query_target_e::any_samples_passed;
            case AnySamplesPassedConservative            : return gl::query_target_e::any_samples_passed_conservative;
            case ClippingInputPrimitives                 : return gl::query_target_e::clipping_input_primitives;
            case ClippingOutputPrimitives                : return gl::query_target_e::clipping_output_primitives;
            case ComputeShaderInvocations                : return gl::query_target_e::compute_shader_invocations;
            case FragmentShaderInvocations               : return gl::query_target_e::fragment_shader_invocations;
            case GeometryShaderInvocations               : return gl::query_target_e::geometry_shader_invocations;
            case GeometryShaderPrimitivesEmitted         : return gl::query_target_e::geometry_shader_primitives_emitted;
            case PrimitivesGenerated                     : return gl::query_target_e::primitives_generated;
            case PrimitivesSubmitted                     : return gl::query_target_e::primitives_submitted;
            case SamplesPassed                           : return gl::query_target_e::samples_passed;
            case TessellationControlShaderPatches        : return gl::query_target_e::tessellation_control_shader_patches;
            case TessellationEvaluationShaderInvocations : return gl::query_target_e::tessellation_evaluation_shader_invocations;
            case TimeElapsed                             : return gl::query_target_e::time_elapsed;
            case Timestamp                               : return gl::query_target_e::timestamp;
            case TransformFeedbackOverflow               : return gl::query_target_e::transform_feedback_overflow;
            case TransformFeedbackPrimitivesWritten      : return gl::query_target_e::transform_feedback_primitives_written;
            case TransformFeedbackStreamOverflow         : return gl::query_target_e::transform_feedback_stream_overflow;
            case VertexShaderInvocations                 : return gl::query_target_e::vertex_shader_invocations;
            case VerticesSubmitted                       : return gl::query_target_e::vertices_submitted;

            default: throw std::invalid_argument{ "Invalid target!" };
        }
    }
    auto map_depth_function             (api::RenderState::DepthFunction depthFunction) -> gl::depth_function_e
    {
        switch (depthFunction)
        {
            using enum api::RenderState::DepthFunction;

            case Always      : return gl::depth_function_e::always;
            case Never       : return gl::depth_function_e::never;
            case Equal       : return gl::depth_function_e::equal;
            case NotEqual    : return gl::depth_function_e::not_equal;
            case Less        : return gl::depth_function_e::less;
            case Greater     : return gl::depth_function_e::greater;
            case LessEqual   : return gl::depth_function_e::less_equal;
            case GreaterEqual: return gl::depth_function_e::greater_equal;

            default: throw std::invalid_argument{ "Invalid function!" };
        }
    }
    auto map_culling_face               (api::RenderState::FaceCulling cullingFace) -> gl::culling_facet_e
    {
        switch (cullingFace)
        {
            using enum api::RenderState::FaceCulling;

            case Front    : return gl::culling_facet_e::front;
            case Back     : return gl::culling_facet_e::back;
            case FrontBack: return gl::culling_facet_e::front_and_back;

            default: throw std::invalid_argument{ "Invalid face!" };
        }
    }
}
