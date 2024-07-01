#pragma once

#include "stdafx.hpp"

#include "GLMappings.hpp"

namespace fox::gfx::imp::api::gl
{
    struct Buffer
    {
        enum Mask : GLbitfield
        {
            ColorBuffer   = GL_COLOR_BUFFER_BIT,
            DepthBuffer   = GL_DEPTH_BUFFER_BIT,
            StencilBuffer = GL_STENCIL_BUFFER_BIT, 

            All           = ColorBuffer | DepthBuffer | StencilBuffer
        };
        enum class Access : GLenum
        {
            Read      = GL_READ_ONLY, 
            Write     = GL_WRITE_ONLY, 
            ReadWrite = GL_READ_WRITE, 
        };
        enum class Target : GLenum
        {
            ArrayBuffer              = GL_ARRAY_BUFFER, 
            AtomicCounterBuffer      = GL_ATOMIC_COUNTER_BUFFER, 
            CopyReadBuffer           = GL_COPY_READ_BUFFER, 
            CopyWriteBuffer          = GL_COPY_WRITE_BUFFER, 
            DispatchIndirectBuffer   = GL_DISPATCH_INDIRECT_BUFFER, 
            DrawIndirectBuffer       = GL_DRAW_INDIRECT_BUFFER, 
            ElementArrayBuffer       = GL_ELEMENT_ARRAY_BUFFER, 
            PixelPackBuffer          = GL_PIXEL_PACK_BUFFER, 
            PixelUnpackBuffer        = GL_PIXEL_UNPACK_BUFFER, 
            QueryBuffer              = GL_QUERY_BUFFER, 
            ShaderStorageBuffer      = GL_SHADER_STORAGE_BUFFER, 
            TextureBuffer            = GL_TEXTURE_BUFFER, 
            TransformFeedbackBuffer  = GL_TRANSFORM_FEEDBACK_BUFFER, 
            UniformBuffer            = GL_UNIFORM_BUFFER, 
        };
        enum class TargetBase : GLenum
        {
            AtomicCounterBuffer     = GL_ATOMIC_COUNTER_BUFFER, 
            TransformFeedbackBuffer = GL_TRANSFORM_FEEDBACK_BUFFER, 
            UniformBuffer           = GL_UNIFORM_BUFFER, 
            ShaderStorageBuffer     = GL_SHADER_STORAGE_BUFFER, 
        };
        enum class TargetRange : GLenum
        {
            TransformFeedbackBuffer = GL_TRANSFORM_FEEDBACK_BUFFER,
            UniformBuffer           = GL_UNIFORM_BUFFER,
        };
        enum StorageFlags : GLbitfield
        {
            DynamicStorage = GL_DYNAMIC_STORAGE_BIT, 
            MapRead        = GL_MAP_READ_BIT, 
            MapWrite       = GL_MAP_WRITE_BIT, 
            MapPersistent  = GL_MAP_PERSISTENT_BIT, 
            MapCoherent    = GL_MAP_COHERENT_BIT, 
            ClientStorage  = GL_CLIENT_STORAGE_BIT, 
        };
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



    static GLint integer_v(GLenum parameter)
    {
        GLint result{};
        glGetIntegerv(parameter, &result);

        return result;
    }



    static void clear(Buffer::Mask mask)
    {
        glClear(mask);
    }



