#pragma once

#include "stdafx.hpp"

#include "GLMappings.hpp"

namespace fox::gfx::api::gl
{
    enum
    {
        False = GL_FALSE, 
        True  = GL_TRUE, 
    };

    using bool_t     = GLboolean;
    using char_t     = GLchar;
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

    using enum_t     = GLenum;
    using intptr_t   = GLintptr;
    using sizeptr_t  = GLsizeiptr;
    using sync_t     = GLsync;

    using bitfield_t = GLbitfield;

    enum handle_t : uint32_t {};
    enum query_t  : uint32_t {};



    struct Buffer
    {
        enum       Mask : bitfield_t
        {
            ColorBuffer   = GL_COLOR_BUFFER_BIT,
            DepthBuffer   = GL_DEPTH_BUFFER_BIT,
            StencilBuffer = GL_STENCIL_BUFFER_BIT, 

            All           = ColorBuffer | DepthBuffer | StencilBuffer
        };
        enum class Access : enum_t
        {
            Read      = GL_READ_ONLY, 
            Write     = GL_WRITE_ONLY, 
            ReadWrite = GL_READ_WRITE, 
        };
        enum class Target : enum_t
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
        enum class TargetBase : enum_t
        {
            AtomicCounterBuffer     = GL_ATOMIC_COUNTER_BUFFER, 
            TransformFeedbackBuffer = GL_TRANSFORM_FEEDBACK_BUFFER, 
            UniformBuffer           = GL_UNIFORM_BUFFER, 
            ShaderStorageBuffer     = GL_SHADER_STORAGE_BUFFER, 
        };
        enum class TargetRange : enum_t
        {
            TransformFeedbackBuffer = GL_TRANSFORM_FEEDBACK_BUFFER,
            UniformBuffer           = GL_UNIFORM_BUFFER,
        };
        enum       StorageFlags : bitfield_t
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
    constexpr enum_t  type_enum() requires (std::is_fundamental_v<T>)
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
    constexpr size_t  type_size() requires (std::is_fundamental_v<T>)
    {
        if constexpr (std::is_same_v<T, char>)               return sizeof(int8_t);
        if constexpr (std::is_same_v<T, unsigned char>)      return sizeof(uint8_t);
        if constexpr (std::is_same_v<T, short>)              return sizeof(int16_t);
        if constexpr (std::is_same_v<T, unsigned short>)     return sizeof(uint16_t);
        if constexpr (std::is_same_v<T, int>)                return sizeof(int32_t);
        if constexpr (std::is_same_v<T, unsigned int>)       return sizeof(uint32_t);
        if constexpr (std::is_same_v<T, long long>)          return sizeof(int64_t);
        if constexpr (std::is_same_v<T, unsigned long long>) return sizeof(uint64_t);
        if constexpr (std::is_same_v<T, float>)              return sizeof(f32_t);
        if constexpr (std::is_same_v<T, double>)             return sizeof(f64_t);
    }



    static int32_t     integer_v(enum_t parameter)
    {
        int32_t result{};
        glGetIntegerv(parameter, &result);

        return result;
    }



    static void        clear(Buffer::Mask mask)
    {
        glClear(mask);
    }



