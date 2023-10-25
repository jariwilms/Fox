#pragma once

#include "stdafx.hpp"

#include "glad/glad.h"
#include "glfw/glfw3.h"

#include "Helix/Experimental/Rendering/Buffer/Buffer.hpp"
#include "Helix/Experimental/Rendering/Texture/Texture.hpp"
#include "Helix/Experimental/Rendering/Buffer/FrameBuffer.hpp"
#include "Helix/Experimental/Rendering/Shader/Pipeline.hpp"
#include "Helix/Experimental/Rendering/Shader/Shader.hpp"

namespace hlx::gfx::api::gl
{
    template<typename T>
    constexpr GLenum      type_enum()
    {
        if constexpr (std::is_same_v<T, char>)           return GL_BYTE;
        if constexpr (std::is_same_v<T, unsigned char>)  return GL_UNSIGNED_BYTE;
        if constexpr (std::is_same_v<T, short>)          return GL_SHORT;
        if constexpr (std::is_same_v<T, unsigned short>) return GL_UNSIGNED_SHORT;
        if constexpr (std::is_same_v<T, int>)            return GL_INT;
        if constexpr (std::is_same_v<T, unsigned int>)   return GL_UNSIGNED_INT;
        if constexpr (std::is_same_v<T, float>)          return GL_FLOAT;
        if constexpr (std::is_same_v<T, double>)         return GL_DOUBLE;

        throw std::invalid_argument{ "Invalid type!" };
    }
    template<typename T>
    constexpr GLsizei     type_size()
    {
        if constexpr (std::is_same_v<T, char>)               return sizeof(GLbyte);
        if constexpr (std::is_same_v<T, unsigned char>)      return sizeof(GLubyte);
        if constexpr (std::is_same_v<T, short>)              return sizeof(GLshort);
        if constexpr (std::is_same_v<T, unsigned short>)     return sizeof(GLushort);
        if constexpr (std::is_same_v<T, int>)                return sizeof(GLint);
        if constexpr (std::is_same_v<T, unsigned int>)       return sizeof(GLuint);
        if constexpr (std::is_same_v<T, long long>)          return sizeof(GLint64);
        if constexpr (std::is_same_v<T, unsigned long long>) return sizeof(GLuint64);
        if constexpr (std::is_same_v<T, float>)              return sizeof(GLfloat);
        if constexpr (std::is_same_v<T, double>)             return sizeof(GLdouble);

        throw std::invalid_argument{ "Invalid type!" };
    }