    static GLuint      create_buffer()
    {
        GLuint buffer{};
        glCreateBuffers(1, &buffer);

        return buffer;
    }
    static void        delete_buffer(GLuint buffer)
    {
        glDeleteBuffers(1, &buffer);
    }
    static void        bind_buffer(GLuint buffer, Buffer::Target target)
    {
        glBindBuffer(static_cast<GLenum>(target), buffer);
    }
    static void        bind_buffer_base(GLuint buffer, Buffer::TargetBase target, GLuint index)
    {
        glBindBufferBase(static_cast<GLenum>(target), index, buffer);
    }
    static void        bind_buffer_range(GLuint buffer, Buffer::TargetRange target, GLuint index, GLsizeiptr size, GLintptr offset)
    {
        glBindBufferRange(static_cast<GLenum>(target), index, buffer, offset, size);
    }
    static void        buffer_storage(GLuint buffer, Buffer::StorageFlags flags, GLsizeiptr size)
    {
        glNamedBufferStorage(buffer, size, nullptr, static_cast<GLbitfield>(flags));
    }
    template<typename T>
    static void        buffer_storage(GLuint buffer, Buffer::StorageFlags flags, std::span<const T> data)
    {
        glNamedBufferStorage(buffer, static_cast<GLsizeiptr>(data.size_bytes()), data.data(), flags);
    }
    template<typename T>
    static void        buffer_sub_data(GLuint buffer, GLintptr offset, std::span<const T> data)
    {
        const auto& _ = data.size_bytes();
        glNamedBufferSubData(buffer, offset, static_cast<GLsizeiptr>(data.size_bytes()), data.data());
    }







    static void*       map_buffer(GLuint buffer, size_t size)
    {
        return glMapNamedBuffer(buffer, GL_READ_WRITE);
    }
    static void*       map_buffer_range(GLuint buffer, GLenum access, GLsizeiptr size, GLintptr offset)
    {
        return glMapNamedBufferRange(buffer, offset, size, access);
    }
    static GLboolean   unmap_buffer(GLuint buffer)
    {
        return glUnmapNamedBuffer(buffer);
    }










    static GLuint      create_vertex_array()
    {
        GLuint array{};
        glCreateVertexArrays(1, &array);

        return array;
    }
    static void        delete_vertex_array(GLuint array)
    {
        glDeleteVertexArrays(1, &array);
    }
    static void        bind_vertex_array(GLuint array)
    {
        glBindVertexArray(array);
    }
    static void        vertex_array_vertex_buffer(GLuint array, GLuint buffer, GLuint index, GLsizei stride)
    {
        glVertexArrayVertexBuffer(array, index, buffer, 0, stride);
    }
    static void        enable_vertex_array_attribute(GLuint array, GLuint index)
    {
        glEnableVertexArrayAttrib(array, index);
    }
    static void        vertex_array_attribute_format(GLuint array, GLuint index, GLuint offset, GLenum type, GLint size, GLboolean normalized)
    {
        glVertexArrayAttribFormat(array, index, size, type, normalized, offset);
    }
    static void        vertex_array_attribute_binding(GLuint array, GLuint index, GLuint binding)
    {
        glVertexArrayAttribBinding(array, index, binding);
    }

    static GLuint      create_frame_buffer()
    {
        GLuint frameBuffer{};
        glCreateFramebuffers(1, &frameBuffer);
        
        return frameBuffer;
    }
    static void        delete_frame_buffer(GLuint frameBuffer)
    {
        glDeleteFramebuffers(1, &frameBuffer);
    }
    static void        bind_frame_buffer(GLuint frameBuffer, GLenum target)
    {
        glBindFramebuffer(target, frameBuffer);
    }
    static void        frame_buffer_read_buffer(GLuint frameBuffer, GLenum source)
    {
        glNamedFramebufferReadBuffer(frameBuffer, source);
    }
    static void        frame_buffer_draw_buffer(GLuint frameBuffer, GLenum buffer)
    {
        glNamedFramebufferDrawBuffer(frameBuffer, buffer);
    }
    static void        frame_buffer_draw_buffers(GLuint frameBuffer, std::span<const GLenum> buffers)
    {
        glNamedFramebufferDrawBuffers(frameBuffer, static_cast<GLsizei>(buffers.size()), buffers.data());
    }
    static void        frame_buffer_texture(GLuint frameBuffer, GLuint texture, GLenum attachment, GLint level)
    {
        glNamedFramebufferTexture(frameBuffer, attachment, texture, level);
    }
    static void        frame_buffer_render_buffer(GLuint frameBuffer, GLuint renderBuffer, GLenum attachment)
    {
        glNamedFramebufferRenderbuffer(frameBuffer, attachment, GL_RENDERBUFFER, renderBuffer);
    }
    static GLenum      check_frame_buffer_status(GLuint frameBuffer)
    {
        return glCheckNamedFramebufferStatus(frameBuffer, GL_FRAMEBUFFER);
    }

