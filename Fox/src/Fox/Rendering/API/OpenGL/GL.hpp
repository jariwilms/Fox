#pragma once

#include "stdafx.hpp"

#include "GLMappings.hpp"

namespace fox::gfx::api::gl
{
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



    template<typename T> //TODO: outdated types, change to int32_t etc.
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
    template<typename T> //TODO: idem as above
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



    static handle_t    create_buffer()
    {
        uint32_t handle{};
        glCreateBuffers(1, &handle);

        return static_cast<handle_t>(handle);
    }
    static void        delete_buffer(handle_t buffer)
    {
        glDeleteBuffers(1, reinterpret_cast<uint32_t*>(&buffer));
    }
    static void        bind_buffer(handle_t buffer, Buffer::Target target)
    {
        glBindBuffer(static_cast<enum_t>(target), static_cast<uint32_t>(buffer));
    }
    static void        bind_buffer_base(handle_t buffer, Buffer::TargetBase target, uint32_t index)
    {
        glBindBufferBase(static_cast<enum_t>(target), index, static_cast<uint32_t>(buffer));
    }
    static void        bind_buffer_range(handle_t buffer, Buffer::TargetRange target, uint32_t index, sizeptr_t size, intptr_t offset)
    {
        glBindBufferRange(static_cast<enum_t>(target), index, static_cast<uint32_t>(buffer), offset, size);
    }
    static void        buffer_storage(handle_t buffer, Buffer::StorageFlags flags, sizeptr_t size)
    {
        glNamedBufferStorage(static_cast<uint32_t>(buffer), size, nullptr, static_cast<bitfield_t>(flags));
    }
    template<typename T>
    static void        buffer_storage(handle_t buffer, Buffer::StorageFlags flags, std::span<const T> data)
    {
        glNamedBufferStorage(static_cast<uint32_t>(buffer), static_cast<sizeptr_t>(data.size_bytes()), data.data(), flags);
    }
    template<typename T>
    static void        buffer_sub_data(handle_t buffer, intptr_t offset, std::span<const T> data)
    {
        glNamedBufferSubData(static_cast<uint32_t>(buffer), offset, static_cast<sizeptr_t>(data.size_bytes()), data.data());
    }

    static void*       map_buffer(handle_t buffer, size_t size)
    {
        return glMapNamedBuffer(static_cast<uint32_t>(buffer), GL_READ_WRITE);
    }
    static void*       map_buffer_range(handle_t buffer, enum_t access, sizeptr_t size, intptr_t offset)
    {
        return glMapNamedBufferRange(static_cast<uint32_t>(buffer), offset, size, access);
    }
    static bool_t      unmap_buffer(handle_t buffer)
    {
        return glUnmapNamedBuffer(static_cast<uint32_t>(buffer));
    }



    static handle_t    create_vertex_array()
    {
        uint32_t vertexArray{};
        glCreateVertexArrays(1, &vertexArray);

        return static_cast<handle_t>(vertexArray);
    }
    static void        delete_vertex_array(handle_t vertexArray)
    {
        glDeleteVertexArrays(1, reinterpret_cast<uint32_t*>(&vertexArray));
    }
    static void        bind_vertex_array(handle_t vertexArray)
    {
        glBindVertexArray(static_cast<uint32_t>(vertexArray));
    }
    static void        vertex_array_vertex_buffer(handle_t vertexArray, handle_t buffer, uint32_t index, size_t stride)
    {
        glVertexArrayVertexBuffer(static_cast<uint32_t>(vertexArray), index, static_cast<uint32_t>(buffer), 0, stride);
    }
    static void        enable_vertex_array_attribute(handle_t vertexArray, uint32_t index)
    {
        glEnableVertexArrayAttrib(static_cast<uint32_t>(vertexArray), index);
    }
    static void        vertex_array_attribute_format(handle_t vertexArray, uint32_t index, uint32_t offset, enum_t type, int32_t size, bool_t normalized)
    {
        glVertexArrayAttribFormat(static_cast<uint32_t>(vertexArray), index, size, type, normalized, offset);
    }
    static void        vertex_array_attribute_binding(handle_t vertexArray, uint32_t index, uint32_t binding)
    {
        glVertexArrayAttribBinding(static_cast<uint32_t>(vertexArray), index, binding);
    }



