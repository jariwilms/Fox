#pragma once

#include "stdafx.hpp"

#include "Fox/Rendering/GraphicsAPI/OpenGL/Flags.hpp"
#include "Fox/Rendering/GraphicsAPI/OpenGL/Mapping.hpp"
#include "Fox/Rendering/GraphicsAPI/OpenGL/Object/Object.hpp"
#include "Fox/Rendering/GraphicsAPI/OpenGL/Parameters.hpp"
#include "Fox/Rendering/GraphicsAPI/OpenGL/Types.hpp"

namespace fox::gfx::api::gl
{
    //https://registry.khronos.org/OpenGL/specs/gl/glspec46.core.pdf



    static gl::bool_t                     bool_v(glf::Data flag)
    {
        gl::bool_t value{};
        glGetBooleanv(std::to_underlying(flag), &value);

        return value;
    }
    static gl::int32_t                    integer_v(glf::Data flag)
    {
        gl::int32_t value{};
        glGetIntegerv(static_cast<gl::enum_t>(flag), &value);

        return value;
    }
    static gl::int32_t                    integer_iv(glf::Data flag, gl::uint32_t index)
    {
        gl::int32_t value{};
        glGetIntegeri_v(std::to_underlying(flag), index, &value);

        return value;
    }
    static gl::int64_t                    integer64_v(glf::Data flag)
    {
        gl::int64_t value{};
        glGetInteger64v(std::to_underlying(flag), &value);

        return value;
    }
    static gl::int64_t                    integer64_iv(glf::Data flag, gl::uint32_t index)
    {
        gl::int64_t value{};
        glGetInteger64i_v(std::to_underlying(flag), index, &value);

        return value;
    }
    static gl::float32_t                  float_v(glf::Data flag)
    {
        gl::float32_t value{};
        glGetFloatv(std::to_underlying(flag), &value);

        return value;
    }
    static gl::float64_t                  float64_v(glf::Data flag)
    {
        gl::float64_t value{};
        glGetDoublev(std::to_underlying(flag), &value);

        return value;
    }
    static std::string                    string(glf::Connection connection)
    {
        const auto* value = reinterpret_cast<const gl::char_t*>(glGetString(std::to_underlying(connection)));

        return std::string{ value };
    }

    template<glf::VertexAttribute::Parameter P, gl::uint32_t U>
    static auto                           vertex_attribute_iv()
    {
        constexpr auto uv = std::to_underlying(P);

        if constexpr (P == glf::VertexAttribute::Parameter::Enabled)
        {
            gl::int32_t value{};
            glGetVertexAttribiv(U, uv, &value);

            return static_cast<gl::bool_t>(value);
        }
        if constexpr (P == glf::VertexAttribute::Parameter::Size)
        {
            gl::int32_t value{};
            glGetVertexAttribiv(U, uv, &value);

            return value;
        }
        if constexpr (P == glf::VertexAttribute::Parameter::Stride)
        {
            gl::int32_t value{};
            glGetVertexAttribiv(U, uv, &value);

            return static_cast<gl::uint32_t>(value);
        }
        if constexpr (P == glf::VertexAttribute::Parameter::Type)
        {
            gl::int32_t value{};
            glGetVertexAttribiv(U, uv, &value);

            return glf::DataType{ value };
        }
        if constexpr (P == glf::VertexAttribute::Parameter::IsNormalized)
        {
            gl::int32_t value{};
            glGetVertexAttribiv(U, uv, &value);

            return static_cast<gl::bool_t>(value);
        }
        if constexpr (P == glf::VertexAttribute::Parameter::IsIntegerData)
        {
            gl::int32_t value{};
            glGetVertexAttribiv(U, uv, &value);

            return static_cast<gl::bool_t>(value);
        }
        if constexpr (P == glf::VertexAttribute::Parameter::IsLongData)
        {
            gl::int32_t value{};
            glGetVertexAttribiv(U, uv, &value);

            return static_cast<gl::bool_t>(value);
        }
        if constexpr (P == glf::VertexAttribute::Parameter::Divisor)
        {
            gl::int32_t value{};
            glGetVertexAttribiv(U, uv, &value);

            return static_cast<gl::uint32_t>(value);
        }
        if constexpr (P == glf::VertexAttribute::Parameter::Binding)
        {
            gl::int32_t value{};
            glGetVertexAttribiv(U, uv, &value);

            return static_cast<gl::uint32_t>(value);
        }
        if constexpr (P == glf::VertexAttribute::Parameter::BufferBinding)
        {
            gl::int32_t value{};
            glGetVertexAttribiv(U, uv, &value);

            return value;
        }
        if constexpr (P == glf::VertexAttribute::Parameter::RelativeOffset)
        {
            gl::int32_t value{};
            glGetVertexAttribiv(U, uv, &value);

            return static_cast<gl::uint32_t>(value);
        }

        throw std::invalid_argument{ "Invalid Parameter!" };
    }

    template<glf::Feature F>
    static gl::bool_t                     is_enabled()
    {
        constexpr auto uv = std::to_underlying(F);

        if constexpr (F == glf::Feature::PrimitiveRestart)           return glIsEnabled(uv);
        if constexpr (F == glf::Feature::PrimitiveRestartFixedIndex) return glIsEnabled(uv);
        if constexpr (F == glf::Feature::DepthClamp)                 return glIsEnabled(uv);
        
        throw std::invalid_argument{ "Invalid Feature!" };
    }
    template<glf::Feature F, gl::uint32_t I>
    static gl::bool_t                     is_enabled()
    {
        constexpr auto uv = std::to_underlying(F);

        if constexpr (F == glf::Feature::ClipDistance)               return glIsEnabledi(uv, I);



        throw std::invalid_argument{ "Invalid Feature!" };
    }

    template<glf::Data D>
    static auto                           get_v()
    {
        constexpr auto uv = std::to_underlying(D);



        if constexpr (D == glf::Data::PatchDefaultOuterLevel)
        {
            std::array<gl::float32_t, 4> values{};
            glGetFloatv(uv, values.data());

            return fox::Vector4f{ values.at(0), values.at(1), values.at(2), values.at(3) };
        }
        if constexpr (D == glf::Data::PatchDefaultInnerLevel)
        {
            std::array<gl::float32_t, 2> values{};
            glGetFloatv(uv, values.data());

            return fox::Vector2f{ values.at(0), values.at(1) };
        }

        if constexpr (D == glf::Data::IndexArrayBufferBinding)        return static_cast<gl::uint32_t>(gl::integer_v(D));
                                                                      
        if constexpr (D == glf::Data::ArrayBufferBinding)             return static_cast<gl::uint32_t>(gl::integer_v(D));
        if constexpr (D == glf::Data::DrawIndirectBufferBinding)      return static_cast<gl::uint32_t>(gl::integer_v(D));
        if constexpr (D == glf::Data::VertexArrayBinding)             return static_cast<gl::uint32_t>(gl::integer_v(D));
        if constexpr (D == glf::Data::ParameterBufferBinding)         return static_cast<gl::uint32_t>(gl::integer_v(D));
                                                                      
        if constexpr (D == glf::Data::PrimitiveRestartIndex)          return static_cast<gl::uint32_t>(gl::integer_v(D));
                                                                      
        if constexpr (D == glf::Data::ClipOrigin)                     return glf::Clip::Origin{ gl::integer_v(D) };
        if constexpr (D == glf::Data::ClipDepthMode)                  return glf::Clip::DepthMode{ gl::integer_v(D) };

        if constexpr (D == glf::Data::TransformFeedbackBinding)       return static_cast<gl::uint32_t>(gl::integer_v(D));
        if constexpr (D == glf::Data::TransformFeedbackBufferBinding) return static_cast<gl::uint32_t>(gl::integer_v(D));











        if constexpr (D == glf::Data::MaximumVertexAttributeBindings) return static_cast<gl::uint32_t>(gl::integer_v(D));

        if constexpr (D == glf::Data::MaximumViewports)               return static_cast<gl::uint32_t>(gl::integer_v(D));






        if constexpr (D == glf::Data::ResetNotificationStrategy)      return  glf::Context::ResetStrategy{ gl::integer_v(D) };





        if constexpr (D == glf::Data::ActiveTexture)                     return gl::integer_v(D);
        if constexpr (D == glf::Data::AliasedLineWidthRange) 
        {
            std::array<gl::float32_t, 2> values{};
            glGetFloatv(uv, values.data());

            return gl::Vector2f{ values.at(0), values.at(1) };
        }
        if constexpr (D == glf::Data::ArrayBufferBinding)                return gl::integer_v(D);
        if constexpr (D == glf::Data::BlendColor)
        {
            std::array<gl::float32_t, 4> values{};
            glGetFloatv(uv, values.data());

            return gl::Vector4f{ values.at(0), values.at(1), values.at(2), values.at(3) };
        }
        if constexpr (D == glf::Data::BlendEquationAlpha)                return glf::Blending::Factor{ gl::integer_v(D) };
        if constexpr (D == glf::Data::BlendDestinationRGB)               return glf::Blending::Factor{ gl::integer_v(D) };
        if constexpr (D == glf::Data::BlendEquationAlpha)                return glf::Blending::Equation{ gl::integer_v(D) };
        if constexpr (D == glf::Data::BlendEquationRGB)                  return glf::Blending::Equation{ gl::integer_v(D) };
        if constexpr (D == glf::Data::Blending)                          return gl::bool_v(D);
        if constexpr (D == glf::Data::BlendSourceAlpha)                  return glf::Blending::Factor{ gl::integer_v(D) };
        if constexpr (D == glf::Data::BlendSourceRGB)                    return glf::Blending::Factor{ gl::integer_v(D) };
        if constexpr (D == glf::Data::ColorClearValue)
        {
            std::array<gl::float32_t, 4> values{};
            glGetFloatv(uv, values.data());

            return gl::Vector4f{ values.at(0), values.at(1), values.at(2), values.at(3) };
        }
        if constexpr (D == glf::Data::ColorLogicOperation)               return gl::bool_v(D);
        if constexpr (D == glf::Data::ColorWritemask)
        {
            std::array<gl::bool_t, 4> values{};
            glGetBooleanv(uv, values.data());

            return values;
        }
        if constexpr (D == glf::Data::CompressedTextureFormats)
        {
            const auto& nctf = gl::get_v<glf::Data::NumberCompressedTextureFormats>();

            std::vector<gl::int32_t> values{ nctf };
            glGetIntegerv(uv, values.data());

            std::vector<glf::Texture::CompressedFormat> results{};
            results.resize(nctf);

            std::transform(values.begin(), values.end(), results.begin(), [](gl::int32_t _)
                {
                    return glf::Texture::CompressedFormat{ static_cast<gl::uint32_t>(_) };
                });

            return results;
        }
        if constexpr (D == glf::Data::ContextFlags)                      return gl::integer_v(D);
        if constexpr (D == glf::Data::ContextFlags)                      return gl::integer_v(D);
        if constexpr (D == glf::Data::FaceCulling)                       return gl::bool_v(D);




        if constexpr (D == glf::Data::MaximumComputeShaderStorageBlocks) return gl::integer_v(D);



        if constexpr (D == glf::Data::NumberCompressedTextureFormats) return gl::integer_v(D);








        throw std::invalid_argument{ "" };
    }
    template<glf::Data D, gl::uint32_t I>
    static auto                           get_v()
    {
        const auto& uv = std::to_underlying(D);

        if constexpr (
            D == glf::Data::VertexBindingOffset  ||
            D == glf::Data::VertexBindingStride  ||
            D == glf::Data::VertexBindingDivisor ||
            D == glf::Data::VertexBindingBuffer  )
        {
            if (I >= gl::get_v<glf::Data::MaximumVertexAttributeBindings>()) throw std::invalid_argument{ "Index out of range!" };

            return gl::integer64_iv(D, I);
        }
        if constexpr (D == glf::Data::Viewport)
        {
            if (I >= gl::get_v<glf::Data::MaximumViewports>()) throw std::invalid_argument{ "Index out of range!" };

            std::array<gl::float32_t, 4> values{};
            glGetFloati_v(uv, I, values.data());

            return gl::Area{ values.at(0), values.at(1), values.at(2), values.at(3) };
        }
        if constexpr (D == glf::Data::DepthRange)
        {
            if (I >= gl::get_v<glf::Data::MaximumViewports>()) throw std::invalid_argument{ "Index out of range!" };

            std::array<gl::float64_t, 2> values{};
            glGetDoublei_v(uv, I, values.data());

            return gl::Range{ values.at(0), values.at(1) };
        }
    }















    //Execution Model [2.1]
    //Command Execution [2.3]
    static glf::Error::Flag                get_error()
    {
        return glf::Error::Flag{ glGetError() };
    }
    static glf::Error::GraphicsResetStatus get_graphics_reset_status()
    {
        return glf::Error::GraphicsResetStatus{ glGetGraphicsResetStatus() };
    }
    static void                            flush()
    {
        glFlush();
    }
    static void                            finish()
    {
        glFinish();
    }



