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
    constexpr auto map_type             () -> glf::VertexArray::Attribute::Type
    {
        if constexpr (std::is_same_v<std::remove_cvref_t<T>, gl::int8_t   >) return glf::VertexArray::Attribute::Type::Byte           ;
        if constexpr (std::is_same_v<std::remove_cvref_t<T>, gl::uint8_t  >) return glf::VertexArray::Attribute::Type::UnsignedByte   ;
        if constexpr (std::is_same_v<std::remove_cvref_t<T>, gl::int16_t  >) return glf::VertexArray::Attribute::Type::Short          ;
        if constexpr (std::is_same_v<std::remove_cvref_t<T>, gl::uint16_t >) return glf::VertexArray::Attribute::Type::UnsignedShort  ;
        if constexpr (std::is_same_v<std::remove_cvref_t<T>, gl::int32_t  >) return glf::VertexArray::Attribute::Type::Integer        ;
        if constexpr (std::is_same_v<std::remove_cvref_t<T>, gl::uint32_t >) return glf::VertexArray::Attribute::Type::UnsignedInteger;
        if constexpr (std::is_same_v<std::remove_cvref_t<T>, gl::float32_t>) return glf::VertexArray::Attribute::Type::Float          ;
        if constexpr (std::is_same_v<std::remove_cvref_t<T>, gl::float64_t>) return glf::VertexArray::Attribute::Type::Double         ;
    }

    auto map_texture_format_base        (api::Texture::Format format) -> glf::Texture::BaseFormat
    {
        switch (format)
        {
            using enum api::Texture::Format;

            case R8_UNORM    :
            case R16_UNORM   :
            case R8_SNORM    :
            case R16_SNORM   :
            case R16_FLOAT   :
            case R32_FLOAT   : return glf::Texture::BaseFormat::R;
            
            case RG8_UNORM   :
            case RG16_UNORM  :
            case RG8_SNORM   :
            case RG16_SNORM  :
            case RG16_FLOAT  :
            case RG32_FLOAT  : return glf::Texture::BaseFormat::RG;
            
            case RGB8_UNORM  :
            case RGB16_UNORM :
            case RGB8_SNORM  :
            case RGB16_SNORM :
            case RGB8_SRGB   :
            case RGB16_FLOAT :
            case RGB32_FLOAT : return glf::Texture::BaseFormat::RGB;
            
            case RGBA8_UNORM :
            case RGBA16_UNORM:
            case RGBA8_SNORM :
            case RGBA16_SNORM:
            case RGBA8_SRGB  :
            case RGBA16_FLOAT:
            case RGBA32_FLOAT: return glf::Texture::BaseFormat::RGBA;
            
            case D16_UNORM   :
            case D24_UNORM   :
            case D32_FLOAT   : return glf::Texture::BaseFormat::D;
            
            case S8_UINT     : return glf::Texture::BaseFormat::S;

            default: throw std::invalid_argument{ "Invalid format!" };
        }
    }
    auto map_texture_format             (api::Texture::Format format) -> glf::Texture::Format
    {
        switch (format)
        {
            using enum api::Texture::Format;

            case R8_UNORM         : return glf::Texture::Format::R8_UNORM;
            case RG8_UNORM        : return glf::Texture::Format::RG8_UNORM;
            case RGB8_UNORM       : return glf::Texture::Format::RGB8_UNORM;
            case RGBA8_UNORM      : return glf::Texture::Format::RGBA8_UNORM;
            case R16_UNORM        : return glf::Texture::Format::R16_UNORM;
            case RG16_UNORM       : return glf::Texture::Format::RG16_UNORM;
            case RGB16_UNORM      : return glf::Texture::Format::RGB16_UNORM;
            case RGBA16_UNORM     : return glf::Texture::Format::RGBA16_UNORM;
            case R8_SNORM         : return glf::Texture::Format::R8_SNORM;
            case RG8_SNORM        : return glf::Texture::Format::RG8_SNORM;
            case RGB8_SNORM       : return glf::Texture::Format::RGB8_SNORM;
            case RGBA8_SNORM      : return glf::Texture::Format::RGBA8_SNORM;
            case R16_SNORM        : return glf::Texture::Format::R16_SNORM;
            case RG16_SNORM       : return glf::Texture::Format::RG16_SNORM;
            case RGB16_SNORM      : return glf::Texture::Format::RGB16_SNORM;
            case RGBA16_SNORM     : return glf::Texture::Format::RGBA16_SNORM;
            case RGB8_SRGB        : return glf::Texture::Format::RGB8_SRGB;
            case RGBA8_SRGB       : return glf::Texture::Format::RGBA8_SRGB;
            case R16_FLOAT        : return glf::Texture::Format::R16_FLOAT;
            case RG16_FLOAT       : return glf::Texture::Format::RG16_FLOAT;
            case RGB16_FLOAT      : return glf::Texture::Format::RGB16_FLOAT;
            case RGBA16_FLOAT     : return glf::Texture::Format::RGBA16_FLOAT;
            case R32_FLOAT        : return glf::Texture::Format::R32_FLOAT;
            case RG32_FLOAT       : return glf::Texture::Format::RG32_FLOAT;
            case RGB32_FLOAT      : return glf::Texture::Format::RGB32_FLOAT;
            case RGBA32_FLOAT     : return glf::Texture::Format::RGBA32_FLOAT;
            case D16_UNORM        : return glf::Texture::Format::D16_UNORM;
            case D24_UNORM        : return glf::Texture::Format::D24_UNORM;
            case D32_FLOAT        : return glf::Texture::Format::D32_FLOAT;
            case D24_UNORM_S8_UINT: return glf::Texture::Format::D24_UNORM_S8_UINT;
            case D32_FLOAT_S8_UINT: return glf::Texture::Format::D32_FLOAT_S8_UINT;
            case S8_UINT          : return glf::Texture::Format::S8_UINT;

            default: throw std::invalid_argument{ "Invalid format!" };
        }
    }
    auto map_texture_format_type        (api::Texture::Format format) -> glf::PixelData::Type
    {
        switch (format)
        {
            using enum api::Texture::Format;

            case R8_UNORM    :
            case RG8_UNORM   :
            case RGB8_UNORM  :
            case RGBA8_UNORM :  return glf::PixelData::Type::UnsignedByte;

            case R16_UNORM   :
            case RG16_UNORM  :
            case RGB16_UNORM :
            case RGBA16_UNORM: return glf::PixelData::Type::UnsignedShort;

            case R8_SNORM    :
            case RG8_SNORM   :
            case RGB8_SNORM  :
            case RGBA8_SNORM : return glf::PixelData::Type::Byte;

            case R16_SNORM   :
            case RG16_SNORM  :
            case RGB16_SNORM :
            case RGBA16_SNORM: return glf::PixelData::Type::Short;

            case RGB8_SRGB   :
            case RGBA8_SRGB  : return glf::PixelData::Type::UnsignedByte;
            
            case R16_FLOAT   :
            case RG16_FLOAT  :
            case RGB16_FLOAT :
            case RGBA16_FLOAT: return glf::PixelData::Type::HalfFloat;
            
            case R32_FLOAT   :
            case RG32_FLOAT  :
            case RGB32_FLOAT :
            case RGBA32_FLOAT: return glf::PixelData::Type::Float;
            
            default: throw std::invalid_argument{ "Invalid format!" };
        }
    }
    auto map_texture_min_filter         (api::Texture::Filter filter) -> glf::Texture::MinificationFilter
    {
        switch (filter)
        {
            using enum api::Texture::Filter;

            case None     : return glf::Texture::MinificationFilter::Nearest;
            case Nearest  : return glf::Texture::MinificationFilter::NearestMipmapNearest;
            case Bilinear : return glf::Texture::MinificationFilter::LinearMipmapNearest;
            case Trilinear: return glf::Texture::MinificationFilter::LinearMipmapLinear;

            default: throw std::invalid_argument{ "Invalid filter!" };
        }
    }
    auto map_texture_mag_filter         (api::Texture::Filter filter) -> glf::Texture::MagnificationFilter
    {
        switch (filter)
        {
            using enum api::Texture::Filter;

            case None     : return glf::Texture::MagnificationFilter::Nearest;
            case Nearest  : return glf::Texture::MagnificationFilter::Nearest;
            case Bilinear : return glf::Texture::MagnificationFilter::Linear;
            case Trilinear: return glf::Texture::MagnificationFilter::Linear;

            default: throw std::invalid_argument{ "Invalid filter!" };
        }
    }
    auto map_texture_wrapping           (api::Texture::Wrapping wrapping) -> glf::Texture::Wrapping
    {
        switch (wrapping)
        {
            using enum api::Texture::Wrapping;

            case ClampToEdge        : return glf::Texture::Wrapping::ClampToEdge;
            case ClampToBorder      : return glf::Texture::Wrapping::ClampToBorder;
            case Repeat             : return glf::Texture::Wrapping::Repeat;
            case MirroredRepeat     : return glf::Texture::Wrapping::MirroredRepeat;
            case MirroredClampToEdge: return glf::Texture::Wrapping::MirroredClampToEdge;

            default: throw std::invalid_argument{ "Invalid wrapping!" };
        }
    }
    auto map_render_buffer_format       (api::RenderBuffer::Format format) -> glf::RenderBuffer::Format
    {
        switch (format)
        {
            using enum api::RenderBuffer::Format;

            case R8_UNORM         : return glf::RenderBuffer::Format::R8;
            case RG8_UNORM        : return glf::RenderBuffer::Format::RG8;
            case RGB8_UNORM       : return glf::RenderBuffer::Format::RGB8;
            case RGBA8_UNORM      : return glf::RenderBuffer::Format::RGBA8;
            case RGBA8_SRGB       : return glf::RenderBuffer::Format::RGBA8_SRGB;
            case D16_UNORM        : return glf::RenderBuffer::Format::D16_UNORM;
            case D24_UNORM        : return glf::RenderBuffer::Format::D24_UNORM;
            case D32_FLOAT        : return glf::RenderBuffer::Format::D32_FLOAT;
            case D24_UNORM_S8_UINT: return glf::RenderBuffer::Format::D24_UNORM_S8_UINT;
            case D32_FLOAT_S8_UINT: return glf::RenderBuffer::Format::D32_FLOAT_S8_UINT;
            case S8_UINT          : return glf::RenderBuffer::Format::S8_UINT;

            default: throw std::invalid_argument{ "Invalid format!" };
        }
    }
    auto map_cubemap_texture_format_base(api::Cubemap::Format format) -> glf::Texture::BaseFormat
    {
        switch (format)
        {
            using enum api::Cubemap::Format;

            case R8_UNORM    :
            case R16_UNORM   :
            case R8_SNORM    :
            case R16_SNORM   :
            case R16_FLOAT   :
            case R32_FLOAT   : return glf::Texture::BaseFormat::R;
            
            case RG8_UNORM   :
            case RG16_UNORM  :
            case RG8_SNORM   :
            case RG16_SNORM  :
            case RG16_FLOAT  :
            case RG32_FLOAT  : return glf::Texture::BaseFormat::RG;
            
            case RGB8_UNORM  :
            case RGB16_UNORM :
            case RGB8_SNORM  :
            case RGB16_SNORM :
            case RGB8_SRGB   :
            case RGB16_FLOAT :
            case RGB32_FLOAT : return glf::Texture::BaseFormat::RGB;
            
            case RGBA8_UNORM :
            case RGBA16_UNORM:
            case RGBA8_SNORM :
            case RGBA16_SNORM:
            case RGBA8_SRGB  :
            case RGBA16_FLOAT:
            case RGBA32_FLOAT: return glf::Texture::BaseFormat::RGBA;
            
            case D16_UNORM   :
            case D24_UNORM   :
            case D32_FLOAT   : return glf::Texture::BaseFormat::D;
            
            case S8_UINT     : return glf::Texture::BaseFormat::S;

            default: throw std::invalid_argument{ "Invalid format!" };
        }
    }
    auto map_cubemap_texture_format     (api::Cubemap::Format format) -> glf::Texture::Format
    {
        switch (format)
        {
            using enum api::Cubemap::Format;

            case R8_UNORM         : return glf::Texture::Format::R8_UNORM;
            case RG8_UNORM        : return glf::Texture::Format::RG8_UNORM;
            case RGB8_UNORM       : return glf::Texture::Format::RGB8_UNORM;
            case RGBA8_UNORM      : return glf::Texture::Format::RGBA8_UNORM;
            
            case R16_UNORM        : return glf::Texture::Format::R16_UNORM;
            case RG16_UNORM       : return glf::Texture::Format::RG16_UNORM;
            case RGB16_UNORM      : return glf::Texture::Format::RGB16_UNORM;
            case RGBA16_UNORM     : return glf::Texture::Format::RGBA16_UNORM;
            
            case R8_SNORM         : return glf::Texture::Format::R8_SNORM;
            case RG8_SNORM        : return glf::Texture::Format::RG8_SNORM;
            case RGB8_SNORM       : return glf::Texture::Format::RGB8_SNORM;
            case RGBA8_SNORM      : return glf::Texture::Format::RGBA8_SNORM;
            
            case R16_SNORM        : return glf::Texture::Format::R16_SNORM;
            case RG16_SNORM       : return glf::Texture::Format::RG16_SNORM;
            case RGB16_SNORM      : return glf::Texture::Format::RGB16_SNORM;
            case RGBA16_SNORM     : return glf::Texture::Format::RGBA16_SNORM;
            
            case RGB8_SRGB        : return glf::Texture::Format::RGB8_SRGB;
            case RGBA8_SRGB       : return glf::Texture::Format::RGBA8_SRGB;
            
            case R16_FLOAT        : return glf::Texture::Format::R16_FLOAT;
            case RG16_FLOAT       : return glf::Texture::Format::RG16_FLOAT;
            case RGB16_FLOAT      : return glf::Texture::Format::RGB16_FLOAT;
            case RGBA16_FLOAT     : return glf::Texture::Format::RGBA16_FLOAT;
            
            case R32_FLOAT        : return glf::Texture::Format::R32_FLOAT;
            case RG32_FLOAT       : return glf::Texture::Format::RG32_FLOAT;
            case RGB32_FLOAT      : return glf::Texture::Format::RGB32_FLOAT;
            case RGBA32_FLOAT     : return glf::Texture::Format::RGBA32_FLOAT;
            
            case D16_UNORM        : return glf::Texture::Format::D16_UNORM;
            case D24_UNORM        : return glf::Texture::Format::D24_UNORM;
            case D32_FLOAT        : return glf::Texture::Format::D32_FLOAT;
            
            case D24_UNORM_S8_UINT: return glf::Texture::Format::D24_UNORM_S8_UINT;
            case D32_FLOAT_S8_UINT: return glf::Texture::Format::D32_FLOAT_S8_UINT;
            
            case S8_UINT          : return glf::Texture::Format::S8_UINT;

            default: throw std::invalid_argument{ "Invalid format!" };
        }
    }
    auto map_cubemap_texture_format_type(api::Cubemap::Format format) -> glf::PixelData::Type
    {
        switch (format)
        {
            using enum api::Cubemap::Format;

            case R8_UNORM    :
            case RG8_UNORM   :
            case RGB8_UNORM  :
            case RGBA8_UNORM : return glf::PixelData::Type::UnsignedByte;

            case R16_UNORM   :
            case RG16_UNORM  :
            case RGB16_UNORM :
            case RGBA16_UNORM: return glf::PixelData::Type::UnsignedShort;

            case R8_SNORM    :
            case RG8_SNORM   :
            case RGB8_SNORM  :
            case RGBA8_SNORM : return glf::PixelData::Type::Byte;

            case R16_SNORM   :
            case RG16_SNORM  :
            case RGB16_SNORM :
            case RGBA16_SNORM: return glf::PixelData::Type::Short;

            case RGB8_SRGB   :
            case RGBA8_SRGB  : return glf::PixelData::Type::UnsignedByte;

            case R16_FLOAT   :
            case RG16_FLOAT  :
            case RGB16_FLOAT :
            case RGBA16_FLOAT: return glf::PixelData::Type::HalfFloat;

            case R32_FLOAT   :
            case RG32_FLOAT  :
            case RGB32_FLOAT :
            case RGBA32_FLOAT: return glf::PixelData::Type::Float;
            
            default: throw std::invalid_argument{ "Invalid format!" };
        }
    }
    auto map_frame_buffer_target        (api::FrameBuffer::Target  target) -> glf::FrameBuffer::Target
    {
        switch (target)
        {
            using enum api::FrameBuffer::Target;

            case Read : return glf::FrameBuffer::Target::Read;
            case Write: return glf::FrameBuffer::Target::Write;

            default: throw std::invalid_argument{ "Invalid target!" };
        }
    }
    auto map_frame_buffer_attachment    (api::FrameBuffer::Attachment attachment) -> glf::FrameBuffer::Attachment
    {
        switch (attachment)
        {
            using enum api::FrameBuffer::Attachment;

            case Color0      : return glf::FrameBuffer::Attachment::Color0; 
            case Color1      : return glf::FrameBuffer::Attachment::Color1; 
            case Color2      : return glf::FrameBuffer::Attachment::Color2; 
            case Color3      : return glf::FrameBuffer::Attachment::Color3; 
            case Color4      : return glf::FrameBuffer::Attachment::Color4; 
            case Color5      : return glf::FrameBuffer::Attachment::Color5; 
            case Color6      : return glf::FrameBuffer::Attachment::Color6; 
            case Color7      : return glf::FrameBuffer::Attachment::Color7; 

            case Depth       : return glf::FrameBuffer::Attachment::Depth;
            case Stencil     : return glf::FrameBuffer::Attachment::Stencil;
            case DepthStencil: return glf::FrameBuffer::Attachment::DepthStencil;

            default: throw std::invalid_argument{ "Invalid attachment!" };
        }
    }
    auto map_program_stage              (api::Shader::Stage stage) -> glf::Program::Stage
    {
        switch (stage)
        {
            using enum api::Shader::Stage;

            case Vertex                : return glf::Program::Stage::Vertex;
            case TessellationControl   : return glf::Program::Stage::TessellationControl;
            case TessellationEvaluation: return glf::Program::Stage::TessellationEvaluation;
            case Geometry              : return glf::Program::Stage::Geometry;
            case Fragment              : return glf::Program::Stage::Fragment;
            case Compute               : return glf::Program::Stage::Compute;

            default: throw std::invalid_argument{ "Invalid stage!" };
        }
    }                                                                      
    auto map_shader_type                (api::Shader::Stage stage) -> glf::Shader::Type
    {
        switch (stage)
        {
            using enum api::Shader::Stage;

            case Vertex                : return glf::Shader::Type::Vertex;
            case TessellationControl   : return glf::Shader::Type::TessellationControl;
            case TessellationEvaluation: return glf::Shader::Type::TessellationEvaluation;
            case Geometry              : return glf::Shader::Type::Geometry;
            case Fragment              : return glf::Shader::Type::Fragment;
            case Compute               : return glf::Shader::Type::Compute;

            default: throw std::invalid_argument{ "Invalid stage!" };
        }
    }
    auto map_query_target               (api::Query::Target target) -> glf::Query::Target
    {
        switch (target)
        {
            using enum api::Query::Target;

            case AnySamplesPassed                        : return glf::Query::Target::AnySamplesPassed;
            case AnySamplesPassedConservative            : return glf::Query::Target::AnySamplesPassedConservative;
            case ClippingInputPrimitives                 : return glf::Query::Target::ClippingInputPrimitives;
            case ClippingOutputPrimitives                : return glf::Query::Target::ClippingOutputPrimitives;
            case ComputeShaderInvocations                : return glf::Query::Target::ComputeShaderInvocations;
            case FragmentShaderInvocations               : return glf::Query::Target::FragmentShaderInvocations;
            case GeometryShaderInvocations               : return glf::Query::Target::GeometryShaderInvocations;
            case GeometryShaderPrimitivesEmitted         : return glf::Query::Target::GeometryShaderPrimitivesEmitted;
            case PrimitivesGenerated                     : return glf::Query::Target::PrimitivesGenerated;
            case PrimitivesSubmitted                     : return glf::Query::Target::PrimitivesSubmitted;
            case SamplesPassed                           : return glf::Query::Target::SamplesPassed;
            case TessellationControlShaderPatches        : return glf::Query::Target::TessellationControlShaderPatches;
            case TessellationEvaluationShaderInvocations : return glf::Query::Target::TessellationEvaluationShaderInvocations;
            case TimeElapsed                             : return glf::Query::Target::TimeElapsed;
            case Timestamp                               : return glf::Query::Target::Timestamp;
            case TransformFeedbackOverflow               : return glf::Query::Target::TransformFeedbackOverflow;
            case TransformFeedbackPrimitivesWritten      : return glf::Query::Target::TransformFeedbackPrimitivesWritten;
            case TransformFeedbackStreamOverflow         : return glf::Query::Target::TransformFeedbackStreamOverflow;
            case VertexShaderInvocations                 : return glf::Query::Target::VertexShaderInvocations;
            case VerticesSubmitted                       : return glf::Query::Target::VerticesSubmitted;

            default: throw std::invalid_argument{ "Invalid target!" };
        }
    }
    auto map_depth_function             (api::RenderState::DepthFunction depthFunction) -> glf::DepthFunction
    {
        switch (depthFunction)
        {
            using enum api::RenderState::DepthFunction;

            case Always      : return glf::DepthFunction::Always;
            case Never       : return glf::DepthFunction::Never;
            case Equal       : return glf::DepthFunction::Equal;
            case NotEqual    : return glf::DepthFunction::NotEqual;
            case Less        : return glf::DepthFunction::Less;
            case LessEqual   : return glf::DepthFunction::LessEqual;
            case Greater     : return glf::DepthFunction::Greater;
            case GreaterEqual: return glf::DepthFunction::GreaterEqual;

            default: throw std::invalid_argument{ "Invalid function!" };
        }
    }
    auto map_culling_face               (api::RenderState::FaceCulling cullingFace) -> glf::Culling::Facet
    {
        switch (cullingFace)
        {
            using enum api::RenderState::FaceCulling;

            case Front    : return glf::Culling::Facet::Front;
            case Back     : return glf::Culling::Facet::Back;
            case FrontBack: return glf::Culling::Facet::FrontBack;

            default: throw std::invalid_argument{ "Invalid face!" };
        }
    }
}