    static handle_t    create_frame_buffer()
    {
        uint32_t frameBuffer{};
        glCreateFramebuffers(1, &frameBuffer);
        
        return static_cast<handle_t>(frameBuffer);
    }
    static void        delete_frame_buffer(handle_t frameBuffer)
    {
        glDeleteFramebuffers(1, reinterpret_cast<uint32_t*>(&frameBuffer));
    }
    static void        bind_frame_buffer(handle_t frameBuffer, enum_t target)
    {
        glBindFramebuffer(target, static_cast<uint32_t>(frameBuffer));
    }
    static void        frame_buffer_read_buffer(handle_t frameBuffer, enum_t source)
    {
        glNamedFramebufferReadBuffer(static_cast<uint32_t>(frameBuffer), source);
    }
    static void        frame_buffer_draw_buffer(handle_t frameBuffer, enum_t buffer)
    {
        glNamedFramebufferDrawBuffer(static_cast<uint32_t>(frameBuffer), buffer);
    }
    static void        frame_buffer_draw_buffers(handle_t frameBuffer, std::span<const enum_t> buffers)
    {
        glNamedFramebufferDrawBuffers(static_cast<uint32_t>(frameBuffer), static_cast<size_t>(buffers.size()), buffers.data());
    }
    static void        frame_buffer_texture(handle_t frameBuffer, handle_t texture, enum_t attachment, int32_t level)
    {
        glNamedFramebufferTexture(static_cast<uint32_t>(frameBuffer), attachment, static_cast<uint32_t>(texture), level);
    }
    static void        frame_buffer_render_buffer(handle_t frameBuffer, uint32_t renderBuffer, enum_t attachment)
    {
        glNamedFramebufferRenderbuffer(static_cast<uint32_t>(frameBuffer), attachment, GL_RENDERBUFFER, renderBuffer);
    }
    static enum_t      check_frame_buffer_status(handle_t frameBuffer)
    {
        return glCheckNamedFramebufferStatus(static_cast<uint32_t>(frameBuffer), GL_FRAMEBUFFER);
    }



    static handle_t    create_texture(enum_t target)
    {
        uint32_t texture{};
        glCreateTextures(target, 1, &texture);

        return static_cast<handle_t>(texture);
    }
    static void        delete_texture(handle_t texture)
    {
        glDeleteTextures(1, reinterpret_cast<uint32_t*>(&texture));
    }
    static void        bind_texture(handle_t texture, std::uint32_t slot)
    {
        glBindTextureUnit(static_cast<uint32_t>(slot), static_cast<uint32_t>(texture));
    }
    static void        texture_parameter(handle_t texture, enum_t parameter, uint32_t value)
    {
        glTextureParameteri(static_cast<uint32_t>(texture), parameter, value);
    }
    static void        texture_storage_1d(handle_t texture, enum_t format, const Vector1u& dimensions, size_t levels)
    {
        glTextureStorage1D(static_cast<uint32_t>(texture), levels, format, static_cast<size_t>(dimensions.x));
    }
    static void        texture_storage_2d(handle_t texture, enum_t format, const Vector2u& dimensions, size_t levels)
    {
        glTextureStorage2D(static_cast<uint32_t>(texture), levels, format, static_cast<size_t>(dimensions.x), static_cast<size_t>(dimensions.y));
    }
    static void        texture_storage_3d(handle_t texture, enum_t format, const Vector3u& dimensions, size_t levels)
    {
        glTextureStorage3D(static_cast<uint32_t>(texture), levels, format, static_cast<size_t>(dimensions.x), static_cast<size_t>(dimensions.y), static_cast<size_t>(dimensions.z));
    }
    static void        texture_storage_2d_multisample(handle_t texture, enum_t format, const Vector2u& dimensions, size_t samples)
    {
        glTextureStorage2DMultisample(static_cast<uint32_t>(texture), samples, format, static_cast<size_t>(dimensions.x), static_cast<size_t>(dimensions.y), GL_TRUE);
    }
    static void        texture_storage_3d_multisample(handle_t texture, enum_t format, const Vector3u& dimensions, size_t samples)
    {
        glTextureStorage3DMultisample(static_cast<uint32_t>(texture), samples, format, static_cast<size_t>(dimensions.x), static_cast<size_t>(dimensions.y), static_cast<size_t>(dimensions.z), GL_TRUE);
    }
    static void        texture_sub_image_1d(handle_t texture, enum_t format, const Vector1u& dimensions, const Vector1u& offset, int32_t level, const void* data)
    {
        glTextureSubImage1D(static_cast<uint32_t>(texture), level, static_cast<int32_t>(offset.x), static_cast<size_t>(dimensions.x), format, GL_UNSIGNED_BYTE, data);
    }
    static void        texture_sub_image_2d(handle_t texture, enum_t format, const Vector2u& dimensions, const Vector2u& offset, uint32_t level, const void* data)
    {
        glTextureSubImage2D(static_cast<uint32_t>(texture), level, static_cast<int32_t>(offset.x), static_cast<int32_t>(offset.y), static_cast<size_t>(dimensions.x), static_cast<size_t>(dimensions.y), format, GL_UNSIGNED_BYTE, data);
    }
    static void        texture_sub_image_3d(handle_t texture, enum_t format, const Vector3u& dimensions, const Vector3u& offset, int32_t level, const void* data) //80 column rule my ass
    {
        glTextureSubImage3D(static_cast<uint32_t>(texture), level, static_cast<int32_t>(offset.x), static_cast<int32_t>(offset.y), static_cast<int32_t>(offset.z), static_cast<size_t>(dimensions.x), static_cast<size_t>(dimensions.y), static_cast<size_t>(dimensions.z), format, GL_UNSIGNED_BYTE, data);
    }



