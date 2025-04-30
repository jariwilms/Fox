#pragma once

#include "stdafx.hpp"

#include "Flags.hpp"
#include "Mapping.hpp"
#include "Object/Object.hpp"
#include "Parameters.hpp"
#include "Types.hpp"
#include "Concepts.hpp"

namespace fox::gfx::api::gl
{
    //OpenGL wrapper library
    // 
    //This library has the following goals:
    //    * Provide a more modern OpenGL interface
    //    * Wrap around existing OpenGL functions, allowing decoration with custom logic
    //    * Compile/Runtime input validation and safety
    // 
    //Functions are ordered according to their appearance in the OpenGL 4.6 core specification
    //https://registry.khronos.org/OpenGL/specs/gl/glspec46.core.pdf





    //Chapter 22 - Context State Queries
    static auto get_boolean_v            (glf::Data data, std::optional<gl::uint32_t> index = std::nullopt)
    {
        gl::bool_t value{};

        if   (index.has_value()) glGetBooleani_v(gl::to_underlying(data), index.value(), &value);
        else                     glGetBooleanv  (gl::to_underlying(data),                &value);

        return value;
    }
    static auto get_integer_v            (glf::Data data, std::optional<gl::uint32_t> index = std::nullopt)
    {
        gl::int32_t value{};

        if   (index.has_value()) glGetIntegeri_v(gl::to_underlying(data), index.value(), &value);
        else                     glGetIntegerv  (gl::to_underlying(data),                &value);

        return value;
    }
    static auto get_integer64_v          (glf::Data data, std::optional<gl::uint32_t> index = std::nullopt)
    {
        gl::int64_t value{};

        if   (index.has_value()) glGetInteger64i_v(gl::to_underlying(data), index.value(), &value);
        else                     glGetInteger64v  (gl::to_underlying(data),                &value);

        return value;
    }
    static auto get_float_v              (glf::Data data, std::optional<gl::uint32_t> index = std::nullopt)
    {
        gl::float32_t value{};

        if   (index.has_value()) glGetFloati_v(gl::to_underlying(data), index.value(), &value);
        else                     glGetFloatv  (gl::to_underlying(data),                &value);

        return value;
    }
    static auto get_float64_v            (glf::Data data, std::optional<gl::uint32_t> index = std::nullopt)
    {
        gl::float64_t value{};

        if   (index.has_value()) glGetDoublei_v(gl::to_underlying(data), index.value(), &value);
        else                     glGetDoublev  (gl::to_underlying(data),                &value);

        return value;
    }
    static auto is_enabled               (glf::Feature feature, std::optional<gl::uint32_t> index = std::nullopt)
    {
        gl::bool_t value{};

        if   (index.has_value()) value = glIsEnabledi(gl::to_underlying(feature), index.value());
        else                     value = glIsEnabled (gl::to_underlying(feature)               );

        return value;
    }
    static auto get_pointer_v            (glf::Callback::Pointer pointer)
    {
        gl::void_t* value{};
        glGetPointerv(gl::to_underlying(pointer), &value);

        return value;
    }
    static auto get_string               (glf::Connection connection, std::optional<gl::uint32_t> index = std::nullopt)
    {
        const gl::uint8_t* value{};

        if   (index.has_value()) value = glGetStringi(gl::to_underlying(connection), index.value());
        else                     value = glGetString (gl::to_underlying(connection)               );

        return std::string{ reinterpret_cast<const gl::char_t*>(value) };
    }
    static auto get_internal_format_v    (gl::enum_t target, gl::enum_t internalformat, gl::enum_t pname, gl::sizei_t bufsize)
    {
        throw std::logic_error{ "The method or operation has not been implemented!" };
    }
    static auto get_transform_feedback_v (gl::handle_t transformFeedback, glf::TransformFeedback::Property property)
    {
        gl::int32_t value{};
        glGetTransformFeedbackiv(gl::to_underlying(transformFeedback), gl::to_underlying(property), &value);

        return value;
    }
    


    //Chapter 4 - Event Model
    static auto get_sync_iv(gl::sync_t sync, glf::Synchronization::Property property)
    {
        gl::int32_t value{};
        glGetSynciv(sync, gl::to_underlying(property), sizeof(gl::int32_t), nullptr, &value);

        return value;
    }

    static auto get_query_iv                 (glf::Query::Target target, glf::Query::Symbol symbol, std::optional<gl::uint32_t> index = std::nullopt)
    {
        gl::int32_t value{};
        glGetQueryIndexediv(gl::to_underlying(target), index.value_or(gl::uint32_t{ 0 }), gl::to_underlying(symbol), &value);

        return value;
    }
    static auto get_query_object_iv          (gl::handle_t query, glf::Query::Parameter parameter)
    {
        gl::int32_t value{};
        glGetQueryObjectiv(gl::to_underlying(query), gl::to_underlying(parameter), &value);

        return value;
    }
    static auto get_query_object_uiv         (gl::handle_t query, glf::Query::Parameter parameter)
    {
        gl::uint32_t value{};
        glGetQueryObjectuiv(gl::to_underlying(query), gl::to_underlying(parameter), &value);

        return value;
    }
    static auto get_query_object_i64v        (gl::handle_t query, glf::Query::Parameter parameter)
    {
        gl::int64_t value{};
        glGetQueryObjecti64v(gl::to_underlying(query), gl::to_underlying(parameter), &value);

        return value;
    }
    static auto get_query_object_ui64v       (gl::handle_t query, glf::Query::Parameter parameter)
    {
        gl::uint64_t value{};
        glGetQueryObjectui64v(gl::to_underlying(query), gl::to_underlying(parameter), &value);

        return value;
    }
    static void get_query_buffer_object_iv   (gl::handle_t query, gl::handle_t buffer, glf::Query::Parameter parameter, gl::offset_t offset)
    {
        glGetQueryBufferObjectiv(gl::to_underlying(query), gl::to_underlying(buffer), gl::to_underlying(parameter), offset);
    }
    static void get_query_buffer_object_uiv  (gl::handle_t query, gl::handle_t buffer, glf::Query::Parameter parameter, gl::offset_t offset)
    {
        glGetQueryBufferObjectuiv(gl::to_underlying(query), gl::to_underlying(buffer), gl::to_underlying(parameter), offset);
    }
    static void get_query_buffer_object_i64v (gl::handle_t query, gl::handle_t buffer, glf::Query::Parameter parameter, gl::offset_t offset)
    {
        glGetQueryBufferObjecti64v(gl::to_underlying(query), gl::to_underlying(buffer), gl::to_underlying(parameter), offset);
    }
    static void get_query_buffer_object_ui64v(gl::handle_t query, gl::handle_t buffer, glf::Query::Parameter parameter, gl::offset_t offset)
    {
        glGetQueryBufferObjectui64v(gl::to_underlying(query), gl::to_underlying(buffer), gl::to_underlying(parameter), offset);
    }



    //Chapter 6 - Buffer Objects
    static auto get_buffer_parameter_iv  (gl::handle_t buffer, glf::Buffer::Parameter parameter)
    {
        gl::int32_t value{};
        glGetNamedBufferParameteriv(gl::to_underlying(buffer), gl::to_underlying(parameter), &value);

        return value;
    }
    static auto get_buffer_parameter_i64v(gl::handle_t buffer, glf::Buffer::Parameter parameter)
    {
        gl::int64_t value{};
        glGetNamedBufferParameteri64v(gl::to_underlying(buffer), gl::to_underlying(parameter), &value);

        return value;
    }



    //Chapter 7 - Programs and Shaders
    static auto get_shader_iv          (gl::handle_t shader, glf::Shader::Parameter parameter)
    {
        gl::int32_t value{};
        glGetShaderiv(gl::to_underlying(shader), gl::to_underlying(parameter), &value);

        return value;
    };
    static auto get_program_iv         (gl::handle_t program, glf::Program::Parameter parameter)
    {
        gl::int32_t value{};
        glGetProgramiv(gl::to_underlying(program), gl::to_underlying(parameter), &value);

        return value;
    };
    static auto get_program_pipeline_iv(gl::handle_t pipeline, glf::Program::Pipeline::Property property)
    {
        gl::int32_t value{};
        glGetProgramPipelineiv(gl::to_underlying(pipeline), gl::to_underlying(property), &value);

        return value;
    }

    static auto get_program_stage_iv(gl::handle_t program, glf::Shader::Type type, glf::Program::StageProperty property)
    {
        gl::int32_t value{};
        glGetProgramStageiv(gl::to_underlying(program), gl::to_underlying(type), gl::to_underlying(property), &value);

        return value;
    }

    static auto get_program_interface_iv(gl::handle_t program, glf::Program::Interface interface, glf::Program::Property property)
    {
        gl::int32_t value{};
        glGetProgramInterfaceiv(gl::to_underlying(program), gl::to_underlying(interface), gl::to_underlying(property), &value);

        return value;
    };

    static auto get_program_resource_index(gl::handle_t program, glf::Program::Interface interface, const std::string& identifier)
    {
        const auto* cstr   = identifier.c_str();
        gl::uint32_t value = glGetProgramResourceIndex(gl::to_underlying(program), gl::to_underlying(interface), cstr);

        return value;
    }
    
    static auto get_program_resource_name(gl::handle_t program, glf::Program::Interface interface, gl::uint32_t index)
    {
        std::string name{};
        gl::sizei_t length{};

        const auto& maximumLength = gl::get_program_interface_iv(program, interface, glf::Program::Property::MaximumNameLength);
        name.resize(maximumLength);

        glGetProgramResourceName(gl::to_underlying(program), gl::to_underlying(interface), index, maximumLength, &length, name.data());

        if (std::cmp_less(length, maximumLength)) name.resize(static_cast<std::size_t>(length) - 1u);
        
        return name;
    }
    static auto get_program_resource_iv(gl::handle_t program, glf::Program::Interface interface, std::span<const glf::Program::Resource> resources, gl::uint32_t index)
    {
        std::vector<gl::int32_t> values{};

        values.resize(resources.size());

        glGetProgramResourceiv(
            gl::to_underlying(program),
            gl::to_underlying(interface), index,
            static_cast<gl::sizei_t>(resources.size()), gl::to_underlying_ptr(resources.data()),
            static_cast<gl::sizei_t>(values.size()), nullptr, values.data());

        return values;
    }
    static auto get_program_resource_location(gl::handle_t program, glf::Program::Interface interface, const std::string& identifier)
    {
        const auto* cstr  = identifier.c_str();
        gl::int32_t value = glGetProgramResourceLocation(gl::to_underlying(program), gl::to_underlying(interface), cstr);

        return value;
    }
    static auto get_program_resource_location_index(gl::handle_t program, const std::string& identifier)
    {
        const auto* cstr  = identifier.c_str();
        gl::int32_t value = glGetProgramResourceLocationIndex(gl::to_underlying(program), gl::to_underlying(glf::Program::Interface::ProgramOutput), cstr);

        return value;
    }

    static auto get_active_uniforms_iv(gl::handle_t program, glf::Uniform::Property property, std::span<const gl::uint32_t> indices)
    {
        std::vector<gl::int32_t> values{};

        values.resize(indices.size());

        glGetActiveUniformsiv(gl::to_underlying(program), static_cast<gl::sizei_t>(indices.size()), indices.data(), gl::to_underlying(property), values.data());

        return values;
    };