    static uint32_t    create_buffer()
    {
        uint32_t buffer{};
        glCreateBuffers(1, &buffer);

        return buffer;
    }
    static void        delete_buffer(uint32_t buffer)
    {
        glDeleteBuffers(1, &buffer);
    }
    static void        bind_buffer(uint32_t buffer, Buffer::Target target)
    {
        glBindBuffer(static_cast<enum_t>(target), buffer);
    }
    static void        bind_buffer_base(uint32_t buffer, Buffer::TargetBase target, uint32_t index)
    {
        glBindBufferBase(static_cast<enum_t>(target), index, buffer);
    }
    static void        bind_buffer_range(uint32_t buffer, Buffer::TargetRange target, uint32_t index, sizeptr_t size, intptr_t offset)
    {
        glBindBufferRange(static_cast<enum_t>(target), index, buffer, offset, size);
    }
    static void        buffer_storage(uint32_t buffer, Buffer::StorageFlags flags, sizeptr_t size)
    {
        glNamedBufferStorage(buffer, size, nullptr, static_cast<bitfield_t>(flags));
    }
    template<typename T>
    static void        buffer_storage(uint32_t buffer, Buffer::StorageFlags flags, std::span<const T> data)
    {
        glNamedBufferStorage(buffer, static_cast<sizeptr_t>(data.size_bytes()), data.data(), flags);
    }
    template<typename T>
    static void        buffer_sub_data(uint32_t buffer, intptr_t offset, std::span<const T> data)
    {
        glNamedBufferSubData(buffer, offset, static_cast<sizeptr_t>(data.size_bytes()), data.data());
    }



    static void*       map_buffer(uint32_t buffer, size_t size)
    {
        return glMapNamedBuffer(buffer, GL_READ_WRITE);
    }
    static void*       map_buffer_range(uint32_t buffer, enum_t access, sizeptr_t size, intptr_t offset)
    {
        return glMapNamedBufferRange(buffer, offset, size, access);
    }
    static bool_t      unmap_buffer(uint32_t buffer)
    {
        return glUnmapNamedBuffer(buffer);
    }



    static uint32_t    create_vertex_array()
    {
        uint32_t array{};
        glCreateVertexArrays(1, &array);

        return array;
    }
    static void        delete_vertex_array(uint32_t array)
    {
        glDeleteVertexArrays(1, &array);
    }
    static void        bind_vertex_array(uint32_t array)
    {
        glBindVertexArray(array);
    }
    static void        vertex_array_vertex_buffer(uint32_t array, uint32_t buffer, uint32_t index, size_t stride)
    {
        glVertexArrayVertexBuffer(array, index, buffer, 0, stride);
    }
    static void        enable_vertex_array_attribute(uint32_t array, uint32_t index)
    {
        glEnableVertexArrayAttrib(array, index);
    }
    static void        vertex_array_attribute_format(uint32_t array, uint32_t index, uint32_t offset, enum_t type, int32_t size, bool_t normalized)
    {
        glVertexArrayAttribFormat(array, index, size, type, normalized, offset);
    }
    static void        vertex_array_attribute_binding(uint32_t array, uint32_t index, uint32_t binding)
    {
        glVertexArrayAttribBinding(array, index, binding);
    }

    static uint32_t    create_frame_buffer()
    {
        uint32_t frameBuffer{};
        glCreateFramebuffers(1, &frameBuffer);
        
        return frameBuffer;
    }
    static void        delete_frame_buffer(uint32_t frameBuffer)
    {
        glDeleteFramebuffers(1, &frameBuffer);
    }
    static void        bind_frame_buffer(uint32_t frameBuffer, enum_t target)
    {
        glBindFramebuffer(target, frameBuffer);
    }
    static void        frame_buffer_read_buffer(uint32_t frameBuffer, enum_t source)
    {
        glNamedFramebufferReadBuffer(frameBuffer, source);
    }
    static void        frame_buffer_draw_buffer(uint32_t frameBuffer, enum_t buffer)
    {
        glNamedFramebufferDrawBuffer(frameBuffer, buffer);
    }
    static void        frame_buffer_draw_buffers(uint32_t frameBuffer, std::span<const enum_t> buffers)
    {
        glNamedFramebufferDrawBuffers(frameBuffer, static_cast<size_t>(buffers.size()), buffers.data());
    }
    static void        frame_buffer_texture(uint32_t frameBuffer, uint32_t texture, enum_t attachment, int32_t level)
    {
        glNamedFramebufferTexture(frameBuffer, attachment, texture, level);
    }
    static void        frame_buffer_render_buffer(uint32_t frameBuffer, uint32_t renderBuffer, enum_t attachment)
    {
        glNamedFramebufferRenderbuffer(frameBuffer, attachment, GL_RENDERBUFFER, renderBuffer);
    }
    static enum_t      check_frame_buffer_status(uint32_t frameBuffer)
    {
        return glCheckNamedFramebufferStatus(frameBuffer, GL_FRAMEBUFFER);
    }