    static GLuint      create_texture(GLenum target)
    {
        GLuint texture{};
        glCreateTextures(target, 1, &texture);

        return texture;
    }
    static void        delete_texture(GLuint texture)
    {
        glDeleteTextures(1, &texture);
    }
    static void        bind_texture(GLuint texture, std::uint32_t slot)
    {
        glBindTextureUnit(static_cast<GLuint>(slot), texture);
    }
    static void        texture_parameter(GLuint texture, GLenum parameter, GLuint value)
    {
        glTextureParameteri(texture, parameter, value);
    }
    static void        texture_storage_1d(GLuint texture, GLenum format, const Vector1u& dimensions, GLsizei levels)
    {
        glTextureStorage1D(texture, levels, format, static_cast<GLsizei>(dimensions.x));
    }
    static void        texture_storage_2d(GLuint texture, GLenum format, const Vector2u& dimensions, GLsizei levels)
    {
        glTextureStorage2D(texture, levels, format, static_cast<GLsizei>(dimensions.x), static_cast<GLsizei>(dimensions.y));
    }
    static void        texture_storage_3d(GLuint texture, GLenum format, const Vector3u& dimensions, GLsizei levels)
    {
        glTextureStorage3D(texture, levels, format, static_cast<GLsizei>(dimensions.x), static_cast<GLsizei>(dimensions.y), static_cast<GLsizei>(dimensions.z));
    }
    static void        texture_storage_2d_multisample(GLuint texture, GLenum format, const Vector2u& dimensions, GLsizei samples)
    {
        glTextureStorage2DMultisample(texture, samples, format, static_cast<GLsizei>(dimensions.x), static_cast<GLsizei>(dimensions.y), GL_TRUE);
    }
    static void        texture_storage_3d_multisample(GLuint texture, GLenum format, const Vector3u& dimensions, GLsizei samples)
    {
        glTextureStorage3DMultisample(texture, samples, format, static_cast<GLsizei>(dimensions.x), static_cast<GLsizei>(dimensions.y), static_cast<GLsizei>(dimensions.z), GL_TRUE);
    }
    static void        texture_sub_image_1d(GLuint texture, GLenum format, const Vector1u& dimensions, const Vector1u& offset, GLint level, const void* data)
    {
        glTextureSubImage1D(texture, level, static_cast<GLint>(offset.x), static_cast<GLsizei>(dimensions.x), format, GL_UNSIGNED_BYTE, data);
    }
    static void        texture_sub_image_2d(GLuint texture, GLenum format, const Vector2u& dimensions, const Vector2u& offset, GLuint level, const void* data)
    {
        glTextureSubImage2D(texture, level, static_cast<GLint>(offset.x), static_cast<GLint>(offset.y), static_cast<GLsizei>(dimensions.x), static_cast<GLsizei>(dimensions.y), format, GL_UNSIGNED_BYTE, data);
    }
    static void        texture_sub_image_3d(GLuint texture, GLenum format, const Vector3u& dimensions, const Vector3u& offset, GLint level, const void* data) //80 column rule my ass
    {
        glTextureSubImage3D(texture, level, static_cast<GLint>(offset.x), static_cast<GLint>(offset.y), static_cast<GLint>(offset.z), static_cast<GLsizei>(dimensions.x), static_cast<GLsizei>(dimensions.y), static_cast<GLsizei>(dimensions.z), format, GL_UNSIGNED_BYTE, data);
    }