    static auto get_active_uniform_block_iv(gl::handle_t program, glf::UniformBlock::Info info, gl::uint32_t index)
    {
        gl::int32_t value{};
        glGetActiveUniformBlockiv(gl::to_underlying(program), index, gl::to_underlying(info), &value);

        return value;
    };

    static auto get_active_atomic_counter_buffer_iv(gl::handle_t program, glf::AtomicCounterBuffer::Info info, gl::uint32_t index)
    {
        gl::int32_t value{};
        glGetActiveAtomicCounterBufferiv(gl::to_underlying(program), index, gl::to_underlying(info), &value);

        return value;
    };

    static auto get_active_subroutine_uniform_iv(gl::handle_t program, glf::Shader::Type type, glf::Shader::SubroutineParameter parameter, gl::uint32_t index)
    {
        gl::int32_t value{};
        glGetActiveSubroutineUniformiv(gl::to_underlying(program), gl::to_underlying(type), index, gl::to_underlying(parameter), &value);

        return value;
    }

    static auto uniform_subroutines_uiv(glf::Shader::Type type, std::span<const gl::uint32_t> indices)
    {
        glUniformSubroutinesuiv(gl::to_underlying(type), static_cast<gl::sizei_t>(indices.size()), indices.data());
    }

    static auto get_uniform_iv  (gl::handle_t program, gl::int32_t location, gl::sizei_t amount)
    {
        std::vector<gl::int32_t> values{};

        values.resize(amount);

        glGetnUniformiv(gl::to_underlying(program), location, amount, values.data());

        return values;
    }
    static auto get_uniform_uiv (gl::handle_t program, gl::int32_t location, gl::sizei_t amount)
    {
        std::vector<gl::uint32_t> values{};

        values.resize(amount);

        glGetnUniformuiv(gl::to_underlying(program), location, amount, values.data());

        return values;
    }
    static auto get_uniform_fv  (gl::handle_t program, gl::int32_t location, gl::sizei_t amount)
    {
        std::vector<gl::float32_t> values{};

        values.resize(amount);

        glGetnUniformfv(gl::to_underlying(program), location, amount, values.data());

        return values;
    }
    static auto get_uniform_f64v(gl::handle_t program, gl::int32_t location, gl::sizei_t amount)
    {
        std::vector<gl::float64_t> values{};

        values.resize(amount);

        glGetnUniformdv(gl::to_underlying(program), location, amount, values.data());

        return values;
    }

    static auto get_uniform_subroutine_uiv(glf::Shader::Type type, gl::int32_t location)
    {
        gl::uint32_t value{};
        glGetUniformSubroutineuiv(gl::to_underlying(type), location, &value);

        return value;
    }






    //Chapter 8 - Textures and Samplers
    static void sampler_parameter_iv     (gl::handle_t sampler, glf::Sampler::Parameter parameter, std::span<const gl::int32_t>   values)
    {
        glSamplerParameterIiv(gl::to_underlying(sampler), gl::to_underlying(parameter), values.data());
    }
    static void sampler_parameter_uiv    (gl::handle_t sampler, glf::Sampler::Parameter parameter, std::span<const gl::uint32_t>  values)
    {
        glSamplerParameterIuiv(gl::to_underlying(sampler), gl::to_underlying(parameter), values.data());
    }
    static void sampler_parameter_fv     (gl::handle_t sampler, glf::Sampler::Parameter parameter, std::span<const gl::float32_t> values)
    {
        glSamplerParameterfv(gl::to_underlying(sampler), gl::to_underlying(parameter), values.data());
    }
    static auto get_sampler_parameter_iv (gl::handle_t sampler, glf::Sampler::Parameter parameter)
    {
        gl::int32_t value{};
        glGetSamplerParameteriv(gl::to_underlying(sampler), gl::to_underlying(parameter), &value);

        return value;
    }
    static auto get_sampler_parameter_uiv(gl::handle_t sampler, glf::Sampler::Parameter parameter)
    {
        gl::uint32_t value{};
        glGetSamplerParameterIuiv(gl::to_underlying(sampler), gl::to_underlying(parameter), &value);

        return value;
    }
    static auto get_sampler_parameter_fv (gl::handle_t sampler, glf::Sampler::Parameter parameter)
    {
        gl::float32_t value{};
        glGetSamplerParameterfv(gl::to_underlying(sampler), gl::to_underlying(parameter), &value);

        return value;
    }

    static void texture_parameter(gl::handle_t texture, glf::Texture::Parameter parameter, gl::TextureParameter value) //TODO: implement further
    {
        if (std::holds_alternative<glf::Texture::MinificationFilter>(value))
        {
            const auto& v = std::get<glf::Texture::MinificationFilter>(value);
            glTextureParameteri(static_cast<gl::uint32_t>(texture), gl::to_underlying(parameter), gl::to_underlying(v));

            return;
        }
        if (std::holds_alternative<glf::Texture::MagnificationFilter>(value))
        {
            const auto& v = std::get<glf::Texture::MagnificationFilter>(value);
            glTextureParameteri(static_cast<gl::uint32_t>(texture), gl::to_underlying(parameter), gl::to_underlying(v));

            return;
        }
        if (std::holds_alternative<glf::Texture::Wrapping>(value))
        {
            const auto& v = std::get<glf::Texture::Wrapping>(value);
            glTextureParameteri(static_cast<gl::uint32_t>(texture), gl::to_underlying(parameter), gl::to_underlying(v));

            return;
        }

        throw std::invalid_argument{ "Invalid Texture Parameter!" };
    }

    static auto get_frame_buffer_parameter_iv           (gl::handle_t frameBuffer, glf::FrameBuffer::Parameter parameter)
    {
        gl::int32_t value{};
        glGetNamedFramebufferParameteriv(gl::to_underlying(frameBuffer), gl::to_underlying(parameter), &value);

        return value;
    }
    static auto get_frame_buffer_attachment_parameter_iv()
    {
        throw std::logic_error{ "The method or operation has not been implemented!" };
    }
    static auto get_render_buffer_parameter_iv          ()
    {
        throw std::logic_error{ "The method or operation has not been implemented!" };
    }

    static auto vertex_array_iv              (gl::handle_t vertexArray, glf::VertexArray::Parameter parameter)
    {
        gl::int32_t value{};
        glGetVertexArrayiv(gl::to_underlying(vertexArray), gl::to_underlying(parameter), &value);

        return value;
    }
    static auto get_vertex_array_indexed_iv  (gl::handle_t vertexArray, glf::VertexArray::IndexedParameter parameter, gl::uint32_t index)
    {
        gl::int32_t value{};
        glGetVertexArrayIndexediv(gl::to_underlying(vertexArray), index, gl::to_underlying(parameter), &value);

        return value;
    };
    static auto get_vertex_array_indexed_i64v(gl::handle_t vertexArray, glf::VertexArray::IndexedParameter parameter, gl::uint32_t index)
    {
        gl::int64_t value{};
        glGetVertexArrayIndexed64iv(gl::to_underlying(vertexArray), index, gl::to_underlying(parameter), &value);

        return value;
    };
    
    static auto get_vertex_attribute_iv (glf::VertexAttribute::Parameter parameter, gl::uint32_t index)
    {
        gl::int32_t value{};
        glGetVertexAttribIiv(index, gl::to_underlying(parameter), &value);

        return value;
    };
    static auto get_vertex_attribute_uiv(glf::VertexAttribute::Parameter parameter, gl::uint32_t index)
    {
        gl::uint32_t value{};
        glGetVertexAttribIuiv(index, gl::to_underlying(parameter), &value);

        return value;
    };
    static auto get_vertex_attribute_fv (glf::VertexAttribute::Parameter parameter, gl::uint32_t index)
    {
        gl::float32_t value{};
        glGetVertexAttribfv(index, gl::to_underlying(parameter), &value);

        return value;
    };
    static auto get_vertex_attribute_dv (glf::VertexAttribute::Parameter parameter, gl::uint32_t index)
    {
        gl::float64_t value{};
        glGetVertexAttribLdv(index, gl::to_underlying(parameter), &value);

        return value;
    };















    //Chapter 2 - OpenGL Fundamentals
    static auto get_graphics_reset_status()
    {
        gl::enum_t value{};
        value = glGetGraphicsResetStatus();

        return glf::Error::GraphicsResetStatus{ value };
    }
    static void flush()
    {
        glFlush();
    }
    static void finish()
    {
        glFinish();
    }



    //Chapter 4 - Event Model
    static void fence_sync      ()
    {
        glFenceSync(gl::to_underlying(glf::Synchronization::Object::Condition::GPUCommandsComplete), gl::bitfield_t{ 0 });
    }
    static void delete_sync     (gl::sync_t sync)
    {
        if (sync) glDeleteSync(sync);
    }
    static auto client_wait_sync(gl::sync_t sync, gl::uint64_t timeout)
    {
        gl::enum_t value{};
        value = glClientWaitSync(sync, gl::to_underlying(glf::Synchronization::FlushingBehavior::Commands), timeout);

        return glf::Synchronization::Status{ value };
    }
    static void server_wait_sync(gl::sync_t sync)
    {
        glWaitSync(sync, gl::bitfield_t{ 0 }, gl::to_underlying(glf::Synchronization::Timeout::Ignored));
    }

    static auto create_query    (glf::Query::Target target)
    {
        gl::handle_t handle{};
        glCreateQueries(gl::to_underlying(target), gl::sizei_t{ 1 }, gl::to_underlying_ptr(&handle));

        return handle;
    }
    static void delete_query    (gl::handle_t query)
    {
        if (query != gl::NullObject) glDeleteQueries(gl::sizei_t{ 1 }, gl::to_underlying_ptr(&query));
    }
    static void begin_query     (gl::handle_t query, glf::Query::Target target, std::optional<gl::uint32_t> index = std::nullopt)
    {
        glBeginQueryIndexed(gl::to_underlying(target), index.value_or(gl::uint32_t{ 0 }), gl::to_underlying(query));
    }
    static void end_query       (glf::Query::Target target, std::optional<gl::uint32_t> index = std::nullopt)
    {
        glEndQueryIndexed(gl::to_underlying(target), index.value_or(gl::uint32_t{ 0 }));
    }

    static void query_counter   (gl::handle_t query)
    {
        glQueryCounter(gl::to_underlying(query), gl::to_underlying(glf::Query::Counter::Timestamp));
    }



    //Chapter 6 - Buffer Objects
    static auto create_buffer            ()
    {
        gl::handle_t handle{};
        glCreateBuffers(gl::sizei_t{ 1 }, gl::to_underlying_ptr(&handle));

        return handle;
    }
    static void delete_buffer            (gl::handle_t buffer)
    {
        if (buffer != gl::NullObject) glDeleteBuffers(gl::sizei_t{ 1 }, gl::to_underlying_ptr(&buffer));
    }
    static void bind_buffer_range        (gl::handle_t buffer, glf::Buffer::BaseTarget target, gl::uint32_t index, gl::byterange_t range)
    {
        glBindBufferRange(gl::to_underlying(target), index, gl::to_underlying(buffer), range.offset, range.size);
    }
    static void bind_buffer_base         (gl::handle_t buffer, glf::Buffer::BaseTarget target, gl::uint32_t index)
    {
        glBindBufferBase(gl::to_underlying(target), index, gl::to_underlying(buffer));
    }
    