    //Event Model [4.0]
    //Sync Objects and Fences [4.1]
    static void                            delete_sync(gl::sync_t sync)
    {
        glDeleteSync(sync);
    }
    static void                            fence_sync()
    {
        glFenceSync(std::to_underlying(glf::Synchronization::Condition::GPUCommandsComplete), gl::bitfield_t{ 0 });
    }
    static void                            client_wait_sync(gl::sync_t sync, gl::uint64_t timeout)
    {
        glClientWaitSync(sync, std::to_underlying(glf::Synchronization::FlushBehavior::FlushCommands), timeout);
    }
    static void                            server_wait_sync(gl::sync_t sync)
    {
        glWaitSync(sync, gl::bitfield_t{ 0 }, std::to_underlying(glf::Synchronization::Timeout::Ignored));
    }
    template<glf::Synchronization::Property P>
    static auto                            get_sync_v(gl::sync_t sync)
    {
        gl::int32_t value{};
        glGetSynciv(sync, std::to_underlying(P), sizeof(value), nullptr, &value);

        if constexpr (P == glf::Synchronization::Property::Type)      return glf::Synchronization::Type{ value };
        if constexpr (P == glf::Synchronization::Property::Status)    return glf::Synchronization::Status{ value };
        if constexpr (P == glf::Synchronization::Property::Condition) return glf::Synchronization::Condition{ value };
        if constexpr (P == glf::Synchronization::Property::Flags)     return glf::Synchronization::Flags{ value };
    }
    //Query Objects and Asynchronous Queries [4.2]
    static gl::handle_t                    create_query(glf::Query::Target target)
    {
        gl::uint32_t query{};
        glCreateQueries(std::to_underlying(target), gl::size_t{ 1 }, &query);

        return gl::handle_t{ query };
    }
    static void                            delete_query(gl::handle_t query)
    {
        if (query == gl::NullObject) return;

        const auto& uv = std::to_underlying(query);
        glDeleteQueries(gl::size_t{ 1 }, &uv);
    }
    static void                            begin_query(gl::handle_t query, glf::Query::Target target)
    {
        glBeginQuery(std::to_underlying(target), std::to_underlying(query));
    }
    static void                            begin_query_indexed(gl::handle_t query, glf::Query::Target target, gl::uint32_t index)
    {
        glBeginQueryIndexed(std::to_underlying(target), index, std::to_underlying(query));
    }
    static void                            end_query(glf::Query::Target target)
    {
        glEndQuery(std::to_underlying(target));
    }
    static void                            end_query_indexed(glf::Query::Target target, gl::uint32_t index)
    {
        glEndQueryIndexed(std::to_underlying(target), index);
    }
    template<glf::Query::Target T, glf::Query::TargetParameter TP>
    static auto                            get_query_v()
    {
        gl::int32_t value{};
        glGetQueryiv(std::to_underlying(T), std::to_underlying(TP), &value);

        return value;
    }
    template<glf::Query::Target T, glf::Query::TargetParameter TP>
    static auto                            get_query_indexed_v(gl::uint32_t index)
    {
        gl::int32_t value{};
        glGetQueryIndexediv(std::to_underlying(T), index, std::to_underlying(TP), &value);

        return value;
    }
    //Time Queries [4.3]
    static void                            query_counter(gl::handle_t query)
    {
        glQueryCounter(std::to_underlying(query), GL_TIMESTAMP);
    }



    //Buffer Objects [6.0]
    //Creating and Binding Buffer Objects [6.1]
    static gl::handle_t                    create_buffer()
    {
        gl::uint32_t buffer{};
        glCreateBuffers(gl::size_t{ 1 }, &buffer);

        return gl::handle_t{ buffer };
    }
    static void                            delete_buffer(gl::handle_t buffer)
    {
        if (buffer == gl::NullObject) return;

        const auto& uv = std::to_underlying(buffer);
        glDeleteBuffers(gl::size_t{ 1 }, &uv);
    }
    static void                            bind_buffer_base(gl::handle_t buffer, glf::Buffer::BaseTarget target, gl::uint32_t index)
    {
        glBindBufferBase(std::to_underlying(target), index, std::to_underlying(buffer));
    }
    static void                            bind_buffer_range(gl::handle_t buffer, glf::Buffer::BaseTarget target, gl::uint32_t index, gl::sizeptr_t size, gl::intptr_t offset)
    {
        glBindBufferRange(std::to_underlying(target), index, std::to_underlying(buffer), offset, size);
    }
    //Creating and Modifying Buffer Object Data Stores [6.2]
    static void                            buffer_storage(gl::handle_t buffer, glf::Buffer::StorageFlags flags, gl::sizeptr_t size)
    {
        glNamedBufferStorage(std::to_underlying(buffer), size, nullptr, std::to_underlying(flags));
    }
    template<typename T>                  
    static void                            buffer_storage(gl::handle_t buffer, glf::Buffer::StorageFlags flags, std::span<const T> data)
    {
        glNamedBufferStorage(std::to_underlying(buffer), static_cast<gl::sizeptr_t>(data.size_bytes()), data.data(), std::to_underlying(flags));
    }
    template<typename T, auto N>
    static void                            buffer_sub_data(gl::handle_t buffer, gl::intptr_t offset, std::span<const T, N> data)
    {
        glNamedBufferSubData(std::to_underlying(buffer), offset, static_cast<gl::sizeptr_t>(data.size_bytes()), data.data());
    }
    static void                            clear_buffer_data(gl::handle_t buffer, glf::DataType type, glf::Buffer::BaseFormat baseFormat, glf::Buffer::Format format, const void* data)
    {
        glClearNamedBufferData(std::to_underlying(buffer), std::to_underlying(format), std::to_underlying(baseFormat), std::to_underlying(type), data);
    }
    static void                            clear_buffer_sub_data(gl::handle_t buffer, glf::DataType type, glf::Buffer::BaseFormat baseFormat, glf::Buffer::Format format, gl::sizeptr_t size, gl::intptr_t offset, const void* data)
    {
        glClearNamedBufferSubData(std::to_underlying(buffer), std::to_underlying(format), offset, size, std::to_underlying(baseFormat), std::to_underlying(type), data);
    }
    //Mapping and Unmapping Buffer Data [6.3]
    template<typename T>
    static T*                              map_buffer(gl::handle_t buffer, glf::Buffer::Mapping::Access access)
    {
        auto* data = glMapNamedBuffer(std::to_underlying(buffer), std::to_underlying(access));

        return reinterpret_cast<T*>(data);
    }
    template<typename T>
    static T*                              map_buffer_range(gl::handle_t buffer, glf::Buffer::Mapping::AccessFlags access, gl::sizeptr_t size, gl::intptr_t offset)
    {
        auto* data = glMapNamedBufferRange(std::to_underlying(buffer), offset, size, std::to_underlying(access));

        return reinterpret_cast<T*>(data);
    }
    static void                            flush_mapped_buffer_range(gl::handle_t buffer, gl::sizeptr_t length, gl::intptr_t offset)
    {
        glFlushMappedNamedBufferRange(std::to_underlying(buffer), offset, length);
    }
    static void                            unmap_buffer(gl::handle_t buffer)
    {
        const auto& isValidState = glUnmapNamedBuffer(std::to_underlying(buffer));
        if (isValidState != gl::True) throw std::runtime_error{ "Buffer data store may be undefined!" };
    }
    //Invalidating Buffer Data [6.5]
    static void                            invalidate_buffer_data(gl::handle_t buffer)
    {
        glInvalidateBufferData(std::to_underlying(buffer));
    }
    static void                            invalidate_buffer_sub_data(gl::handle_t buffer, gl::sizeptr_t size, gl::intptr_t offset)
    {
        glInvalidateBufferSubData(std::to_underlying(buffer), offset, size);
    }
    //Copying Between Buffers [6.6]
    static void                            copy_buffer_sub_data(gl::handle_t source, gl::handle_t destination, gl::sizeptr_t size, gl::intptr_t sourceOffset, gl::intptr_t destinationOffset)
    {
        glCopyNamedBufferSubData(std::to_underlying(source), std::to_underlying(destination), sourceOffset, destinationOffset, size);
    }
    //Buffer Object Queries [6.7]
    template<typename T>
    static std::vector<T>                  get_buffer_sub_data(gl::handle_t buffer, gl::sizeptr_t size, gl::intptr_t offset)
    {
        std::vector<T> value{ size / sizeof(T) };
        glGetNamedBufferSubData(std::to_underlying(buffer), offset, size, value.data());

        return value;
    }
    template<glf::Buffer::Parameter P>
    static auto                            get_buffer_parameter_v(gl::handle_t buffer)
    {
        const auto& get_buffer_parameter_iv   = [](gl::handle_t buffer, glf::Buffer::Parameter parameter) -> gl::int32_t
            {
                gl::int32_t value{};
                glGetNamedBufferParameteriv(std::to_underlying(buffer), std::to_underlying(parameter), &value);

                return value;
            };
        const auto& get_buffer_parameter_i64v = [](gl::handle_t buffer, glf::Buffer::Parameter parameter) -> gl::int64_t
            {
                gl::int64_t value{};
                glGetNamedBufferParameteri64v(std::to_underlying(buffer), std::to_underlying(parameter), &value);

                return value;
            };
        
        if constexpr (P == glf::Buffer::Parameter::Size)         return static_cast<gl::uint64_t>(get_buffer_parameter_i64v(buffer, P));
        if constexpr (P == glf::Buffer::Parameter::Usage)        return static_cast<glf::Buffer::Usage>(get_buffer_parameter_iv(buffer, P));
        if constexpr (P == glf::Buffer::Parameter::Access)       return static_cast<glf::Buffer::Access>(get_buffer_parameter_iv(buffer, P));
        if constexpr (P == glf::Buffer::Parameter::AccessFlags)  return static_cast<glf::Buffer::AccessFlags>(get_buffer_parameter_iv(buffer, P));
        if constexpr (P == glf::Buffer::Parameter::IsImmutable)  return static_cast<gl::bool_t>(get_buffer_parameter_iv(buffer, P));
        if constexpr (P == glf::Buffer::Parameter::StorageFlags) return static_cast<glf::Buffer::StorageFlags>(get_buffer_parameter_iv(buffer, P));
        if constexpr (P == glf::Buffer::Parameter::IsMapped)     return static_cast<gl::bool_t>(get_buffer_parameter_iv(buffer, P));
        if constexpr (P == glf::Buffer::Parameter::MapOffset)    return static_cast<gl::uint64_t>(get_buffer_parameter_i64v(buffer, P));
        if constexpr (P == glf::Buffer::Parameter::MapLength)    return static_cast<gl::uint64_t>(get_buffer_parameter_i64v(buffer, P));

        throw std::invalid_argument{ "Invalid Parameter!" };
    }



    //Programs and Shaders [7.0]
    template<glf::Shader::Parameter P>
    static auto                            get_shader_v(gl::handle_t shader)
    {
        const auto& get_shader_iv = [](gl::handle_t shader, glf::Shader::Parameter parameter)
            {
                gl::int32_t value{};
                glGetShaderiv(std::to_underlying(shader), std::to_underlying(parameter), &value);

                return value;
            };

        if constexpr (
            P == glf::Shader::Parameter::Type)            return glf::Shader::Type{ get_shader_iv(shader, P) };
        if constexpr (
            P == glf::Shader::Parameter::DeleteStatus ||
            P == glf::Shader::Parameter::CompileStatus ||
            P == glf::Shader::Parameter::SpirVBinary) return static_cast<gl::bool_t>(get_shader_iv(shader, P));
        if constexpr (
            P == glf::Shader::Parameter::InfoLogLength ||
            P == glf::Shader::Parameter::SourceLength) return static_cast<gl::uint32_t>(get_shader_iv(shader, P));
    }
    template<glf::Program::Parameter P>
    static auto                            get_program_v(gl::handle_t program)
    {
        const auto& program_iv = [](gl::handle_t program, glf::Program::Parameter parameter) -> gl::int32_t
            {
                gl::int32_t value{};
                glGetProgramiv(std::to_underlying(program), std::to_underlying(parameter), &value);

                return value;
            };

        if constexpr (P == glf::Program::Parameter::IsSeparable)                           return static_cast<gl::bool_t>(  program_iv(program, P));
        if constexpr (P == glf::Program::Parameter::DeleteStatus)                          return static_cast<gl::bool_t>(  program_iv(program, P));
        if constexpr (P == glf::Program::Parameter::LinkStatus)                            return static_cast<gl::bool_t>(  program_iv(program, P));
        if constexpr (P == glf::Program::Parameter::ValidateStatus)                        return static_cast<gl::bool_t>(  program_iv(program, P));
        if constexpr (P == glf::Program::Parameter::AttachedShaders)                       return static_cast<gl::uint32_t>(program_iv(program, P));
        if constexpr (P == glf::Program::Parameter::InfoLogLength)                         return static_cast<gl::uint32_t>(program_iv(program, P));
        if constexpr (P == glf::Program::Parameter::BinaryLength)                          return static_cast<gl::uint32_t>(program_iv(program, P));
        if constexpr (P == glf::Program::Parameter::IsBinaryRetrievable)                   return static_cast<gl::bool_t>(  program_iv(program, P));
        if constexpr (P == glf::Program::Parameter::ComputeWorkGroupSize)
        {
            std::array<gl::int32_t, 3> values{};
            glGetProgramiv(std::to_underlying(program), std::to_underlying(P), values.data());

            return gl::Vector3u{ values.at(0), values.at(1), values.at(2) };
        }
        if constexpr (P == glf::Program::Parameter::ActiveUniforms)                        return static_cast<gl::uint32_t>(program_iv(program, P));
        if constexpr (P == glf::Program::Parameter::ActiveUniformMaximumLength)            return static_cast<gl::uint32_t>(program_iv(program, P));
        if constexpr (P == glf::Program::Parameter::ActiveAttributes)                      return static_cast<gl::uint32_t>(program_iv(program, P));
        if constexpr (P == glf::Program::Parameter::ActiveAttributeMaximumLength)          return static_cast<gl::uint32_t>(program_iv(program, P));
        if constexpr (P == glf::Program::Parameter::GeometryVerticesOut)                   return static_cast<gl::uint32_t>(program_iv(program, P));
        if constexpr (P == glf::Program::Parameter::GeometryInputType)                     return glf::Geometry::InputPrimitive{ program_iv(program, P) };
        if constexpr (P == glf::Program::Parameter::GeometryOutputType)                    return glf::Geometry::OutputPrimitive{ program_iv(program, P) };
        if constexpr (P == glf::Program::Parameter::GeometryShaderInvocations)             return static_cast<gl::uint32_t>(program_iv(program, P));
        if constexpr (P == glf::Program::Parameter::TransformFeedbackBufferMode)           return glf::TransformFeedback::BufferMode{ program_iv(program, P) };
        if constexpr (P == glf::Program::Parameter::TransformFeedbackVaryings)             return static_cast<gl::uint32_t>(program_iv(program, P));
        if constexpr (P == glf::Program::Parameter::TransformFeedbackVaryingMaximumLength) return static_cast<gl::uint32_t>(program_iv(program, P));
        if constexpr (P == glf::Program::Parameter::ActiveUniformBlocks)                   return static_cast<gl::uint32_t>(program_iv(program, P));
        if constexpr (P == glf::Program::Parameter::ActiveUniformBlockMaximumNameLength)   return static_cast<gl::uint32_t>(program_iv(program, P));
        if constexpr (P == glf::Program::Parameter::TessellationControlOutputVertices)     return static_cast<gl::uint32_t>(program_iv(program, P));
        if constexpr (P == glf::Program::Parameter::TessellationGenerationMode)            return glf::Tessellation::GenerationMode{ program_iv(program, P) };
        if constexpr (P == glf::Program::Parameter::TessellationGenerationSpacing)         return glf::Tessellation::Spacing{ program_iv(program, P) };
        if constexpr (P == glf::Program::Parameter::TessellationGenerationVertexOrder)     return glf::Tessellation::VertexOrder{ program_iv(program, P) };
        if constexpr (P == glf::Program::Parameter::TessellationGenerationPointMode)       return static_cast<gl::bool_t>(program_iv(program, P));
        if constexpr (P == glf::Program::Parameter::ActiveAtomicCounterBuffers)            return static_cast<gl::uint32_t>(program_iv(program, P));
    }
    static auto                            get_program_pipeline_v(gl::handle_t pipeline, glf::Program::Pipeline::Property property)
    {
        gl::int32_t value{};
        glGetProgramPipelineiv(std::to_underlying(pipeline), std::to_underlying(property), &value);

        return static_cast<gl::uint32_t>(value);
    }

