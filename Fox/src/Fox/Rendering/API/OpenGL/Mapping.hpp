#pragma once

#include "glad/gl.h"
#include "glfw/glfw3.h"

#include "Fox/Rendering/API/OpenGL/Query/Query.hpp"
#include "Fox/Rendering/API/OpenGL/Types.hpp"
#include "Fox/Rendering/Buffer/Buffer.hpp"
#include "Fox/Rendering/Buffer/DataTypes.hpp"
#include "Fox/Rendering/FrameBuffer/FrameBuffer.hpp"
#include "Fox/Rendering/RenderBuffer/RenderBuffer.hpp"
#include "Fox/Rendering/RenderState/RenderState.hpp"
#include "Fox/Rendering/Shader/Pipeline.hpp"
#include "Fox/Rendering/Shader/Shader.hpp"
#include "Fox/Rendering/Texture/AntiAliasing.hpp"
#include "Fox/Rendering/Texture/Dimensions.hpp"
#include "Fox/Rendering/Texture/Texture.hpp"
#include "Fox/Rendering/Texture/Cubemap.hpp"

namespace fox::gfx::api::gl
{
    static constexpr glf::Buffer::Mapping              map_buffer_mapping(api::Buffer::Mapping mapping)
    {
        switch (mapping)
        {
            case api::Buffer::Mapping::Read:      return glf::Buffer::Mapping::Read;
            case api::Buffer::Mapping::Write:     return glf::Buffer::Mapping::Write;
            case api::Buffer::Mapping::ReadWrite: return glf::Buffer::Mapping::ReadWrite;

            default: throw std::invalid_argument{ "Invalid Mapping!" };
        }
    }
    static constexpr glf::Buffer::Target               map_buffer_target(api::Buffer::Type type)
    {
        switch (type)
        {
            case api::Buffer::Type::Vertex:  return glf::Buffer::Target::ArrayBuffer;
            case api::Buffer::Type::Index:   return glf::Buffer::Target::ElementArrayBuffer;

            default: throw std::invalid_argument{ "Invalid type!" };
        }
    }
    static constexpr glf::Texture::BaseFormat          map_texture_format_base(api::Texture::Format format)
    {
        const auto& flags = (static_cast<gl::int32_t>(format) & 0xFF00) >> 8;

        switch (flags)
        {
            case 0x01: return glf::Texture::BaseFormat::R;
            case 0x02: return glf::Texture::BaseFormat::RG;
            case 0x03: return glf::Texture::BaseFormat::RGB;
            case 0x04: return glf::Texture::BaseFormat::RGBA;

            case 0x10: return glf::Texture::BaseFormat::Depth;
            case 0x20: return glf::Texture::BaseFormat::Stencil;

            case 0x30: throw std::invalid_argument{ "Invalid texture format!" };

            default: throw std::invalid_argument{ "Invalid texture format!" };
        }
    }
    static constexpr glf::Texture::Format              map_texture_format(api::Texture::Format format)
    {
        switch (format)
        {
            case api::Texture::Format::R8_UNORM:          return glf::Texture::Format::R8_UNORM;
            case api::Texture::Format::RG8_UNORM:         return glf::Texture::Format::RG8_UNORM;
            case api::Texture::Format::RGB8_UNORM:        return glf::Texture::Format::RGB8_UNORM;
            case api::Texture::Format::RGBA8_UNORM:       return glf::Texture::Format::RGBA8_UNORM;
            case api::Texture::Format::R16_UNORM:         return glf::Texture::Format::R16_UNORM;
            case api::Texture::Format::RG16_UNORM:        return glf::Texture::Format::RG16_UNORM;
            case api::Texture::Format::RGB16_UNORM:       return glf::Texture::Format::RGB16_UNORM;
            case api::Texture::Format::RGBA16_UNORM:      return glf::Texture::Format::RGBA16_UNORM;
            case api::Texture::Format::R8_SNORM:          return glf::Texture::Format::R8_SNORM;
            case api::Texture::Format::RG8_SNORM:         return glf::Texture::Format::RG8_SNORM;
            case api::Texture::Format::RGB8_SNORM:        return glf::Texture::Format::RGB8_SNORM;
            case api::Texture::Format::RGBA8_SNORM:       return glf::Texture::Format::RGBA8_SNORM;
            case api::Texture::Format::R16_SNORM:         return glf::Texture::Format::R16_SNORM;
            case api::Texture::Format::RG16_SNORM:        return glf::Texture::Format::RG16_SNORM;
            case api::Texture::Format::RGB16_SNORM:       return glf::Texture::Format::RGB16_SNORM;
            case api::Texture::Format::RGBA16_SNORM:      return glf::Texture::Format::RGBA16_SNORM;
            case api::Texture::Format::RGB8_SRGB:         return glf::Texture::Format::RGB8_SRGB;
            case api::Texture::Format::RGBA8_SRGB:        return glf::Texture::Format::RGBA8_SRGB;
            case api::Texture::Format::R16_FLOAT:         return glf::Texture::Format::R16_FLOAT;
            case api::Texture::Format::RG16_FLOAT:        return glf::Texture::Format::RG16_FLOAT;
            case api::Texture::Format::RGB16_FLOAT:       return glf::Texture::Format::RGB16_FLOAT;
            case api::Texture::Format::RGBA16_FLOAT:      return glf::Texture::Format::RGBA16_FLOAT;
            case api::Texture::Format::R32_FLOAT:         return glf::Texture::Format::R32_FLOAT;
            case api::Texture::Format::RG32_FLOAT:        return glf::Texture::Format::RG32_FLOAT;
            case api::Texture::Format::RGB32_FLOAT:       return glf::Texture::Format::RGB32_FLOAT;
            case api::Texture::Format::RGBA32_FLOAT:      return glf::Texture::Format::RGBA32_FLOAT;
            case api::Texture::Format::D16_UNORM:         return glf::Texture::Format::D16_UNORM;
            case api::Texture::Format::D24_UNORM:         return glf::Texture::Format::D24_UNORM;
            case api::Texture::Format::D32_FLOAT:         return glf::Texture::Format::D32_FLOAT;
            case api::Texture::Format::D24_UNORM_S8_UINT: return glf::Texture::Format::D24_UNORM_S8_UINT;
            case api::Texture::Format::D32_FLOAT_S8_UINT: return glf::Texture::Format::D32_FLOAT_S8_UINT;
            case api::Texture::Format::S8_UINT:           return glf::Texture::Format::S8_UINT;

            default: throw std::invalid_argument{ "Invalid format!" };
        }
    }
    static constexpr glf::Texture::MinificationFilter  map_texture_min_filter(api::Texture::Filter filter)
    {
        switch (filter)
        {
            case api::Texture::Filter::None:      return glf::Texture::MinificationFilter::Nearest;
            case api::Texture::Filter::Nearest:   return glf::Texture::MinificationFilter::NearestMipmapNearest;
            case api::Texture::Filter::Bilinear:  return glf::Texture::MinificationFilter::LinearMipmapNearest;
            case api::Texture::Filter::Trilinear: return glf::Texture::MinificationFilter::LinearMipmapLinear;

            default: throw std::invalid_argument{ "Invalid filter!" };
        }
    }
    static constexpr glf::Texture::MagnificationFilter map_texture_mag_filter(api::Texture::Filter filter)
    {
        switch (filter)
        {
            case api::Texture::Filter::None:      return glf::Texture::MagnificationFilter::Nearest;
            case api::Texture::Filter::Nearest:   return glf::Texture::MagnificationFilter::Nearest;
            case api::Texture::Filter::Bilinear:  return glf::Texture::MagnificationFilter::Linear;
            case api::Texture::Filter::Trilinear: return glf::Texture::MagnificationFilter::Linear;

            default: throw std::invalid_argument{ "Invalid filter!" };
        }
    }
    template<gfx::Dimensions DIMS, gfx::AntiAliasing AA>
    static constexpr glf::Texture::Target              map_texture_target()
    {
        if constexpr (AA == gfx::AntiAliasing::None)
        {
            if constexpr (DIMS == gfx::Dimensions::_1D) return glf::Texture::Target::_1D;
            if constexpr (DIMS == gfx::Dimensions::_2D) return glf::Texture::Target::_2D;
            if constexpr (DIMS == gfx::Dimensions::_3D) return glf::Texture::Target::_3D;
        }
        if constexpr (AA == gfx::AntiAliasing::MSAA)
        {
            if constexpr (DIMS == gfx::Dimensions::_2D) return glf::Texture::Target::_2DMultisample;
            if constexpr (DIMS == gfx::Dimensions::_3D) return glf::Texture::Target::_2DMultisampleArray;
        }

        throw std::invalid_argument{ "The given input can not be mapped to a texture type!" };
    }
    static constexpr glf::Texture::Wrapping            map_texture_wrapping(api::Texture::Wrapping wrapping)
    {
        switch (wrapping)
        {
            case api::Texture::Wrapping::ClampToEdge:         return glf::Texture::Wrapping::ClampToEdge;
            case api::Texture::Wrapping::ClampToBorder:       return glf::Texture::Wrapping::ClampToBorder;
            case api::Texture::Wrapping::Repeat:              return glf::Texture::Wrapping::Repeat;
            case api::Texture::Wrapping::MirroredRepeat:      return glf::Texture::Wrapping::MirroredRepeat;
            case api::Texture::Wrapping::MirroredClampToEdge: return glf::Texture::Wrapping::MirroredClampToEdge;

            default: throw std::invalid_argument{ "Invalid wrapping!" };
        }
    }
    static constexpr glf::RenderBuffer::Format         map_render_buffer_format(api::RenderBuffer::Format format)
    {
        switch (format)
        {
            case api::RenderBuffer::Format::R8_UNORM:          return glf::RenderBuffer::Format::R8;
            case api::RenderBuffer::Format::RG8_UNORM:         return glf::RenderBuffer::Format::RG8;
            case api::RenderBuffer::Format::RGB8_UNORM:        return glf::RenderBuffer::Format::RGB8;
            case api::RenderBuffer::Format::RGBA8_UNORM:       return glf::RenderBuffer::Format::RGBA8;
            case api::RenderBuffer::Format::RGBA8_SRGB:        return glf::RenderBuffer::Format::RGBA8_SRGB;
            case api::RenderBuffer::Format::D16_UNORM:         return glf::RenderBuffer::Format::D16_UNORM;
            case api::RenderBuffer::Format::D24_UNORM:         return glf::RenderBuffer::Format::D24_UNORM;
            case api::RenderBuffer::Format::D32_FLOAT:         return glf::RenderBuffer::Format::D32_FLOAT;
            case api::RenderBuffer::Format::D24_UNORM_S8_UINT: return glf::RenderBuffer::Format::D24_UNORM_S8_UINT;
            case api::RenderBuffer::Format::D32_FLOAT_S8_UINT: return glf::RenderBuffer::Format::D32_FLOAT_S8_UINT;
            case api::RenderBuffer::Format::S8_UINT:           return glf::RenderBuffer::Format::S8_UINT;

            default: throw std::invalid_argument{ "Invalid format!" };
        }
    }
    static constexpr glf::Texture::Format              map_cubemap_texture_format(api::Cubemap::Format format)
    {
        switch (format)
        {
            case api::Cubemap::Format::R8_UNORM:          return glf::Texture::Format::R8_UNORM;
            case api::Cubemap::Format::RG8_UNORM:         return glf::Texture::Format::RG8_UNORM;
            case api::Cubemap::Format::RGB8_UNORM:        return glf::Texture::Format::RGB8_UNORM;
            case api::Cubemap::Format::RGBA8_UNORM:       return glf::Texture::Format::RGBA8_UNORM;
            case api::Cubemap::Format::R16_UNORM:         return glf::Texture::Format::R16_UNORM;
            case api::Cubemap::Format::RG16_UNORM:        return glf::Texture::Format::RG16_UNORM;
            case api::Cubemap::Format::RGB16_UNORM:       return glf::Texture::Format::RGB16_UNORM;
            case api::Cubemap::Format::RGBA16_UNORM:      return glf::Texture::Format::RGBA16_UNORM;
            case api::Cubemap::Format::R8_SNORM:          return glf::Texture::Format::R8_SNORM;
            case api::Cubemap::Format::RG8_SNORM:         return glf::Texture::Format::RG8_SNORM;
            case api::Cubemap::Format::RGB8_SNORM:        return glf::Texture::Format::RGB8_SNORM;
            case api::Cubemap::Format::RGBA8_SNORM:       return glf::Texture::Format::RGBA8_SNORM;
            case api::Cubemap::Format::R16_SNORM:         return glf::Texture::Format::R16_SNORM;
            case api::Cubemap::Format::RG16_SNORM:        return glf::Texture::Format::RG16_SNORM;
            case api::Cubemap::Format::RGB16_SNORM:       return glf::Texture::Format::RGB16_SNORM;
            case api::Cubemap::Format::RGBA16_SNORM:      return glf::Texture::Format::RGBA16_SNORM;
            case api::Cubemap::Format::RGB8_SRGB:         return glf::Texture::Format::RGB8_SRGB;
            case api::Cubemap::Format::RGBA8_SRGB:        return glf::Texture::Format::RGBA8_SRGB;
            case api::Cubemap::Format::R16_FLOAT:         return glf::Texture::Format::R16_FLOAT;
            case api::Cubemap::Format::RG16_FLOAT:        return glf::Texture::Format::RG16_FLOAT;
            case api::Cubemap::Format::RGB16_FLOAT:       return glf::Texture::Format::RGB16_FLOAT;
            case api::Cubemap::Format::RGBA16_FLOAT:      return glf::Texture::Format::RGBA16_FLOAT;
            case api::Cubemap::Format::R32_FLOAT:         return glf::Texture::Format::R32_FLOAT;
            case api::Cubemap::Format::RG32_FLOAT:        return glf::Texture::Format::RG32_FLOAT;
            case api::Cubemap::Format::RGB32_FLOAT:       return glf::Texture::Format::RGB32_FLOAT;
            case api::Cubemap::Format::RGBA32_FLOAT:      return glf::Texture::Format::RGBA32_FLOAT;
            case api::Cubemap::Format::D16_UNORM:         return glf::Texture::Format::D16_UNORM;
            case api::Cubemap::Format::D24_UNORM:         return glf::Texture::Format::D24_UNORM;
            case api::Cubemap::Format::D32_FLOAT:         return glf::Texture::Format::D32_FLOAT;
            case api::Cubemap::Format::D24_UNORM_S8_UINT: return glf::Texture::Format::D24_UNORM_S8_UINT;
            case api::Cubemap::Format::D32_FLOAT_S8_UINT: return glf::Texture::Format::D32_FLOAT_S8_UINT;
            case api::Cubemap::Format::S8_UINT:           return glf::Texture::Format::S8_UINT;

            default: throw std::invalid_argument{ "Invalid format!" };
        }
    }
    static constexpr glf::FrameBuffer::Attachment      map_frame_buffer_attachment(api::FrameBuffer::Attachment attachment)
    {
        switch (attachment)
        {
            case api::FrameBuffer::Attachment::Color:        return glf::FrameBuffer::Attachment::ColorIndex;
            case api::FrameBuffer::Attachment::Depth:        return glf::FrameBuffer::Attachment::Depth;
            case api::FrameBuffer::Attachment::Stencil:      return glf::FrameBuffer::Attachment::Stencil;
            case api::FrameBuffer::Attachment::DepthStencil: return glf::FrameBuffer::Attachment::DepthStencil;

            default: throw std::invalid_argument{ "Invalid attachment!" };
        }
    }
    static constexpr glf::FrameBuffer::Target          map_frame_buffer_target(api::FrameBuffer::Target target)
    {
        switch (target)
        {
            case api::FrameBuffer::Target::Read:  return glf::FrameBuffer::Target::Read;
            case api::FrameBuffer::Target::Write: return glf::FrameBuffer::Target::Write;

            default: throw std::invalid_argument{ "Invalid framebuffer target!" };
        }
    }
    static constexpr glf::Shader::Stage                map_shader_stage(api::Shader::Stage stage)
    {
        switch (stage)
        {
            case api::Shader::Stage::Vertex:                 return glf::Shader::Stage::Vertex;
            case api::Shader::Stage::TessellationControl:    return glf::Shader::Stage::TessellationControl;
            case api::Shader::Stage::TessellationEvaluation: return glf::Shader::Stage::TessellationEvaluation;
            case api::Shader::Stage::Geometry:               return glf::Shader::Stage::Geometry;
            case api::Shader::Stage::Fragment:               return glf::Shader::Stage::Fragment;
            case api::Shader::Stage::Compute:                return glf::Shader::Stage::Compute;

            default: throw std::invalid_argument{ "Invalid stage!" };
        }
    }                                                                      
    static constexpr glf::Shader::Type                 map_shader_type(api::Shader::Stage stage)
    {
        switch (stage)
        {
            case api::Shader::Stage::Vertex:                 return glf::Shader::Type::Vertex;
            case api::Shader::Stage::TessellationControl:    return glf::Shader::Type::TessellationControl;
            case api::Shader::Stage::TessellationEvaluation: return glf::Shader::Type::TessellationEvaluation;
            case api::Shader::Stage::Geometry:               return glf::Shader::Type::Geometry;
            case api::Shader::Stage::Fragment:               return glf::Shader::Type::Fragment;
            case api::Shader::Stage::Compute:                return glf::Shader::Type::Compute;

            default: throw std::invalid_argument{ "Invalid stage!" };
        }
    }
    static constexpr glf::DepthFunction                map_depth_function(api::RenderState::DepthFunction depthFunction)
    {
        switch (depthFunction)
        {
            case api::RenderState::DepthFunction::Always:       return glf::DepthFunction::Always;
            case api::RenderState::DepthFunction::Never:        return glf::DepthFunction::Never;
            case api::RenderState::DepthFunction::Equal:        return glf::DepthFunction::Equal;
            case api::RenderState::DepthFunction::NotEqual:     return glf::DepthFunction::NotEqual;
            case api::RenderState::DepthFunction::Less:         return glf::DepthFunction::Less;
            case api::RenderState::DepthFunction::LessEqual:    return glf::DepthFunction::LessEqual;
            case api::RenderState::DepthFunction::Greater:      return glf::DepthFunction::Greater;
            case api::RenderState::DepthFunction::GreaterEqual: return glf::DepthFunction::GreaterEqual;

            default: throw std::invalid_argument{ "Invalid depth function!" };
        }
    }
    static constexpr glf::Culling::Face                map_culling_face(api::RenderState::FaceCulling cullingFace)
    {
        switch (cullingFace)
        {
            case api::RenderState::FaceCulling::Front:     return glf::Culling::Face::Front;
            case api::RenderState::FaceCulling::Back:      return glf::Culling::Face::Back;
            case api::RenderState::FaceCulling::FrontBack: return glf::Culling::Face::FrontBack;

            default: throw std::invalid_argument{ "Invalid culling face!" };
        }
    }
                                                             