    static void buffer_storage           (gl::handle_t buffer, glf::Buffer::StorageFlags flags, gl::size_t size)
    {
        glNamedBufferStorage(gl::to_underlying(buffer), size, nullptr, gl::to_underlying(flags));
    }
    template<typename T>                  
    static void buffer_storage           (gl::handle_t buffer, glf::Buffer::StorageFlags flags, std::span<const T> data)
    {
        glNamedBufferStorage(gl::to_underlying(buffer), static_cast<gl::size_t>(data.size_bytes()), data.data(), gl::to_underlying(flags));
    }
    template<typename T>
    static void buffer_data              (gl::handle_t buffer, gl::offset_t offset, std::span<const T> data)
    {
        glNamedBufferSubData(gl::to_underlying(buffer), offset, static_cast<gl::size_t>(data.size_bytes()), data.data());
    }
    static void clear_buffer_data        (gl::handle_t buffer, glf::DataType type, glf::Buffer::BaseFormat baseFormat, glf::Buffer::Format format, gl::byterange_t range, const void* data)
    {
        glClearNamedBufferSubData(gl::to_underlying(buffer), gl::to_underlying(format), range.offset, range.size, gl::to_underlying(baseFormat), gl::to_underlying(type), data);
    }
    
    template<typename T>
    static auto map_buffer               (gl::handle_t buffer, glf::Buffer::Mapping::Access access)
    {
        return reinterpret_cast<T*>(glMapNamedBuffer(gl::to_underlying(buffer), gl::to_underlying(access)));
    }
    template<typename T>
    static auto map_buffer_range         (gl::handle_t buffer, glf::Buffer::Mapping::AccessFlags access, gl::size_t size, gl::offset_t offset)
    {
        reinterpret_cast<T*>(glMapNamedBufferRange(gl::to_underlying(buffer), offset, size, gl::to_underlying(access)));
    }
    static void flush_mapped_buffer_range(gl::handle_t buffer, gl::byterange_t range)
    {
        glFlushMappedNamedBufferRange(gl::to_underlying(buffer), range.offset, range.size);
    }
    static void unmap_buffer             (gl::handle_t buffer)
    {
        if (!glUnmapNamedBuffer(gl::to_underlying(buffer))) throw std::runtime_error{ "Buffer data store may be undefined!" };
    }
    static void invalidate_buffer_data   (gl::handle_t buffer, std::optional<gl::byterange_t> range = {})
    {
        if   (range.has_value()) glInvalidateBufferSubData(gl::to_underlying(buffer), range->offset, range->size);
        else                     glInvalidateBufferSubData(gl::to_underlying(buffer), 0            , gl::get_buffer_parameter_iv(buffer, glf::Buffer::Parameter::Size));
    }
    
    static void copy_buffer_sub_data     (gl::handle_t source, gl::handle_t destination, gl::byterange_t sourceRange, gl::offset_t destinationOffset)
    {
        glCopyNamedBufferSubData(gl::to_underlying(source), gl::to_underlying(destination), sourceRange.offset, destinationOffset, sourceRange.size);
    }
    
    template<typename T>
    static auto get_buffer_data          (gl::handle_t buffer, std::optional<gl::byterange_t> range)
    {
        std::vector<T> data{};

        if (range.has_value())
        {
            data.resize(range->size);

            glGetNamedBufferSubData(gl::to_underlying(buffer), range->offset, range->size, data.data());
        }
        else
        {
            const auto& size = gl::get_buffer_parameter_iv(buffer, glf::Buffer::Parameter::Size);
            data.resize(size);

            glGetNamedBufferSubData(gl::to_underlying(buffer), gl::offset_t{ 0 }, size, data.data());
        }

        return data;
    }



    //Chapter 7 - Programs and Shaders
    static auto create_shader(glf::Shader::Type type)
    {
        return gl::handle_t{ glCreateShader(gl::to_underlying(type)) };
    }
    static void shader_source(gl::handle_t shader, const std::string& source)
    {
        const auto* cstr = source.c_str();
        glShaderSource(gl::to_underlying(shader), gl::sizei_t{ 1 }, &cstr, nullptr);
    }
    static void compile_shader(gl::handle_t shader)
    {
        glCompileShader(gl::to_underlying(shader));
    }
    static void release_shader_compiler()
    {
        glReleaseShaderCompiler();
    }
    static void delete_shader(gl::handle_t shader)
    {
        if (shader != gl::NullObject) glDeleteShader(gl::to_underlying(shader));
    }
    static void shader_binary(gl::handle_t shader, gl::enum_t format, std::span<const gl::byte_t> binary)
    {
        glShaderBinary(gl::sizei_t{ 1 }, gl::to_underlying_ptr(&shader), format, binary.data(), static_cast<gl::sizei_t>(binary.size_bytes()));
    }
    template<gl::uint32_t N = 0>
    static void specialize_shader(gl::handle_t shader, const std::string& entry, std::span<const gl::uint32_t, N> indices = {}, std::span<const gl::uint32_t, N> values = {})
    {
        const auto* cstr = entry.c_str();
        glSpecializeShader(gl::to_underlying(shader), cstr, N, indices.data(), values.data());
    }

    static auto create_program()
    {
        return gl::handle_t{ glCreateProgram() };
    }
    static void attach_shader(gl::handle_t program, gl::handle_t shader)
    {
        glAttachShader(gl::to_underlying(program), gl::to_underlying(shader));
    }
    static void detach_shader(gl::handle_t program, gl::handle_t shader)
    {
        glDetachShader(gl::to_underlying(program), gl::to_underlying(shader));
    }
    static void link_program(gl::handle_t program)
    {
        glLinkProgram(gl::to_underlying(program));
    }
    static auto create_shader_program(glf::Shader::Type type, const std::string& source)
    {
        const auto* cstr = source.c_str();
        return gl::handle_t{ glCreateShaderProgramv(gl::to_underlying(type), gl::sizei_t{ 1 }, &cstr) };
    }
    static void program_specification(gl::handle_t program, glf::Program::Specification specification, gl::bool_t value)
    {
        glProgramParameteri(gl::to_underlying(program), gl::to_underlying(specification), value);
    }
    static void delete_program(gl::handle_t program)
    {
        if (program != gl::NullObject) glDeleteProgram(gl::to_underlying(program));
    }

    static auto create_program_pipeline()
    {
        gl::handle_t handle{};
        glCreateProgramPipelines(gl::sizei_t{ 1 }, gl::to_underlying_ptr(&handle));

        return handle;
    }
    static void delete_program_pipeline(gl::handle_t pipeline)
    {
        if (pipeline != gl::NullObject) glDeleteProgramPipelines(gl::sizei_t{ 1 }, gl::to_underlying_ptr(&pipeline));
    }
    static void bind_program_pipeline(gl::handle_t pipeline)
    {
        glBindProgramPipeline(gl::to_underlying(pipeline));
    }
    static void use_program_stages(gl::handle_t pipeline, gl::handle_t program, glf::Program::Stage stages)
    {
        glUseProgramStages(gl::to_underlying(pipeline), gl::to_underlying(stages), gl::to_underlying(program));
    }
    static void active_shader_program(gl::handle_t pipeline, gl::handle_t program)
    {
        glActiveShaderProgram(gl::to_underlying(pipeline), gl::to_underlying(program));
    }

    static auto get_program_binary(gl::handle_t program)
    {
        std::vector<gl::uint8_t> binary{};
        gl::enum_t               format{};

        const auto& binaryLength = gl::get_program_iv(program, glf::Program::Parameter::BinaryLength);
        binary.resize(static_cast<std::size_t>(binaryLength));

        glGetProgramBinary(gl::to_underlying(program), binaryLength, nullptr, &format, binary.data());

        struct result_t{ std::vector<gl::uint8_t> binary{}; gl::enum_t format{}; };
        return result_t{ binary, format };
    }
    static void program_binary(gl::handle_t program, gl::enum_t format, std::span<const gl::byte_t> binary)
    {
        glProgramBinary(gl::to_underlying(program), format, binary.data(), static_cast<gl::sizei_t>(binary.size()));
    }

    static auto get_uniform_location(gl::handle_t program, const std::string& identifier)
    {
        const auto* cstr  = identifier.c_str();
        gl::int32_t value = glGetUniformLocation(gl::to_underlying(program), cstr);

        return value;
    }
    static auto get_active_uniform_name(gl::handle_t program, gl::uint32_t index)
    {
        std::string name{};
        gl::sizei_t length{};

        const auto& maximumLength = gl::get_program_iv(program, glf::Program::Parameter::ActiveUniformMaximumLength);
        name.resize(maximumLength);

        glGetActiveUniformName(gl::to_underlying(program), index, maximumLength, &length, name.data());

        if (length ==                          0) throw std::invalid_argument{ "Identifier does not correspond to an active uniform name!" };
        if (std::cmp_less(length, maximumLength)) name.resize(static_cast<std::size_t>(length) - 1u);

        return name;
    }
    static auto get_uniform_indices(gl::handle_t program, gl::sizei_t count, std::span<const std::string> identifiers)
    {
        std::vector<const gl::char_t*> cstrs{};
        std::vector<gl::uint32_t>      values{};

        cstrs .resize (identifiers.size());
        values.reserve(identifiers.size());

        std::transform(identifiers.begin(), identifiers.end(), cstrs.begin(), [](const std::string& _)
            {
                return _.c_str();
            });
        glGetUniformIndices(gl::to_underlying(program), count, cstrs.data(), values.data());

        std::ranges::for_each(values, [](const auto& value)
            {
                if (value == gl::to_underlying(glf::Error::Sentinel::InvalidIndex)) throw std::invalid_argument{ "Identifier does not correspond to an active uniform name!" };
            });

        return values;
    }
    static auto get_active_uniform(gl::handle_t program, gl::uint32_t index)
    {
        std::string name{};
        gl::enum_t  type{};
        gl::int32_t size{};
        gl::sizei_t length{};

        const auto& maximumLength = gl::get_program_iv(program, glf::Program::Parameter::ActiveUniformMaximumLength);
        name.resize(maximumLength);

        glGetActiveUniform(gl::to_underlying(program), index, maximumLength, &length, &size, &type, name.data());

        if (std::cmp_less(length, maximumLength)) name.resize(static_cast<std::size_t>(length) - 1u);

        struct result_t{ std::string name{}; glf::DataType type{}; };
        return result_t{ name, glf::DataType{ type } };
    }

    static auto get_uniform_block_index(gl::handle_t program, const std::string& identifier)
    {
        const auto&  cstr  = identifier.c_str();
        gl::uint32_t value = glGetUniformBlockIndex(gl::to_underlying(program), cstr);

        return value;
    }
    static auto get_active_uniform_block_name(gl::handle_t program, gl::uint32_t index)
    {
        const auto& numUniformBlocks = gl::get_program_iv(program, glf::Program::Parameter::ActiveUniformBlocks);
        if (std::cmp_greater_equal(index, numUniformBlocks)) throw std::invalid_argument{ "Index is greater than the amount of uniform blocks!" };

        std::string name{};
        gl::sizei_t length{};

        const auto& maximumLength = gl::get_program_interface_iv(program, glf::Program::Interface::UniformBlock, glf::Program::Property::MaximumNameLength);
        name.resize(maximumLength);

        glGetActiveUniformBlockName(gl::to_underlying(program), index, maximumLength, &length, name.data());

        if (std::cmp_less(length, maximumLength)) name.resize(static_cast<std::size_t>(length) - 1u);

        return name;
    }
    static void uniform_block_binding(gl::handle_t program, gl::uint32_t index, gl::uint32_t binding)
    {
        glUniformBlockBinding(gl::to_underlying(program), index, binding);
    }