    //(actually [7.13])
    template<glf::Program::StageProperty P>
    static auto                            get_program_stage_v(gl::handle_t program, glf::Shader::Type type)
    {
        gl::int32_t value{};
        glGetProgramStageiv(std::to_underlying(program), std::to_underlying(type), std::to_underlying(P), &value);

        return static_cast<gl::uint32_t>(value);
    }

    //Shader Objects [7.1]
    static gl::handle_t                    create_shader(glf::Shader::Type type)
    {
        gl::uint32_t shader{};
        shader = glCreateShader(std::to_underlying(type));

        return gl::handle_t{ shader };
    }
    static void                            shader_source(gl::handle_t shader, const std::string& source)
    {
        const auto* cstr = source.c_str();
        glShaderSource(std::to_underlying(shader), gl::size_t{ 1 }, &cstr, nullptr);
    }
    static void                            compile_shader(gl::handle_t shader)
    {
        glCompileShader(std::to_underlying(shader));
    }
    static void                            release_shader_compiler()
    {
        glReleaseShaderCompiler();
    }
    static void                            delete_shader(gl::handle_t shader)
    {
        if (shader == gl::NullObject) return;

        glDeleteShader(std::to_underlying(shader));
    }
    static void                            shader_binary(gl::handle_t shader, std::span<const gl::byte_t> binary)
    {
        const auto& uv = std::to_underlying(shader);
        glShaderBinary(gl::size_t{ 1 }, &uv, GL_SHADER_BINARY_FORMAT_SPIR_V, binary.data(), static_cast<gl::size_t>(binary.size_bytes()));
    }
    template<fox::uint32_t N = 0>
    static void                            specialize_shader(gl::handle_t shader, const std::string& entry, std::span<const gl::uint32_t, N> indices = {}, std::span<const gl::uint32_t, N> values = {})
    {
        const auto* cstr = entry.c_str();
        glSpecializeShader(std::to_underlying(shader), cstr, N, indices.data(), values.data());
    }
    //Program Objects [7.3]
    static gl::handle_t                    create_program()
    {
        return gl::handle_t{ glCreateProgram() };
    }
    static void                            attach_shader(gl::handle_t program, gl::handle_t shader)
    {
        glAttachShader(std::to_underlying(program), std::to_underlying(shader));
    }
    static void                            detach_shader(gl::handle_t program, gl::handle_t shader)
    {
        glDetachShader(std::to_underlying(program), std::to_underlying(shader));
    }
    static void                            link_program(gl::handle_t program)
    {
        glLinkProgram(std::to_underlying(program));
    }
    static gl::handle_t                    create_shader_program(glf::Shader::Type type, const std::string& source)
    {
        const auto* cstr = source.c_str();
        return gl::handle_t{ glCreateShaderProgramv(std::to_underlying(type), gl::size_t{ 1 }, &cstr) };
    }
    static void                            program_specification(gl::handle_t program, glf::Program::Specification specification, gl::bool_t value)
    {
        glProgramParameteri(std::to_underlying(program), std::to_underlying(specification), value);
    }
    static void                            delete_program(gl::handle_t program)
    {
        if (program == gl::NullObject) return;

        glDeleteProgram(std::to_underlying(program));
    }
    //Program Interfaces [7.3.1]
    template<glf::Program::Interface I, glf::Program::Property P>
    static auto                            get_program_interface_v(gl::handle_t program)
    {
        const auto& get_program_interface_iv = [](gl::handle_t program, glf::Program::Interface interface, glf::Program::Property property) -> gl::int32_t
            {
                gl::int32_t value{};
                glGetProgramInterfaceiv(std::to_underlying(program), std::to_underlying(interface), std::to_underlying(property), &value);

                return value;
            };

        if constexpr (
            P == glf::Program::Property::ActiveResources                               ) return get_program_interface_iv(program, I, P);
        if constexpr (
            P == glf::Program::Property::MaximumNameLength                            && (
                I != glf::Program::Interface::AtomicCounterBuffer                     ||
                I != glf::Program::Interface::TransformFeedbackBuffer                 )) return get_program_interface_iv(program, I, P);
        if constexpr (
            P == glf::Program::Property::MaximumNumberActiveVariables                 && (
                I == glf::Program::Interface::AtomicCounterBuffer                     ||
                I == glf::Program::Interface::UniformBlock                            || 
                I == glf::Program::Interface::ShaderStorageBlock                      ||
                I == glf::Program::Interface::TransformFeedbackBuffer                 )) return get_program_interface_iv(program, I, P);
        if constexpr (
            P == glf::Program::Property::MaximumNumberCompatibleSubroutines           && (
                I == glf::Program::Interface::VertexSubroutineUniform                 || 
                I == glf::Program::Interface::TessellationControlSubroutineUniform    ||
                I == glf::Program::Interface::TessellationEvaluationSubroutineUniform ||
                I == glf::Program::Interface::GeometrySubroutineUniform               ||
                I == glf::Program::Interface::FragmentSubroutineUniform               ||
                I == glf::Program::Interface::ComputeSubroutineUniform                ||
                I == glf::Program::Interface::ShaderStorageBlock                      )) return get_program_interface_iv(program, I, P);
        else
        {
            return get_program_interface_iv(program, I, P);
        }
    }
    template<glf::Program::Interface I>
    static auto                            get_program_resource_index(gl::handle_t program, const std::string& identifier)
    {
        if constexpr (
            I != glf::Program::Interface::AtomicCounterBuffer &&
            I != glf::Program::Interface::TransformFeedbackBuffer)
        {
            const auto* cstr = identifier.c_str();
            gl::uint32_t value = glGetProgramResourceIndex(std::to_underlying(program), std::to_underlying(I), cstr);

            return value;
        }
    }
    template<glf::Program::Interface I>
    static auto                            get_program_resource_name(gl::handle_t program, gl::uint32_t index)
    {
        if constexpr (
            I != glf::Program::Interface::AtomicCounterBuffer     &&
            I != glf::Program::Interface::TransformFeedbackBuffer  )
        {
            const auto& maximumLength = gl::get_program_interface_v<I, glf::Program::Property::MaximumNameLength>();

            std::string name{};
            gl::size_t  length{};

            name.resize(maximumLength);

            glGetProgramResourceName(std::to_underlying(program), std::to_underlying(I), index, maximumLength, &length, name.data());

            if (length < maximumLength) name.resize(static_cast<fox::size_t>(length) - 1u);
            return name;
        }
    }
    template<glf::Program::Interface I, glf::Program::Resource... R>
    static auto                            get_program_resource_v(gl::handle_t program, gl::uint32_t index)
    {
        static_assert(sizeof...(R) > 0, "At least one resource must be queried!");
        
        constexpr auto is_supported_resource = []<glf::Program::Interface I, glf::Program::Resource R>() -> gl::bool_t
        {
            if constexpr (
                R == glf::Program::Resource::NameLength                                   && (
                    I != glf::Program::Interface::AtomicCounterBuffer                     &&
                    I != glf::Program::Interface::TransformFeedbackBuffer                 )) return gl::True;
            if constexpr (                                                                
                R == glf::Program::Resource::Type                                         && (
                    I == glf::Program::Interface::Uniform                                 ||
                    I == glf::Program::Interface::ProgramInput                            ||
                    I == glf::Program::Interface::ProgramOutput                           ||
                    I == glf::Program::Interface::TransformFeedbackVarying                ||
                    I == glf::Program::Interface::BufferVariable                          )) return gl::True;
            if constexpr (
                R == glf::Program::Resource::ArraySize                                    && (
                    I == glf::Program::Interface::Uniform                                 ||
                    I == glf::Program::Interface::BufferVariable                          ||
                    I == glf::Program::Interface::ProgramInput                            ||
                    I == glf::Program::Interface::ProgramOutput                           ||
                    I == glf::Program::Interface::VertexSubroutineUniform                 ||
                    I == glf::Program::Interface::TessellationControlSubroutineUniform    ||
                    I == glf::Program::Interface::TessellationEvaluationSubroutineUniform ||
                    I == glf::Program::Interface::GeometrySubroutineUniform               ||
                    I == glf::Program::Interface::FragmentSubroutineUniform               ||
                    I == glf::Program::Interface::ComputeSubroutineUniform                ||
                    I == glf::Program::Interface::TransformFeedbackVarying                )) return gl::True;
            if constexpr (
                R == glf::Program::Resource::Offset                                       && (
                    I == glf::Program::Interface::Uniform                                 ||
                    I == glf::Program::Interface::BufferVariable                          ||
                    I == glf::Program::Interface::TransformFeedbackVarying                )) return gl::True;
            if constexpr (                                                                
                R == glf::Program::Resource::BlockIndex                                   && (
                    I == glf::Program::Interface::Uniform                                 ||
                    I == glf::Program::Interface::BufferVariable                          )) return gl::True;
            if constexpr (                                                                
                R == glf::Program::Resource::ArrayStride                                  && (
                    I == glf::Program::Interface::Uniform                                 ||
                    I == glf::Program::Interface::BufferVariable                          )) return gl::True;
            if constexpr (                                                                
                R == glf::Program::Resource::MatrixStride                                 && (
                    I == glf::Program::Interface::Uniform                                 ||
                    I == glf::Program::Interface::BufferVariable                          )) return gl::True;
            if constexpr (                                                                
                R == glf::Program::Resource::IsRowMajor                                   && (
                    I == glf::Program::Interface::Uniform                                 ||
                    I == glf::Program::Interface::BufferVariable                          )) return gl::True;
            if constexpr (                                                                
                R == glf::Program::Resource::AtomicCounterBufferIndex                     && (
                    I == glf::Program::Interface::Uniform                                 )) return gl::True;
            if constexpr (
                R == glf::Program::Resource::TextureBuffer)                                  return gl::False;
            if constexpr (
                R == glf::Program::Resource::BufferBinding                                && (
                    I == glf::Program::Interface::UniformBlock                            ||
                    I == glf::Program::Interface::AtomicCounterBuffer                     ||
                    I == glf::Program::Interface::ShaderStorageBlock                      ||
                    I == glf::Program::Interface::TransformFeedbackBuffer                 )) return gl::True;
            if constexpr (
                R == glf::Program::Resource::BufferDataSize                               && (
                    I == glf::Program::Interface::UniformBlock                            ||
                    I == glf::Program::Interface::AtomicCounterBuffer                     ||
                    I == glf::Program::Interface::ShaderStorageBlock                      )) return gl::True;
            if constexpr (
                R == glf::Program::Resource::NumberActiveVariables                        && (
                    I == glf::Program::Interface::UniformBlock                            ||
                    I == glf::Program::Interface::AtomicCounterBuffer                     ||
                    I == glf::Program::Interface::ShaderStorageBlock                      ||
                    I == glf::Program::Interface::TransformFeedbackBuffer                 )) return gl::True;
            if constexpr (
                R == glf::Program::Resource::ActiveVariables                              && (
                    I == glf::Program::Interface::UniformBlock                            ||
                    I == glf::Program::Interface::AtomicCounterBuffer                     ||
                    I == glf::Program::Interface::ShaderStorageBlock                      ||
                    I == glf::Program::Interface::TransformFeedbackBuffer                 )) return gl::True;
            if constexpr (
                R == glf::Program::Resource::ReferencedByVertexShader                     && (
                    I == glf::Program::Interface::Uniform                                 ||
                    I == glf::Program::Interface::UniformBlock                            ||
                    I == glf::Program::Interface::AtomicCounterBuffer                     ||
                    I == glf::Program::Interface::ShaderStorageBlock                      ||
                    I == glf::Program::Interface::BufferVariable                          ||
                    I == glf::Program::Interface::ProgramInput                            ||
                    I == glf::Program::Interface::ProgramOutput                           )) return gl::True;
            if constexpr (
                R == glf::Program::Resource::ReferencedByTessellationControlShader        && (
                    I == glf::Program::Interface::Uniform                                 ||
                    I == glf::Program::Interface::UniformBlock                            ||
                    I == glf::Program::Interface::AtomicCounterBuffer                     ||
                    I == glf::Program::Interface::ShaderStorageBlock                      ||
                    I == glf::Program::Interface::BufferVariable                          ||
                    I == glf::Program::Interface::ProgramInput                            ||
                    I == glf::Program::Interface::ProgramOutput                           )) return gl::True;
            if constexpr (
                R == glf::Program::Resource::ReferencedByTessellationEvaluationShader     && (
                    I == glf::Program::Interface::Uniform                                 ||
                    I == glf::Program::Interface::UniformBlock                            ||
                    I == glf::Program::Interface::AtomicCounterBuffer                     ||
                    I == glf::Program::Interface::ShaderStorageBlock                      ||
                    I == glf::Program::Interface::BufferVariable                          ||
                    I == glf::Program::Interface::ProgramInput                            ||
                    I == glf::Program::Interface::ProgramOutput                           )) return gl::True;
            if constexpr (
                R == glf::Program::Resource::ReferencedByGeometryShader                   && (
                    I == glf::Program::Interface::Uniform                                 ||
                    I == glf::Program::Interface::UniformBlock                            ||
                    I == glf::Program::Interface::AtomicCounterBuffer                     ||
                    I == glf::Program::Interface::ShaderStorageBlock                      ||
                    I == glf::Program::Interface::BufferVariable                          ||
                    I == glf::Program::Interface::ProgramInput                            ||
                    I == glf::Program::Interface::ProgramOutput                           )) return gl::True;
            if constexpr (
                R == glf::Program::Resource::ReferencedByFragmentShader                   && (
                    I == glf::Program::Interface::Uniform                                 ||
                    I == glf::Program::Interface::UniformBlock                            ||
                    I == glf::Program::Interface::AtomicCounterBuffer                     ||
                    I == glf::Program::Interface::ShaderStorageBlock                      ||
                    I == glf::Program::Interface::BufferVariable                          ||
                    I == glf::Program::Interface::ProgramInput                            ||
                    I == glf::Program::Interface::ProgramOutput                           )) return gl::True;
            if constexpr (
                R == glf::Program::Resource::ReferencedByComputeShader                    && (
                    I == glf::Program::Interface::Uniform                                 ||
                    I == glf::Program::Interface::UniformBlock                            ||
                    I == glf::Program::Interface::AtomicCounterBuffer                     ||
                    I == glf::Program::Interface::ShaderStorageBlock                      ||
                    I == glf::Program::Interface::BufferVariable                          ||
                    I == glf::Program::Interface::ProgramInput                            ||
                    I == glf::Program::Interface::ProgramOutput                           )) return gl::True;
            if constexpr (
                R == glf::Program::Resource::NumberCompatibleSubroutines                  && (
                    I == glf::Program::Interface::VertexSubroutineUniform                 ||
                    I == glf::Program::Interface::TessellationControlSubroutineUniform    ||
                    I == glf::Program::Interface::TessellationEvaluationSubroutineUniform ||
                    I == glf::Program::Interface::GeometrySubroutineUniform               ||
                    I == glf::Program::Interface::FragmentSubroutineUniform               ||
                    I == glf::Program::Interface::ComputeSubroutineUniform                )) return gl::True;
            if constexpr (
                R == glf::Program::Resource::CompatibleSubroutines                        && (
                    I == glf::Program::Interface::VertexSubroutineUniform                 ||
                    I == glf::Program::Interface::TessellationControlSubroutineUniform    ||
                    I == glf::Program::Interface::TessellationEvaluationSubroutineUniform ||
                    I == glf::Program::Interface::GeometrySubroutineUniform               ||
                    I == glf::Program::Interface::FragmentSubroutineUniform               ||
                    I == glf::Program::Interface::ComputeSubroutineUniform                )) return gl::True;
            if constexpr (
                R == glf::Program::Resource::TopLevelArraySize                            && (
                    I == glf::Program::Interface::BufferVariable                          )) return gl::True;
            if constexpr (
                R == glf::Program::Resource::TopLevelArrayStride                          && (
                    I == glf::Program::Interface::BufferVariable                          )) return gl::True;
            if constexpr (
                R == glf::Program::Resource::Location && (
                    I == glf::Program::Interface::Uniform                                 ||
                    I == glf::Program::Interface::ProgramInput                            ||
                    I == glf::Program::Interface::ProgramOutput                           ||
                    I == glf::Program::Interface::VertexSubroutineUniform                 ||
                    I == glf::Program::Interface::TessellationControlSubroutineUniform    ||
                    I == glf::Program::Interface::TessellationEvaluationSubroutineUniform ||
                    I == glf::Program::Interface::GeometrySubroutineUniform               ||
                    I == glf::Program::Interface::FragmentSubroutineUniform               ||
                    I == glf::Program::Interface::ComputeSubroutineUniform                )) return gl::True;
            if constexpr (
                R == glf::Program::Resource::LocationIndex                                && (
                    I == glf::Program::Interface::ProgramOutput                           )) return gl::True;
            if constexpr (
                R == glf::Program::Resource::IsPerPatch                                   && (
                    I == glf::Program::Interface::ProgramInput                            ||
                    I == glf::Program::Interface::ProgramOutput                           )) return gl::True;
            if constexpr (
                R == glf::Program::Resource::LocationComponent                            && (
                    I == glf::Program::Interface::ProgramInput                            ||
                    I == glf::Program::Interface::ProgramOutput                           )) return gl::True;
            if constexpr (
                R == glf::Program::Resource::TransformFeedbackBufferIndex                 && (
                    I == glf::Program::Interface::TransformFeedbackVarying                )) return gl::True;
            if constexpr (
                R == glf::Program::Resource::TransformFeedbackBufferStride                && (
                    I == glf::Program::Interface::TransformFeedbackBuffer                 )) return gl::True;

            else                                                                             return gl::False;
        };
        if constexpr ((is_supported_resource.template operator()<I, R>() && ...))
        {
            constexpr auto resourceCount = sizeof...(R);
            constexpr std::array<gl::enum_t,  resourceCount> resources{ std::to_underlying(R)... };
                      std::array<gl::int32_t, resourceCount> values{};
     
            glGetProgramResourceiv(
                std::to_underlying(program), 
                std::to_underlying(I), 
                index, 
                static_cast<gl::size_t>(resources.size()),          resources.data(), 
                static_cast<gl::size_t>(values.size()),    nullptr, values.data());

            return values;
        }
    }
    template<glf::Program::Interface I>
    static auto                            get_program_resource_location(gl::handle_t program, const std::string& identifier)
    {
        if constexpr (
            I == glf::Program::Interface::Uniform ||
            I == glf::Program::Interface::ProgramInput ||
            I == glf::Program::Interface::ProgramOutput ||
            I == glf::Program::Interface::VertexSubroutineUniform ||
            I == glf::Program::Interface::TessellationControlSubroutineUniform ||
            I == glf::Program::Interface::TessellationEvaluationSubroutineUniform ||
            I == glf::Program::Interface::GeometrySubroutineUniform ||
            I == glf::Program::Interface::FragmentSubroutineUniform ||
            I == glf::Program::Interface::ComputeSubroutineUniform ||
            I == glf::Program::Interface::TransformFeedbackBuffer)
        {
            const auto* cstr = identifier.c_str();
            gl::int32_t value = glGetProgramResourceLocation(std::to_underlying(program), std::to_underlying(I), cstr);

            if (value == -1) throw std::invalid_argument{ "Identifier does not match an active variable or does not have a valid location assigned!" };

            return value;
        }
    }
    static auto                            get_program_resource_location_index(gl::handle_t program, const std::string& identifier)
    {
        const auto* cstr = identifier.c_str();
        gl::int32_t value = glGetProgramResourceLocationIndex(std::to_underlying(program), std::to_underlying(glf::Program::Interface::ProgramOutput), cstr);

        if (value == -1) throw std::invalid_argument{ "Identifier does not match an active variable or does not have a valid location assigned!" };

        return value;
    }
    //Program Pipeline Objects [7.4]
    static gl::handle_t                    create_program_pipeline()
    {
        gl::uint32_t pipeline{};
        glCreateProgramPipelines(gl::size_t{ 1 }, &pipeline);

        return gl::handle_t{ pipeline };
    }
    static void                            delete_program_pipeline(gl::handle_t pipeline)
    {
        if (pipeline == gl::NullObject) return;

        const auto& uv = std::to_underlying(pipeline);
        glDeleteProgramPipelines(gl::size_t{ 1 }, &uv);
    }
    static void                            bind_program_pipeline(gl::handle_t pipeline)
    {
        glBindProgramPipeline(std::to_underlying(pipeline));
    }
    static void                            use_program_stages(gl::handle_t pipeline, gl::handle_t program, glf::Program::Stage stages)
    {
        glUseProgramStages(std::to_underlying(pipeline), std::to_underlying(stages), std::to_underlying(program));
    }
    static void                            active_shader_program(gl::handle_t pipeline, gl::handle_t program)
    {
        glActiveShaderProgram(std::to_underlying(pipeline), std::to_underlying(program));
    }
    //Program Binaries [7.5]
    static auto                            get_program_binary(gl::handle_t program)
    {
        gl::enum_t               format{};
        std::vector<gl::uint8_t> binary{};

        const auto& binaryLength = gl::get_program_v<glf::Program::Parameter::BinaryLength>(program);
        binary.resize(binaryLength);

        glGetProgramBinary(std::to_underlying(program), binaryLength, nullptr, &format, binary.data());

        return std::make_tuple(binary, gl::format_t{ format });
    }
    static void                            program_binary(gl::handle_t program, gl::format_t format, std::span<const gl::uint8_t> binary)
    {
        glProgramBinary(std::to_underlying(program), std::to_underlying(format), binary.data(), static_cast<gl::size_t>(binary.size()));
    }
    //Uniform Variables [7.6]
    static auto                            get_uniform_location(gl::handle_t program, const std::string& identifier)
    {
        const auto* cstr = identifier.c_str();
        gl::int32_t value = glGetUniformLocation(std::to_underlying(program), cstr);

        if (value == -1) throw std::invalid_argument{ "Identifier does not correspond to an active uniform variable!" };

        return value;
    }
    static auto                            get_active_uniform_name(gl::handle_t program, gl::uint32_t index)
    {
        const auto& maximumLength = gl::get_program_v<glf::Program::Parameter::ActiveUniformMaximumLength>(program);

        std::string name{};
        gl::size_t  length{};

        name.resize(maximumLength);

        glGetActiveUniformName(std::to_underlying(program), index, maximumLength, &length, name.data());

        if (length == 0)                          throw std::invalid_argument{ "Identifier does not correspond to an active uniform name!" };
        if (std::cmp_less(length, maximumLength)) name.resize(static_cast<fox::size_t>(length) - 1u);

        return name;
    }
    static auto                            get_uniform_indices(gl::handle_t program, gl::size_t count, std::span<const std::string> identifiers)
    {
        std::vector<const gl::char_t*> cstrs{};
        std::vector<gl::uint32_t>      values{};

        cstrs.resize(identifiers.size());
        values.reserve(identifiers.size());

        std::transform(identifiers.begin(), identifiers.end(), cstrs.begin(), [](const std::string& _) -> const gl::char_t*
            {
                return _.c_str();
            });
        glGetUniformIndices(std::to_underlying(program), count, cstrs.data(), values.data());

        std::ranges::for_each(values, [](gl::uint32_t value)
            {
                if (value == std::to_underlying(glf::Error::Sentinel::InvalidIndex)) throw std::invalid_argument{ "Identifier does not correspond to an active uniform name!" };
            });

        return values;
    }
    static auto                            get_active_uniform(gl::handle_t program, gl::uint32_t index)
    {
        const auto& maximumLength = gl::get_program_v<glf::Program::Parameter::ActiveUniformMaximumLength>(program);

        std::string name{};
        gl::enum_t  type{};
        gl::size_t  size{};
        gl::size_t  length{};

        name.resize(maximumLength);

        glGetActiveUniform(std::to_underlying(program), index, maximumLength, &length, &size, &type, name.data());

        if (std::cmp_less(length, maximumLength)) name.resize(static_cast<fox::size_t>(length) - 1u);

        return std::make_tuple(name, type);
    }
    template<glf::Uniform::Property P, fox::uint32_t N>
    static auto                            get_active_uniforms_v(gl::handle_t program, std::span<const gl::uint32_t, N> indices)
    {
        const auto& get_active_uniforms_iv               = [](gl::handle_t program, glf::Uniform::Property property, std::span<gl::uint32_t, N> indices) -> std::array<gl::int32_t, N>
            {
                std::array<gl::int32_t, N> values{};
                glGetActiveUniformsiv(std::to_underlying(program), static_cast<gl::size_t>(indices.size()), indices.data(), std::to_underlying(property), values.data());

                return values;
            };
        const auto& get_active_uniforms_iv_and_transform = [get_active_uniforms_iv]<typename T>(gl::handle_t program, glf::Uniform::Property property, std::span<gl::uint32_t, N> indices) -> std::array<T, N>
            {
                auto values = get_active_uniforms_iv(program, P, indices);
                std::array<T, N> results{};

                std::transform(values.begin(), values.end(), results.begin(), [](auto _)
                    {
                        return static_cast<T>(_);
                    });

                return results;
            };

        if constexpr (P == glf::Uniform::Property::Type)                     return get_active_uniforms_iv_and_transform.template operator()<glf::Uniform::Type>(program, P, indices);
        if constexpr (P == glf::Uniform::Property::Size)                     return get_active_uniforms_iv_and_transform.template operator()<gl::uint32_t>(program, P, indices);
        if constexpr (P == glf::Uniform::Property::NameLength)               return get_active_uniforms_iv_and_transform.template operator()<gl::uint32_t>(program, P, indices);
        if constexpr (P == glf::Uniform::Property::BlockIndex)               return get_active_uniforms_iv(program, P, indices);
        if constexpr (P == glf::Uniform::Property::Offset)                   return get_active_uniforms_iv(program, P, indices);
        if constexpr (P == glf::Uniform::Property::ArrayStride)              return get_active_uniforms_iv(program, P, indices);
        if constexpr (P == glf::Uniform::Property::MatrixStride)             return get_active_uniforms_iv(program, P, indices);
        if constexpr (P == glf::Uniform::Property::IsRowMajor)               return get_active_uniforms_iv_and_transform.template operator()<gl::bool_t>(program, P, indices);
        if constexpr (P == glf::Uniform::Property::AtomicCounterBufferIndex) return get_active_uniforms_iv_and_transform.template operator()<gl::uint32_t>(program, P, indices);
    }
    static auto                            get_uniform_block_index(gl::handle_t program, const std::string& identifier)
    {
        const auto& cstr = identifier.c_str();
        gl::uint32_t value = glGetUniformBlockIndex(std::to_underlying(program), cstr);

        if (value == std::to_underlying(glf::Error::Sentinel::InvalidIndex)) throw std::invalid_argument{ "Identifier does not identify an active uniform block!" };

        return value;
    }
    static auto                            get_active_uniform_block_name(gl::handle_t program, gl::uint32_t index)
    {
        const auto& numUniformBlocks = gl::get_program_v<glf::Program::Parameter::ActiveUniformBlocks>(program);
        const auto& maximumLength    = gl::get_program_interface_v<glf::Program::Interface::UniformBlock, glf::Program::Property::MaximumNameLength>(program);

        if (index >= numUniformBlocks) throw std::invalid_argument{ "Index is greater than the amount of uniform blocks!" };

        std::string name{};
        gl::size_t  length{};

        name.resize(maximumLength);

        glGetActiveUniformBlockName(std::to_underlying(program), index, maximumLength, &length, name.data());

        if (length ==         0) throw std::invalid_argument{ "A uniform block with the given index does not exist!" };
        if (length <  maximumLength) name.resize(static_cast<fox::size_t>(length) - 1u);

        return name;
    }
    template<glf::UniformBlock::Info I>
    static auto                            get_active_uniform_block_v(gl::handle_t program, gl::uint32_t index)
    {
        const auto& get_active_uniform_block_iv = [](gl::handle_t program, glf::UniformBlock::Info info, gl::uint32_t index)
            {
                gl::int32_t value{};
                glGetActiveUniformBlockiv(std::to_underlying(program), index, std::to_underlying(info), &value);

                return value;
            };

        const auto& numUniformBlocks = gl::get_program_v<glf::Program::Parameter::ActiveUniformBlocks>(program);
        if (index >= numUniformBlocks) throw std::invalid_argument{ "Index is greater than the amount of uniform blocks!" };

        if constexpr (I == glf::UniformBlock::Info::Binding)                                  return static_cast<gl::uint32_t>(get_active_uniform_block_iv(program, I, index));
        if constexpr (I == glf::UniformBlock::Info::DataSize)                                 return static_cast<gl::uint32_t>(get_active_uniform_block_iv(program, I, index));
        if constexpr (I == glf::UniformBlock::Info::NameLength)                               return static_cast<gl::uint32_t>(get_active_uniform_block_iv(program, I, index));
        if constexpr (I == glf::UniformBlock::Info::ActiveUniforms)                           return static_cast<gl::uint32_t>(get_active_uniform_block_iv(program, I, index));
        if constexpr (I == glf::UniformBlock::Info::ActiveUniformIndices)
        {
            const auto& activeUniforms = gl::get_active_uniform_block_v<glf::UniformBlock::Info::ActiveUniforms>(program, index);
            std::vector<gl::int32_t>  values{};
            std::vector<gl::uint32_t> results{};

            values.resize(activeUniforms);
            results.resize(activeUniforms);

            glGetActiveUniformBlockiv(std::to_underlying(program), index, std::to_underlying(I), values.data());

            std::transform(values.begin(), values.end(), results.begin(), [](auto _)
                {
                    return static_cast<gl::uint32_t>(_);
                });

            return results;
        }
        if constexpr (I == glf::UniformBlock::Info::ReferencedByVertexShader)                 return static_cast<gl::bool_t>(get_active_uniform_block_iv(program, I, index));
        if constexpr (I == glf::UniformBlock::Info::ReferencedByTessellationControlShader)    return static_cast<gl::bool_t>(get_active_uniform_block_iv(program, I, index));
        if constexpr (I == glf::UniformBlock::Info::ReferencedByTessellationEvaluationShader) return static_cast<gl::bool_t>(get_active_uniform_block_iv(program, I, index));
        if constexpr (I == glf::UniformBlock::Info::ReferencedByGeometryShader)               return static_cast<gl::bool_t>(get_active_uniform_block_iv(program, I, index));
        if constexpr (I == glf::UniformBlock::Info::ReferencedByFragmentShader)               return static_cast<gl::bool_t>(get_active_uniform_block_iv(program, I, index));
        if constexpr (I == glf::UniformBlock::Info::ReferencedByComputeShader)                return static_cast<gl::bool_t>(get_active_uniform_block_iv(program, I, index));
    }
    template<glf::AtomicCounterBuffer::Info I>
    static auto                            get_active_atomic_counter_buffer_v(gl::handle_t program, gl::uint32_t index)
    {
        const auto& get_active_atomic_counter_buffer_iv = [](gl::handle_t program, glf::AtomicCounterBuffer::Info info, gl::uint32_t index)
            {
                gl::int32_t value{};
                glGetActiveAtomicCounterBufferiv(std::to_underlying(program), index, std::to_underlying(info), &value);

                return value;
            };

        const auto& numUniformBlocks = gl::get_program_v<glf::Program::Parameter::ActiveAtomicCounterBuffers>(program);
        if (index >= numUniformBlocks) throw std::invalid_argument{ "Index is greater than the amount of uniform blocks!" };

        if constexpr (I == glf::AtomicCounterBuffer::Info::Binding)                                  return static_cast<gl::uint32_t>(get_active_atomic_counter_buffer_iv(program, I, index));
        if constexpr (I == glf::AtomicCounterBuffer::Info::DataSize)                                 return static_cast<gl::uint32_t>(get_active_atomic_counter_buffer_iv(program, I, index));
        if constexpr (I == glf::AtomicCounterBuffer::Info::ActiveAtomicCounters)                     return static_cast<gl::uint32_t>(get_active_atomic_counter_buffer_iv(program, I, index));
        if constexpr (I == glf::AtomicCounterBuffer::Info::ActiveAtomicCounterIndices)               return static_cast<gl::uint32_t>(get_active_atomic_counter_buffer_iv(program, I, index));
        if constexpr (I == glf::AtomicCounterBuffer::Info::ReferencedByVertexShader)                 return static_cast<gl::bool_t>(get_active_atomic_counter_buffer_iv(program, I, index));
        if constexpr (I == glf::AtomicCounterBuffer::Info::ReferencedByTessellationControlShader)    return static_cast<gl::bool_t>(get_active_atomic_counter_buffer_iv(program, I, index));
        if constexpr (I == glf::AtomicCounterBuffer::Info::ReferencedByTessellationEvaluationShader) return static_cast<gl::bool_t>(get_active_atomic_counter_buffer_iv(program, I, index));
        if constexpr (I == glf::AtomicCounterBuffer::Info::ReferencedByGeometryShader)               return static_cast<gl::bool_t>(get_active_atomic_counter_buffer_iv(program, I, index));
        if constexpr (I == glf::AtomicCounterBuffer::Info::ReferencedByFragmentShader)               return static_cast<gl::bool_t>(get_active_atomic_counter_buffer_iv(program, I, index));
        if constexpr (I == glf::AtomicCounterBuffer::Info::ReferencedByComputeShader)                return static_cast<gl::bool_t>(get_active_atomic_counter_buffer_iv(program, I, index));
    }
    static void                            uniform_block_binding(gl::handle_t program, gl::uint32_t index, gl::uint32_t binding)
    {
        glUniformBlockBinding(std::to_underlying(program), index, binding);
    }
    //Shader Buffer Variables and Shader Storage Blocks [7.8]
    static void                            shader_storage_block_binding(gl::handle_t program, gl::uint32_t index, gl::uint32_t binding)
    {
        glShaderStorageBlockBinding(std::to_underlying(program), index, binding);
    }
    //Invocation Groups [7.9]
    static auto                            get_subroutine_uniform_location(gl::handle_t program, glf::Shader::Type type, const std::string& identifier)
    {
        const auto* cstr = identifier.c_str();
        gl::int32_t value = glGetSubroutineUniformLocation(std::to_underlying(program), std::to_underlying(type), cstr);

        return value;
    }
    static auto                            get_subroutine_index(gl::handle_t program, glf::Shader::Type type, const std::string& identifier)
    {
        const auto* cstr = identifier.c_str();
        gl::uint32_t value = glGetSubroutineIndex(std::to_underlying(program), std::to_underlying(type), cstr);

        return value;
    }
    static auto                            get_active_subroutine_name(gl::handle_t program, glf::Shader::Type type, gl::uint32_t index)
    {
        const auto& maximumSize = gl::get_program_stage_v<glf::Program::StageProperty::ActiveSubroutineMaximumLength>(program, type);

        std::string name{};
        gl::size_t  length{};

        name.resize(maximumSize);

        glGetActiveSubroutineName(std::to_underlying(program), std::to_underlying(type), index, maximumSize, &length, name.data());

        if (std::cmp_less(length, maximumSize)) name.resize(static_cast<fox::size_t>(length) - 1u);

        return name;
    }
    static auto                            get_active_subroutine_uniform_name(gl::handle_t program, glf::Shader::Type type, gl::uint32_t index)
    {
        const auto& maximumSize = gl::get_program_stage_v<glf::Program::StageProperty::ActiveSubroutineUniformMaximumLength>(program, type);

        std::string name{};
        gl::size_t  length{};

        name.resize(maximumSize);

        glGetActiveSubroutineUniformName(std::to_underlying(program), std::to_underlying(type), index, maximumSize, &length, name.data());

        if (std::cmp_less(length, maximumSize)) name.resize(static_cast<fox::size_t>(length) - 1u);

        return name;
    }
    template<glf::Shader::SubroutineParameter P>
    static auto                            get_active_subroutine_uniform_v(gl::handle_t program, glf::Shader::Type type, gl::uint32_t index)
    {
        const auto& uv = std::to_underlying(P);

        if constexpr (
            P == glf::Shader::SubroutineParameter::NumberCompatibleSubroutines ||
            P == glf::Shader::SubroutineParameter::UniformSize                 ||
            P == glf::Shader::SubroutineParameter::UniformNameLength            )
        {
            gl::int32_t value{};
            glGetActiveSubroutineUniformiv(std::to_underlying(program), std::to_underlying(type), index, uv, &value);

            return static_cast<gl::uint32_t>(value);
        }
        if constexpr (P == glf::Shader::SubroutineParameter::CompatibleSubroutines)
        {
            const auto& numberCompatibleSubroutines = gl::get_active_subroutine_uniform_v<glf::Shader::SubroutineParameter::NumberCompatibleSubroutines>(program, type, index);

            std::vector<gl::uint32_t> value{};

            value.resize(numberCompatibleSubroutines);

            glGetActiveSubroutineUniformiv(std::to_underlying(program), std::to_underlying(type), index, uv, value.data());

            return value;
        }
    }
    static auto                            uniform_subroutines_v(glf::Shader::Type type, std::span<const gl::uint32_t> indices)
    {
        glUniformSubroutinesuiv(std::to_underlying(type), static_cast<gl::size_t>(indices.size()), indices.data());
    }
    //Shader Memory Access [7.13]
    static void                            memory_barrier(glf::Memory::Barrier barrier)
    {
        glMemoryBarrier(std::to_underlying(barrier));
    }
    static void                            memory_barrier_by_region(glf::Memory::RegionalBarrier barrier)
    {
        glMemoryBarrierByRegion(std::to_underlying(barrier));
    }
    //Shader, Program, and Program Pipeline Queries [7.14]
    static auto                            get_attached_shaders(gl::handle_t program)
    {
        const auto& shaderCount = gl::get_program_v<glf::Program::Parameter::AttachedShaders>(program);

        gl::size_t                count{};
        std::vector<gl::uint32_t> shaders{};

        shaders.resize(shaderCount);

        glGetAttachedShaders(std::to_underlying(program), shaderCount, &count, shaders.data());

        return shaders;
    }
    static auto                            shader_info_log(gl::handle_t shader)
    {
        const auto& length = get_shader_v<glf::Shader::Parameter::InfoLogLength>(shader);

        std::string log{};

        log.resize(length);

        glGetShaderInfoLog(std::to_underlying(shader), length, nullptr, log.data());

        if (not log.empty()) log.resize(log.size() - 1u);

        return log;
    }
    static auto                            program_info_log(gl::handle_t program)
    {
        const auto& length = gl::get_program_v<glf::Program::Parameter::InfoLogLength>(program);

        std::string log{};

        log.resize(length);

        glGetProgramInfoLog(std::to_underlying(program), length, nullptr, log.data());

        if (not log.empty()) log.resize(log.size() - 1u);

        return log;
    }
    static auto                            pipeline_info_log(gl::handle_t pipeline)
    {
        const auto& length = gl::get_program_pipeline_v(pipeline, glf::Program::Pipeline::Property::InfoLogLength);

        std::string log{};

        log.resize(length);

        glGetProgramPipelineInfoLog(std::to_underlying(pipeline), length, nullptr, log.data());

        if (not log.empty()) log.resize(log.size() - 1u);

        return log;
    }
    static auto                            get_shader_source(gl::handle_t shader)
    {
        const auto& length = gl::get_shader_v<glf::Shader::Parameter::SourceLength>(shader);

        std::string source{};

        source.resize(length);

        glGetShaderSource(std::to_underlying(shader), length, nullptr, source.data());

        if (not source.empty()) source.resize(source.size() - 1u);

        return source;
    }
    template<glf::Shader::Type T>
    static auto                            get_shader_precision_format(glf::Shader::PrecisionFormat format)
    {
        if constexpr (
            T == glf::Shader::Type::Vertex   ||
            T == glf::Shader::Type::Fragment  )
        {
            std::array<gl::int32_t, 2> range{};
            gl::int32_t                precision{};

            glGetShaderPrecisionFormat(std::to_underlying(T), std::to_underlying(format), range.data(), &precision);

            return std::make_tuple(range, precision);
        }
    }
    template<glf::DataType D, gl::size_t C>
    static auto                            get_uniform_v(gl::handle_t program, gl::int32_t location)
    {
        const auto& uv = std::to_underlying(program);

        if constexpr (D == glf::DataType::Integer)
        {
            std::array<gl::int32_t, C> values{};

            glGetnUniformiv(uv, location, C, values.data());

            return values;
        }
        if constexpr (D == glf::DataType::UnsignedInteger)
        {
            std::array<gl::uint32_t, C> values{};

            glGetnUniformuiv(uv, location, C, values.data());

            return values;
        }
        if constexpr (D == glf::DataType::Float)
        {
            std::array<gl::float32_t, C> values{};

            glGetnUniformfv(uv, location, C, values.data());

            return values;
        }
        if constexpr (D == glf::DataType::Double)
        {
            std::array<gl::float64_t, C> values{};

            glGetnUniformdv(uv, location, C, values.data());

            return values;
        }
    }
    static auto                            get_uniform_subroutine_v(glf::Shader::Type type, gl::int32_t location)
    {
        gl::uint32_t value{};
        glGetUniformSubroutineuiv(std::to_underlying(type), location, &value);

        return value;
    }