    constexpr GLenum      texture_format(Texture::Format format)
    {
        switch (format)
        {
            case Texture::Format::R8_UNORM:          return GL_R8;
            case Texture::Format::RG8_UNORM:         return GL_RG8;
            case Texture::Format::RGB8_UNORM:        return GL_RGB8;
            case Texture::Format::RGBA8_UNORM:       return GL_RGBA8;
            case Texture::Format::R16_UNORM:         return GL_R16;
            case Texture::Format::RG16_UNORM:        return GL_RG16;
            case Texture::Format::RGB16_UNORM:       return GL_RGB16;
            case Texture::Format::RGBA16_UNORM:      return GL_RGBA16;
            case Texture::Format::R8_SNORM:          return GL_R8_SNORM;
            case Texture::Format::RG8_SNORM:         return GL_RG8_SNORM;
            case Texture::Format::RGB8_SNORM:        return GL_RGB8_SNORM;
            case Texture::Format::RGBA8_SNORM:       return GL_RGBA8_SNORM;
            case Texture::Format::R16_SNORM:         return GL_R16_SNORM;
            case Texture::Format::RG16_SNORM:        return GL_RG16_SNORM;
            case Texture::Format::RGB16_SNORM:       return GL_RGB16_SNORM;
            case Texture::Format::RGBA16_SNORM:      return GL_RGBA16_SNORM;
            case Texture::Format::R8_SRGB:           throw std::invalid_argument{ "This format is not supported in OpenGL!" };
            case Texture::Format::RG8_SRGB:          throw std::invalid_argument{ "This format is not supported in OpenGL!" };
            case Texture::Format::RGB8_SRGB:         return GL_SRGB8;
            case Texture::Format::RGBA8_SRGB:        return GL_SRGB8_ALPHA8;
            case Texture::Format::R16_SFLOAT:        return GL_R16F;
            case Texture::Format::RG16_SFLOAT:       return GL_RG16F;
            case Texture::Format::RGB16_SFLOAT:      return GL_RGB16F;
            case Texture::Format::RGBA16_SFLOAT:     return GL_RGBA16F;
            case Texture::Format::R32_SFLOAT:        return GL_R32F;
            case Texture::Format::RG32_SFLOAT:       return GL_RG32F;
            case Texture::Format::RGB32_SFLOAT:      return GL_RGB32F;
            case Texture::Format::RGBA32_SFLOAT:     return GL_RGBA32F;
            case Texture::Format::D16_UNORM:         return GL_DEPTH_COMPONENT16;
            case Texture::Format::D24_UNORM:         return GL_DEPTH_COMPONENT24;
            case Texture::Format::D32_FLOAT:         return GL_DEPTH_COMPONENT32F;
            case Texture::Format::D24_UNORM_S8_UINT: return GL_DEPTH24_STENCIL8;
            case Texture::Format::D32_FLOAT_S8_UINT: return GL_DEPTH32F_STENCIL8;
            case Texture::Format::S8_UINT:           return GL_STENCIL_INDEX8;

            default: throw std::invalid_argument{ "Invalid format!" };
        }
    }
    constexpr GLenum      texture_min_filter(Texture::Filter filter)
    {
        switch (filter)
        {
            case Texture::Filter::None:      return GL_NEAREST;
            case Texture::Filter::Point:     return GL_NEAREST_MIPMAP_NEAREST;
            case Texture::Filter::Bilinear:  return GL_LINEAR_MIPMAP_NEAREST;
            case Texture::Filter::Trilinear: return GL_LINEAR_MIPMAP_LINEAR;

            default: throw std::invalid_argument{ "Invalid filter!" };
        }
    }
    constexpr GLenum      texture_mag_filter(Texture::Filter filter)
    {
        switch (filter)
        {
            case Texture::Filter::None:      return GL_NEAREST;
            case Texture::Filter::Point:     return GL_NEAREST;
            case Texture::Filter::Bilinear:  return GL_LINEAR;
            case Texture::Filter::Trilinear: return GL_LINEAR;

            default: throw std::invalid_argument{ "Invalid filter!" };
        }
    }
    constexpr GLenum      texture_wrapping(Texture::Wrapping wrapping)
    {
        switch (wrapping)
        {
            case Texture::Wrapping::ClampToEdge:         return GL_CLAMP_TO_EDGE;
            case Texture::Wrapping::ClampToBorder:       return GL_CLAMP_TO_BORDER;
            case Texture::Wrapping::MirroredRepeat:      return GL_MIRRORED_REPEAT;
            case Texture::Wrapping::Repeat:              return GL_REPEAT;
            case Texture::Wrapping::MirroredClampToEdge: return GL_MIRROR_CLAMP_TO_EDGE;

            default: throw std::invalid_argument{ "Invalid wrapping!" };
        }
    }

    constexpr GLbitfield  buffer_usage(Buffer::Usage usage)
    {
        switch (usage)
        {
            case Buffer::Usage::Static:  return {};
            case Buffer::Usage::Dynamic: return GL_DYNAMIC_STORAGE_BIT;

            default: throw std::invalid_argument{ "Invalid usage!" };
        }
    }
    constexpr GLenum      buffer_target(Buffer::Type type)
    {
        switch (type)
        {
            case Buffer::Type::Vertex:  return GL_ARRAY_BUFFER;
            case Buffer::Type::Index:   return GL_ELEMENT_ARRAY_BUFFER;
            case Buffer::Type::Uniform: return GL_UNIFORM_BUFFER;

            default: throw std::invalid_argument{ "Invalid type!" };
        }
    }