    static void shader_storage_block_binding(gl::handle_t program, gl::uint32_t index, gl::uint32_t binding)
    {
        glShaderStorageBlockBinding(gl::to_underlying(program), index, binding);
    }

    static auto get_subroutine_uniform_location(gl::handle_t program, glf::Shader::Type type, const std::string& identifier)
    {
        const auto* cstr  = identifier.c_str();
        gl::int32_t value = glGetSubroutineUniformLocation(gl::to_underlying(program), gl::to_underlying(type), cstr);

        return value;
    }
    static auto get_subroutine_index(gl::handle_t program, glf::Shader::Type type, const std::string& identifier)
    {
        const auto* cstr   = identifier.c_str();
        gl::uint32_t value = glGetSubroutineIndex(gl::to_underlying(program), gl::to_underlying(type), cstr);

        return value;
    }
    static auto get_active_subroutine_name(gl::handle_t program, glf::Shader::Type type, gl::uint32_t index)
    {
        std::string name{};
        gl::sizei_t length{};

        const auto& maximumSize = gl::get_program_stage_iv(program, type, glf::Program::StageProperty::ActiveSubroutineMaximumLength);
        name.resize(maximumSize);

        glGetActiveSubroutineName(gl::to_underlying(program), gl::to_underlying(type), index, maximumSize, &length, name.data());

        if (std::cmp_less(length, maximumSize)) name.resize(static_cast<std::size_t>(length) - 1u);

        return name;
    }
    static auto get_active_subroutine_uniform_name(gl::handle_t program, glf::Shader::Type type, gl::uint32_t index)
    {
        std::string name{};
        gl::sizei_t length{};

        const auto& maximumSize = gl::get_program_stage_iv(program, type, glf::Program::StageProperty::ActiveSubroutineUniformMaximumLength);
        name.resize(maximumSize);

        glGetActiveSubroutineUniformName(gl::to_underlying(program), gl::to_underlying(type), index, maximumSize, &length, name.data());

        if (std::cmp_less(length, maximumSize)) name.resize(static_cast<std::size_t>(length) - 1u);

        return name;
    }

    static void memory_barrier(glf::Memory::Barrier barrier)
    {
        glMemoryBarrier(gl::to_underlying(barrier));
    }
    static void memory_barrier_by_region(glf::Memory::RegionalBarrier barrier)
    {
        glMemoryBarrierByRegion(gl::to_underlying(barrier));
    }

    static auto get_attached_shaders(gl::handle_t program)
    {
        std::vector<gl::handle_t> shaders{};

        const auto& attachedShaders = gl::get_program_iv(program, glf::Program::Parameter::AttachedShaders);
        shaders.resize(attachedShaders);

        glGetAttachedShaders(gl::to_underlying(program), attachedShaders, nullptr, gl::to_underlying_ptr(shaders.data()));

        return shaders;
    }
    static auto shader_info_log(gl::handle_t shader)
    {
        std::string infoLog{};

        const auto& infoLogLength = get_shader_iv(shader, glf::Shader::Parameter::InfoLogLength);
        infoLog.resize(infoLogLength);

        glGetShaderInfoLog(gl::to_underlying(shader), infoLogLength, nullptr, infoLog.data());

        if (!infoLog.empty()) infoLog.resize(infoLog.size() - 1u);

        return infoLog;
    }
    static auto program_info_log(gl::handle_t program)
    {
        std::string infoLog{};

        const auto& infoLogLength = gl::get_program_iv(program, glf::Program::Parameter::InfoLogLength);
        infoLog.resize(infoLogLength);

        glGetProgramInfoLog(gl::to_underlying(program), infoLogLength, nullptr, infoLog.data());

        if (!infoLog.empty()) infoLog.resize(infoLog.size() - 1u);

        return infoLog;
    }
    static auto pipeline_info_log(gl::handle_t pipeline)
    {
        std::string infoLog{};

        const auto& infoLogLength = gl::get_program_pipeline_iv(pipeline, glf::Program::Pipeline::Property::InfoLogLength);
        infoLog.resize(infoLogLength);

        glGetProgramPipelineInfoLog(gl::to_underlying(pipeline), infoLogLength, nullptr, infoLog.data());

        if (!infoLog.empty()) infoLog.resize(infoLog.size() - 1u);

        return infoLog;
    }
    static auto get_shader_source(gl::handle_t shader)
    {
        std::string source{};

        const auto& sourceLength = gl::get_shader_iv(shader, glf::Shader::Parameter::SourceLength);
        source.resize(sourceLength);

        glGetShaderSource(gl::to_underlying(shader), sourceLength, nullptr, source.data());

        if (!source.empty()) source.resize(source.size() - 1u);

        return source;
    }
    template<glf::Shader::Type T>
    static auto get_shader_precision_format(glf::Shader::PrecisionFormat format)
    {
        if constexpr (
            T == glf::Shader::Type::Vertex   ||
            T == glf::Shader::Type::Fragment  )
        {
            std::array<gl::int32_t, 2> range{};
            gl::int32_t                precision{};

            glGetShaderPrecisionFormat(gl::to_underlying(T), gl::to_underlying(format), range.data(), &precision);

            struct result_t{ std::array<gl::int32_t, 2> range{}; gl::int32_t precision{}; };
            return result_t{ range, precision };
        }
    }



    //Chapter 8 - Textures and Samplers
    static auto create_texture(glf::Texture::Target target)
    {
        gl::handle_t handle{};
        glCreateTextures(gl::to_underlying(target), gl::sizei_t{ 1 }, gl::to_underlying_ptr(&handle));

        return handle;
    }
    static void delete_texture(gl::handle_t texture)
    {
        if (texture != gl::NullObject) glDeleteTextures(gl::sizei_t{ 1 }, gl::to_underlying_ptr(&texture));
    }
    static void bind_texture_unit(gl::handle_t texture, gl::uint32_t unit)
    {
        glBindTextureUnit(unit, gl::to_underlying(texture));
    }

    static auto create_sampler()
    {
        gl::handle_t handle{};
        glCreateSamplers(1, gl::to_underlying_ptr(&handle));

        return handle;
    }
    static void delete_sampler(gl::handle_t sampler)
    {
        if (sampler != gl::NullObject) glDeleteSamplers(1, gl::to_underlying_ptr(&sampler));
    }
    static void bind_sampler(gl::handle_t sampler, gl::uint32_t slot)
    {
        glBindSampler(slot, gl::to_underlying(sampler));
    }

    static auto pixel_store(glf::PackingMode mode, gl::int32_t parameter)
    {
        glPixelStorei(gl::to_underlying(mode), parameter);
    }

    static void texture_sub_image_1d(gl::handle_t texture, glf::Texture::BaseFormat format, const gl::line_t  <gl::uint32_t>& line,   gl::uint32_t level, std::span<const gl::byte_t> data)
    {
        glTextureSubImage1D(
            gl::to_underlying(texture), static_cast<gl::int32_t>(level),
            line.origin.x, 
            line.extent.x,
            gl::to_underlying(format), gl::to_underlying(glf::PixelData::Type::UnsignedByte),
            data.data());
    }
    static void texture_sub_image_2d(gl::handle_t texture, glf::Texture::BaseFormat format, const gl::area_t  <gl::uint32_t>& area,   gl::uint32_t level, std::span<const gl::byte_t> data)
    {
        glTextureSubImage2D(
            gl::to_underlying(texture), level,
            area.origin.x, area.origin.y,
            area.extent.x, area.extent.y,
            gl::to_underlying(format), gl::to_underlying(glf::PixelData::Type::UnsignedByte),
            data.data());
    }
    static void texture_sub_image_3d(gl::handle_t texture, glf::Texture::BaseFormat format, const gl::volume_t<gl::uint32_t>& volume, gl::uint32_t level, std::span<const gl::byte_t> data)
    {
        glTextureSubImage3D(
            gl::to_underlying(texture), level,
            volume.origin.x, volume.origin.y, volume.origin.z,
            volume.extent.x, volume.extent.y, volume.extent.z,
            gl::to_underlying(format), gl::to_underlying(glf::PixelData::Type::UnsignedByte),
            data.data());
    }
    static void copy_texture_sub_image_1d(gl::handle_t texture, gl::uint32_t level, const gl::Vector2u& offset, const gl::line_t  <gl::uint32_t>& line)
    {
        glCopyTextureSubImage1D(
            gl::to_underlying(texture), static_cast<gl::int32_t>(level),
            line.origin.x,
            offset.x,      offset.y,
            line.extent.x);
    }
    static void copy_texture_sub_image_2d(gl::handle_t texture, gl::uint32_t level, const gl::Vector2u& offset, const gl::area_t  <gl::uint32_t>& area)
    {
        glCopyTextureSubImage2D(
            gl::to_underlying(texture), static_cast<gl::int32_t>(level),
            area.origin.x, area.origin.y,
            offset.x,      offset.y,
            area.extent.x, area.extent.y);
    }
    static void copy_texture_sub_image_3d(gl::handle_t texture, gl::uint32_t level, const gl::Vector2u& offset, const gl::volume_t<gl::uint32_t>& volume)
    {
        glCopyTextureSubImage3D(
            gl::to_underlying(texture), static_cast<gl::int32_t>(level),
            volume.origin.x, volume.origin.y, volume.origin.z,
            offset.x,        offset.y,
            volume.extent.x, volume.extent.y);
    }

    static void compressed_texture_sub_image_1d(gl::handle_t texture, glf::Texture::CompressedFormat format, gl::uint32_t level, const gl::line_t  <gl::uint32_t> line,   std::span<const gl::byte_t> data)
    {
        glCompressedTextureSubImage1D(
            gl::to_underlying(texture),
            level,
            line.origin.x, 
            line.extent.x, 
            gl::to_underlying(format),
            static_cast<gl::sizei_t>(data.size()), data.data());
    }
    static void compressed_texture_sub_image_2d(gl::handle_t texture, glf::Texture::CompressedFormat format, gl::uint32_t level, const gl::area_t  <gl::uint32_t> area,   std::span<const gl::byte_t> data)
    {
        glCompressedTextureSubImage2D(
            gl::to_underlying(texture), 
            level, 
            area.origin.x, area.origin.y, 
            area.extent.x, area.extent.y, 
            gl::to_underlying(format), 
            static_cast<gl::sizei_t>(data.size()), data.data());
    }
    static void compressed_texture_sub_image_3d(gl::handle_t texture, glf::Texture::CompressedFormat format, gl::uint32_t level, const gl::volume_t<gl::uint32_t> volume, std::span<const gl::byte_t> data)
    {
        glCompressedTextureSubImage3D(
            gl::to_underlying(texture),
            level,
            volume.origin.x, volume.origin.y, volume.origin.z,
            volume.extent.x, volume.extent.y, volume.extent.z,
            gl::to_underlying(format),
            static_cast<gl::sizei_t>(data.size()), data.data());
    }