    static GLuint      create_render_buffer()
    {
        GLuint id{};
        glCreateRenderbuffers(1, &id);

        return id;
    }
    static void        delete_render_buffer(GLuint renderBuffer)
    {
        glDeleteRenderbuffers(1, &renderBuffer);
    }
    static void        bind_render_buffer(GLuint renderBuffer)
    {
        glBindRenderbuffer(GL_RENDERBUFFER, renderBuffer);
    }
    static void        render_buffer_storage(GLuint renderBuffer, GLenum format, const Vector2u& dimensions)
    {
        glNamedRenderbufferStorage(renderBuffer, format, static_cast<GLsizei>(dimensions.x), static_cast<GLsizei>(dimensions.y));
    }
    static void        render_buffer_storage_multisample(GLuint renderBuffer, GLenum format, const Vector2u& dimensions, std::uint8_t samples)
    {
        glNamedRenderbufferStorageMultisample(renderBuffer, samples, format, static_cast<GLsizei>(dimensions.x), static_cast<GLsizei>(dimensions.y));
    }

    static GLuint      create_program()
    {
        return glCreateProgram();
    }
    static void        delete_program(GLuint program)
    {
        glDeleteProgram(program);
    }
    static void        link_program(GLuint program)
    {
        glLinkProgram(program);
    }
    static void        program_parameter(GLuint program, GLenum parameter, GLint value)
    {
        glProgramParameteri(program, parameter, value);
    }
    static GLint       program_iv(GLuint program, GLenum parameter)
    {
        GLint result{};
        glGetProgramiv(program, parameter, &result);

        return result;
    }
    static std::string program_infolog(GLuint program)
    {
        std::string infolog{};
        GLsizei length = program_iv(program, GL_INFO_LOG_LENGTH);
        GLsizei bufSize{ length };

        infolog.resize(length);
        glGetProgramInfoLog(program, bufSize, nullptr, infolog.data());

        return infolog;
    }

    static GLuint      create_shader(GLenum type)
    {
        return glCreateShader(type);
    }
    static void        delete_shader(GLuint shader)
    {
        glDeleteShader(shader);
    }
    static void        attach_shader(GLuint program, GLuint shader)
    {
        glAttachShader(program, shader);
    }
    static void        detach_shader(GLuint program, GLuint shader)
    {
        glDetachShader(program, shader);
    }
    static void        shader_binary(GLuint shader, std::span<const byte> binary)
    {
        glShaderBinary(1, &shader, GL_SHADER_BINARY_FORMAT_SPIR_V, binary.data(), static_cast<GLsizei>(binary.size_bytes()));
    }
    static void        specialize_shader(GLuint shader, std::string_view entry)
    {
        glSpecializeShader(shader, entry.data(), 0, nullptr, nullptr);
    }
    static GLint       shader_iv(GLuint shader, GLenum parameter)
    {
        GLint result{};
        glGetShaderiv(shader, parameter, &result);

        return result;
    }
    static std::string shader_infolog(GLuint shader)
    {
        const auto& length = shader_iv(shader, GL_INFO_LOG_LENGTH);

        std::string infolog{};
        infolog.resize(length);

        glGetShaderInfoLog(shader, length, nullptr, infolog.data());

        return infolog;
    }

    static GLuint      create_program_pipeline()
    {
        GLuint pipeline{};
        glCreateProgramPipelines(1, &pipeline);

        return pipeline;
    }
    static void        delete_program_pipeline(GLuint pipeline)
    {
        glDeleteProgramPipelines(1, &pipeline);
    }
    static void        bind_program_pipeline(GLuint pipeline)
    {
        glBindProgramPipeline(pipeline);
    }
    static void        use_program_stages(GLuint pipeline, GLuint program, GLbitfield stages)
    {
        glUseProgramStages(pipeline, stages, program);
    }