    static uint32_t    create_texture(enum_t target)
    {
        uint32_t texture{};
        glCreateTextures(target, 1, &texture);

        return texture;
    }
    static void        delete_texture(uint32_t texture)
    {
        glDeleteTextures(1, &texture);
    }
    static void        bind_texture(uint32_t texture, std::uint32_t slot)
    {
        glBindTextureUnit(static_cast<uint32_t>(slot), texture);
    }
    static void        texture_parameter(uint32_t texture, enum_t parameter, uint32_t value)
    {
        glTextureParameteri(texture, parameter, value);
    }
    static void        texture_storage_1d(uint32_t texture, enum_t format, const Vector1u& dimensions, size_t levels)
    {
        glTextureStorage1D(texture, levels, format, static_cast<size_t>(dimensions.x));
    }
    static void        texture_storage_2d(uint32_t texture, enum_t format, const Vector2u& dimensions, size_t levels)
    {
        glTextureStorage2D(texture, levels, format, static_cast<size_t>(dimensions.x), static_cast<size_t>(dimensions.y));
    }
    static void        texture_storage_3d(uint32_t texture, enum_t format, const Vector3u& dimensions, size_t levels)
    {
        glTextureStorage3D(texture, levels, format, static_cast<size_t>(dimensions.x), static_cast<size_t>(dimensions.y), static_cast<size_t>(dimensions.z));
    }
    static void        texture_storage_2d_multisample(uint32_t texture, enum_t format, const Vector2u& dimensions, size_t samples)
    {
        glTextureStorage2DMultisample(texture, samples, format, static_cast<size_t>(dimensions.x), static_cast<size_t>(dimensions.y), GL_TRUE);
    }
    static void        texture_storage_3d_multisample(uint32_t texture, enum_t format, const Vector3u& dimensions, size_t samples)
    {
        glTextureStorage3DMultisample(texture, samples, format, static_cast<size_t>(dimensions.x), static_cast<size_t>(dimensions.y), static_cast<size_t>(dimensions.z), GL_TRUE);
    }
    static void        texture_sub_image_1d(uint32_t texture, enum_t format, const Vector1u& dimensions, const Vector1u& offset, int32_t level, const void* data)
    {
        glTextureSubImage1D(texture, level, static_cast<int32_t>(offset.x), static_cast<size_t>(dimensions.x), format, GL_UNSIGNED_BYTE, data);
    }
    static void        texture_sub_image_2d(uint32_t texture, enum_t format, const Vector2u& dimensions, const Vector2u& offset, uint32_t level, const void* data)
    {
        glTextureSubImage2D(texture, level, static_cast<int32_t>(offset.x), static_cast<int32_t>(offset.y), static_cast<size_t>(dimensions.x), static_cast<size_t>(dimensions.y), format, GL_UNSIGNED_BYTE, data);
    }
    static void        texture_sub_image_3d(uint32_t texture, enum_t format, const Vector3u& dimensions, const Vector3u& offset, int32_t level, const void* data) //80 column rule my ass
    {
        glTextureSubImage3D(texture, level, static_cast<int32_t>(offset.x), static_cast<int32_t>(offset.y), static_cast<int32_t>(offset.z), static_cast<size_t>(dimensions.x), static_cast<size_t>(dimensions.y), static_cast<size_t>(dimensions.z), format, GL_UNSIGNED_BYTE, data);
    }