    static void texture_buffer(gl::handle_t texture, gl::handle_t buffer, glf::Buffer::Format format)
    {
        glTextureBuffer(gl::to_underlying(texture), gl::to_underlying(format), gl::to_underlying(buffer));
    }
    static void texture_buffer_range(gl::handle_t texture, gl::handle_t buffer, glf::Buffer::Format format, gl::line_t<gl::uint32_t> line)
    {
        glTextureBufferRange(gl::to_underlying(texture), gl::to_underlying(format), gl::to_underlying(buffer), line.origin.x, line.extent.x);
    }

    static void generate_texture_mipmap(gl::handle_t texture)
    {
        glGenerateTextureMipmap(gl::to_underlying(texture));
    }

    template<glf::Texture::Target T, glf::Texture::Target U> requires valid_texture_view<T, U>
    static void texture_view(gl::handle_t source, gl::handle_t destination, glf::Texture::Format format, gl::uint32_t minimumLevel, gl::uint32_t levels, gl::uint32_t minimumLayer, gl::uint32_t layers)
    {
        glTextureView(gl::to_underlying(destination), gl::to_underlying(U), gl::to_underlying(source), gl::to_underlying(format), minimumLevel, levels, minimumLayer, layers);
    }

    static void texture_storage_1d(gl::handle_t texture, glf::Texture::Format format, const gl::Vector1u& dimensions, gl::uint32_t levels)
    {
        glTextureStorage1D(gl::to_underlying(texture), static_cast<gl::sizei_t>(levels), gl::to_underlying(format), static_cast<gl::sizei_t>(dimensions.x));
    }
    static void texture_storage_2d(gl::handle_t texture, glf::Texture::Format format, const gl::Vector2u& dimensions, gl::uint32_t levels)
    {
        glTextureStorage2D(gl::to_underlying(texture), static_cast<gl::sizei_t>(levels), gl::to_underlying(format), static_cast<gl::sizei_t>(dimensions.x), static_cast<gl::sizei_t>(dimensions.y));
    }
    static void texture_storage_3d(gl::handle_t texture, glf::Texture::Format format, const gl::Vector3u& dimensions, gl::uint32_t levels)
    {
        glTextureStorage3D(gl::to_underlying(texture), static_cast<gl::sizei_t>(levels), gl::to_underlying(format), static_cast<gl::sizei_t>(dimensions.x), static_cast<gl::sizei_t>(dimensions.y), static_cast<gl::sizei_t>(dimensions.z));
    }
    static void texture_storage_2d_multisample(gl::handle_t texture, glf::Texture::Format format, const gl::Vector2u& dimensions, gl::uint32_t samples, gl::bool_t fixed = gl::True)
    {
        glTextureStorage2DMultisample(gl::to_underlying(texture), static_cast<gl::sizei_t>(samples), gl::to_underlying(format), static_cast<gl::sizei_t>(dimensions.x), static_cast<gl::sizei_t>(dimensions.y), fixed);
    }
    static void texture_storage_3d_multisample(gl::handle_t texture, glf::Texture::Format format, const gl::Vector3u& dimensions, gl::uint32_t samples, gl::bool_t fixed = gl::True)
    {
        glTextureStorage3DMultisample(gl::to_underlying(texture), static_cast<gl::sizei_t>(samples), gl::to_underlying(format), static_cast<gl::sizei_t>(dimensions.x), static_cast<gl::sizei_t>(dimensions.y), static_cast<gl::sizei_t>(dimensions.z), fixed);
    }

    static void invalidate_texture_image(gl::handle_t texture, gl::uint32_t level, std::optional<gl::volume_t<gl::uint32_t>> volume = {})
    {
        if (volume.has_value())
        {
            glInvalidateTexSubImage(
                gl::to_underlying(texture), static_cast<gl::int32_t>(level),
                static_cast<gl::int32_t>(volume->origin.x), static_cast<gl::int32_t>(volume->origin.y), static_cast<gl::int32_t>(volume->origin.z),
                static_cast<gl::sizei_t>(volume->extent.x), static_cast<gl::sizei_t>(volume->extent.y), static_cast<gl::sizei_t>(volume->extent.z));
        }
        else
        {
            glInvalidateTexImage(gl::to_underlying(texture), static_cast<gl::int32_t>(level));
        }
    }

    static void clear_texture_image(gl::handle_t texture, glf::Texture::BaseFormat format, glf::Texture::Type type, gl::uint32_t level, std::optional<gl::volume_t<gl::uint32_t>> volume, std::span<const gl::byte_t> data)
    {
        if (volume.has_value())
        {
            glClearTexSubImage(
                gl::to_underlying(texture),  static_cast<gl::int32_t>(level), 
                static_cast<gl::int32_t>(volume->origin.x), static_cast<gl::int32_t>(volume->origin.y), static_cast<gl::int32_t>(volume->origin.z),
                static_cast<gl::sizei_t>(volume->extent.x), static_cast<gl::sizei_t>(volume->extent.y), static_cast<gl::sizei_t>(volume->extent.z), 
                gl::to_underlying(format), 
                gl::to_underlying(type), 
                data.data());
        }
        else
        {
            glClearTexImage(
                gl::to_underlying(texture), static_cast<gl::int32_t>(level), 
                gl::to_underlying(format), 
                gl::to_underlying(type),
                data.data());
        }
    }

    static void bind_image_texture(gl::handle_t image, gl::handle_t texture, glf::Image::Format format, glf::Image::Access access, gl::uint32_t level, std::optional<gl::uint32_t> layer)
    {
        glBindImageTexture(
            gl::to_underlying(image), 
            gl::to_underlying(texture),
            static_cast<gl::int32_t>(level),
            layer.has_value(), static_cast<gl::int32_t>(layer.value_or(gl::uint32_t{ 0 })),
            gl::to_underlying(access), 
            gl::to_underlying(format));
    }



    //Chapter 9 - FrameBuffers and FrameBuffer Objects
    static auto create_frame_buffer()
    {
        gl::handle_t handle{};
        glCreateFramebuffers(gl::sizei_t{ 1 }, gl::to_underlying_ptr(&handle));

        return handle;
    }
    static void delete_frame_buffer(gl::handle_t frameBuffer)
    {
        if (frameBuffer != gl::NullObject) glDeleteFramebuffers(gl::sizei_t{ 1 }, gl::to_underlying_ptr(&frameBuffer));
    }
    static void bind_frame_buffer(gl::handle_t frameBuffer, glf::FrameBuffer::Target target)
    {
        glBindFramebuffer(gl::to_underlying(target), gl::to_underlying(frameBuffer));
    }

    static void frame_buffer_parameter(gl::handle_t frameBuffer, glf::FrameBuffer::Parameter parameter, gl::uint32_t value)
    {
        glNamedFramebufferParameteri(gl::to_underlying(frameBuffer), gl::to_underlying(parameter), static_cast<gl::int32_t>(value));
    }

    static auto create_render_buffer()
    {
        gl::handle_t handle{};
        glCreateRenderbuffers(gl::sizei_t{ 1 }, gl::to_underlying_ptr(&handle));

        return handle;
    }
    static void delete_render_buffer(gl::handle_t renderBuffer)
    {
        if (renderBuffer != gl::NullObject) glDeleteRenderbuffers(1, gl::to_underlying_ptr(&renderBuffer));
    }
    static void render_buffer_storage(gl::handle_t renderBuffer, glf::RenderBuffer::Format format, const gl::Vector2u& dimensions)
    {
        glNamedRenderbufferStorage(
            gl::to_underlying(renderBuffer), 
            gl::to_underlying(format), 
            static_cast<gl::sizei_t>(dimensions.x), static_cast<gl::sizei_t>(dimensions.y));
    }
    static void render_buffer_storage_multisample(gl::handle_t renderBuffer, glf::RenderBuffer::Format format, const gl::Vector2u& dimensions, gl::uint8_t samples)
    {
        glNamedRenderbufferStorageMultisample(
            gl::to_underlying(renderBuffer), static_cast<gl::sizei_t>(samples), 
            gl::to_underlying(format), 
            static_cast<gl::sizei_t>(dimensions.x), static_cast<gl::sizei_t>(dimensions.y));
    }

    static void frame_buffer_render_buffer(gl::handle_t frameBuffer, gl::handle_t renderBuffer, glf::FrameBuffer::Source attachment)
    {
        glNamedFramebufferRenderbuffer(gl::to_underlying(frameBuffer), gl::to_underlying(attachment), gl::to_underlying(glf::RenderBuffer::Target::RenderBuffer), gl::to_underlying(renderBuffer));
    }

    static void frame_buffer_texture(gl::handle_t frameBuffer, gl::handle_t texture, glf::FrameBuffer::Source attachment, gl::uint32_t level)
    {
        glNamedFramebufferTexture(gl::to_underlying(frameBuffer), gl::to_underlying(attachment), gl::to_underlying(texture), static_cast<gl::int32_t>(level));
    }
    static void frame_buffer_texture_layer(gl::handle_t frameBuffer, gl::handle_t texture, glf::FrameBuffer::Attachment attachment, gl::uint32_t level, gl::uint32_t layer)
    {
        glNamedFramebufferTextureLayer(gl::to_underlying(frameBuffer), gl::to_underlying(attachment), gl::to_underlying(texture), static_cast<gl::int32_t>(level), static_cast<gl::int32_t>(layer));
    }

    static void texture_barrier()
    {
        glTextureBarrier();
    }

    static auto check_frame_buffer_status(gl::handle_t frameBuffer)
    {
        return glf::FrameBuffer::Status{ glCheckNamedFramebufferStatus(gl::to_underlying(frameBuffer), gl::to_underlying(glf::FrameBuffer::Target::Write)) };
    }



    //Chapter 10 - Vertex Specification and Drawing Commands
    static void patch_parameter_separate(glf::Patch::Parameter parameter, gl::int32_t value)
    {
        glPatchParameteri(gl::to_underlying(parameter), value);
    }

