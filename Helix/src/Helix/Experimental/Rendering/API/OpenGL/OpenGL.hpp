#pragma once

#include "stdafx.hpp"

#include "glad/glad.h"
#include "glfw/glfw3.h"

#include "Helix/Experimental/Rendering/Buffer/Buffer.hpp"
#include "Helix/Experimental/Rendering/Buffer/FrameBuffer.hpp"
#include "Helix/Experimental/Rendering/Shader/Pipeline.hpp"
#include "Helix/Experimental/Rendering/Shader/Shader.hpp"
#include "Helix/Experimental/Rendering/Texture/Texture.hpp"

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
    constexpr GLenum      texture_format_base(Texture::Format format)
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

    constexpr GLenum      render_buffer_format(Texture::Format format)
    {
        switch (format)
        {
            case Texture::Format::R8_UNORM:          return GL_R8;
            case Texture::Format::RG8_UNORM:         return GL_RG8;
            case Texture::Format::RGB8_UNORM:        return GL_RGB8;
            case Texture::Format::RGBA8_UNORM:       return GL_RGBA8;
            case Texture::Format::D16_UNORM:         return GL_DEPTH_COMPONENT16;
            case Texture::Format::D24_UNORM:         return GL_DEPTH_COMPONENT24;
            case Texture::Format::D32_FLOAT:         return GL_DEPTH_COMPONENT32;
            case Texture::Format::D24_UNORM_S8_UINT: return GL_DEPTH24_STENCIL8;
            case Texture::Format::D32_FLOAT_S8_UINT: return GL_DEPTH32F_STENCIL8;
            case Texture::Format::S8_UINT:           return GL_STENCIL_INDEX8;

            default: throw std::invalid_argument{ "Invalid format!" };
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
        glGetIntegerv(parameter, &result);

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
        const auto& length = shader_iv(shader, GL_INFO_LOG_LENGTH);

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
        GLuint buffer{};
        glCreateBuffers(1, &buffer);

        return buffer;
    }
    void   delete_buffer(GLuint buffer)
    {
        glDeleteBuffers(1, &buffer);
    }
    void   bind_buffer(GLuint buffer, GLenum target)
    {
        glBindBuffer(target, buffer);
    }
    template<typename T>
    void   buffer_storage(GLuint buffer, GLbitfield flags, std::span<const T> data) //TODO: storage types (STATIC, DYNAMIC ETC.)
    {
        glNamedBufferStorage(buffer, static_cast<GLsizeiptr>(data.size_bytes()), data.data(), flags);
    }
    void   buffer_storage(GLuint buffer, GLbitfield flags, size_t size) //TODO: storage types (STATIC, DYNAMIC ETC.)
    {
        glNamedBufferStorage(buffer, static_cast<GLsizeiptr>(size), nullptr, flags);
    }
    template<typename T>
    void   buffer_sub_data(GLuint buffer, size_t offset, std::span<const T> data)
    {
        glNamedBufferSubData(buffer, static_cast<GLintptr>(offset), static_cast<GLsizeiptr>(data.size_bytes()), data.data());
    }



    GLuint create_vertex_array()
    {
        GLuint array{};
        glCreateVertexArrays(1, &array);

        return array;
    }
    void   delete_vertex_array(GLuint array)
    {
        glDeleteVertexArrays(1, &array);
    }
    void   bind_vertex_array(GLuint array)
    {
        glBindVertexArray(array);
    }
    void   vertex_array_vertex_buffer(GLuint array, GLuint buffer, GLuint index, GLsizei stride)
    {
        glVertexArrayVertexBuffer(array, index, buffer, 0, stride);
    }
    void   enable_vertex_array_attribute(GLuint array, GLuint index)
    {
        glEnableVertexArrayAttrib(array, index);
    }
    void   vertex_array_attribute_format(GLuint array, GLuint index, GLuint offset, GLenum type, GLint size, GLboolean normalized)
    {
        glVertexArrayAttribFormat(array, index, size, type, normalized, offset);
    }
    void   vertex_array_attribute_binding(GLuint array, GLuint index, GLuint binding)
    {
        glVertexArrayAttribBinding(array, index, binding);
    }



    GLuint create_frame_buffer()
    {
        GLuint frameBuffer{};
        glCreateFramebuffers(1, &frameBuffer);
        
        return frameBuffer;
    }
    void   delete_frame_buffer(GLuint frameBuffer)
    {
        glDeleteFramebuffers(1, &frameBuffer);
    }
    void   bind_frame_buffer(GLuint frameBuffer, GLenum target)
    {
        glBindFramebuffer(target, frameBuffer);
    }
    void   frame_buffer_read_buffer(GLuint frameBuffer, GLenum source)
    {
        glNamedFramebufferReadBuffer(frameBuffer, source);
    }
    void   frame_buffer_draw_buffer(GLuint frameBuffer, GLenum buffer)
    {
        glNamedFramebufferDrawBuffer(frameBuffer, buffer);
    }
    void   frame_buffer_draw_buffers(GLuint frameBuffer, std::span<const GLenum> buffers)
    {
        glNamedFramebufferDrawBuffers(frameBuffer, static_cast<GLsizei>(buffers.size()), buffers.data());
    }
    void   frame_buffer_texture(GLuint frameBuffer, GLuint texture, GLenum attachment, GLint level)
    {
        glNamedFramebufferTexture(frameBuffer, attachment, texture, level);
    }
    void   frame_buffer_render_buffer(GLuint frameBuffer, GLuint renderBuffer, GLenum attachment)
    {
        glNamedFramebufferRenderbuffer(frameBuffer, attachment, GL_RENDERBUFFER, renderBuffer);
    }
    GLenum check_frame_buffer_status(GLuint frameBuffer)
    {
        return glCheckNamedFramebufferStatus(frameBuffer, GL_FRAMEBUFFER);
    }



    GLuint create_texture(GLenum target)
    {
        GLuint texture{};
        glCreateTextures(target, 1, &texture);

        return texture;
    }
    void   delete_texture(GLuint texture)
    {
        glDeleteTextures(1, &texture);
    }
    void   bind_texture(GLuint texture, u32 slot)
    {
        glBindTextureUnit(static_cast<GLuint>(slot), texture);
    }
    void   texture_parameter(GLuint texture, GLenum parameter, GLuint value)
    {
        glTextureParameteri(texture, parameter, value);
    }
    void   texture_storage_1d(GLuint texture, GLenum format, const Vector1u& dimensions, GLsizei levels)
    {
        glTextureStorage1D(texture, levels, format, static_cast<GLsizei>(dimensions.x));
    }
    void   texture_storage_2d(GLuint texture, GLenum format, const Vector2u& dimensions, GLsizei levels)
    {
        glTextureStorage2D(texture, levels, format, static_cast<GLsizei>(dimensions.x), static_cast<GLsizei>(dimensions.y));
    }
    void   texture_storage_3d(GLuint texture, GLenum format, const Vector3u& dimensions, GLsizei levels)
    {
        glTextureStorage3D(texture, levels, format, static_cast<GLsizei>(dimensions.x), static_cast<GLsizei>(dimensions.y), static_cast<GLsizei>(dimensions.z));
    }
    void   texture_storage_2d_multisample(GLuint texture, GLenum format, const Vector2u& dimensions, GLsizei samples)
    {
        glTextureStorage2DMultisample(texture, samples, format, static_cast<GLsizei>(dimensions.x), static_cast<GLsizei>(dimensions.y), GL_TRUE);
    }
    void   texture_storage_3d_multisample(GLuint texture, GLenum format, const Vector3u& dimensions, GLsizei samples)
    {
        glTextureStorage3DMultisample(texture, samples, format, static_cast<GLsizei>(dimensions.x), static_cast<GLsizei>(dimensions.y), static_cast<GLsizei>(dimensions.z), GL_TRUE);
    }
    void   texture_sub_image_1d(GLuint texture, GLenum format, const Vector1u& dimensions, const Vector1u& offset, GLint level, const void* data)
    {
        glTextureSubImage1D(texture, level, static_cast<GLint>(offset.x), static_cast<GLsizei>(dimensions.x), format, GL_UNSIGNED_BYTE, data);
    }
    void   texture_sub_image_2d(GLuint texture, GLenum format, const Vector2u& dimensions, const Vector2u& offset, GLuint level, const void* data)
    {
        glTextureSubImage2D(texture, level, static_cast<GLint>(offset.x), static_cast<GLint>(offset.y), static_cast<GLsizei>(dimensions.x), static_cast<GLsizei>(dimensions.y), format, GL_UNSIGNED_BYTE, data);
    }
    void   texture_sub_image_3d(GLuint texture, GLenum format, const Vector3u& dimensions, const Vector3u& offset, GLint level, const void* data) //80 column rule my ass
    {
        glTextureSubImage3D(texture, level, static_cast<GLint>(offset.x), static_cast<GLint>(offset.y), static_cast<GLint>(offset.z), static_cast<GLsizei>(dimensions.x), static_cast<GLsizei>(dimensions.y), static_cast<GLsizei>(dimensions.z), format, GL_UNSIGNED_BYTE, data);
    }



    GLuint create_render_buffer()
    {
        GLuint id{};
        glCreateRenderbuffers(1, &id);

        return id;
    }
    void   delete_render_buffer(GLuint renderBuffer)
    {
        glDeleteRenderbuffers(1, &renderBuffer);
    }
    void   bind_render_buffer(GLuint renderBuffer)
    {
        glBindRenderbuffer(GL_RENDERBUFFER, renderBuffer);
    }
    void   render_buffer_storage(GLuint renderBuffer, GLenum format, const Vector2u& dimensions)
    {
        glNamedRenderbufferStorage(renderBuffer, format, static_cast<GLsizei>(dimensions.x), static_cast<GLsizei>(dimensions.y));
    }
    void   render_buffer_storage_multisample(GLuint renderBuffer, GLenum format, const Vector2u& dimensions, u8 samples)
    {
        glNamedRenderbufferStorageMultisample(renderBuffer, samples, format, static_cast<GLsizei>(dimensions.x), static_cast<GLsizei>(dimensions.y));
    }



    GLuint create_program()
    {
        return glCreateProgram();
    }
    void   delete_program(GLuint program)
    {
        glDeleteProgram(program);
    }
    void   link_program(GLuint program)
    {
        glLinkProgram(program);
    }
    void   program_parameter(GLuint program, GLenum parameter, GLint value)
    {
        glProgramParameteri(program, parameter, value);
    }
    GLuint create_shader(GLenum type)
    {
        return glCreateShader(type);
    }
    void   delete_shader(GLuint shader)
    {
        glDeleteShader(shader);
    }
    void   attach_shader(GLuint program, GLuint shader)
    {
        glAttachShader(program, shader);
    }
    void   detach_shader(GLuint program, GLuint shader)
    {
        glDetachShader(program, shader);
    }
    void   shader_binary(GLuint shader, std::span<const byte> binary)
    {
        glShaderBinary(1, &shader, GL_SHADER_BINARY_FORMAT_SPIR_V, binary.data(), static_cast<GLsizei>(binary.size_bytes()));
    }
    void   specialize_shader(GLuint shader, std::string_view entry)
    {
        glSpecializeShader(shader, entry.data(), 0, nullptr, nullptr);
    }



    GLuint create_program_pipeline()
    {
        GLuint pipeline{};
        glCreateProgramPipelines(1, &pipeline);

        return pipeline;
    }
    void   delete_program_pipeline(GLuint pipeline)
    {
        glDeleteProgramPipelines(1, &pipeline);
    }
    void   bind_program_pipeline(GLuint pipeline)
    {
        glBindProgramPipeline(pipeline);
    }
    void   use_program_stages(GLuint pipeline, GLuint program, GLbitfield stages)
    {
        glUseProgramStages(pipeline, stages, program);
    }
}