    constexpr GLenum      frame_buffer_attachment(FrameBuffer::Attachment attachment)
    {
        switch (attachment)
        {
            case FrameBuffer::Attachment::Color:        return GL_COLOR_ATTACHMENT0;
            case FrameBuffer::Attachment::Depth:        return GL_DEPTH_ATTACHMENT;
            case FrameBuffer::Attachment::Stencil:      return GL_STENCIL_ATTACHMENT;
            case FrameBuffer::Attachment::DepthStencil: return GL_DEPTH_STENCIL_ATTACHMENT;

            default: throw std::invalid_argument{ "Invalid attachment!" };
        }
    }

    constexpr GLenum      shader_type(Shader::Stage stage)
    {
        switch (stage)
        {
            case Shader::Stage::Vertex:                 return GL_VERTEX_SHADER;
            case Shader::Stage::TessellationControl:    return GL_TESS_CONTROL_SHADER;
            case Shader::Stage::TessellationEvaluation: return GL_TESS_EVALUATION_SHADER;
            case Shader::Stage::Geometry:               return GL_GEOMETRY_SHADER;
            case Shader::Stage::Fragment:			    return GL_FRAGMENT_SHADER;
            case Shader::Stage::Compute:				return GL_COMPUTE_SHADER;

            default: throw std::invalid_argument{ "Invalid stage!" };
        }
    }
    constexpr GLenum      shader_stage(Shader::Stage stage)
    {
        switch (stage)
        {
            case Shader::Stage::Vertex:                 return GL_VERTEX_SHADER_BIT;
            case Shader::Stage::TessellationControl:    return GL_TESS_CONTROL_SHADER_BIT;
            case Shader::Stage::TessellationEvaluation: return GL_TESS_EVALUATION_SHADER_BIT;
            case Shader::Stage::Geometry:               return GL_GEOMETRY_SHADER_BIT;
            case Shader::Stage::Fragment:			    return GL_FRAGMENT_SHADER_BIT;
            case Shader::Stage::Compute:				return GL_COMPUTE_SHADER_BIT;

            default: throw std::invalid_argument{ "Invalid stage!" };
        }
    }



    GLint       integer_v(GLenum parameter)
    {
        GLint result{};
        //glGetIntegerv(parameter, &result);

        return result;
    }
    GLint       shader_iv(GLuint shader, GLenum parameter)
    {
        GLint result{};
        glGetShaderiv(shader, parameter, &result);

        return result;
    }
    GLint       program_iv(GLuint program, GLenum parameter)
    {
        GLint result{};
        glGetProgramiv(program, parameter, &result);

        return result;
    }
    std::string shader_infolog(GLuint shader)
    {
        const GLsizei length = shader_iv(shader, GL_INFO_LOG_LENGTH);

        std::string infolog{};
        infolog.resize(length);
        
        glGetShaderInfoLog(shader, length, nullptr, infolog.data());

        return infolog;
    }
    std::string program_infolog(GLuint program)
    {
        std::string infolog{};
        GLsizei length = program_iv(program, GL_INFO_LOG_LENGTH);
        GLsizei bufSize{ length };

        infolog.resize(length);
        glGetProgramInfoLog(program, bufSize, nullptr, infolog.data());

        return infolog;
    }