    template<typename T, gl::uint32_t N, gl::bool_t NORM = gl::False>
    static void vertex_attribute(gl::uint32_t index, const gl::Vector<T, N>& value)
    {
        const auto& maximumAttributes = gl::get_integer_v(glf::Data::MaximumVertexAttributes);
        if (std::cmp_greater(index, maximumAttributes)) throw std::invalid_argument{ "Index exceeds the maximum amount of vertex attributes!" };



             if constexpr (std::is_same_v<T, gl::int16_t>   and N == 1 and NORM == gl::False) glVertexAttrib1s  (index, value.x);
        else if constexpr (std::is_same_v<T, gl::int16_t>   and N == 2 and NORM == gl::False) glVertexAttrib2s  (index, value.x, value.y);
        else if constexpr (std::is_same_v<T, gl::int16_t>   and N == 3 and NORM == gl::False) glVertexAttrib3s  (index, value.x, value.y, value.z);
        else if constexpr (std::is_same_v<T, gl::int16_t>   and N == 4 and NORM == gl::False) glVertexAttrib4s  (index, value.x, value.y, value.z, value.w);

        else if constexpr (std::is_same_v<T, gl::float32_t> and N == 1 and NORM == gl::False) glVertexAttrib1f  (index, value.x);
        else if constexpr (std::is_same_v<T, gl::float32_t> and N == 2 and NORM == gl::False) glVertexAttrib2f  (index, value.x, value.y);
        else if constexpr (std::is_same_v<T, gl::float32_t> and N == 3 and NORM == gl::False) glVertexAttrib3f  (index, value.x, value.y, value.z);
        else if constexpr (std::is_same_v<T, gl::float32_t> and N == 4 and NORM == gl::False) glVertexAttrib4f  (index, value.x, value.y, value.z, value.w);

        else if constexpr (std::is_same_v<T, gl::float64_t> and N == 1 and NORM == gl::False) glVertexAttribL1d (index, value.x);
        else if constexpr (std::is_same_v<T, gl::float64_t> and N == 2 and NORM == gl::False) glVertexAttribL2d (index, value.x, value.y);
        else if constexpr (std::is_same_v<T, gl::float64_t> and N == 3 and NORM == gl::False) glVertexAttribL3d (index, value.x, value.y, value.z);
        else if constexpr (std::is_same_v<T, gl::float64_t> and N == 4 and NORM == gl::False) glVertexAttribL4d (index, value.x, value.y, value.z, value.w);
                                                                                                           
        else if constexpr (std::is_same_v<T, gl::uint8_t>   and N == 4 and NORM == gl::True ) glVertexAttrib4Nub(index, value.x, value.y, value.z, value.w);

        else if constexpr (std::is_same_v<T, gl::int32_t>   and N == 1 and NORM == gl::False) glVertexAttribI1i (index, value.x);
        else if constexpr (std::is_same_v<T, gl::int32_t>   and N == 2 and NORM == gl::False) glVertexAttribI2i (index, value.x, value.y);
        else if constexpr (std::is_same_v<T, gl::int32_t>   and N == 3 and NORM == gl::False) glVertexAttribI3i (index, value.x, value.y, value.z);
        else if constexpr (std::is_same_v<T, gl::int32_t>   and N == 4 and NORM == gl::False) glVertexAttribI4i (index, value.x, value.y, value.z, value.w);

        else if constexpr (std::is_same_v<T, gl::int32_t>   and N == 1 and NORM == gl::False) glVertexAttribI1ui(index, value.x);
        else if constexpr (std::is_same_v<T, gl::int32_t>   and N == 2 and NORM == gl::False) glVertexAttribI2ui(index, value.x, value.y);
        else if constexpr (std::is_same_v<T, gl::int32_t>   and N == 3 and NORM == gl::False) glVertexAttribI3ui(index, value.x, value.y, value.z);
        else if constexpr (std::is_same_v<T, gl::int32_t>   and N == 4 and NORM == gl::False) glVertexAttribI4ui(index, value.x, value.y, value.z, value.w);

        else    static_assert(false, "The given input does not match a valid Vertex Attribute function!");
    }

    static auto create_vertex_array()
    {
        gl::handle_t handle{};
        glCreateVertexArrays(gl::sizei_t{ 1 }, gl::to_underlying_ptr(&handle));

        return handle;
    }
    static void delete_vertex_array(gl::handle_t vertexArray)
    {
        if (vertexArray != gl::NullObject) glDeleteVertexArrays(1, gl::to_underlying_ptr(&vertexArray));
    }
    static void bind_vertex_array(gl::handle_t vertexArray)
    {
        glBindVertexArray(gl::to_underlying(vertexArray));
    }
    static void vertex_array_element_buffer(gl::handle_t vertexArray, gl::handle_t elementBuffer)
    {
        glVertexArrayElementBuffer(gl::to_underlying(vertexArray), gl::to_underlying(elementBuffer));
    }
    
    static void vertex_array_attribute_format(gl::handle_t vertexArray, gl::uint32_t index, gl::offset_t offset, glf::VertexArray::Attribute::Type type, gl::uint32_t count, gl::bool_t normalized = gl::False)
    {
        const auto& maximumVertexAttributes = gl::get_integer_v(glf::Data::MaximumVertexAttributes);
        if (std::cmp_greater(index, maximumVertexAttributes)) throw std::invalid_argument{ "Index exceeds the maximum amount of vertex attributes!" };

        switch (type)
        {
            case glf::VertexArray::Attribute::Type::Byte                                 : 
            case glf::VertexArray::Attribute::Type::UnsignedByte                         : 
            case glf::VertexArray::Attribute::Type::Short                                : 
            case glf::VertexArray::Attribute::Type::UnsignedShort                        : 
            case glf::VertexArray::Attribute::Type::Integer                              : 
            case glf::VertexArray::Attribute::Type::UnsignedInteger                      : 
            case glf::VertexArray::Attribute::Type::Int_2_10_10_10_Rev                   : 
            case glf::VertexArray::Attribute::Type::UnsignedInteger_2_10_10_10_Rev       : 
            case glf::VertexArray::Attribute::Type::UnsignedInteger_10_11_11_11_Float_Rev:
            {
                glVertexArrayAttribIFormat(gl::to_underlying(vertexArray), index, static_cast<gl::int32_t>(count), gl::to_underlying(type), static_cast<gl::uint32_t>(offset));
                break;
            }

            case glf::VertexArray::Attribute::Type::Float                                : 
            case glf::VertexArray::Attribute::Type::HalfFloat                            : 
            case glf::VertexArray::Attribute::Type::Fixed                                : 
            {
                glVertexArrayAttribFormat(gl::to_underlying(vertexArray), index, static_cast<gl::int32_t>(count), gl::to_underlying(type), normalized, static_cast<gl::uint32_t>(offset));
                break;
            }

            case glf::VertexArray::Attribute::Type::Double                               : 
            {
                glVertexArrayAttribLFormat(gl::to_underlying(vertexArray), index, static_cast<gl::int32_t>(count), gl::to_underlying(type), static_cast<gl::uint32_t>(offset));
                break;
            }
        }
    }

    static void vertex_array_vertex_buffer(gl::handle_t vertexArray, gl::handle_t buffer, gl::uint32_t index, gl::sizei_t stride, gl::offset_t offset = {})
    {
        glVertexArrayVertexBuffer(gl::to_underlying(vertexArray), index, gl::to_underlying(buffer), offset, stride);
    }
    static void vertex_array_attribute_binding(gl::handle_t vertexArray, gl::uint32_t index, gl::uint32_t binding)
    {
        glVertexArrayAttribBinding(gl::to_underlying(vertexArray), index, binding);
    }
    static void enable_vertex_array_attribute(gl::handle_t vertexArray, gl::uint32_t index)
    {
        glEnableVertexArrayAttrib(gl::to_underlying(vertexArray), index);
    }
    static void disable_vertex_array_attribute(gl::handle_t vertexArray, gl::uint32_t index)
    {
        glDisableVertexArrayAttrib(gl::to_underlying(vertexArray), index);
    }

    static void vertex_array_binding_divisor(gl::handle_t vertexArray, gl::uint32_t binding, gl::uint32_t divisor)
    {
        glVertexArrayBindingDivisor(gl::to_underlying(vertexArray), binding, divisor);
    }

    static void enable(glf::Feature feature)
    {
        glEnable(gl::to_underlying(feature));
    }
    static void disable(glf::Feature feature)
    {
        glDisable(gl::to_underlying(feature));
    }
    static void primitive_restart_index(gl::uint32_t index)
    {
        glPrimitiveRestartIndex(index);
    }

    static void draw_arrays(glf::Draw::Mode mode, gl::range_t range)
    {
        glDrawArrays(gl::to_underlying(mode), static_cast<gl::int32_t>(range.offset), static_cast<gl::sizei_t>(range.count));
    }
    static void draw_arrays_instanced(glf::Draw::Mode mode, gl::range_t range, gl::sizei_t instanceCount, std::optional<gl::uint32_t> baseInstance)
    {
        if   (baseInstance.has_value()) glDrawArraysInstancedBaseInstance(gl::to_underlying(mode), static_cast<gl::int32_t>(range.offset), static_cast<gl::sizei_t>(range.count), instanceCount, baseInstance.value());
        else                            glDrawArraysInstanced            (gl::to_underlying(mode), static_cast<gl::int32_t>(range.offset), static_cast<gl::sizei_t>(range.count), instanceCount);
    }
    static void draw_elements(glf::Draw::Mode mode, glf::Draw::Type type, gl::count_t count)
    {
        glDrawElements(gl::to_underlying(mode), static_cast<gl::sizei_t>(count), gl::to_underlying(type), nullptr);
    }
    static void draw_elements_instanced(glf::Draw::Mode mode, glf::Draw::Type type, gl::count_t count, gl::uint32_t instanceCount, std::optional<gl::uint32_t> baseInstance)
    {
        if   (baseInstance.has_value()) glDrawElementsInstancedBaseInstance(gl::to_underlying(mode), static_cast<gl::sizei_t>(count), gl::to_underlying(type), nullptr, static_cast<gl::sizei_t>(instanceCount), baseInstance.value());
        else                            glDrawElementsInstanced            (gl::to_underlying(mode), static_cast<gl::sizei_t>(count), gl::to_underlying(type), nullptr, static_cast<gl::sizei_t>(instanceCount));
    }

    static void begin_conditional_render(gl::handle_t query, glf::Query::Mode mode)
    {
        glBeginConditionalRender(gl::to_underlying(query), gl::to_underlying(mode));
    }
    static void end_conditional_render()
    {
        glEndConditionalRender();
    }

    static void bind_attribute_location(gl::handle_t program, gl::uint32_t index, const std::string& identifier)
    {
        const auto* cstr = identifier.c_str();
        glBindAttribLocation(gl::to_underlying(program), index, cstr);
    }
    static auto active_attribute(gl::handle_t program, gl::uint32_t index)
    {
        std::string name{};
        gl::sizei_t length{};
        gl::int32_t size{};
        gl::enum_t  type{};

        const auto& maximumLength = gl::get_program_iv(program, glf::Program::Parameter::ActiveAttributeMaximumLength);
        name.resize(maximumLength);

        glGetActiveAttrib(gl::to_underlying(program), index, maximumLength, &length, &size, &type, name.data());

        if (std::cmp_less(length, maximumLength)) name.resize(static_cast<std::size_t>(length) - 1u);

        struct result_t{ std::string name{}; glf::DataType type{}; gl::sizei_t size{}; };
        return result_t{ name, glf::DataType{ type }, size };
    }
    static auto get_attribute_location(gl::handle_t program)
    {
        const gl::char_t* identifier{};
        glGetAttribLocation(gl::to_underlying(program), identifier);

        if   (identifier) return std::string{ identifier };
        else              return std::string{};
    }