    static void        debug_callback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* user_param)
    {
        if (severity != GL_DEBUG_SEVERITY_HIGH) return;

        const auto& sourceMessage   = [source]() -> std::string
        {
            switch (source)
            {
                case GL_DEBUG_SOURCE_API:             return "API";
                case GL_DEBUG_SOURCE_WINDOW_SYSTEM:   return "WINDOW_SYSTEM";
                case GL_DEBUG_SOURCE_SHADER_COMPILER: return "SHADER_COMPILER";
                case GL_DEBUG_SOURCE_THIRD_PARTY:     return "THIRD_PARTY";
                case GL_DEBUG_SOURCE_APPLICATION:     return "APPLICATION";
                case GL_DEBUG_SOURCE_OTHER:           return "OTHER";

                default:                              throw std::invalid_argument{ "Invalid source!" };
            }
        }();
        const auto& typeMessage     = [type]() -> std::string
            {
                switch (type)
                {
                    case GL_DEBUG_TYPE_ERROR:               return "ERROR";
                    case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: return "DEPRECATED_BEHAVIOR";
                    case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:  return "UNDEFINED_BEHAVIOR";
                    case GL_DEBUG_TYPE_PORTABILITY:         return "PORTABILITY";
                    case GL_DEBUG_TYPE_PERFORMANCE:         return "PERFORMANCE";
                    case GL_DEBUG_TYPE_MARKER:              return "MARKER";
                    case GL_DEBUG_TYPE_OTHER:               return "OTHER";

                    default:                                throw std::invalid_argument{ "Invalid type!" };
                }
            }();
        const auto& severityMessage = [severity]() -> std::string
        {
            switch (severity)
            {
                case GL_DEBUG_SEVERITY_NOTIFICATION: return "NOTIFICATION";
                case GL_DEBUG_SEVERITY_LOW:          return "LOW";
                case GL_DEBUG_SEVERITY_MEDIUM:       return "MEDIUM";
                case GL_DEBUG_SEVERITY_HIGH:         return "HIGH";

                default:                             throw std::invalid_argument{ "Invalid severity!" };
            }
        }();

        std::cout << std::format("[GL_DEBUG] {0}, {1}, {2}, {3}: {4}\n", sourceMessage, typeMessage, severityMessage, id, message);
    }
}


namespace gl
{
    enum
    {
        False = GL_FALSE, 
        True  = GL_TRUE, 
    };

    using int8_t     = GLbyte;
    using uint8_t    = GLubyte;
    using int16_t    = GLshort;
    using uint16_t   = GLushort;
    using int32_t    = GLint;
    using uint32_t   = GLuint;
    using int64_t    = GLint64;
    using uint64_t   = GLuint64;
    using size_t     = GLsizei;
    using f16_t      = GLhalf;
    using f32_t      = GLfloat;
    using f64_t      = GLdouble;

    using intptr_t   = GLintptr;
    using sizeptr_t  = GLsizeiptr;
    using sync_t     = GLsync;

    using bitfield_t = GLbitfield;

    enum handle_t : uint32_t {};
    enum query_t  : uint32_t {};



    struct Query
    {
        enum class Mode : GLenum
        {
            QueryWait, 
            QueryNoWait, 
            QueryRegionWait, 
            QueryRegionNoWait, 
        };
    };



    class State
    {
    public:
        static void init()
        {
            glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, &s_maxCombinedTextureImageUnits);
        }

        static int32_t max_combined_texture_image_units()
        {
            return s_maxCombinedTextureImageUnits;
        }

    private:
        static inline int32_t s_maxCombinedTextureImageUnits;
    };



    static void active_shader_program(handle_t pipeline, handle_t program)
    {
        glActiveShaderProgram(pipeline, program);
    }
    static void active_texture(uint32_t unit)
    {
        const auto& maxTextureUnits = State::max_combined_texture_image_units();
        if (std::cmp_greater_equal(unit, maxTextureUnits)) throw std::invalid_argument{ "The given texture unit exceeds capacity!" };

        glActiveTexture(GL_TEXTURE0 + unit);
    }
    static void attach_shader(handle_t program, handle_t shader)
    {
        glAttachShader(program, shader);
    }
    static void begin_conditional_render()
    {

    }
    static void begin_query()
    {

    }
}