    static handle_t    create_render_buffer()
    {
        uint32_t renderBuffer{};
        glCreateRenderbuffers(1, &renderBuffer);

        return static_cast<handle_t>(renderBuffer);
    }
    static void        delete_render_buffer(handle_t renderBuffer)
    {
        glDeleteRenderbuffers(1, reinterpret_cast<uint32_t*>(&renderBuffer));
    }
    static void        bind_render_buffer(handle_t renderBuffer)
    {
        glBindRenderbuffer(GL_RENDERBUFFER, static_cast<uint32_t>(renderBuffer));
    }
    static void        render_buffer_storage(handle_t renderBuffer, enum_t format, const Vector2u& dimensions)
    {
        glNamedRenderbufferStorage(static_cast<uint32_t>(renderBuffer), format, static_cast<size_t>(dimensions.x), static_cast<size_t>(dimensions.y));
    }
    static void        render_buffer_storage_multisample(handle_t renderBuffer, enum_t format, const Vector2u& dimensions, std::uint8_t samples)
    {
        glNamedRenderbufferStorageMultisample(static_cast<uint32_t>(renderBuffer), samples, format, static_cast<size_t>(dimensions.x), static_cast<size_t>(dimensions.y));
    }



    static handle_t    create_program()
    {
        return static_cast<handle_t>(glCreateProgram());
    }
    static void        delete_program(handle_t program)
    {
        glDeleteProgram(static_cast<uint32_t>(program));
    }
    static void        link_program(handle_t program)
    {
        glLinkProgram(static_cast<uint32_t>(program));
    }
    static void        program_parameter(handle_t program, enum_t parameter, int32_t value)
    {
        glProgramParameteri(static_cast<uint32_t>(program), parameter, value);
    }
    static int32_t     program_iv(handle_t program, enum_t parameter)
    {
        int32_t result{};
        glGetProgramiv(static_cast<uint32_t>(program), parameter, &result);

        return result;
    }
    static std::string program_infolog(handle_t program)
    {
        std::string infolog{};
        const size_t bufferSize = program_iv(program, GL_INFO_LOG_LENGTH);

        infolog.resize(bufferSize);
        glGetProgramInfoLog(static_cast<uint32_t>(program), bufferSize, nullptr, infolog.data());

        return infolog;
    }



    static handle_t    create_shader(enum_t type)
    {
        return static_cast<handle_t>(glCreateShader(type));
    }
    static void        delete_shader(handle_t shader)
    {
        glDeleteShader(static_cast<uint32_t>(shader));
    }
    static void        attach_shader(handle_t program, handle_t shader)
    {
        glAttachShader(static_cast<uint32_t>(program), static_cast<uint32_t>(shader));
    }
    static void        detach_shader(handle_t program, handle_t shader)
    {
        glDetachShader(static_cast<uint32_t>(program), static_cast<uint32_t>(shader));
    }
    static void        shader_binary(handle_t shader, std::span<const byte> binary)
    {
        glShaderBinary(1, reinterpret_cast<uint32_t*>(&shader), GL_SHADER_BINARY_FORMAT_SPIR_V, binary.data(), static_cast<size_t>(binary.size_bytes()));
    }
    static void        specialize_shader(handle_t shader, std::string_view entry)
    {
        glSpecializeShader(static_cast<uint32_t>(shader), entry.data(), 0, nullptr, nullptr);
    }
    static int32_t     shader_iv(handle_t shader, enum_t parameter)
    {
        int32_t result{};
        glGetShaderiv(static_cast<uint32_t>(shader), parameter, &result);

        return result;
    }
    static std::string shader_infolog(handle_t shader)
    {
        const auto& length = shader_iv(shader, GL_INFO_LOG_LENGTH);

        std::string infolog{};
        infolog.resize(length);

        glGetShaderInfoLog(static_cast<uint32_t>(shader), length, nullptr, infolog.data());

        return infolog;
    }



    static handle_t    create_program_pipeline()
    {
        uint32_t pipeline{};
        glCreateProgramPipelines(1, &pipeline);

        return static_cast<handle_t>(pipeline);
    }
    static void        delete_program_pipeline(handle_t pipeline)
    {
        glDeleteProgramPipelines(1, reinterpret_cast<uint32_t*>(&pipeline));
    }
    static void        bind_program_pipeline(handle_t pipeline)
    {
        glBindProgramPipeline(static_cast<uint32_t>(pipeline));
    }
    static void        use_program_stages(handle_t pipeline, handle_t program, bitfield_t stages)
    {
        glUseProgramStages(static_cast<uint32_t>(pipeline), stages, static_cast<uint32_t>(program));
    }



    static void        active_shader_program(handle_t pipeline, handle_t program)
    {
        glActiveShaderProgram(static_cast<uint32_t>(pipeline), static_cast<uint32_t>(program));
    }
    static void        active_texture(uint32_t unit)
    {
        const auto& maxTextureUnits = State::max_combined_texture_image_units();
        if (std::cmp_greater_equal(unit, maxTextureUnits)) throw std::invalid_argument{ "The given texture unit exceeds capacity!" };

        glActiveTexture(GL_TEXTURE0 + unit);
    }
    static void        begin_conditional_render()
    {

    }
    static void        begin_query()
    {

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
}