    template<gl::uint32_t N>
    static void                           transform_feedback_varyings(gl::handle_t program, std::span<const std::string, N> varyings, glf::TransformFeedback::BufferMode mode)
    {
        //const auto& transform = [](const std::string& identifier) { return identifier.c_str(); };
        //std::transform(varyings.begin(), varyings.end(), names.begin(), transform);

        std::array<const gl::char_t*, N> names{};

        std::uint32_t index{};
        for (const auto& varying : varyings)
        {
            names.at(index++) = varying.c_str();
        }

        glTransformFeedbackVaryings(gl::to_underlying(program), names.size(), names.data(), gl::to_underlying(mode));
    }
    static auto get_transform_feedback_varying(gl::handle_t program, gl::uint32_t index)
    {
        const auto& maximumIndex = gl::get_program_iv(program, glf::Program::Parameter::TransformFeedbackVaryings);
        if (std::cmp_greater_equal(index, maximumIndex)) throw std::invalid_argument{ "The given index is out of range!" };

        std::string name{};
        gl::sizei_t length{};
        gl::int32_t size{};
        gl::enum_t  type{};

        const auto& maximumLength = gl::get_program_iv(program, glf::Program::Parameter::TransformFeedbackVaryingMaximumLength);
        name.resize(maximumLength);

        glGetTransformFeedbackVarying(gl::to_underlying(program), index, maximumLength, &length, &size, &type, name.data());

        if (std::cmp_less(length, maximumLength)) name.resize(static_cast<std::size_t>(length) - 1u);

        struct result_t{ std::string identifier{}; glf::DataType type{}; gl::sizei_t size{}; };
        return result_t{ name, glf::DataType{ type }, size };
    }

    static void validate_program(gl::handle_t program)
    {
        glValidateProgram(gl::to_underlying(program));
    }
    static void validate_program_pipeline(gl::handle_t pipeline)
    {
        glValidateProgramPipeline(gl::to_underlying(pipeline));
    }

    static void patch_parameter(glf::Patch::Parameter parameter, std::span<const gl::float32_t, 4> values)
    {
        glPatchParameterfv(gl::to_underlying(parameter), values.data());
    }



    //Chapter 13 - Fixed-Function Vertex Post-Processing
    static auto create_transform_feedback()
    {
        gl::handle_t handle{};
        glCreateTransformFeedbacks(gl::sizei_t{ 1 }, gl::to_underlying_ptr(&handle));

        return handle;
    }
    static void delete_transform_feedback(gl::handle_t transformFeedback)
    {
        if (transformFeedback != gl::NullObject) glDeleteTransformFeedbacks(gl::sizei_t{ 1 }, gl::to_underlying_ptr(&transformFeedback));
    }
    static void begin_transform_feedback(glf::TransformFeedback::PrimitiveMode mode)
    {
        glBeginTransformFeedback(gl::to_underlying(mode));
    }
    static void end_transform_feedback()
    {
        glEndTransformFeedback();
    }
    static void resume_transform_feedback()
    {
        glResumeTransformFeedback();
    }
    static void pause_tranform_feedback()
    {
        glPauseTransformFeedback();
    }
    static void transform_feedback_buffer_range(gl::handle_t transformFeedback, gl::handle_t buffer, gl::uint32_t index, gl::byterange_t range)
    {
        glTransformFeedbackBufferRange(gl::to_underlying(transformFeedback), index, gl::to_underlying(buffer), range.offset, range.size);
    }
    static void transform_feedback_buffer_base(gl::handle_t transformFeedback, gl::handle_t buffer, gl::uint32_t index)
    {
        glTransformFeedbackBufferBase(gl::to_underlying(transformFeedback), index, gl::to_underlying(buffer));
    }

    static void draw_transform_feedback(gl::handle_t transformFeedback, glf::Draw::Mode mode, std::optional<gl::uint32_t> instances)
    {
        if   (instances.has_value()) glDrawTransformFeedbackInstanced(gl::to_underlying(mode), gl::to_underlying(transformFeedback), static_cast<gl::sizei_t>(instances.value()));
        else                         glDrawTransformFeedback         (gl::to_underlying(mode), gl::to_underlying(transformFeedback));
    }
    static void draw_transform_feedback_stream(gl::handle_t transformFeedback, glf::Draw::Mode mode, gl::uint32_t stream, std::optional<gl::uint32_t> instances)
    {
        if   (instances.has_value()) glDrawTransformFeedbackStreamInstanced(gl::to_underlying(mode), gl::to_underlying(transformFeedback), stream, static_cast<gl::sizei_t>(instances.value()));
        else                         glDrawTransformFeedbackStream         (gl::to_underlying(mode), gl::to_underlying(transformFeedback), stream);
    }

    static void provoking_vertex(glf::ProvokingVertex provokingVertex)
    {
        glProvokingVertex(gl::to_underlying(provokingVertex));
    }

    static void clip_control(glf::Clip::Origin origin, glf::Clip::DepthMode mode)
    {
        glClipControl(gl::to_underlying(origin), gl::to_underlying(mode));
    }

    static void depth_range_array_v(gl::count_t offset, std::span<const gl::Vector2d> ranges)
    {
        glDepthRangeArrayv(offset, static_cast<gl::sizei_t>(ranges.size()), glm::value_ptr(*ranges.data()));
    }
    static void depth_range_indexed(gl::uint32_t index, const gl::Vector2d& range)
    {
        glDepthRangeIndexed(index, range.x, range.y);
    }
    static void depth_range(const gl::Vector2d& range)
    {
        glDepthRange(range.x, range.y);
    }
    static void depth_range(const gl::Vector2f& range)
    {
        glDepthRangef(range.x, range.y);
    }
    static void viewport_array_v(gl::count_t first, std::span<const gl::Vector2f> ranges)
    {
        glViewportArrayv(first, static_cast<gl::sizei_t>(ranges.size()), glm::value_ptr(*ranges.data()));
    }
    static void viewport_indexed(gl::uint32_t index, const gl::area_t<gl::float32_t>& area)
    {
        glViewportIndexedf(index, area.origin.x, area.origin.y, area.extent.x, area.extent.y);
    }
    static void viewport(const gl::area_t<gl::uint32_t>& area)
    {
        glViewport(area.origin.x, area.origin.y, area.extent.x, area.extent.y);
    }



    //Chapter 14 - Fixed-Function Primitive Assembly and Rasterization
    static auto multisample_v(gl::uint32_t index)
    {
        gl::Vector2f value{};
        glGetMultisamplefv(gl::to_underlying(glf::Multisample::Parameter::SamplePosition), index, glm::value_ptr(value));

        return value;
    }
    static void minimum_sample_shading(gl::float32_t value)
    {
        glMinSampleShading(value);
    }

    static void point_size(gl::float32_t size)
    {
        glPointSize(size);
    }
    template<glf::Point::Parameter, typename... Args> 
    static void                           point_parameter(Args... args) = delete;
    template<> 
    static void                           point_parameter<glf::Point::Parameter::FadeThresholdSize>(gl::float32_t value)
    {
        glPointParameterf(gl::to_underlying(glf::Point::Parameter::FadeThresholdSize), value);
    }
    template<> 
    static void                           point_parameter<glf::Point::Parameter::SpriteCoordinateOrigin>(glf::Point::CoordinateOrigin origin)
    {
        glPointParameteri(gl::to_underlying(glf::Point::Parameter::SpriteCoordinateOrigin), gl::to_underlying(origin));
    }

    static void line_width(gl::float32_t value)
    {
        glLineWidth(value);
    }

    static void front_face(glf::Orientation orientation)
    {
        glFrontFace(gl::to_underlying(orientation));
    }
    static void cull_face(glf::Culling::Face face)
    {
        glCullFace(gl::to_underlying(face));
    }

    static void polygon_mode(glf::Polygon::Mode mode)
    {
        glPolygonMode(gl::to_underlying(glf::Polygon::Face::FrontAndBack), gl::to_underlying(mode));
    }
    static void polygon_offset(gl::float32_t factor, gl::float32_t units, std::optional<gl::float32_t> clamp)
    {
        glPolygonOffsetClamp(factor, units, clamp.value_or(gl::float32_t{ 0.0f }));
    }

    static void scissor(const gl::area_t<gl::uint32_t>& area)
    {
        glScissor(
            static_cast<gl::int32_t>(area.origin.x), static_cast<gl::int32_t>(area.origin.y), 
            static_cast<gl::sizei_t>(area.extent.x), static_cast<gl::sizei_t>(area.extent.y));
    }
    

    
    //Chapter 15 - Programmable Fragment Processing
    static void bind_frag_data_location(gl::handle_t program, gl::uint32_t binding, std::optional<gl::uint32_t> index, const std::string& identifier)
    {
        const auto* cstr = identifier.c_str();
        glBindFragDataLocationIndexed(gl::to_underlying(program), binding, index.value_or(gl::uint32_t{ 0u }), cstr);
    }
    static auto get_frag_data_location(gl::handle_t program, const std::string& identifier)
    {
        const auto& cstr  = identifier.c_str();
        gl::int32_t value = glGetFragDataLocation(gl::to_underlying(program), cstr);

        return value;
    }
    static auto get_frag_data_index(gl::handle_t program, const std::string& identifier)
    {
        const auto& cstr  = identifier.c_str();
        gl::int32_t value = glGetFragDataIndex(gl::to_underlying(program), cstr);

        return value;
    }



    //Chapter 17 - Writing Fragments and Samples to the Framebuffer
    static void stencil_function(glf::Stencil::Function function, gl::int32_t value, gl::uint32_t mask)
    {
        glStencilFunc(gl::to_underlying(function), value, mask);
    }
    static void stencil_function_separate(glf::Stencil::Face face, glf::Stencil::Function function, gl::int32_t value, gl::uint32_t mask)
    {
        glStencilFuncSeparate(gl::to_underlying(face), gl::to_underlying(function), value, mask);
    }
    static void stencil_operation(glf::Stencil::Action stencil, glf::Stencil::Action depth, glf::Stencil::Action depthStencil)
    {
        glStencilOp(gl::to_underlying(stencil), gl::to_underlying(depth), gl::to_underlying(depthStencil));
    }
    static void stencil_operation_separate(glf::Stencil::Face face, glf::Stencil::Action stencil, glf::Stencil::Action depth, glf::Stencil::Action depthStencil)
    {
        glStencilOpSeparate(gl::to_underlying(face), gl::to_underlying(stencil), gl::to_underlying(depth), gl::to_underlying(depthStencil));
    }

    static void depth_function(glf::DepthFunction function)
    {
        glDepthFunc(gl::to_underlying(function));
    }

    static void blend_equation(glf::Blending::Equation equation)
    {
        glBlendEquation(gl::to_underlying(equation));
    }
    static void blend_equation_separate(glf::Blending::Equation equationRGB, glf::Blending::Equation equationAlpha)
    {
        glBlendEquationSeparate(gl::to_underlying(equationRGB), gl::to_underlying(equationAlpha));
    }
    //There are blend equation functions for individual buffers. Add -here-?
    static void blend_function(glf::Blending::Factor source, glf::Blending::Factor destination)
    {
        glBlendFunc(gl::to_underlying(source), gl::to_underlying(destination));
    }
    static void blend_function_separate(glf::Blending::Factor sourceRGB, glf::Blending::Factor sourceAlpha, glf::Blending::Factor destinationRGB, glf::Blending::Factor destinationAlpha)
    {
        glBlendFuncSeparate(gl::to_underlying(sourceRGB), gl::to_underlying(destinationRGB), gl::to_underlying(sourceAlpha), gl::to_underlying(destinationAlpha));
    }
    //There are blend functions for individual buffers. Add -here-?
    static void blend_color(const gl::Vector4f& color)
    {
        glBlendColor(color.r, color.g, color.b, color.a);
    }

    static void logical_pixel_operation(glf::Logic::Operation operation)
    {
        glLogicOp(gl::to_underlying(operation));
    }