    //[8.0.0] Textures and Samplers
    //[8.1.0] Texture Objects
    static gl::handle_t                   create_texture(glf::Texture::Target target)
    {
        gl::uint32_t handle{};
        glCreateTextures(std::to_underlying(target), 1, &handle);

        return gl::handle_t{ handle };
    }
    static void                           delete_texture(gl::handle_t texture)
    {
        if (texture == gl::NullObject) return;

        const auto& uv = std::to_underlying(texture);
        glDeleteTextures(1, &uv);
    }
    static void                           bind_texture_unit(gl::handle_t texture, gl::uint32_t unit)
    {
        glBindTextureUnit(static_cast<gl::uint32_t>(unit), static_cast<gl::uint32_t>(texture));
    }
    //[8.2.0] Sampler Objects
    static gl::handle_t                   create_sampler()
    {
        gl::uint32_t sampler{};
        glCreateSamplers(1, &sampler);

        return gl::handle_t{ sampler };
    }
    static void                           delete_sampler(gl::handle_t sampler)
    {
        if (sampler == gl::NullObject) return;

        const auto& uv = std::to_underlying(sampler);
        glDeleteSamplers(1, &uv);
    }
    static void                           bind_sampler(gl::handle_t sampler, gl::uint32_t slot)
    {
        glBindSampler(slot, static_cast<gl::uint32_t>(sampler));
    }
    //[8.3.0] Sampler Object Queries
    template<glf::Sampler::Parameter P>
    static void                           sampler_parameter(gl::handle_t sampler, glf::Sampler::Parameter parameter, std::span<const gl::int32_t> value)
    {
        throw std::logic_error{ "The method or operation has not been implemented!" };
    }
    template<glf::Sampler::Parameter P>
    static auto                           get_sampler_parameter_v(gl::handle_t sampler)
    {
        const auto& get_sampler_parameter_iv = [](gl::handle_t sampler, glf::Sampler::Parameter parameter)
            {
                gl::int32_t value{};
                glGetSamplerParameteriv(std::to_underlying(sampler), std::to_underlying(parameter), &value);

                return value;
            };
        const auto& get_sampler_parameter_fv = [](gl::handle_t sampler, glf::Sampler::Parameter parameter)
            {
                gl::float32_t value{};
                glGetSamplerParameterfv(std::to_underlying(sampler), std::to_underlying(parameter), &value);

                return value;
            };

        if constexpr (P == glf::Sampler::Parameter::BorderColor)
        {
            std::array<gl::float32_t, 4> values{};

            glGetSamplerParameterfv(std::to_underlying(sampler), std::to_underlying(P), values.data());

            return gl::Vector4f{ values.at(0), values.at(1), values.at(2), values.at(3) };
        }
        if constexpr (P == glf::Sampler::Parameter::CompareMode)         return glf::Texture::ComparisonMode{ get_sampler_parameter_iv(sampler, P) };
        if constexpr (P == glf::Sampler::Parameter::CompareFunction)     return glf::Texture::ComparisonFunction{ get_sampler_parameter_iv(sampler, P) };
        if constexpr (P == glf::Sampler::Parameter::MagnificationFilter) return glf::Texture::MagnificationFilter{ get_sampler_parameter_iv(sampler, P) };
        if constexpr (P == glf::Sampler::Parameter::MinificationFilter)  return glf::Texture::MinificationFilter{ get_sampler_parameter_iv(sampler, P) };
        if constexpr (P == glf::Sampler::Parameter::MaximumAnisotropy)   return get_sampler_parameter_fv(sampler, P);
        if constexpr (P == glf::Sampler::Parameter::LodBias)             return get_sampler_parameter_fv(sampler, P);
        if constexpr (P == glf::Sampler::Parameter::MinimumLod)          return get_sampler_parameter_fv(sampler, P);
        if constexpr (P == glf::Sampler::Parameter::MaximumLod)          return get_sampler_parameter_fv(sampler, P);
        if constexpr (
            P == glf::Sampler::Parameter::WrappingS ||
            P == glf::Sampler::Parameter::WrappingT ||
            P == glf::Sampler::Parameter::WrappingR  )                   return glf::Texture::Wrapping{ get_sampler_parameter_iv(sampler, P) };
    }
    //[8.4.0] Pixel Rectangles 
    //[8.4.1] Pixel Storage Modes and Pixel Buffer Objects
    static auto                           pixel_store(glf::PackingMode mode, gl::int32_t parameter)
    {
        glPixelStorei(std::to_underlying(mode), parameter);
    }
    //[8.6.0] Alternate Texture Image Specification Commands
    static void                           texture_sub_image_1d(gl::handle_t texture, glf::Texture::BaseFormat format, const gl::Vector1u& dimensions, const gl::Vector1u& offset, gl::uint32_t level, std::span<const gl::byte_t> data)
    {
        glTextureSubImage1D(
            std::to_underlying(texture),
            level,
            offset.x, 
            dimensions.x,
            std::to_underlying(format), GL_UNSIGNED_BYTE,
            data.data());
    }
    static void                           texture_sub_image_2d(gl::handle_t texture, glf::Texture::BaseFormat format, const gl::Vector2u& dimensions, const gl::Vector2u& offset, gl::uint32_t level, std::span<const gl::byte_t> data)
    {
        glTextureSubImage2D(
            std::to_underlying(texture),
            level,
            offset.x, offset.y,
            dimensions.x, dimensions.y,
            std::to_underlying(format), GL_UNSIGNED_BYTE,
            data.data());
    }
    static void                           texture_sub_image_3d(gl::handle_t texture, glf::Texture::BaseFormat format, const gl::Vector3u& dimensions, const gl::Vector3u& offset, gl::uint32_t level, std::span<const gl::byte_t> data)
    {
        glTextureSubImage3D(
            std::to_underlying(texture),
            level,
            offset.x, offset.y, offset.z,
            dimensions.x, dimensions.y, dimensions.z,
            std::to_underlying(format), GL_UNSIGNED_BYTE,
            data.data());
    }
    static void                           copy_texture_sub_image_1d(gl::handle_t texture, gl::uint32_t level, const gl::Vector1u& offset, const gl::Vector2u& target, const gl::Vector1u& dimensions)
    {
        glCopyTextureSubImage1D(
            std::to_underlying(texture),
            level, 
            offset.x,
            target.x,     target.y,
            dimensions.x);
    }
    static void                           copy_texture_sub_image_2d(gl::handle_t texture, gl::uint32_t level, const gl::Vector2u& offset, const gl::Vector2u& target, const gl::Vector2u& dimensions)
    {
        glCopyTextureSubImage2D(
            std::to_underlying(texture),
            level,
            offset.x,     offset.y,
            target.x,     target.y,
            dimensions.x, dimensions.y);
    }
    static void                           copy_texture_sub_image_3d(gl::handle_t texture, gl::uint32_t level, const gl::Vector3u& offset, const gl::Vector2u& target, const gl::Vector2u& dimensions)
    {
        glCopyTextureSubImage3D(
            std::to_underlying(texture),
            level,
            offset.x,     offset.y,     offset.z,
            target.x,     target.y,
            dimensions.x, dimensions.y);
    }
    //[8.7.0] Compressed Texture Images
    static void                           compressed_texture_sub_image_1d(gl::handle_t texture, glf::Texture::CompressedFormat format, gl::uint32_t level, const gl::Vector1u& dimensions, const gl::Vector1u& offset, std::span<const gl::byte_t> data)
    {
        glCompressedTextureSubImage1D(
            std::to_underlying(texture),
            level,
            offset.x, 
            dimensions.x, 
            std::to_underlying(format),
            static_cast<gl::size_t>(data.size()),  data.data());
    }
    static void                           compressed_texture_sub_image_2d(gl::handle_t texture, glf::Texture::CompressedFormat format, gl::uint32_t level, const gl::Vector2u& dimensions, const gl::Vector2u& offset, std::span<const gl::byte_t> data)
    {
        glCompressedTextureSubImage2D(
            std::to_underlying(texture), 
            level, 
            offset.x,     offset.y, 
            dimensions.x, dimensions.y, 
            std::to_underlying(format), 
            static_cast<gl::size_t>(data.size()),  data.data());
    }
    static void                           compressed_texture_sub_image_3d(gl::handle_t texture, glf::Texture::CompressedFormat format, gl::uint32_t level, const gl::Vector3u& dimensions, const gl::Vector3u& offset, std::span<const gl::byte_t> data)
    {
        glCompressedTextureSubImage3D(
            std::to_underlying(texture),
            level,
            offset.x,     offset.y,     offset.z,
            dimensions.x, dimensions.y, dimensions.z,
            std::to_underlying(format),
            static_cast<gl::size_t>(data.size()),  data.data());
    }
    //[8.9.0] Buffer Textures
    static void                           texture_buffer(gl::handle_t texture, gl::handle_t buffer, glf::Buffer::Format format)
    {
        glTextureBuffer(std::to_underlying(texture), std::to_underlying(format), std::to_underlying(buffer));
    }
    static void                           texture_buffer_range(gl::handle_t texture, gl::handle_t buffer, glf::Buffer::Format format, gl::sizeptr_t size, gl::intptr_t offset)
    {
        glTextureBufferRange(std::to_underlying(texture), std::to_underlying(format), std::to_underlying(buffer), offset, size);
    }
    //[8.10.0] Texture Parameters
    static void                           texture_parameter(gl::handle_t texture, glf::Texture::Parameter parameter, gl::TextureParameter value) //TODO: implement further
    {
        if (std::holds_alternative<glf::Texture::MinificationFilter>(value))
        {
            const auto& v = std::get<glf::Texture::MinificationFilter>(value);
            glTextureParameteri(static_cast<gl::uint32_t>(texture), static_cast<gl::enum_t>(parameter), std::to_underlying(v));

            return;
        }
        if (std::holds_alternative<glf::Texture::MagnificationFilter>(value))
        {
            const auto& v = std::get<glf::Texture::MagnificationFilter>(value);
            glTextureParameteri(static_cast<gl::uint32_t>(texture), static_cast<gl::enum_t>(parameter), std::to_underlying(v));

            return;
        }
        if (std::holds_alternative<glf::Texture::Wrapping>(value))
        {
            const auto& v = std::get<glf::Texture::Wrapping>(value);
            glTextureParameteri(static_cast<gl::uint32_t>(texture), static_cast<gl::enum_t>(parameter), std::to_underlying(v));

            return;
        }

        throw std::invalid_argument{ "Invalid Texture Parameter!" };
    }
    //[8.11.0] Texture Queries
    //TODO
    //[8.14.4] Manual Mipmap Generation
    static void                           generate_texture_mipmap(gl::handle_t texture)
    {
        glGenerateTextureMipmap(std::to_underlying(texture));
    }
    //[8.18.0] Texture Views
    static void texture_view(gl::handle_t source, gl::handle_t destination, gl::enum_t target, gl::enum_t format, const gl::Vector2u& levels, const gl::Vector2u& layers)
    {
        //TODO target and format checking
        glTextureView(std::to_underlying(destination), target, std::to_underlying(source), format, levels.x, levels.y, layers.x, layers.y);
    }
    //[8.19.0] Immutable-Format Texture Images
    static void                           texture_storage_1d(gl::handle_t texture, glf::Texture::Format format, const gl::Vector1u& dimensions, gl::size_t levels)
    {
        glTextureStorage1D(std::to_underlying(texture), levels, std::to_underlying(format), static_cast<gl::size_t>(dimensions.x));
    }
    static void                           texture_storage_2d(gl::handle_t texture, glf::Texture::Format format, const gl::Vector2u& dimensions, gl::size_t levels)
    {
        glTextureStorage2D(std::to_underlying(texture), levels, std::to_underlying(format), static_cast<gl::size_t>(dimensions.x), static_cast<gl::size_t>(dimensions.y));
    }
    static void                           texture_storage_3d(gl::handle_t texture, glf::Texture::Format format, const gl::Vector3u& dimensions, gl::size_t levels)
    {
        glTextureStorage3D(std::to_underlying(texture), levels, std::to_underlying(format), static_cast<gl::size_t>(dimensions.x), static_cast<gl::size_t>(dimensions.y), static_cast<gl::size_t>(dimensions.z));
    }
    static void                           texture_storage_2d_multisample(gl::handle_t texture, glf::Texture::Format format, const gl::Vector2u& dimensions, gl::size_t samples, gl::bool_t fixed = gl::True)
    {
        glTextureStorage2DMultisample(std::to_underlying(texture), samples, std::to_underlying(format), static_cast<gl::size_t>(dimensions.x), static_cast<gl::size_t>(dimensions.y), fixed);
    }
    static void                           texture_storage_3d_multisample(gl::handle_t texture, glf::Texture::Format format, const gl::Vector3u& dimensions, gl::size_t samples, gl::bool_t fixed = gl::True)
    {
        glTextureStorage3DMultisample(std::to_underlying(texture), samples, std::to_underlying(format), static_cast<gl::size_t>(dimensions.x), static_cast<gl::size_t>(dimensions.y), static_cast<gl::size_t>(dimensions.z), fixed);
    }
    //[8.20.0] Invalidating Texture Image Data
    static void                           invalidate_texture_image(gl::handle_t texture, gl::int32_t level)
    {
        glInvalidateTexImage(std::to_underlying(texture), level);
    }
    static void                           invalidate_texture_sub_image(gl::handle_t texture, gl::uint32_t level, const gl::Vector3u& size, const gl::Vector3u& offset)
    {
        glInvalidateTexSubImage(
            std::to_underlying(texture), 
            static_cast<gl::int32_t>(level),
            static_cast<gl::int32_t>(offset.x), static_cast<gl::int32_t>(offset.y), static_cast<gl::int32_t>(offset.z),
            static_cast<gl::size_t> (size.x),   static_cast<gl::size_t> (size.y),   static_cast<gl::size_t> (size.z));
    }
    //[8.21.0] Clearing Texture Image Data
    static void                           clear_texture_image_data(gl::handle_t texture, gl::uint32_t level, glf::Texture::BaseFormat format, glf::Texture::Type type, std::span<const gl::byte_t> data)
    {
        glClearTexImage(
            std::to_underlying(texture), 
            static_cast<gl::int32_t>(level), 
            std::to_underlying(format), 
            std::to_underlying(type),
            data.data());
    }
    static void                           clear_texture_sub_image_data(gl::handle_t texture, const gl::Vector3u& dimensions, const gl::Vector3u& offset, gl::uint32_t level, glf::Texture::BaseFormat format, glf::Texture::Type type, std::span<const gl::byte_t> data)
    {
        glClearTexSubImage(
            std::to_underlying(texture), 
            static_cast<gl::int32_t>(level), 
            static_cast<gl::int32_t>(offset.x),     static_cast<gl::int32_t>(offset.y),     static_cast<gl::int32_t>(offset.z),
            static_cast<gl::int32_t>(dimensions.x), static_cast<gl::int32_t>(dimensions.y), static_cast<gl::int32_t>(dimensions.z), 
            std::to_underlying(format), 
            std::to_underlying(type), 
            data.data());
    }
    //[8.26.0] Texture Image Loads and Stores
    static void bind_image_texture(gl::handle_t image, gl::handle_t texture, glf::Image::Format format, glf::Image::Access access, gl::uint32_t level, gl::bool_t isLayered, gl::uint32_t layer)
    {
        glBindImageTexture(
            std::to_underlying(image), 
            std::to_underlying(texture),
            static_cast<gl::int32_t>(level),
            isLayered, layer, 
            std::to_underlying(access), 
            std::to_underlying(format));
    }