    GLuint create_buffer()
    {
        GLuint id{};
        //glCreateBuffers(1, &id);

        return id;
    }
    void   delete_buffer(GLuint id)
    {
        //glDeleteBuffers(1, &id);
    }
    void   bind_buffer(GLuint id, Buffer::Type type)
    {
        const auto& target = buffer_target(type);
        //glBindBuffer(target, id);
    }
    template<typename T>
    void   buffer_storage(GLuint id, Buffer::Usage usage, std::span<const T> data) //TODO: storage types (STATIC, DYNAMIC ETC.)
    {
        const auto& flags = buffer_usage(usage);

        //glNamedBufferStorage(id, static_cast<GLsizeiptr>(data.size_bytes()), data.data(), flags);
    }
    void   buffer_storage(GLuint id, Buffer::Usage usage, size_t size) //TODO: storage types (STATIC, DYNAMIC ETC.)
    {
        //const auto& flags = buffer_usage(usage);

        //glNamedBufferStorage(id, static_cast<GLsizeiptr>(size), nullptr, flags);
    }
    template<typename T>
    void   buffer_sub_data(GLuint id, size_t offset, std::span<const T> data)
    {
        //glNamedBufferSubData(id, static_cast<GLintptr>(offset), static_cast<GLsizeiptr>(data.size_bytes()), data.data());
    }

    GLuint create_vertex_array()
    {
        GLuint id{};
        //glCreateVertexArrays(1, &id);

        return id;
    }
    void   delete_vertex_array(GLuint id)
    {
        //glDeleteVertexArrays(1, &id);
    }
    void   bind_vertex_array(GLuint id)
    {
        //glBindVertexArray(id);
    }
    void   vertex_array_vertex_buffer(GLuint arrayId, GLuint bufferId, GLuint index, GLsizei stride)
    {
        //glVertexArrayVertexBuffer(arrayId, index, bufferId, 0, stride);
    }
    void   enable_vertex_array_attribute(GLuint id, GLuint index)
    {
        //glEnableVertexArrayAttrib(id, index);
    }
    void   vertex_array_attribute_format(GLuint id, GLuint index, GLuint offset, GLenum type, GLint size, GLboolean normalized)
    {
        //glVertexArrayAttribFormat(id, index, size, type, normalized, offset);
    }
    void   vertex_array_attribute_binding(GLuint id, GLuint index, GLuint binding)
    {
        //glVertexArrayAttribBinding(id, index, binding);
    }



    GLuint create_frame_buffer()
    {
        GLuint id{};
        glCreateFramebuffers(1, &id);

        return id;
    }
    void   delete_frame_buffer(GLuint id)
    {
        glDeleteFramebuffers(1, &id);
    }
    void   bind_frame_buffer(GLuint id, GLenum target)
    {
        glBindFramebuffer(target, id);
    }
    void   frame_buffer_read_buffer(GLuint id, GLenum buffer)
    {
        glNamedFramebufferReadBuffer(id, buffer);
    }
    void   frame_buffer_draw_buffer(GLuint id, GLenum buffer)
    {
        glNamedFramebufferDrawBuffer(id, buffer);
    }
    void   frame_buffer_draw_buffers(GLuint id, std::span<const GLenum> buffers)
    {
        glNamedFramebufferDrawBuffers(id, static_cast<GLsizei>(buffers.size()), buffers.data());
    }
    void   frame_buffer_texture(GLuint frameBufferId, GLuint textureId, GLenum attachment, GLint level)
    {
        glNamedFramebufferTexture(frameBufferId, attachment, textureId, level);
    }
    void   frame_buffer_render_buffer(GLuint frameBufferId, GLuint renderBufferId, GLenum attachment)
    {
        glNamedFramebufferRenderbuffer(frameBufferId, attachment, GL_RENDERBUFFER, renderBufferId);
    }
    GLenum check_frame_buffer_status(GLuint id)
    {
        return glCheckNamedFramebufferStatus(id, GL_FRAMEBUFFER);
    }