    static void frame_buffer_draw_buffer(gl::handle_t frameBuffer, glf::FrameBuffer::Source source)
    {
        glNamedFramebufferDrawBuffer(gl::to_underlying(frameBuffer), gl::to_underlying(source));
    }
    static void frame_buffer_draw_buffers(gl::handle_t frameBuffer, std::span<const glf::FrameBuffer::Source> sources)
    {
        glNamedFramebufferDrawBuffers(gl::to_underlying(frameBuffer), static_cast<gl::sizei_t>(sources.size()), gl::to_underlying_ptr(sources.data()));
    }

    static void color_mask(const gl::Vector4b& mask)
    {
        glColorMask(mask.r, mask.g, mask.b, mask.a);
    }
    static void depth_mask(gl::bool_t flag)
    {
        glDepthMask(flag);
    }
    static void stencil_mask(gl::uint32_t mask)
    {
        glStencilMask(mask);
    }
    static void stencil_mask_separate(glf::Stencil::Face face, gl::uint32_t mask)
    {
        glStencilMaskSeparate(gl::to_underlying(face), mask);
    }

    static void clear(glf::Buffer::Mask mask)
    {
        glClear(gl::to_underlying(mask));
    }
    static void clear_color(const gl::Vector4f& color)
    {
        glClearColor(color.r, color.g, color.b, color.a);
    }
    static void clear_depth(gl::float32_t depth)
    {
        glClearDepthf(depth);
    }
    static void clear_stencil(gl::uint32_t index)
    {
        glClearStencil(static_cast<gl::int32_t>(index));
    }
    static void                           clear_frame_buffer(gl::handle_t frameBuffer, gl::int32_t index, gl::ClearValue value)
    {
        //TODO
        __debugbreak();

        if (std::holds_alternative<gl::color_t<gl::int32_t>>(value))
        {
            const auto& v = std::get<gl::color_t<gl::int32_t>>(value);

            glClearNamedFramebufferiv(gl::to_underlying(frameBuffer), v.buffer, index, glm::value_ptr(v.value));
        }

        //
    }

    static void invalidate_frame_buffer_data(gl::handle_t frameBuffer, std::span<const glf::FrameBuffer::Attachment> attachments, std::optional<gl::area_t<gl::uint32_t>> area)
    {
        if (area.has_value())
        {
            glInvalidateNamedFramebufferSubData(
                gl::to_underlying(frameBuffer), 
                static_cast<gl::sizei_t>(attachments.size()), gl::to_underlying_ptr(attachments.data()), 
                static_cast<gl::int32_t>(area->origin.x), static_cast<gl::int32_t>(area->origin.y), 
                static_cast<gl::sizei_t>(area->extent.x), static_cast<gl::sizei_t>(area->extent.y));
        }
        else
        {
            glInvalidateNamedFramebufferData(gl::to_underlying(frameBuffer), static_cast<gl::sizei_t>(attachments.size()), gl::to_underlying_ptr(attachments.data()));
        }
    }



    //Chapter 18 - Reading and Copying Pixels
    static void frame_buffer_read_buffer(gl::handle_t frameBuffer, glf::FrameBuffer::Source source)
    {
        glNamedFramebufferReadBuffer(gl::to_underlying(frameBuffer), gl::to_underlying(source));
    }
    static void                           read_pixels(glf::PixelData::Format format, glf::PixelData::Type type, gl::area_t<gl::uint32_t> area)
    {
        const auto& size = gl::Vector2f{ area.extent.x - area.origin.x, area.extent.y - area.origin.y };

        __debugbreak();
        //glReadnPixels(area.origin.x, area.origin.y, area.extent.x, area.extent.y, gl::to_underlying(format), gl::to_underlying(type), );
    }

    static void clamp_color(gl::bool_t value)
    {
        glClampColor(gl::to_underlying(glf::ClampColor::Read), static_cast<gl::enum_t>(value));
    }

    static void blit_framebuffer(gl::handle_t source, gl::handle_t destination, glf::Buffer::Mask mask, glf::FrameBuffer::Filter filter, const gl::area_t<gl::uint32_t> sourceArea, const gl::area_t<gl::uint32_t> destinationArea)
    {
        glBlitNamedFramebuffer(
            gl::to_underlying(source),
            gl::to_underlying(destination),
            sourceArea.origin.x,      sourceArea.origin.y,      sourceArea.extent.x,      sourceArea.extent.y,
            destinationArea.origin.x, destinationArea.origin.y, destinationArea.extent.x, destinationArea.extent.y,
            gl::to_underlying(mask), gl::to_underlying(filter));
    }

    static void                           copy_image_sub_data(gl::handle_t source, glf::Texture::Target sourceTarget, gl::uint32_t sourceLevel, gl::volume_t<gl::uint32_t> sourceVolume, gl::handle_t destination, glf::Texture::Target destinationTarget, gl::uint32_t destinationLevel, gl::volume_t<gl::uint32_t> destinationVolume)
    {
        __debugbreak(); //prob wrong

        glCopyImageSubData(
            gl::to_underlying(source),      gl::to_underlying(sourceTarget),      sourceLevel, 
            sourceVolume.origin.x,          sourceVolume.origin.y,                sourceVolume.origin.z,
            gl::to_underlying(destination), gl::to_underlying(destinationTarget), destinationLevel,
            destinationVolume.origin.x,     destinationVolume.origin.y,           destinationVolume.origin.z, 
            sourceVolume.extent.x,          sourceVolume.extent.y,                sourceVolume.extent.z);
    }



    //Chapter 19 - Compute Shaders
    static void dispatch_compute(gl::dispatch_t dispatch)
    {
        if (std::holds_alternative<gl::Vector3u>(dispatch))
        {
            const auto& group = std::get<gl::Vector3u>(dispatch);
            glDispatchCompute(group.x, group.y, group.z);
        }
        if (std::holds_alternative<gl::offset_t>(dispatch))
        {
            const auto& offset = std::get<gl::offset_t>(dispatch);
            glDispatchComputeIndirect(offset);
        }
    }



    //Chapter 20 - Debug Output
    static void debug_message_callback(debug_callback_t callback, const void* parameter = nullptr)
    {
        glDebugMessageCallback(callback, parameter);
    }
    static void debug_message_control(glf::Debug::Source source, glf::Debug::Type type, glf::Debug::Severity severity, gl::bool_t state)
    {
        glDebugMessageControl(gl::to_underlying(source), gl::to_underlying(type), gl::to_underlying(severity), 0, nullptr, state);
    }
    static void debug_message_insert(gl::uint32_t id, glf::Debug::Type type, glf::Debug::Severity severity, const std::string& message)
    {
        glDebugMessageInsert(
            gl::to_underlying(glf::Debug::Source::Application), 
            gl::to_underlying(type), id, gl::to_underlying(severity), 
            static_cast<gl::sizei_t>(message.length()), message.data());
    }
    static void push_debug_group(gl::uint32_t id, const std::string& message)
    {
        const auto* cstr = message.c_str();
        glPushDebugGroup(gl::to_underlying(glf::Debug::Source::Application), id, -1, cstr);
    }
    static void pop_debug_group()
    {
        glPopDebugGroup();
    }
    static void object_label(gl::handle_t handle, glf::Object::Type type, const std::string& label)
    {
        const auto* cstr = label.c_str();
        glObjectLabel(gl::to_underlying(type), gl::to_underlying(handle), -1, cstr);
    }
    static void object_pointer_label(gl::sync_t sync, const std::string& identifier)
    {
        const auto* cstr = identifier.c_str();
        glObjectPtrLabel(sync, -1, cstr);
    }
    static auto get_debug_message_log(gl::uint32_t count)
    {
        std::string                       messageLog{};
        std::vector<glf::Debug::Source>   sources{};
        std::vector<glf::Debug::Type>     types{};
        std::vector<gl::uint32_t>         ids{};
        std::vector<glf::Debug::Severity> severities{};
        std::vector<gl::sizei_t>          lengths{};

        const auto& maximumLength = gl::get_integer_v(glf::Data::MaximumDebugMessageLength);

        messageLog.resize(count * static_cast<gl::uint64_t>(maximumLength));
        sources   .resize(count);
        types     .resize(count);
        ids       .resize(count);
        severities.resize(count);
        lengths   .resize(count);

        gl::uint32_t amount = glGetDebugMessageLog(
            count, maximumLength, 
            gl::to_underlying_ptr(sources.data()), 
            gl::to_underlying_ptr(types.data()), ids.data(), 
            gl::to_underlying_ptr(severities.data()), 
            lengths.data(), messageLog.data());

        

        struct result_t
        {
            gl::uint32_t         id{};
            std::string          message{};
            glf::Debug::Source   source{};
            glf::Debug::Type     type{};
            glf::Debug::Severity severity{};
        };

        std::vector<result_t> result{};

        if (std::cmp_greater(amount, 0))
        {
            result.reserve(amount);

            std::size_t offset{};

            for (const auto& index : std::ranges::views::iota(0u, amount))
            {
                const auto& length = lengths.at(index);

                std::string message{ messageLog.data() + offset, static_cast<std::size_t>(length) - 1 };
                offset += length;

                result.emplace_back(
                    ids       .at(index),
                    message,
                    sources   .at(index),
                    types     .at(index),
                    severities.at(index));
            }
        }

        return result;
    }
    static auto get_object_label(gl::handle_t handle, glf::Object::Type type)
    {
        std::string label{};
        gl::sizei_t length{};

        const auto& maximumLabelLength = gl::get_integer_v(glf::Data::MaximumLabelLength);
        label.resize(static_cast<std::size_t>(maximumLabelLength));

        glGetObjectLabel(gl::to_underlying(type), gl::to_underlying(handle), maximumLabelLength, &length, label.data());

        if (std::cmp_less(length, maximumLabelLength)) label.resize(static_cast<std::size_t>(length) - 1);

        return label;
    }
    static auto get_object_pointer_label(gl::sync_t sync)
    {
        std::string label{};
        gl::sizei_t length{};

        const auto& maximumLabelLength = gl::get_integer_v(glf::Data::MaximumLabelLength);
        label.resize(static_cast<std::size_t>(maximumLabelLength));

        glGetObjectPtrLabel(sync, maximumLabelLength, &length, label.data());

        if (std::cmp_less(length, maximumLabelLength)) label.resize(static_cast<std::size_t>(length) - 1);

        return label;
    }
    
    
    
    //Chapter 21 - Special Functions
    static void hint(glf::Hint::Target target, glf::Hint::Mode mode)
    {
        glHint(gl::to_underlying(target), gl::to_underlying(mode));
    }



#ifdef FOX_GRAPHICS_API_GL_EXTENDED
    //TODO
    //create_*** functions that return N amount of handles eg.:
    //template<gl::sizei_t N>
    //create_buffers(...) => returns N amount of buffer handles. Returns handle if (N == 1). Returns handle array if (N > 1)
    //Same idea for delete_buffers(...) etc.
#endif
#ifdef FOX_GRAPHICS_API_GL_LEGACY
    static auto get_error()
    {
        gl::enum_t value = glGetError();

        return glf::Error::Flag{ value };
    }
    static auto is_sync(gl::sync_t sync)
    {
        gl::bool_t value{};
        value = glIsSync(sync);

        return value;
    }
    //Legacy OpenGL functions here (pre 3.0)
#endif
}