    //[9.0.0] FrameBuffers and FrameBuffer Objects
    static gl::handle_t                   create_frame_buffer()
    {
        gl::uint32_t handle{};
        glCreateFramebuffers(1, &handle);

        return gl::handle_t{ handle };
    }
    static void                           delete_frame_buffer(gl::handle_t frameBuffer)
    {
        if (frameBuffer == gl::NullObject) return;

        const auto& uv = std::to_underlying(frameBuffer);
        glDeleteFramebuffers(1, &uv);
    }
    static void                           bind_frame_buffer(gl::handle_t frameBuffer, glf::FrameBuffer::Target target)
    {
        glBindFramebuffer(std::to_underlying(target), std::to_underlying(frameBuffer));
    }
    //[9.2.1] FrameBuffer Object Parameters
    static void frame_buffer_parameter(gl::handle_t frameBuffer, glf::FrameBuffer::Parameter parameter, gl::uint32_t value)
    {
        glNamedFramebufferParameteri(std::to_underlying(frameBuffer), std::to_underlying(parameter), static_cast<gl::int32_t>(value));
    }
    //[9.2.3] FrameBuffer Object Queries
    static auto get_named_frame_buffer_parameter_v() { throw std::logic_error{ "The method or operation has not been implemented!" }; }
    static auto get_named_frame_buffer_parameter_attachment_v() { throw std::logic_error{ "The method or operation has not been implemented!" }; }
    //[9.2.4] RenderBuffer Objects
    static gl::handle_t                   create_render_buffer()
    {
        gl::uint32_t handle{};
        glCreateRenderbuffers(1, &handle);

        return gl::handle_t{ handle };
    }
    static void                           delete_render_buffer(gl::handle_t renderBuffer)
    {
        if (renderBuffer == gl::NullObject) return;

        const auto& uv = std::to_underlying(renderBuffer);
        glDeleteRenderbuffers(1, &uv);
    }
    static void                           render_buffer_storage(gl::handle_t renderBuffer, glf::RenderBuffer::Format format, const gl::Vector2u& dimensions)
    {
        glNamedRenderbufferStorage(
            std::to_underlying(renderBuffer), 
            std::to_underlying(format), 
            static_cast<gl::size_t>(dimensions.x), static_cast<gl::size_t>(dimensions.y));
    }
    static void                           render_buffer_storage_multisample(gl::handle_t renderBuffer, glf::RenderBuffer::Format format, const gl::Vector2u& dimensions, gl::uint8_t samples)
    {
        glNamedRenderbufferStorageMultisample(
            std::to_underlying(renderBuffer),
            samples, 
            std::to_underlying(format), 
            static_cast<gl::size_t>(dimensions.x), static_cast<gl::size_t>(dimensions.y));
    }
    //[9.2.6] RenderBuffer Object Queries
    static auto get_render_buffer_parameter_v() { throw std::logic_error{ "The method or operation has not been implemented!" }; }
    //[9.2.7] Attaching RenderBuffer Images to a FrameBuffer
    static void                           frame_buffer_render_buffer(gl::handle_t frameBuffer, gl::handle_t renderBuffer, gl::enum_t attachment)
    {
        glNamedFramebufferRenderbuffer(std::to_underlying(frameBuffer), attachment, GL_RENDERBUFFER, std::to_underlying(renderBuffer));
    }









