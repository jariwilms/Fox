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

namespace fox::gfx::api::gl
{
    static constexpr gl::flg::Buffer::Mapping              map_buffer_mapping(api::Buffer::Mapping mapping)
    {
        switch (mapping)
        {
            case api::Buffer::Mapping::Read:      return gl::flg::Buffer::Mapping::Read;
            case api::Buffer::Mapping::Write:     return gl::flg::Buffer::Mapping::Write;
            case api::Buffer::Mapping::ReadWrite: return gl::flg::Buffer::Mapping::ReadWrite;

            default: throw std::invalid_argument{ "Invalid Mapping!" };
        }
    }
    static constexpr gl::flg::Buffer::StorageFlags         map_buffer_access(api::Buffer::Access access)
    {
        switch (access)
        {
            case api::Buffer::Access::Static:  return gl::flg::Buffer::StorageFlags::None;
            case api::Buffer::Access::Dynamic: return gl::flg::Buffer::StorageFlags::DynamicStorage;

            default: throw std::invalid_argument{ "Invalid access!" };
        }
    }
    static constexpr gl::flg::Buffer::Target               map_buffer_target(api::Buffer::Type type)
    {
        switch (type)
        {
            case api::Buffer::Type::Vertex:  return gl::flg::Buffer::Target::ArrayBuffer;
            case api::Buffer::Type::Index:   return gl::flg::Buffer::Target::ElementArrayBuffer;
            case api::Buffer::Type::Uniform: return gl::flg::Buffer::Target::UniformBuffer;

            default: throw std::invalid_argument{ "Invalid type!" };
        }
    }
    static constexpr gl::flg::Texture::BaseFormat          map_texture_format_base(api::Texture::Format format)
    {
        const auto& flags = (static_cast<gl::int32_t>(format) & 0xFF00) >> 8;

        switch (flags)
        {
            case 0x01: return gl::flg::Texture::BaseFormat::R;
            case 0x02: return gl::flg::Texture::BaseFormat::RG;
            case 0x03: return gl::flg::Texture::BaseFormat::RGB;
            case 0x04: return gl::flg::Texture::BaseFormat::RGBA;

            case 0x10: return gl::flg::Texture::BaseFormat::Depth;
            case 0x20: return gl::flg::Texture::BaseFormat::Stencil;

            case 0x30: throw std::invalid_argument{ "Invalid texture format!" };

            default: throw std::invalid_argument{ "Invalid texture format!" };
        }
    }
    static constexpr gl::flg::Texture::Format              map_texture_format(api::Texture::Format format)
    {
        switch (format)
        {
            case api::Texture::Format::R8_UNORM:          return gl::flg::Texture::Format::R8_UNORM;
            case api::Texture::Format::RG8_UNORM:         return gl::flg::Texture::Format::RG8_UNORM;
            case api::Texture::Format::RGB8_UNORM:        return gl::flg::Texture::Format::RGB8_UNORM;
            case api::Texture::Format::RGBA8_UNORM:       return gl::flg::Texture::Format::RGBA8_UNORM;
            case api::Texture::Format::R16_UNORM:         return gl::flg::Texture::Format::R16_UNORM;
            case api::Texture::Format::RG16_UNORM:        return gl::flg::Texture::Format::RG16_UNORM;
            case api::Texture::Format::RGB16_UNORM:       return gl::flg::Texture::Format::RGB16_UNORM;
            case api::Texture::Format::RGBA16_UNORM:      return gl::flg::Texture::Format::RGBA16_UNORM;
            case api::Texture::Format::R8_SNORM:          return gl::flg::Texture::Format::R8_SNORM;
            case api::Texture::Format::RG8_SNORM:         return gl::flg::Texture::Format::RG8_SNORM;
            case api::Texture::Format::RGB8_SNORM:        return gl::flg::Texture::Format::RGB8_SNORM;
            case api::Texture::Format::RGBA8_SNORM:       return gl::flg::Texture::Format::RGBA8_SNORM;
            case api::Texture::Format::R16_SNORM:         return gl::flg::Texture::Format::R16_SNORM;
            case api::Texture::Format::RG16_SNORM:        return gl::flg::Texture::Format::RG16_SNORM;
            case api::Texture::Format::RGB16_SNORM:       return gl::flg::Texture::Format::RGB16_SNORM;
            case api::Texture::Format::RGBA16_SNORM:      return gl::flg::Texture::Format::RGBA16_SNORM;
            case api::Texture::Format::RGB8_SRGB:         return gl::flg::Texture::Format::RGB8_SRGB;
            case api::Texture::Format::RGBA8_SRGB:        return gl::flg::Texture::Format::RGBA8_SRGB;
            case api::Texture::Format::R16_FLOAT:         return gl::flg::Texture::Format::R16_FLOAT;
            case api::Texture::Format::RG16_FLOAT:        return gl::flg::Texture::Format::RG16_FLOAT;
            case api::Texture::Format::RGB16_FLOAT:       return gl::flg::Texture::Format::RGB16_FLOAT;
            case api::Texture::Format::RGBA16_FLOAT:      return gl::flg::Texture::Format::RGBA16_FLOAT;
            case api::Texture::Format::R32_FLOAT:         return gl::flg::Texture::Format::R32_FLOAT;
            case api::Texture::Format::RG32_FLOAT:        return gl::flg::Texture::Format::RG32_FLOAT;
            case api::Texture::Format::RGB32_FLOAT:       return gl::flg::Texture::Format::RGB32_FLOAT;
            case api::Texture::Format::RGBA32_FLOAT:      return gl::flg::Texture::Format::RGBA32_FLOAT;
            case api::Texture::Format::D16_UNORM:         return gl::flg::Texture::Format::D16_UNORM;
            case api::Texture::Format::D24_UNORM:         return gl::flg::Texture::Format::D24_UNORM;
            case api::Texture::Format::D32_FLOAT:         return gl::flg::Texture::Format::D32_FLOAT;
            case api::Texture::Format::D24_UNORM_S8_UINT: return gl::flg::Texture::Format::D24_UNORM_S8_UINT;
            case api::Texture::Format::D32_FLOAT_S8_UINT: return gl::flg::Texture::Format::D32_FLOAT_S8_UINT;
            case api::Texture::Format::S8_UINT:           return gl::flg::Texture::Format::S8_UINT;

            default: throw std::invalid_argument{ "Invalid format!" };
        }
    }
    static constexpr gl::flg::Texture::MinificationFilter  map_texture_min_filter(api::Texture::Filter filter)
    {
        switch (filter)
        {
            case api::Texture::Filter::None:      return gl::flg::Texture::MinificationFilter::Nearest;
            case api::Texture::Filter::Nearest:   return gl::flg::Texture::MinificationFilter::NearestMipmapNearest;
            case api::Texture::Filter::Bilinear:  return gl::flg::Texture::MinificationFilter::LinearMipmapNearest;
            case api::Texture::Filter::Trilinear: return gl::flg::Texture::MinificationFilter::LinearMipmapLinear;

            default: throw std::invalid_argument{ "Invalid filter!" };
        }
    }
    static constexpr gl::flg::Texture::MagnificationFilter map_texture_mag_filter(api::Texture::Filter filter)
    {
        switch (filter)
        {
            case api::Texture::Filter::None:      return gl::flg::Texture::MagnificationFilter::Nearest;
            case api::Texture::Filter::Nearest:   return gl::flg::Texture::MagnificationFilter::Nearest;
            case api::Texture::Filter::Bilinear:  return gl::flg::Texture::MagnificationFilter::Linear;
            case api::Texture::Filter::Trilinear: return gl::flg::Texture::MagnificationFilter::Linear;

            default: throw std::invalid_argument{ "Invalid filter!" };
        }
    }
    template<gfx::Dimensions DIMS, gfx::AntiAliasing AA>
    static constexpr gl::flg::Texture::Target              map_texture_target()
    {
        if constexpr (AA == gfx::AntiAliasing::None)
        {
            if constexpr (DIMS == gfx::Dimensions::_1D) return gl::flg::Texture::Target::_1D;
            if constexpr (DIMS == gfx::Dimensions::_2D) return gl::flg::Texture::Target::_2D;
            if constexpr (DIMS == gfx::Dimensions::_3D) return gl::flg::Texture::Target::_3D;
        }
        if constexpr (AA == gfx::AntiAliasing::MSAA)
        {
            if constexpr (DIMS == gfx::Dimensions::_2D) return gl::flg::Texture::Target::_2DMultisample;
            if constexpr (DIMS == gfx::Dimensions::_3D) return gl::flg::Texture::Target::_2DMultisampleArray;
        }

        throw std::invalid_argument{ "The given input can not be mapped to a texture type!" };
    }
    static constexpr gl::flg::Texture::Wrapping            map_texture_wrapping(api::Texture::Wrapping wrapping)
    {
        switch (wrapping)
        {
            case api::Texture::Wrapping::ClampToEdge:         return gl::flg::Texture::Wrapping::ClampToEdge;
            case api::Texture::Wrapping::ClampToBorder:       return gl::flg::Texture::Wrapping::ClampToBorder;
            case api::Texture::Wrapping::Repeat:              return gl::flg::Texture::Wrapping::Repeat;
            case api::Texture::Wrapping::MirroredRepeat:      return gl::flg::Texture::Wrapping::MirroredRepeat;
            case api::Texture::Wrapping::MirroredClampToEdge: return gl::flg::Texture::Wrapping::MirroredClampToEdge;

            default: throw std::invalid_argument{ "Invalid wrapping!" };
        }
    }
    static constexpr gl::flg::RenderBuffer::Format         map_render_buffer_format(api::RenderBuffer::Format format)
    {
        switch (format)
        {
            case api::RenderBuffer::Format::R8_UNORM:          return gl::flg::RenderBuffer::Format::R8;
            case api::RenderBuffer::Format::RG8_UNORM:         return gl::flg::RenderBuffer::Format::RG8;
            case api::RenderBuffer::Format::RGB8_UNORM:        return gl::flg::RenderBuffer::Format::RGB8;
            case api::RenderBuffer::Format::RGBA8_UNORM:       return gl::flg::RenderBuffer::Format::RGBA8;
            case api::RenderBuffer::Format::RGBA8_SRGB:        return gl::flg::RenderBuffer::Format::RGBA8_SRGB;
            case api::RenderBuffer::Format::D16_UNORM:         return gl::flg::RenderBuffer::Format::D16_UNORM;
            case api::RenderBuffer::Format::D24_UNORM:         return gl::flg::RenderBuffer::Format::D24_UNORM;
            case api::RenderBuffer::Format::D32_FLOAT:         return gl::flg::RenderBuffer::Format::D32_FLOAT;
            case api::RenderBuffer::Format::D24_UNORM_S8_UINT: return gl::flg::RenderBuffer::Format::D24_UNORM_S8_UINT;
            case api::RenderBuffer::Format::D32_FLOAT_S8_UINT: return gl::flg::RenderBuffer::Format::D32_FLOAT_S8_UINT;
            case api::RenderBuffer::Format::S8_UINT:           return gl::flg::RenderBuffer::Format::S8_UINT;

            default: throw std::invalid_argument{ "Invalid format!" };
        }
    }
    static constexpr gl::flg::FrameBuffer::Attachment      map_frame_buffer_attachment(api::FrameBuffer::Attachment attachment)
    {
        switch (attachment)
        {
            case api::FrameBuffer::Attachment::Color:        return gl::flg::FrameBuffer::Attachment::ColorIndex;
            case api::FrameBuffer::Attachment::Depth:        return gl::flg::FrameBuffer::Attachment::Depth;
            case api::FrameBuffer::Attachment::Stencil:      return gl::flg::FrameBuffer::Attachment::Stencil;
            case api::FrameBuffer::Attachment::DepthStencil: return gl::flg::FrameBuffer::Attachment::DepthStencil;

            default: throw std::invalid_argument{ "Invalid attachment!" };
        }
    }
    static constexpr gl::flg::FrameBuffer::Target          map_frame_buffer_target(api::FrameBuffer::Target target)
    {
        switch (target)
        {
            case api::FrameBuffer::Target::Read:  return gl::flg::FrameBuffer::Target::Read;
            case api::FrameBuffer::Target::Write: return gl::flg::FrameBuffer::Target::Write;

            default: throw std::invalid_argument{ "Invalid framebuffer target!" };
        }
    }
    static constexpr gl::flg::Shader::Stage                map_shader_stage(api::Shader::Stage stage)
    {
        switch (stage)
        {
            case api::Shader::Stage::Vertex:                 return gl::flg::Shader::Stage::Vertex;
            case api::Shader::Stage::TessellationControl:    return gl::flg::Shader::Stage::TessellationControl;
            case api::Shader::Stage::TessellationEvaluation: return gl::flg::Shader::Stage::TessellationEvaluation;
            case api::Shader::Stage::Geometry:               return gl::flg::Shader::Stage::Geometry;
            case api::Shader::Stage::Fragment:               return gl::flg::Shader::Stage::Fragment;
            case api::Shader::Stage::Compute:                return gl::flg::Shader::Stage::Compute;

            default: throw std::invalid_argument{ "Invalid stage!" };
        }
    }                                                                      
    static constexpr gl::flg::Shader::Type                 map_shader_type(api::Shader::Stage stage)
    {
        switch (stage)
        {
            case api::Shader::Stage::Vertex:                 return gl::flg::Shader::Type::Vertex;
            case api::Shader::Stage::TessellationControl:    return gl::flg::Shader::Type::TessellationControl;
            case api::Shader::Stage::TessellationEvaluation: return gl::flg::Shader::Type::TessellationEvaluation;
            case api::Shader::Stage::Geometry:               return gl::flg::Shader::Type::Geometry;
            case api::Shader::Stage::Fragment:               return gl::flg::Shader::Type::Fragment;
            case api::Shader::Stage::Compute:                return gl::flg::Shader::Type::Compute;

            default: throw std::invalid_argument{ "Invalid stage!" };
        }
    }
    static constexpr gl::flg::DepthFunction                map_depth_function(api::RenderState::DepthFunction depthFunction)
    {
        switch (depthFunction)
        {
            case api::RenderState::DepthFunction::Always:       return gl::flg::DepthFunction::Always;
            case api::RenderState::DepthFunction::Never:        return gl::flg::DepthFunction::Never;
            case api::RenderState::DepthFunction::Equal:        return gl::flg::DepthFunction::Equal;
            case api::RenderState::DepthFunction::NotEqual:     return gl::flg::DepthFunction::NotEqual;
            case api::RenderState::DepthFunction::Less:         return gl::flg::DepthFunction::Less;
            case api::RenderState::DepthFunction::LessEqual:    return gl::flg::DepthFunction::LessEqual;
            case api::RenderState::DepthFunction::Greater:      return gl::flg::DepthFunction::Greater;
            case api::RenderState::DepthFunction::GreaterEqual: return gl::flg::DepthFunction::GreaterEqual;

            default: throw std::invalid_argument{ "Invalid depth function!" };
        }
    }
    static constexpr gl::flg::Culling::Face                map_culling_face(api::RenderState::FaceCulling cullingFace)
    {
        switch (cullingFace)
        {
            case api::RenderState::FaceCulling::Front:     return gl::flg::Culling::Face::Front;
            case api::RenderState::FaceCulling::Back:      return gl::flg::Culling::Face::Back;
            case api::RenderState::FaceCulling::FrontBack: return gl::flg::Culling::Face::FrontBack;

            default: throw std::invalid_argument{ "Invalid culling face!" };
        }
    }
                                                             
