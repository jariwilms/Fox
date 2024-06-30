#pragma once

#include "glad/glad.h"
#include "glfw/glfw3.h"

#include "Helix/Rendering/Buffer/Buffer.hpp"
#include "Helix/Rendering/Buffer/FrameBuffer.hpp"
#include "Helix/Rendering/Shader/Pipeline.hpp"
#include "Helix/Rendering/Shader/Shader.hpp"
#include "Helix/Rendering/Texture/Texture.hpp"
#include "Helix/Rendering/RenderState/RenderState.hpp"

namespace hlx::gfx::imp::api::gl
{
    static constexpr GLenum      map_texture_format(gfx::api::Texture::Format format)
    {
        switch (format)
        {
            case gfx::api::Texture::Format::R8_UNORM:          return GL_R8;
            case gfx::api::Texture::Format::RG8_UNORM:         return GL_RG8;
            case gfx::api::Texture::Format::RGB8_UNORM:        return GL_RGB8;
            case gfx::api::Texture::Format::RGBA8_UNORM:       return GL_RGBA8;
            case gfx::api::Texture::Format::R16_UNORM:         return GL_R16;
            case gfx::api::Texture::Format::RG16_UNORM:        return GL_RG16;
            case gfx::api::Texture::Format::RGB16_UNORM:       return GL_RGB16;
            case gfx::api::Texture::Format::RGBA16_UNORM:      return GL_RGBA16;
            case gfx::api::Texture::Format::R8_SNORM:          return GL_R8_SNORM;
            case gfx::api::Texture::Format::RG8_SNORM:         return GL_RG8_SNORM;
            case gfx::api::Texture::Format::RGB8_SNORM:        return GL_RGB8_SNORM;
            case gfx::api::Texture::Format::RGBA8_SNORM:       return GL_RGBA8_SNORM;
            case gfx::api::Texture::Format::R16_SNORM:         return GL_R16_SNORM;
            case gfx::api::Texture::Format::RG16_SNORM:        return GL_RG16_SNORM;
            case gfx::api::Texture::Format::RGB16_SNORM:       return GL_RGB16_SNORM;
            case gfx::api::Texture::Format::RGBA16_SNORM:      return GL_RGBA16_SNORM;
            case gfx::api::Texture::Format::R8_SRGB:           throw std::invalid_argument{ "This format is not supported in OpenGL!" };
            case gfx::api::Texture::Format::RG8_SRGB:          throw std::invalid_argument{ "This format is not supported in OpenGL!" };
            case gfx::api::Texture::Format::RGB8_SRGB:         return GL_SRGB8;
            case gfx::api::Texture::Format::RGBA8_SRGB:        return GL_SRGB8_ALPHA8;
            case gfx::api::Texture::Format::R16_SFLOAT:        return GL_R16F;
            case gfx::api::Texture::Format::RG16_SFLOAT:       return GL_RG16F;
            case gfx::api::Texture::Format::RGB16_SFLOAT:      return GL_RGB16F;
            case gfx::api::Texture::Format::RGBA16_SFLOAT:     return GL_RGBA16F;
            case gfx::api::Texture::Format::R32_SFLOAT:        return GL_R32F;
            case gfx::api::Texture::Format::RG32_SFLOAT:       return GL_RG32F;
            case gfx::api::Texture::Format::RGB32_SFLOAT:      return GL_RGB32F;
            case gfx::api::Texture::Format::RGBA32_SFLOAT:     return GL_RGBA32F;
            case gfx::api::Texture::Format::D16_UNORM:         return GL_DEPTH_COMPONENT16;
            case gfx::api::Texture::Format::D24_UNORM:         return GL_DEPTH_COMPONENT24;
            case gfx::api::Texture::Format::D32_FLOAT:         return GL_DEPTH_COMPONENT32F;
            case gfx::api::Texture::Format::D24_UNORM_S8_UINT: return GL_DEPTH24_STENCIL8;
            case gfx::api::Texture::Format::D32_FLOAT_S8_UINT: return GL_DEPTH32F_STENCIL8;
            case gfx::api::Texture::Format::S8_UINT:           return GL_STENCIL_INDEX8;

            default: throw std::invalid_argument{ "Invalid format!" };
        }
    }
    static constexpr GLenum      map_texture_format_base(gfx::api::Texture::Format format)
    {
        const auto& flags = (static_cast<int>(format) & 0xFF00) >> 8;
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
    static constexpr GLenum      map_texture_min_filter(gfx::api::Texture::Filter filter)
    {
        switch (filter)
        {
            case gfx::api::Texture::Filter::None:      return GL_NEAREST;
            case gfx::api::Texture::Filter::Point:     return GL_NEAREST_MIPMAP_NEAREST;
            case gfx::api::Texture::Filter::Bilinear:  return GL_LINEAR_MIPMAP_NEAREST;
            case gfx::api::Texture::Filter::Trilinear: return GL_LINEAR_MIPMAP_LINEAR;

            default: throw std::invalid_argument{ "Invalid filter!" };
        }
    }
    static constexpr GLenum      map_texture_mag_filter(gfx::api::Texture::Filter filter)
    {
        switch (filter)
        {
            case gfx::api::Texture::Filter::None:      return GL_NEAREST;
            case gfx::api::Texture::Filter::Point:     return GL_NEAREST;
            case gfx::api::Texture::Filter::Bilinear:  return GL_LINEAR;
            case gfx::api::Texture::Filter::Trilinear: return GL_LINEAR;

            default: throw std::invalid_argument{ "Invalid filter!" };
        }
    }
    static constexpr GLenum      map_texture_wrapping(gfx::api::Texture::Wrapping wrapping)
    {
        switch (wrapping)
        {
            case gfx::api::Texture::Wrapping::ClampToEdge:         return GL_CLAMP_TO_EDGE;
            case gfx::api::Texture::Wrapping::ClampToBorder:       return GL_CLAMP_TO_BORDER;
            case gfx::api::Texture::Wrapping::MirroredRepeat:      return GL_MIRRORED_REPEAT;
            case gfx::api::Texture::Wrapping::Repeat:              return GL_REPEAT;
            case gfx::api::Texture::Wrapping::MirroredClampToEdge: return GL_MIRROR_CLAMP_TO_EDGE;

            default: throw std::invalid_argument{ "Invalid wrapping!" };
        }
    }
    static constexpr GLenum      map_render_buffer_format(gfx::api::Texture::Format format)
    {
        switch (format)
        {
            case gfx::api::Texture::Format::R8_UNORM:          return GL_R8;
            case gfx::api::Texture::Format::RG8_UNORM:         return GL_RG8;
            case gfx::api::Texture::Format::RGB8_UNORM:        return GL_RGB8;
            case gfx::api::Texture::Format::RGBA8_UNORM:       return GL_RGBA8;
            case gfx::api::Texture::Format::D16_UNORM:         return GL_DEPTH_COMPONENT16;
            case gfx::api::Texture::Format::D24_UNORM:         return GL_DEPTH_COMPONENT24;
            case gfx::api::Texture::Format::D32_FLOAT:         return GL_DEPTH_COMPONENT32;
            case gfx::api::Texture::Format::D24_UNORM_S8_UINT: return GL_DEPTH24_STENCIL8;
            case gfx::api::Texture::Format::D32_FLOAT_S8_UINT: return GL_DEPTH32F_STENCIL8;
            case gfx::api::Texture::Format::S8_UINT:           return GL_STENCIL_INDEX8;

            default: throw std::invalid_argument{ "Invalid format!" };
        }
    }
    static constexpr GLenum      map_buffer_target(gfx::api::Buffer::Type type)
    {
        switch (type)
        {
            case gfx::api::Buffer::Type::Vertex:  return GL_ARRAY_BUFFER;
            case gfx::api::Buffer::Type::Index:   return GL_ELEMENT_ARRAY_BUFFER;
            case gfx::api::Buffer::Type::Uniform: return GL_UNIFORM_BUFFER;

            default: throw std::invalid_argument{ "Invalid type!" };
        }
    }
    static constexpr GLbitfield  map_buffer_access(gfx::api::Buffer::Access access)
    {
        switch (access)
        {
            case gfx::api::Buffer::Access::Static:  return {};
            case gfx::api::Buffer::Access::Dynamic: return GL_DYNAMIC_STORAGE_BIT;

            default: throw std::invalid_argument{ "Invalid access!" };
        }
    }
    static constexpr GLenum      map_buffer_mapping(gfx::api::Buffer::Mapping mapping)
    {
        switch (mapping)
        {
            case gfx::api::Buffer::Mapping::Read:      return GL_READ_ONLY;
            case gfx::api::Buffer::Mapping::Write:     return GL_WRITE_ONLY;
            case gfx::api::Buffer::Mapping::ReadWrite: return GL_READ_WRITE;

            default: throw std::invalid_argument{ "Invalid Map!" };
        }
    }
    static constexpr GLenum      map_frame_buffer_attachment(gfx::api::FrameBuffer::Attachment attachment)
    {
        switch (attachment)
        {
            case gfx::api::FrameBuffer::Attachment::Color:        return GL_COLOR_ATTACHMENT0;
            case gfx::api::FrameBuffer::Attachment::Depth:        return GL_DEPTH_ATTACHMENT;
            case gfx::api::FrameBuffer::Attachment::Stencil:      return GL_STENCIL_ATTACHMENT;
            case gfx::api::FrameBuffer::Attachment::DepthStencil: return GL_DEPTH_STENCIL_ATTACHMENT;

            default: throw std::invalid_argument{ "Invalid attachment!" };
        }
    }
    static constexpr GLenum      map_frame_buffer_target(gfx::api::FrameBuffer::Target target)
    {
        switch (target)
        {
            case gfx::api::FrameBuffer::Target::Read:  return GL_READ_FRAMEBUFFER;
            case gfx::api::FrameBuffer::Target::Write: return GL_DRAW_FRAMEBUFFER;

            default: throw std::invalid_argument{ "Invalid framebuffer target!" };
        }
    }
    static constexpr GLenum      map_shader_type(gfx::api::Shader::Stage stage)
    {
        switch (stage)
        {
            case gfx::api::Shader::Stage::Vertex:                 return GL_VERTEX_SHADER;
            case gfx::api::Shader::Stage::TessellationControl:    return GL_TESS_CONTROL_SHADER;
            case gfx::api::Shader::Stage::TessellationEvaluation: return GL_TESS_EVALUATION_SHADER;
            case gfx::api::Shader::Stage::Geometry:               return GL_GEOMETRY_SHADER;
            case gfx::api::Shader::Stage::Fragment:               return GL_FRAGMENT_SHADER;
            case gfx::api::Shader::Stage::Compute:                return GL_COMPUTE_SHADER;

            default: throw std::invalid_argument{ "Invalid stage!" };
        }
    }
    static constexpr GLenum      map_shader_stage(gfx::api::Shader::Stage stage)
    {
        switch (stage)
        {
            case gfx::api::Shader::Stage::Vertex:                 return GL_VERTEX_SHADER_BIT;
            case gfx::api::Shader::Stage::TessellationControl:    return GL_TESS_CONTROL_SHADER_BIT;
            case gfx::api::Shader::Stage::TessellationEvaluation: return GL_TESS_EVALUATION_SHADER_BIT;
            case gfx::api::Shader::Stage::Geometry:               return GL_GEOMETRY_SHADER_BIT;
            case gfx::api::Shader::Stage::Fragment:               return GL_FRAGMENT_SHADER_BIT;
            case gfx::api::Shader::Stage::Compute:                return GL_COMPUTE_SHADER_BIT;

            default: throw std::invalid_argument{ "Invalid stage!" };
        }
    }

    static constexpr GLenum      map_depth_function(gfx::api::RenderState::DepthFunction depthFunction)
    {
        switch (depthFunction)
        {
            case gfx::api::RenderState::DepthFunction::Never:        return GL_NEVER;
            case gfx::api::RenderState::DepthFunction::Less:         return GL_LESS;
            case gfx::api::RenderState::DepthFunction::Equal:        return GL_EQUAL;
            case gfx::api::RenderState::DepthFunction::LessEqual:    return GL_LEQUAL;
            case gfx::api::RenderState::DepthFunction::Greater:      return GL_GREATER;
            case gfx::api::RenderState::DepthFunction::NotEqual:     return GL_NOTEQUAL;
            case gfx::api::RenderState::DepthFunction::GreaterEqual: return GL_GEQUAL;
            case gfx::api::RenderState::DepthFunction::Always:       return GL_ALWAYS;

            default: throw std::invalid_argument{ "Invalid depth function!" };
        }
    }
    static constexpr GLenum      map_culling_face(gfx::api::RenderState::FaceCulling cullingFace)
    {
        switch (cullingFace)
        {
            case gfx::api::RenderState::FaceCulling::Front:     return GL_FRONT;
            case gfx::api::RenderState::FaceCulling::Back:      return GL_BACK;
            case gfx::api::RenderState::FaceCulling::FrontBack: return GL_FRONT_AND_BACK;

            default: throw std::invalid_argument{ "Invalid culling face!" };
        }
    }
}