    static void                           frame_buffer_read_buffer(gl::handle_t frameBuffer, glf::FrameBuffer::Source source)
    {
        glNamedFramebufferReadBuffer(static_cast<gl::uint32_t>(frameBuffer), static_cast<gl::enum_t>(source));
    }
    static void                           frame_buffer_draw_buffer(gl::handle_t frameBuffer, glf::FrameBuffer::Source source)
    {
        glNamedFramebufferDrawBuffer(static_cast<gl::uint32_t>(frameBuffer), static_cast<gl::enum_t>(source));
    }
    static void                           frame_buffer_draw_buffers(gl::handle_t frameBuffer, std::span<const gl::enum_t> buffers)
    {
        glNamedFramebufferDrawBuffers(static_cast<gl::uint32_t>(frameBuffer), static_cast<gl::size_t>(buffers.size()), buffers.data());
    }
    static void                           frame_buffer_texture(gl::handle_t frameBuffer, gl::handle_t texture, gl::enum_t attachment, gl::int32_t level)
    {
        glNamedFramebufferTexture(static_cast<gl::uint32_t>(frameBuffer), attachment, static_cast<gl::uint32_t>(texture), level);
    }
    static void                           frame_buffer_texture_layer(gl::handle_t frameBuffer, gl::handle_t texture, gl::enum_t attachment, gl::uint32_t level, gl::uint32_t layer)
    {
        glNamedFramebufferTextureLayer(static_cast<gl::uint32_t>(frameBuffer), attachment, static_cast<gl::uint32_t>(texture), level, layer);
    }
    
