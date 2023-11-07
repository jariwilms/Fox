#pragma once

#include "stdafx.hpp"

#include "glad/glad.h"
#include "glfw/glfw3.h"

#include "GLMappings.hpp"

namespace hlx::gfx::imp::api::gl
{
    enum BufferMask : GLbitfield
    {
        ColorBuffer   = GL_COLOR_BUFFER_BIT,
        DepthBuffer   = GL_DEPTH_BUFFER_BIT,
        StencilBuffer = GL_STENCIL_BUFFER_BIT,
    };



    template<typename T>
    constexpr GLenum  type_enum() requires (std::is_fundamental_v<T>)
    {
        if constexpr (std::is_same_v<T, char>)           return GL_BYTE;
        if constexpr (std::is_same_v<T, unsigned char>)  return GL_UNSIGNED_BYTE;
        if constexpr (std::is_same_v<T, short>)          return GL_SHORT;
        if constexpr (std::is_same_v<T, unsigned short>) return GL_UNSIGNED_SHORT;
        if constexpr (std::is_same_v<T, int>)            return GL_INT;
        if constexpr (std::is_same_v<T, unsigned int>)   return GL_UNSIGNED_INT;
        if constexpr (std::is_same_v<T, float>)          return GL_FLOAT;
        if constexpr (std::is_same_v<T, double>)         return GL_DOUBLE;
    }
    template<typename T>
    constexpr GLsizei type_size() requires (std::is_fundamental_v<T>)
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
    }



    GLint integer_v(GLenum parameter)
    {
        GLint result{};
        glGetIntegerv(parameter, &result);

        return result;
    }



    void draw_elements(GLenum mode)
    {

    }
    void clear(GLbitfield mask)
    {
        glClear(mask);
    }



    GLuint      create_buffer()
    {
        GLuint buffer{};
        glCreateBuffers(1, &buffer);

        return buffer;
    }
    void        delete_buffer(GLuint buffer)
    {
        glDeleteBuffers(1, &buffer);
    }
    void        bind_buffer(GLuint buffer, GLenum target)
    {
        glBindBuffer(target, buffer);
    }
    void        bind_buffer_base(GLuint buffer, GLenum target, GLuint index)
    {
        glBindBufferBase(target, index, buffer);
    }
    void        bind_buffer_range(GLuint buffer, GLenum target, GLuint index, GLsizeiptr size, GLintptr offset)
    {
        glBindBufferRange(target, index, buffer, offset, size);
    }
    void        buffer_storage(GLuint buffer, GLbitfield flags, size_t size) //TODO: storage types (STATIC, DYNAMIC ETC.)
    {
        glNamedBufferStorage(buffer, static_cast<GLsizeiptr>(size), nullptr, flags);
    }
    template<typename T>
    void        buffer_storage(GLuint buffer, GLbitfield flags, std::span<const T> data) //TODO: storage types (STATIC, DYNAMIC ETC.)
    {
        glNamedBufferStorage(buffer, static_cast<GLsizeiptr>(data.size_bytes()), data.data(), flags);
    }
    template<typename T>
    void        buffer_sub_data(GLuint buffer, size_t offset, std::span<const T> data)
    {
        glNamedBufferSubData(buffer, static_cast<GLintptr>(offset), static_cast<GLsizeiptr>(data.size_bytes()), data.data());
    }
    template<typename T>
    void*       map_buffer(GLuint buffer, GLenum access)
    {
        return glMapNamedBuffer(buffer, access);
    }
    void*       map_buffer_range(GLuint buffer, GLenum access, GLsizeiptr size, GLintptr offset)
    {
        return glMapNamedBufferRange(buffer, offset, size, access);
    }
    GLboolean   unmap_buffer(GLuint buffer)
    {
        return glUnmapNamedBuffer(buffer);
    }

    GLuint      create_vertex_array()
    {
        GLuint array{};
        glCreateVertexArrays(1, &array);

        return array;
    }
    void        delete_vertex_array(GLuint array)
    {
        glDeleteVertexArrays(1, &array);
    }
    void        bind_vertex_array(GLuint array)
    {
        glBindVertexArray(array);
    }
    void        vertex_array_vertex_buffer(GLuint array, GLuint buffer, GLuint index, GLsizei stride)
    {
        glVertexArrayVertexBuffer(array, index, buffer, 0, stride);
    }
    void        enable_vertex_array_attribute(GLuint array, GLuint index)
    {
        glEnableVertexArrayAttrib(array, index);
    }
    void        vertex_array_attribute_format(GLuint array, GLuint index, GLuint offset, GLenum type, GLint size, GLboolean normalized)
    {
        glVertexArrayAttribFormat(array, index, size, type, normalized, offset);
    }
    void        vertex_array_attribute_binding(GLuint array, GLuint index, GLuint binding)
    {
        glVertexArrayAttribBinding(array, index, binding);
    }

    GLuint      create_frame_buffer()
    {
        GLuint frameBuffer{};
        glCreateFramebuffers(1, &frameBuffer);
        
        return frameBuffer;
    }
    void        delete_frame_buffer(GLuint frameBuffer)
    {
        glDeleteFramebuffers(1, &frameBuffer);
    }
    void        bind_frame_buffer(GLuint frameBuffer, GLenum target)
    {
        glBindFramebuffer(target, frameBuffer);
    }
    void        frame_buffer_read_buffer(GLuint frameBuffer, GLenum source)
    {
        glNamedFramebufferReadBuffer(frameBuffer, source);
    }
    void        frame_buffer_draw_buffer(GLuint frameBuffer, GLenum buffer)
    {
        glNamedFramebufferDrawBuffer(frameBuffer, buffer);
    }
    void        frame_buffer_draw_buffers(GLuint frameBuffer, std::span<const GLenum> buffers)
    {
        glNamedFramebufferDrawBuffers(frameBuffer, static_cast<GLsizei>(buffers.size()), buffers.data());
    }
    void        frame_buffer_texture(GLuint frameBuffer, GLuint texture, GLenum attachment, GLint level)
    {
        glNamedFramebufferTexture(frameBuffer, attachment, texture, level);
    }
    void        frame_buffer_render_buffer(GLuint frameBuffer, GLuint renderBuffer, GLenum attachment)
    {
        glNamedFramebufferRenderbuffer(frameBuffer, attachment, GL_RENDERBUFFER, renderBuffer);
    }
    GLenum      check_frame_buffer_status(GLuint frameBuffer)
    {
        return glCheckNamedFramebufferStatus(frameBuffer, GL_FRAMEBUFFER);
    }

    GLuint      create_texture(GLenum target)
    {
        GLuint texture{};
        glCreateTextures(target, 1, &texture);

        return texture;
    }
    void        delete_texture(GLuint texture)
    {
        glDeleteTextures(1, &texture);
    }
    void        bind_texture(GLuint texture, u32 slot)
    {
        glBindTextureUnit(static_cast<GLuint>(slot), texture);
    }
    void        texture_parameter(GLuint texture, GLenum parameter, GLuint value)
    {
        glTextureParameteri(texture, parameter, value);
    }
    void        texture_storage_1d(GLuint texture, GLenum format, const Vector1u& dimensions, GLsizei levels)
    {
        glTextureStorage1D(texture, levels, format, static_cast<GLsizei>(dimensions.x));
    }
    void        texture_storage_2d(GLuint texture, GLenum format, const Vector2u& dimensions, GLsizei levels)
    {
        glTextureStorage2D(texture, levels, format, static_cast<GLsizei>(dimensions.x), static_cast<GLsizei>(dimensions.y));
    }
    void        texture_storage_3d(GLuint texture, GLenum format, const Vector3u& dimensions, GLsizei levels)
    {
        glTextureStorage3D(texture, levels, format, static_cast<GLsizei>(dimensions.x), static_cast<GLsizei>(dimensions.y), static_cast<GLsizei>(dimensions.z));
    }
    void        texture_storage_2d_multisample(GLuint texture, GLenum format, const Vector2u& dimensions, GLsizei samples)
    {
        glTextureStorage2DMultisample(texture, samples, format, static_cast<GLsizei>(dimensions.x), static_cast<GLsizei>(dimensions.y), GL_TRUE);
    }
    void        texture_storage_3d_multisample(GLuint texture, GLenum format, const Vector3u& dimensions, GLsizei samples)
    {
        glTextureStorage3DMultisample(texture, samples, format, static_cast<GLsizei>(dimensions.x), static_cast<GLsizei>(dimensions.y), static_cast<GLsizei>(dimensions.z), GL_TRUE);
    }
    void        texture_sub_image_1d(GLuint texture, GLenum format, const Vector1u& dimensions, const Vector1u& offset, GLint level, const void* data)
    {
        glTextureSubImage1D(texture, level, static_cast<GLint>(offset.x), static_cast<GLsizei>(dimensions.x), format, GL_UNSIGNED_BYTE, data);
    }
    void        texture_sub_image_2d(GLuint texture, GLenum format, const Vector2u& dimensions, const Vector2u& offset, GLuint level, const void* data)
    {
        glTextureSubImage2D(texture, level, static_cast<GLint>(offset.x), static_cast<GLint>(offset.y), static_cast<GLsizei>(dimensions.x), static_cast<GLsizei>(dimensions.y), format, GL_UNSIGNED_BYTE, data);
    }
    void        texture_sub_image_3d(GLuint texture, GLenum format, const Vector3u& dimensions, const Vector3u& offset, GLint level, const void* data) //80 column rule my ass
    {
        glTextureSubImage3D(texture, level, static_cast<GLint>(offset.x), static_cast<GLint>(offset.y), static_cast<GLint>(offset.z), static_cast<GLsizei>(dimensions.x), static_cast<GLsizei>(dimensions.y), static_cast<GLsizei>(dimensions.z), format, GL_UNSIGNED_BYTE, data);
    }

    GLuint      create_render_buffer()
    {
        GLuint id{};
        glCreateRenderbuffers(1, &id);

        return id;
    }
    void        delete_render_buffer(GLuint renderBuffer)
    {
        glDeleteRenderbuffers(1, &renderBuffer);
    }
    void        bind_render_buffer(GLuint renderBuffer)
    {
        glBindRenderbuffer(GL_RENDERBUFFER, renderBuffer);
    }
    void        render_buffer_storage(GLuint renderBuffer, GLenum format, const Vector2u& dimensions)
    {
        glNamedRenderbufferStorage(renderBuffer, format, static_cast<GLsizei>(dimensions.x), static_cast<GLsizei>(dimensions.y));
    }
    void        render_buffer_storage_multisample(GLuint renderBuffer, GLenum format, const Vector2u& dimensions, u8 samples)
    {
        glNamedRenderbufferStorageMultisample(renderBuffer, samples, format, static_cast<GLsizei>(dimensions.x), static_cast<GLsizei>(dimensions.y));
    }

    GLuint      create_program()
    {
        return glCreateProgram();
    }
    void        delete_program(GLuint program)
    {
        glDeleteProgram(program);
    }
    void        link_program(GLuint program)
    {
        glLinkProgram(program);
    }
    void        program_parameter(GLuint program, GLenum parameter, GLint value)
    {
        glProgramParameteri(program, parameter, value);
    }
    GLint       program_iv(GLuint program, GLenum parameter)
    {
        GLint result{};
        glGetProgramiv(program, parameter, &result);

        return result;
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

    GLuint      create_shader(GLenum type)
    {
        return glCreateShader(type);
    }
    void        delete_shader(GLuint shader)
    {
        glDeleteShader(shader);
    }
    void        attach_shader(GLuint program, GLuint shader)
    {
        glAttachShader(program, shader);
    }
    void        detach_shader(GLuint program, GLuint shader)
    {
        glDetachShader(program, shader);
    }
    void        shader_binary(GLuint shader, std::span<const byte> binary)
    {
        glShaderBinary(1, &shader, GL_SHADER_BINARY_FORMAT_SPIR_V, binary.data(), static_cast<GLsizei>(binary.size_bytes()));
    }
    void        specialize_shader(GLuint shader, std::string_view entry)
    {
        glSpecializeShader(shader, entry.data(), 0, nullptr, nullptr);
    }
    GLint       shader_iv(GLuint shader, GLenum parameter)
    {
        GLint result{};
        glGetShaderiv(shader, parameter, &result);

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

    GLuint      create_program_pipeline()
    {
        GLuint pipeline{};
        glCreateProgramPipelines(1, &pipeline);

        return pipeline;
    }
    void        delete_program_pipeline(GLuint pipeline)
    {
        glDeleteProgramPipelines(1, &pipeline);
    }
    void        bind_program_pipeline(GLuint pipeline)
    {
        glBindProgramPipeline(pipeline);
    }
    void        use_program_stages(GLuint pipeline, GLuint program, GLbitfield stages)
    {
        glUseProgramStages(pipeline, stages, program);
    }
}