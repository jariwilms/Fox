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
    template<Dimensions DIMS, AntiAliasing AA>
    static constexpr gl::enum_t                         map_texture_target()
    {
        if constexpr (AA == AntiAliasing::None)
        {
            if constexpr (DIMS == Dimensions::_1D) return GL_TEXTURE_1D;
            if constexpr (DIMS == Dimensions::_2D) return GL_TEXTURE_2D;
            if constexpr (DIMS == Dimensions::_3D) return GL_TEXTURE_3D;
        }
        if constexpr (AA == AntiAliasing::MSAA)
        {
            if constexpr (DIMS == Dimensions::_2D) return GL_TEXTURE_2D_MULTISAMPLE;
            if constexpr (DIMS == Dimensions::_3D) return GL_TEXTURE_2D_MULTISAMPLE_ARRAY; 
        }

        throw std::invalid_argument{ "The given input can not be mapped to a texture type!" };
    }
    static constexpr gl::enum_t                         map_texture_format(api::Texture::Format format)
    {
        switch (format)
        {
            case api::Texture::Format::R8_UNORM:           return GL_R8;
            case api::Texture::Format::RG8_UNORM:          return GL_RG8;
            case api::Texture::Format::RGB8_UNORM:         return GL_RGB8;
            case api::Texture::Format::RGBA8_UNORM:        return GL_RGBA8;
            case api::Texture::Format::R16_UNORM:          return GL_R16;
            case api::Texture::Format::RG16_UNORM:         return GL_RG16;
            case api::Texture::Format::RGB16_UNORM:        return GL_RGB16;
            case api::Texture::Format::RGBA16_UNORM:       return GL_RGBA16;
            case api::Texture::Format::R8_SNORM:           return GL_R8_SNORM;
            case api::Texture::Format::RG8_SNORM:          return GL_RG8_SNORM;
            case api::Texture::Format::RGB8_SNORM:         return GL_RGB8_SNORM;
            case api::Texture::Format::RGBA8_SNORM:        return GL_RGBA8_SNORM;
            case api::Texture::Format::R16_SNORM:          return GL_R16_SNORM;
            case api::Texture::Format::RG16_SNORM:         return GL_RG16_SNORM;
            case api::Texture::Format::RGB16_SNORM:        return GL_RGB16_SNORM;
            case api::Texture::Format::RGBA16_SNORM:       return GL_RGBA16_SNORM;
            case api::Texture::Format::RGB8_SRGB:          return GL_SRGB8;
            case api::Texture::Format::RGBA8_SRGB:         return GL_SRGB8_ALPHA8;
            case api::Texture::Format::R16_SFLOAT:         return GL_R16F;
            case api::Texture::Format::RG16_SFLOAT:        return GL_RG16F;
            case api::Texture::Format::RGB16_SFLOAT:       return GL_RGB16F;
            case api::Texture::Format::RGBA16_SFLOAT:      return GL_RGBA16F;
            case api::Texture::Format::R32_SFLOAT:         return GL_R32F;
            case api::Texture::Format::RG32_SFLOAT:        return GL_RG32F;
            case api::Texture::Format::RGB32_SFLOAT:       return GL_RGB32F;
            case api::Texture::Format::RGBA32_SFLOAT:      return GL_RGBA32F;
            case api::Texture::Format::D16_UNORM:          return GL_DEPTH_COMPONENT16;
            case api::Texture::Format::D24_UNORM:          return GL_DEPTH_COMPONENT24;
            case api::Texture::Format::D32_SFLOAT:         return GL_DEPTH_COMPONENT32F;
            case api::Texture::Format::D24_UNORM_S8_UINT:  return GL_DEPTH24_STENCIL8;
            case api::Texture::Format::D32_SFLOAT_S8_UINT: return GL_DEPTH32F_STENCIL8;
            case api::Texture::Format::S8_UINT:            return GL_STENCIL_INDEX8;

            default: throw std::invalid_argument{ "Invalid format!" };
        }
    }
    static constexpr gl::enum_t                         map_texture_format_base(api::Texture::Format format)
    {
        const auto& flags = (static_cast<fox::int32_t>(format) & 0xFF00) >> 8;
        switch (flags)
        {
            case 0x01: return GL_RED;
            case 0x02: return GL_RG;
            case 0x03: return GL_RGB;
            case 0x04: return GL_RGBA;

            case 0x10: return GL_DEPTH_COMPONENT;
            case 0x20: return GL_STENCIL_INDEX;
            case 0x30: throw std::invalid_argument{ "Invalid texture format!" };

            default: throw std::invalid_argument{ "Invalid texture format!" };
        }
    }
    static constexpr gl::enum_t                         map_texture_min_filter(api::Texture::Filter filter)
    {
        switch (filter)
        {
            case api::Texture::Filter::None:      return GL_NEAREST;
            case api::Texture::Filter::Nearest:   return GL_NEAREST_MIPMAP_NEAREST;
            case api::Texture::Filter::Bilinear:  return GL_LINEAR_MIPMAP_NEAREST;
            case api::Texture::Filter::Trilinear: return GL_LINEAR_MIPMAP_LINEAR;

            default: throw std::invalid_argument{ "Invalid filter!" };
        }
    }
    static constexpr gl::enum_t                         map_texture_mag_filter(api::Texture::Filter filter)
    {
        switch (filter)
        {
            case api::Texture::Filter::None:      return GL_NEAREST;
            case api::Texture::Filter::Nearest:   return GL_NEAREST;
            case api::Texture::Filter::Bilinear:  return GL_LINEAR;
            case api::Texture::Filter::Trilinear: return GL_LINEAR;

            default: throw std::invalid_argument{ "Invalid filter!" };
        }
    }
    static constexpr gl::enum_t                         map_texture_wrapping(api::Texture::Wrapping wrapping)
    {
        switch (wrapping)
        {
            case api::Texture::Wrapping::ClampToEdge:         return GL_CLAMP_TO_EDGE;
            case api::Texture::Wrapping::ClampToBorder:       return GL_CLAMP_TO_BORDER;
            case api::Texture::Wrapping::MirroredRepeat:      return GL_MIRRORED_REPEAT;
            case api::Texture::Wrapping::Repeat:              return GL_REPEAT;
            case api::Texture::Wrapping::MirroredClampToEdge: return GL_MIRROR_CLAMP_TO_EDGE;

            default: throw std::invalid_argument{ "Invalid wrapping!" };
        }
    }
    static constexpr gl::enum_t                         map_render_buffer_format(api::RenderBuffer::Format format)
    {
        switch (format)
        {
            case api::RenderBuffer::Format::R8_UNORM:           return GL_R8;
            case api::RenderBuffer::Format::RG8_UNORM:          return GL_RG8;
            case api::RenderBuffer::Format::RGB8_UNORM:         return GL_RGB8;
            case api::RenderBuffer::Format::RGBA8_UNORM:        return GL_RGBA8;
            case api::RenderBuffer::Format::RGBA8_SRGB:         return GL_SRGB8_ALPHA8;
            case api::RenderBuffer::Format::D16_UNORM:          return GL_DEPTH_COMPONENT16;
            case api::RenderBuffer::Format::D24_UNORM:          return GL_DEPTH_COMPONENT24;
            case api::RenderBuffer::Format::D32_SFLOAT:         return GL_DEPTH_COMPONENT32;
            case api::RenderBuffer::Format::D24_UNORM_S8_UINT:  return GL_DEPTH24_STENCIL8;
            case api::RenderBuffer::Format::D32_SFLOAT_S8_UINT: return GL_DEPTH32F_STENCIL8;
            case api::RenderBuffer::Format::S8_UINT:            return GL_STENCIL_INDEX8;

            default: throw std::invalid_argument{ "Invalid format!" };
        }
    }
    static constexpr gl::enum_t                         map_buffer_target(api::Buffer::Type type)
    {
        switch (type)
        {
            case api::Buffer::Type::Vertex:  return GL_ARRAY_BUFFER;
            case api::Buffer::Type::Index:   return GL_ELEMENT_ARRAY_BUFFER;
            case api::Buffer::Type::Uniform: return GL_UNIFORM_BUFFER;

            default: throw std::invalid_argument{ "Invalid type!" };
        }
    }
    static constexpr gl::Flags::Buffer::StorageFlags    map_buffer_access(api::Buffer::Access access)
    {
        switch (access)
        {
            case api::Buffer::Access::Static:  return Flags::Buffer::StorageFlags::None;
            case api::Buffer::Access::Dynamic: return Flags::Buffer::StorageFlags::DynamicStorage;

            default: throw std::invalid_argument{ "Invalid access!" };
        }
    }
    static constexpr gl::enum_t                         map_buffer_mapping(api::Buffer::Mapping mapping)
    {
        switch (mapping)
        {
            case api::Buffer::Mapping::Read:      return GL_READ_ONLY;
            case api::Buffer::Mapping::Write:     return GL_WRITE_ONLY;
            case api::Buffer::Mapping::ReadWrite: return GL_READ_WRITE;

            default: throw std::invalid_argument{ "Invalid Map!" };
        }
    }
    static constexpr gl::Flags::FrameBuffer::Attachment map_frame_buffer_attachment(api::FrameBuffer::Attachment attachment)
    {
        switch (attachment)
        {
            case api::FrameBuffer::Attachment::Color:        return gl::Flags::FrameBuffer::Attachment::ColorIndex;
            case api::FrameBuffer::Attachment::Depth:        return gl::Flags::FrameBuffer::Attachment::Depth;
            case api::FrameBuffer::Attachment::Stencil:      return gl::Flags::FrameBuffer::Attachment::Stencil;
            case api::FrameBuffer::Attachment::DepthStencil: return gl::Flags::FrameBuffer::Attachment::DepthStencil;

            default: throw std::invalid_argument{ "Invalid attachment!" };
        }
    }
    static constexpr gl::Flags::FrameBuffer::Target     map_frame_buffer_target(api::FrameBuffer::Target target)
    {
        switch (target)
        {
            case api::FrameBuffer::Target::Read:  return gl::Flags::FrameBuffer::Target::Read;
            case api::FrameBuffer::Target::Write: return gl::Flags::FrameBuffer::Target::Write;

            default: throw std::invalid_argument{ "Invalid framebuffer target!" };
        }
    }
    static constexpr gl::Flags::Shader::Type            map_shader_type(api::Shader::Stage stage)
    {
        switch (stage)
        {
            case api::Shader::Stage::Vertex:                 return gl::Flags::Shader::Type::Vertex;
            case api::Shader::Stage::TessellationControl:    return gl::Flags::Shader::Type::TessellationControl;
            case api::Shader::Stage::TessellationEvaluation: return gl::Flags::Shader::Type::TessellationEvaluation;
            case api::Shader::Stage::Geometry:               return gl::Flags::Shader::Type::Geometry;
            case api::Shader::Stage::Fragment:               return gl::Flags::Shader::Type::Fragment;
            case api::Shader::Stage::Compute:                return gl::Flags::Shader::Type::Compute;

            default: throw std::invalid_argument{ "Invalid stage!" };
        }
    }
    static constexpr gl::enum_t                         map_shader_stage(api::Shader::Stage stage)
    {
        switch (stage)
        {
            case api::Shader::Stage::Vertex:                 return GL_VERTEX_SHADER_BIT;
            case api::Shader::Stage::TessellationControl:    return GL_TESS_CONTROL_SHADER_BIT;
            case api::Shader::Stage::TessellationEvaluation: return GL_TESS_EVALUATION_SHADER_BIT;
            case api::Shader::Stage::Geometry:               return GL_GEOMETRY_SHADER_BIT;
            case api::Shader::Stage::Fragment:               return GL_FRAGMENT_SHADER_BIT;
            case api::Shader::Stage::Compute:                return GL_COMPUTE_SHADER_BIT;

            default: throw std::invalid_argument{ "Invalid stage!" };
        }
    }
                                                 
    //static constexpr gl::enum_t                         map_query_target(api::Query::Target target)
    //{
    //    switch (target)
    //    {
    //        return 0;
    //    }
    //    throw std::invalid_argument{ "Invalid target!" };
    //}

    static constexpr gl::Flags::DepthFunction           map_depth_function(api::RenderState::DepthFunction depthFunction)
    {
        switch (depthFunction)
        {
            case api::RenderState::DepthFunction::Always:       return gl::Flags::DepthFunction::Always;
            case api::RenderState::DepthFunction::Never:        return gl::Flags::DepthFunction::Never;
            case api::RenderState::DepthFunction::Equal:        return gl::Flags::DepthFunction::Equal;
            case api::RenderState::DepthFunction::NotEqual:     return gl::Flags::DepthFunction::NotEqual;
            case api::RenderState::DepthFunction::Less:         return gl::Flags::DepthFunction::Less;
            case api::RenderState::DepthFunction::LessEqual:    return gl::Flags::DepthFunction::LessEqual;
            case api::RenderState::DepthFunction::Greater:      return gl::Flags::DepthFunction::Greater;
            case api::RenderState::DepthFunction::GreaterEqual: return gl::Flags::DepthFunction::GreaterEqual;

            default: throw std::invalid_argument{ "Invalid depth function!" };
        }
    }
    static constexpr gl::Flags::Culling::Face           map_culling_face(api::RenderState::FaceCulling cullingFace)
    {
        switch (cullingFace)
        {
            case api::RenderState::FaceCulling::Front:     return gl::Flags::Culling::Face::Front;
            case api::RenderState::FaceCulling::Back:      return gl::Flags::Culling::Face::Back;
            case api::RenderState::FaceCulling::FrontBack: return gl::Flags::Culling::Face::FrontBack;

            default: throw std::invalid_argument{ "Invalid culling face!" };
        }
    }
                                                        
    template<typename T>                                
    static constexpr gl::enum_t                         map_type() requires (std::is_fundamental_v<T>)
    {
        if constexpr (std::is_same_v<T, fox::int8_t>)    return GL_BYTE;
        if constexpr (std::is_same_v<T, fox::uint8_t>)   return GL_UNSIGNED_BYTE;
        if constexpr (std::is_same_v<T, fox::int16_t>)   return GL_SHORT;
        if constexpr (std::is_same_v<T, fox::uint16_t>)  return GL_UNSIGNED_SHORT;
        if constexpr (std::is_same_v<T, fox::int32_t>)   return GL_INT;
        if constexpr (std::is_same_v<T, fox::uint32_t>)  return GL_UNSIGNED_INT;
        if constexpr (std::is_same_v<T, fox::float32_t>) return GL_FLOAT;
        if constexpr (std::is_same_v<T, fox::float64_t>) return GL_DOUBLE;
    }
    static constexpr gl::enum_t                         map_data_type(gfx::DataType dataType)
    {
        if (dataType == gfx::DataType::Byte)            return GL_BYTE;
        if (dataType == gfx::DataType::UnsignedByte)    return GL_UNSIGNED_BYTE;
        if (dataType == gfx::DataType::Short)           return GL_SHORT;
        if (dataType == gfx::DataType::UnsignedShort)   return GL_UNSIGNED_SHORT;
        if (dataType == gfx::DataType::Integer)         return GL_INT;
        if (dataType == gfx::DataType::UnsignedInteger) return GL_UNSIGNED_INT;
        if (dataType == gfx::DataType::Float)           return GL_FLOAT;
        if (dataType == gfx::DataType::Double)          return GL_DOUBLE;

        throw std::invalid_argument{ "Invalid Data Type!" };
    }
}