    static glf::FrameBuffer::Status       check_frame_buffer_status(gl::handle_t frameBuffer)
    {
        return glf::FrameBuffer::Status{ glCheckNamedFramebufferStatus(static_cast<gl::uint32_t>(frameBuffer), GL_FRAMEBUFFER) };
    }
    static void                           invalidate_frame_buffer(gl::handle_t frameBuffer, std::span<gl::enum_t> attachments)
    {
        glInvalidateNamedFramebufferData(static_cast<gl::uint32_t>(frameBuffer), static_cast<gl::size_t>(attachments.size()), attachments.data());
    }
    static void                           invalidate_frame_buffer_sub_data(gl::handle_t frameBuffer, std::span<gl::enum_t> attachments, const gl::Vector2u& position, const gl::Vector2u& size)
    {
        glInvalidateNamedFramebufferSubData(
            static_cast<gl::uint32_t>(frameBuffer),
            static_cast<gl::size_t>(attachments.size()), attachments.data(),
            position.x, position.y,
            size.x, size.y);
    }
    static void                           clear_frame_buffer(gl::handle_t frameBuffer, gl::ClearValue value)
    {
        __debugbreak();
    }











    static void                           texture_barrier()
    {
        glTextureBarrier();
    }


    static void test23()
    {

    }





#pragma region TransformFeedback
    static gl::handle_t                   create_transform_feedback()
    {
        gl::uint32_t transformFeedback{};
        glCreateTransformFeedbacks(1, &transformFeedback);

        return gl::handle_t{ transformFeedback };
    }
    static void                           delete_transform_feedback(gl::handle_t transformFeedback)
    {
        if (transformFeedback == gl::NullObject) return;

        const auto& uv = std::to_underlying(transformFeedback);
        glDeleteTransformFeedbacks(1, &uv);
    }
    static void                           bind_transform_feedback(gl::handle_t buffer)
    {
        glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, static_cast<gl::uint32_t>(buffer));
    }
    static void                           begin_transform_feedback(glf::TransformFeedback::PrimitiveMode mode)
    {
        glBeginTransformFeedback(static_cast<gl::enum_t>(mode));
    }
    static void                           resume_transform_feedback()
    {
        glResumeTransformFeedback();
    }
    static void                           pause_tranform_feedback()
    {
        glPauseTransformFeedback();
    }
    static void                           end_transform_feedback()
    {
        glEndTransformFeedback();
    }
#pragma endregion