    template<typename T>                                     
    static constexpr glf::Type                         map_type() requires (std::is_fundamental_v<T>)
    {
        if constexpr (std::is_same_v<T, fox::int8_t>)    return glf::Type::Byte;
        if constexpr (std::is_same_v<T, fox::uint8_t>)   return glf::Type::UnsignedByte;
        if constexpr (std::is_same_v<T, fox::int16_t>)   return glf::Type::Short;
        if constexpr (std::is_same_v<T, fox::uint16_t>)  return glf::Type::UnsignedShort;
        if constexpr (std::is_same_v<T, fox::int32_t>)   return glf::Type::Integer;
        if constexpr (std::is_same_v<T, fox::uint32_t>)  return glf::Type::UnsignedInteger;
        if constexpr (std::is_same_v<T, fox::float32_t>) return glf::Type::Float;
        if constexpr (std::is_same_v<T, fox::float64_t>) return glf::Type::Double;
    }
    static constexpr glf::Type                         map_data_type(gfx::DataType dataType)
    {
        if (dataType == gfx::DataType::Byte)            return glf::Type::Byte;
        if (dataType == gfx::DataType::UnsignedByte)    return glf::Type::UnsignedByte;
        if (dataType == gfx::DataType::Short)           return glf::Type::Short;
        if (dataType == gfx::DataType::UnsignedShort)   return glf::Type::UnsignedShort;
        if (dataType == gfx::DataType::Integer)         return glf::Type::Integer;
        if (dataType == gfx::DataType::UnsignedInteger) return glf::Type::UnsignedInteger;
        if (dataType == gfx::DataType::Float)           return glf::Type::Float;
        if (dataType == gfx::DataType::Double)          return glf::Type::Double;

        throw std::invalid_argument{ "Invalid Data Type!" };
    }
}