    GLuint create_texture(GLenum target)
    {
        GLuint id{};
        //glCreateTextures(target, 1, &id);

        return id;
    }
    void   delete_texture(GLuint id)
    {
        //glDeleteTextures(1, &id);
    }
    void   bind_texture(GLuint id, u32 slot)
    {
        //glBindTextureUnit(static_cast<GLuint>(slot), id);
    }
    void   texture_parameter(GLuint id, GLenum parameter, GLuint value)
    {
        //glTextureParameteri(id, parameter, value);
    }
    void   texture_storage_1d(GLuint id, GLenum format, const Vector1u& dimensions, GLsizei levels)
    {
        //glTextureStorage1D(id, levels, format, static_cast<GLsizei>(dimensions.x));
    }
    void   texture_storage_2d(GLuint id, GLenum format, const Vector2u& dimensions, GLsizei levels)
    {
        //glTextureStorage2D(id, levels, format, static_cast<GLsizei>(dimensions.x), static_cast<GLsizei>(dimensions.y));
    }
    void   texture_storage_3d(GLuint id, GLenum format, const Vector3u& dimensions, GLsizei levels)
    {
        //glTextureStorage3D(id, levels, format, static_cast<GLsizei>(dimensions.x), static_cast<GLsizei>(dimensions.y), static_cast<GLsizei>(dimensions.z));
    }
    void   texture_storage_2d_multisample(GLuint id, GLenum format, const Vector2u& dimensions, GLsizei samples)
    {
        //glTextureStorage2DMultisample(id, samples, format, static_cast<GLsizei>(dimensions.x), static_cast<GLsizei>(dimensions.y), GL_TRUE);
    }
    void   texture_storage_3d_multisample(GLuint id, GLenum format, const Vector3u& dimensions, GLsizei samples)
    {
        //glTextureStorage3DMultisample(id, samples, format, static_cast<GLsizei>(dimensions.x), static_cast<GLsizei>(dimensions.y), static_cast<GLsizei>(dimensions.z), GL_TRUE);
    }
    void   texture_sub_image_2d(GLuint id, GLenum format, const Vector2u& dimensions, const Vector2u& offset, GLuint level, const void* data)
    {
        //glTextureSubImage2D(id, level, static_cast<GLint>(offset.x), static_cast<GLint>(offset.y), static_cast<GLsizei>(dimensions.x), static_cast<GLsizei>(dimensions.y), format, GL_UNSIGNED_BYTE, data);
    }



    GLuint create_program()
    {
        return glCreateProgram();
    }
    void   delete_program(GLuint id)
    {
        glDeleteProgram(id);
    }
    GLuint create_shader(GLenum type)
    {
        return glCreateShader(type);
    }
    void   delete_shader(GLuint id)
    {
        glDeleteShader(id);
    }
    void   program_parameter(GLuint id, GLenum parameter, GLint value)
    {
        glProgramParameteri(id, parameter, value);
    }
    void   shader_binary(GLuint id, std::span<const byte> binary)
    {
        glShaderBinary(1, &id, GL_SHADER_BINARY_FORMAT_SPIR_V, binary.data(), static_cast<GLsizei>(binary.size_bytes()));
    }
    void   specialize_shader(GLuint id, std::string_view entry)
    {
        glSpecializeShader(id, entry.data(), 0, nullptr, nullptr);
    }
    void   attach_shader(GLuint programId, GLuint shaderId)
    {
        glAttachShader(programId, shaderId);
    }
    void   link_program(GLuint id)
    {
        glLinkProgram(id);
    }
    void   detach_shader(GLuint programId, GLuint shaderId)
    {
        glDetachShader(programId, shaderId);
    }

    GLuint create_program_pipeline()
    {
        GLuint id{};
        glCreateProgramPipelines(1, &id);

        return id;
    }
    void   delete_program_pipeline(GLuint id)
    {
        glDeleteProgramPipelines(1, &id);
    }
    void   bind_program_pipeline(GLuint id)
    {
        glBindProgramPipeline(id);
    }
    void   use_program_stages(GLuint pipelineId, GLuint programId, GLbitfield stages)
    {
        glUseProgramStages(pipelineId, stages, programId);
    }
}