#pragma region VertexArray
    static gl::handle_t                   create_vertex_array()
    {
        gl::uint32_t vertexArray{};
        glCreateVertexArrays(1, &vertexArray);

        return gl::handle_t{ vertexArray };
    }
    static void                           delete_vertex_array(gl::handle_t vertexArray)
    {
        if (vertexArray == gl::NullObject) return;

        const auto& uv = std::to_underlying(vertexArray);
        glDeleteVertexArrays(1, &uv);
    }
    static void                           bind_vertex_array(gl::handle_t vertexArray)
    {
        glBindVertexArray(static_cast<gl::uint32_t>(vertexArray));
    }
    static void                           vertex_array_vertex_buffer(gl::handle_t vertexArray, gl::handle_t buffer, gl::uint32_t index, gl::size_t stride)
    {
        glVertexArrayVertexBuffer(static_cast<gl::uint32_t>(vertexArray), index, static_cast<gl::uint32_t>(buffer), 0, stride);
    }
    static void                           enable_vertex_array_attribute(gl::handle_t vertexArray, gl::uint32_t index)
    {
        glEnableVertexArrayAttrib(static_cast<gl::uint32_t>(vertexArray), index);
    }
    static void                           disable_vertex_array_attribute(gl::handle_t vertexArray, gl::uint32_t index)
    {
        glDisableVertexArrayAttrib(static_cast<gl::uint32_t>(vertexArray), index);
    }
    static void                           vertex_array_attribute_format(gl::handle_t vertexArray, gl::uint32_t index, gl::uint32_t offset, glf::DataType type, gl::int32_t count, gl::bool_t normalized)
    {
        glVertexArrayAttribFormat(static_cast<gl::uint32_t>(vertexArray), index, count, std::to_underlying(type), normalized, offset);
    }
    static void                           vertex_array_attribute_binding(gl::handle_t vertexArray, gl::uint32_t index, gl::uint32_t binding)
    {
        glVertexArrayAttribBinding(static_cast<gl::uint32_t>(vertexArray), index, binding);
    }
    static void                           vertex_array_element_buffer(gl::handle_t vertexArray, gl::handle_t buffer)
    {
        glVertexArrayElementBuffer(static_cast<gl::uint32_t>(vertexArray), static_cast<gl::uint32_t>(buffer));
    }
    static void                           vertex_array_binding_divisor(gl::handle_t vertexArray, gl::uint32_t binding, gl::uint32_t divisor)
    {
        glVertexArrayBindingDivisor(static_cast<gl::uint32_t>(vertexArray), binding, divisor);
    }
#pragma endregion

#pragma region RenderBuffer
#pragma endregion

#pragma region FrameBuffer
#pragma endregion





    //Rendering
    static void                           draw_arrays(glf::Draw::Mode mode, gl::size_t first, gl::size_t vertices)
    {
        glDrawArrays(static_cast<gl::enum_t>(mode), first, vertices);
    }
    static void                           draw_elements(glf::Draw::Mode mode, glf::Draw::Type type, gl::size_t indices)
    {
        glDrawElements(static_cast<gl::enum_t>(mode), indices, static_cast<gl::enum_t>(type), nullptr);
    }
    static void                           draw_elements_base_vertex(glf::Draw::Mode mode, glf::Draw::Type type, gl::size_t indices, gl::uint32_t offset)
    {
        glDrawElementsBaseVertex(static_cast<gl::enum_t>(mode), indices, static_cast<gl::enum_t>(type), nullptr, offset);
    }
    static void                           draw_elements_range(glf::Draw::Mode mode, glf::Draw::Type type, const gl::Vector2u& range, gl::size_t indices)
    {
        glDrawRangeElements(static_cast<gl::enum_t>(mode), range.x, range.y, indices, static_cast<gl::enum_t>(type), nullptr);
    }
    static void                           draw_elements_range_base_vertex(glf::Draw::Mode mode, glf::Draw::Type type, const gl::Vector2u& range, gl::size_t indices, gl::uint32_t offset)
    {
        glDrawRangeElementsBaseVertex(static_cast<gl::enum_t>(mode), range.x, range.y, indices, static_cast<gl::enum_t>(type), nullptr, offset);
    }
    static void                           draw_transform_feedback(gl::handle_t transformFeedback, glf::Draw::Mode mode)
    {
        glDrawTransformFeedback(static_cast<gl::enum_t>(mode), static_cast<gl::uint32_t>(transformFeedback));
    }
    static void                           draw_transform_feedback_stream(gl::handle_t transformFeedback, gl::handle_t stream, glf::Draw::Mode mode)
    {
        glDrawTransformFeedbackStream(static_cast<gl::enum_t>(mode), static_cast<gl::uint32_t>(transformFeedback), static_cast<gl::uint32_t>(stream));
    }
    
    static void                           blit_framebuffer(gl::handle_t source, gl::handle_t destination, const gl::Vector4u& sourceArea, const gl::Vector4u& destinationArea, glf::Buffer::Mask mask, glf::FrameBuffer::Filter filter)
    {
        glBlitNamedFramebuffer(
            static_cast<gl::uint32_t>(source),
            static_cast<gl::uint32_t>(destination),
            sourceArea.x,      sourceArea.y,      sourceArea.z,      sourceArea.w,
            destinationArea.x, destinationArea.y, destinationArea.z, destinationArea.w,
            mask, static_cast<gl::enum_t>(filter));
    }

    //Conditional Rendering
    static void                           begin_conditional_render(gl::handle_t query, glf::Query::Mode mode)
    {
        glBeginConditionalRender(static_cast<gl::uint32_t>(query), static_cast<gl::enum_t>(mode));
    }
    static void                           end_conditional_render()
    {
        glEndConditionalRender();
    }

    //Compute
    static void                           dispatch_compute(const gl::Vector3u& groups)
    {
        glDispatchCompute(groups.x, groups.y, groups.z);
    }
    static void                           dispatch_compute_indirect(gl::intptr_t offset)
    {
        glDispatchComputeIndirect(offset);
    }









    static void test()
    {
        auto res1 = gl::get_v<glf::Data::ActiveTexture>();
        auto res2 = gl::get_v<glf::Data::AliasedLineWidthRange>();
        auto res3 = gl::get_v<glf::Data::CompressedTextureFormats>();
        auto res4 = gl::get_v<glf::Data::VertexBindingOffset, 15>();

        auto res5 = gl::vertex_attribute_iv<glf::VertexAttribute::Parameter::Type, 0>();
    }

#pragma region Control
    static void                           enable(glf::Feature feature)
    {
        glEnable(static_cast<gl::enum_t>(feature));
    }
    static void                           disable(glf::Feature feature)
    {
        glDisable(static_cast<gl::enum_t>(feature));
    }

    static void                           blend_color(const gl::Vector4f& color)
    {
        glBlendColor(color.r, color.g, color.b, color.a);
    }
    static void                           blend_function(glf::Blending::Factor source, glf::Blending::Factor destination)
    {
        glBlendFunc(static_cast<gl::enum_t>(source), static_cast<gl::enum_t>(destination));
    }
    static void                           blend_function_separate(glf::Blending::Factor sourceRGB, glf::Blending::Factor sourceAlpha, glf::Blending::Factor destinationRGB, glf::Blending::Factor destinationAlpha)
    {
        glBlendFuncSeparate(static_cast<gl::enum_t>(sourceRGB), static_cast<gl::enum_t>(destinationRGB), static_cast<gl::enum_t>(sourceAlpha), static_cast<gl::enum_t>(destinationAlpha));
    }
    static void                           blend_equation(glf::Blending::Equation equation)
    {
        glBlendEquation(static_cast<gl::enum_t>(equation));
    }
    static void                           blend_equation_separate(glf::Blending::Equation equationRGB, glf::Blending::Equation equationAlpha)
    {
        glBlendEquationSeparate(static_cast<gl::enum_t>(equationRGB), static_cast<gl::enum_t>(equationAlpha));
    }

    static void                           depth_function(glf::DepthFunction depthFunction)
    {
        glDepthFunc(static_cast<gl::enum_t>(depthFunction));
    }
    static void                           depth_range(const gl::Vector2f& range)
    {
        glDepthRangef(range.x, range.y);
    }
    static void                           depth_mask(gl::bool_t flag)
    {
        glDepthMask(flag);
    }

    static void                           stencil_function(glf::Stencil::Function function, gl::int32_t value, gl::uint32_t mask)
    {
        glStencilFunc(static_cast<gl::enum_t>(function), value, mask);
    }
    static void                           stencil_function_separate(glf::Stencil::Face face, glf::Stencil::Function function, gl::int32_t value, gl::uint32_t mask)
    {
        glStencilFuncSeparate(static_cast<gl::enum_t>(face), static_cast<gl::enum_t>(function), value, mask);
    }
    static void                           stencil_mask(gl::uint32_t mask)
    {
        glStencilMask(mask);
    }
    static void                           stencil_mask_separate(glf::Stencil::Face face, gl::uint32_t mask)
    {
        glStencilMaskSeparate(static_cast<gl::enum_t>(face), mask);
    }
    static void                           stencil_operation(glf::Stencil::Action onStencilFail, glf::Stencil::Action onDepthFail, glf::Stencil::Action onDepthStencilPass)
    {
        glStencilOp(static_cast<gl::enum_t>(onStencilFail), static_cast<gl::enum_t>(onDepthFail), static_cast<gl::enum_t>(onDepthStencilPass));
    }
    static void                           stencil_operation_separate(glf::Stencil::Face face, glf::Stencil::Action onStencilFail, glf::Stencil::Action onDepthFail, glf::Stencil::Action onDepthStencilPass)
    {
        glStencilOpSeparate(static_cast<gl::enum_t>(face), static_cast<gl::enum_t>(onStencilFail), static_cast<gl::enum_t>(onDepthFail), static_cast<gl::enum_t>(onDepthStencilPass));
    }

    static void                           clear(glf::Buffer::Mask mask)
    {
        glClear(mask);
    }
    static void                           clear_color(const gl::Vector4f& color)
    {
        glClearColor(color.r, color.g, color.b, color.a);
    }
    static void                           clear_depth(gl::float32_t depth)
    {
        glClearDepthf(depth);
    }
    static void                           clear_stencil(gl::int32_t index)
    {
        glClearStencil(index);
    }
    
    static void                           scissor(const gl::Vector4u& area)
    {
        glScissor(area.x, area.y, area.z, area.w);
    }
    static void                           viewport(const gl::Vector4u& area)
    {
        glViewport(area.x, area.y, area.z, area.w);
    }

    static void                           polygon_mode(glf::Polygon::Mode mode)
    {
        glPolygonMode(GL_FRONT_AND_BACK, static_cast<gl::enum_t>(mode));
    }
    static void                           polygon_offset(gl::float32_t factor, gl::float32_t units)
    {
        glPolygonOffset(factor, units);
    }

    static void                           point_size(gl::float32_t size)
    {
        glPointSize(size);
    }
    static void                           line_width(gl::float32_t width)
    {
        glLineWidth(width);
    }

    static void                           cull_face(glf::Culling::Face face)
    {
        glCullFace(static_cast<gl::enum_t>(face));
    }
    static void                           front_face(glf::Orientation orientation)
    {
        glFrontFace(static_cast<gl::enum_t>(orientation));
    }

    static void                           clip_control(glf::Clip::Origin origin, glf::Clip::DepthMode mode)
    {
        glClipControl(static_cast<gl::enum_t>(origin), static_cast<gl::enum_t>(mode));
    }

    static void                           clamp_color(gl::bool_t value)
    {
        glClampColor(GL_CLAMP_READ_COLOR, value);
    }

    static void                           provoking_vertex(glf::ProvokingVertex provokingVertex)
    {
        glProvokingVertex(static_cast<gl::enum_t>(provokingVertex));
    }
    static void                           primitive_restart_index(gl::uint32_t index)
    {
        glPrimitiveRestartIndex(index);
    }

    static void                           patch_parameter(glf::Patch::Parameter parameter, gl::int32_t value)
    {
        glPatchParameteri(static_cast<gl::enum_t>(parameter), value);
    }
#pragma endregion





    //Debug
    static void                           debug_callback(gl::enum_t source, gl::enum_t type, gl::uint32_t id, gl::enum_t severity, gl::size_t length, const gl::char_t* message, const void* user_param)
    {
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

        if (severityMessage == "NOTIFICATION") return;

        std::cout << std::format("[GL_DEBUG] {0}, {1}, {2}, {3}: {4}", sourceMessage, typeMessage, severityMessage, id, message) << std::endl;
    }
    static void                           debug_message_callback(decltype(debug_callback) callback)
    {
        glDebugMessageCallback(callback, nullptr);
    }
    static void                           debug_message_control(gl::bool_t state, glf::Debug::Source source, glf::Debug::Type type, glf::Debug::Severity severity)
    {
        glDebugMessageControl(static_cast<gl::enum_t>(source), static_cast<gl::enum_t>(type), static_cast<gl::enum_t>(severity), 0, nullptr, state);
    }
    static void                           debug_message_insert(gl::uint32_t id, glf::Debug::Type type, glf::Debug::Severity severity, std::string_view message)
    {
        glDebugMessageInsert(GL_DEBUG_SOURCE_APPLICATION, static_cast<gl::enum_t>(type), id, static_cast<gl::enum_t>(severity), static_cast<gl::size_t>(message.length()), message.data());
    }
    static void                           push_debug_group(gl::uint32_t id, std::string_view message)
    {
        glPushDebugGroup(GL_DEBUG_SOURCE_APPLICATION, id, static_cast<gl::size_t>(message.length()), message.data());
    }
    static void                           pop_debug_group()
    {
        glPopDebugGroup();
    }



#ifdef FOX_GRAPHICS_API_GL_EXTENDED
    //TODO
    //create_*** functions that return N amount of handles eg.:
    //template<gl::size_t N>
    //create_buffers(...) => returns N amount of buffer handles. Returns handle if (N == 1). Returns handle array if (N > 1)
    //Same idea for delete_buffers(...) etc.
#endif
#ifdef FOX_GRAPHICS_API_GL_LEGACY
    //Legacy OpenGL functions here (pre 3.0)
#endif
}