    template<typename T>                                     
    static constexpr gl::flg::Type                         map_type() requires (std::is_fundamental_v<T>)
    {
        if constexpr (std::is_same_v<T, fox::int8_t>)    return gl::flg::Type::Byte;
        if constexpr (std::is_same_v<T, fox::uint8_t>)   return gl::flg::Type::UnsignedByte;
        if constexpr (std::is_same_v<T, fox::int16_t>)   return gl::flg::Type::Short;
        if constexpr (std::is_same_v<T, fox::uint16_t>)  return gl::flg::Type::UnsignedShort;
        if constexpr (std::is_same_v<T, fox::int32_t>)   return gl::flg::Type::Integer;
        if constexpr (std::is_same_v<T, fox::uint32_t>)  return gl::flg::Type::UnsignedInteger;
        if constexpr (std::is_same_v<T, fox::float32_t>) return gl::flg::Type::Float;
        if constexpr (std::is_same_v<T, fox::float64_t>) return gl::flg::Type::Double;
    }
    static constexpr gl::flg::Type                         map_data_type(gfx::DataType dataType)
    {
        if (dataType == gfx::DataType::Byte)            return gl::flg::Type::Byte;
        if (dataType == gfx::DataType::UnsignedByte)    return gl::flg::Type::UnsignedByte;
        if (dataType == gfx::DataType::Short)           return gl::flg::Type::Short;
        if (dataType == gfx::DataType::UnsignedShort)   return gl::flg::Type::UnsignedShort;
        if (dataType == gfx::DataType::Integer)         return gl::flg::Type::Integer;
        if (dataType == gfx::DataType::UnsignedInteger) return gl::flg::Type::UnsignedInteger;
        if (dataType == gfx::DataType::Float)           return gl::flg::Type::Float;
        if (dataType == gfx::DataType::Double)          return gl::flg::Type::Double;

        throw std::invalid_argument{ "Invalid Data Type!" };
    }
}