    static uint32_t    create_render_buffer()
    {
        uint32_t id{};
        glCreateRenderbuffers(1, &id);

        return id;
    }
    static void        delete_render_buffer(uint32_t renderBuffer)
    {
        glDeleteRenderbuffers(1, &renderBuffer);
    }
    static void        bind_render_buffer(uint32_t renderBuffer)
    {
        glBindRenderbuffer(GL_RENDERBUFFER, renderBuffer);
    }
    static void        render_buffer_storage(uint32_t renderBuffer, enum_t format, const Vector2u& dimensions)
    {
        glNamedRenderbufferStorage(renderBuffer, format, static_cast<size_t>(dimensions.x), static_cast<size_t>(dimensions.y));
    }
    static void        render_buffer_storage_multisample(uint32_t renderBuffer, enum_t format, const Vector2u& dimensions, std::uint8_t samples)
    {
        glNamedRenderbufferStorageMultisample(renderBuffer, samples, format, static_cast<size_t>(dimensions.x), static_cast<size_t>(dimensions.y));
    }

    static uint32_t    create_program()
    {
        return glCreateProgram();
    }
    static void        delete_program(uint32_t program)
    {
        glDeleteProgram(program);
    }
    static void        link_program(uint32_t program)
    {
        glLinkProgram(program);
    }
    static void        program_parameter(uint32_t program, enum_t parameter, int32_t value)
    {
        glProgramParameteri(program, parameter, value);
    }
    static int32_t     program_iv(uint32_t program, enum_t parameter)
    {
        int32_t result{};
        glGetProgramiv(program, parameter, &result);

        return result;
    }
    static std::string program_infolog(uint32_t program)
    {
        std::string infolog{};
        size_t length = program_iv(program, GL_INFO_LOG_LENGTH);
        size_t bufSize{ length };

        infolog.resize(length);
        glGetProgramInfoLog(program, bufSize, nullptr, infolog.data());

        return infolog;
    }

    static uint32_t    create_shader(enum_t type)
    {
        return glCreateShader(type);
    }
    static void        delete_shader(uint32_t shader)
    {
        glDeleteShader(shader);
    }
    static void        attach_shader(uint32_t program, uint32_t shader)
    {
        glAttachShader(program, shader);
    }
    static void        detach_shader(uint32_t program, uint32_t shader)
    {
        glDetachShader(program, shader);
    }
    static void        shader_binary(uint32_t shader, std::span<const byte> binary)
    {
        glShaderBinary(1, &shader, GL_SHADER_BINARY_FORMAT_SPIR_V, binary.data(), static_cast<size_t>(binary.size_bytes()));
    }
    static void        specialize_shader(uint32_t shader, std::string_view entry)
    {
        glSpecializeShader(shader, entry.data(), 0, nullptr, nullptr);
    }
    static int32_t     shader_iv(uint32_t shader, enum_t parameter)
    {
        int32_t result{};
        glGetShaderiv(shader, parameter, &result);

        return result;
    }
    static std::string shader_infolog(uint32_t shader)
    {
        const auto& length = shader_iv(shader, GL_INFO_LOG_LENGTH);

        std::string infolog{};
        infolog.resize(length);

        glGetShaderInfoLog(shader, length, nullptr, infolog.data());

        return infolog;
    }

    static uint32_t    create_program_pipeline()
    {
        uint32_t pipeline{};
        glCreateProgramPipelines(1, &pipeline);

        return pipeline;
    }
    static void        delete_program_pipeline(uint32_t pipeline)
    {
        glDeleteProgramPipelines(1, &pipeline);
    }
    static void        bind_program_pipeline(uint32_t pipeline)
    {
        glBindProgramPipeline(pipeline);
    }
    static void        use_program_stages(uint32_t pipeline, uint32_t program, bitfield_t stages)
    {
        glUseProgramStages(pipeline, stages, program);
    }



    static void        debug_callback(enum_t source, enum_t type, uint32_t id, enum_t severity, size_t length, const char_t* message, const void* user_param)
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





    struct Query
    {
        enum class Mode : enum_t
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
