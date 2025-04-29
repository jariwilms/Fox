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
    //Functions are ordered according to their appearance in the OpenGL 4.6 core specification
    //https://registry.khronos.org/OpenGL/specs/gl/glspec46.core.pdf



    //Chapter 22 - Context State Queries
    static auto get_boolean           (glf::Data data, std::optional<gl::uint32_t> index = std::nullopt)
    {
        gl::bool_t value{};

        if   (index.has_value()) glGetBooleani_v(gl::to_underlying(data), index.value(), &value);
        else                     glGetBooleanv  (gl::to_underlying(data),                &value);

        return value;
    }
    static auto get_integer           (glf::Data data, std::optional<gl::uint32_t> index = std::nullopt)
    {
        gl::int32_t value{};

        if   (index.has_value()) glGetIntegeri_v(gl::to_underlying(data), index.value(), &value);
        else                     glGetIntegerv  (gl::to_underlying(data),                &value);

        return value;
    }
    static auto get_integer64         (glf::Data data, std::optional<gl::uint32_t> index = std::nullopt)
    {
        gl::int64_t value{};

        if   (index.has_value()) glGetInteger64i_v(gl::to_underlying(data), index.value(), &value);
        else                     glGetInteger64v  (gl::to_underlying(data),                &value);

        return value;
    }
    static auto get_float             (glf::Data data, std::optional<gl::uint32_t> index = std::nullopt)
    {
        gl::float32_t value{};

        if   (index.has_value()) glGetFloati_v(gl::to_underlying(data), index.value(), &value);
        else                     glGetFloatv  (gl::to_underlying(data),                &value);

        return value;
    }
    static auto get_float64           (glf::Data data, std::optional<gl::uint32_t> index = std::nullopt)
    {
        gl::float64_t value{};

        if   (index.has_value()) glGetDoublei_v(gl::to_underlying(data), index.value(), &value);
        else                     glGetDoublev  (gl::to_underlying(data),                &value);

        return value;
    }
    static auto is_enabled            (glf::Feature feature, std::optional<gl::uint32_t> index = std::nullopt)
    {
        gl::bool_t value{};

        if   (index.has_value()) value = glIsEnabledi(gl::to_underlying(feature), index.value());
        else                     value = glIsEnabled (gl::to_underlying(feature)               );

        return value;
    }
    static auto get_pointer           (glf::Callback::Pointer pointer)
    {
        gl::void_t* value{};
        glGetPointerv(gl::to_underlying(pointer), &value);

        return value;
    }
    static auto get_string            (glf::Connection connection, std::optional<gl::uint32_t> index = std::nullopt)
    {
        const gl::uint8_t* value{};

        if   (index.has_value()) value = glGetStringi(gl::to_underlying(connection), index.value());
        else                     value = glGetString (gl::to_underlying(connection)               );

        return std::string{ reinterpret_cast<const gl::char_t*>(value) };
    }
    static auto get_internal_format   (gl::enum_t target, gl::enum_t internalformat, gl::enum_t pname, gl::sizei_t bufsize)
    {
        throw std::logic_error{ "The method or operation has not been implemented!" };
    }
    static auto get_transform_feedback(gl::handle_t transformFeedback, glf::TransformFeedback::Property property)
    {
        gl::int32_t value{};
        glGetTransformFeedbackiv(gl::to_underlying(transformFeedback), gl::to_underlying(property), &value);

        return value;
    }
    
    //!
    //Change these to the above format, rename them to get_buffer_parameter or something, and then create separate functions with below functionality?
    template<glf::Synchronization::Property P>
    static auto get_sync        (gl::sync_t sync)
    {
        gl::int32_t value{};
        gl::sizei_t length{};

        glGetSynciv(sync, gl::to_underlying(P), sizeof(value), &length, &value);

        if constexpr (P == glf::Synchronization::Property::Type)      return glf::Synchronization::Object::Type     { value };
        if constexpr (P == glf::Synchronization::Property::Status)    return glf::Synchronization::Object::Status   { value };
        if constexpr (P == glf::Synchronization::Property::Condition) return glf::Synchronization::Object::Condition{ value };
        if constexpr (P == glf::Synchronization::Property::Flags)     return glf::Synchronization::Object::Flags    { value };
    }
    template<glf::Buffer::Parameter P>
    static auto get_buffer_parameter_v(gl::handle_t buffer)
    {
        const auto& get_buffer_parameter_iv   = [](gl::handle_t buffer, glf::Buffer::Parameter parameter)
            {
                gl::int32_t value{};
                glGetNamedBufferParameteriv(gl::to_underlying(buffer), gl::to_underlying(parameter), &value);

                return value;
            };
        const auto& get_buffer_parameter_i64v = [](gl::handle_t buffer, glf::Buffer::Parameter parameter) -> gl::int64_t
            {
                gl::int64_t value{};
                glGetNamedBufferParameteri64v(gl::to_underlying(buffer), gl::to_underlying(parameter), &value);

                return value;
            };
        
        if constexpr (P == glf::Buffer::Parameter::Size)         return static_cast<gl ::uint64_t>                    (get_buffer_parameter_i64v(buffer, P));
        if constexpr (P == glf::Buffer::Parameter::Usage)        return static_cast<glf::Buffer::Usage>               (get_buffer_parameter_iv  (buffer, P));
        if constexpr (P == glf::Buffer::Parameter::Access)       return static_cast<glf::Buffer::Mapping::Access>     (get_buffer_parameter_iv  (buffer, P));
        if constexpr (P == glf::Buffer::Parameter::AccessFlags)  return static_cast<glf::Buffer::Mapping::AccessFlags>(get_buffer_parameter_iv  (buffer, P));
        if constexpr (P == glf::Buffer::Parameter::IsImmutable)  return static_cast<gl ::bool_t>                      (get_buffer_parameter_iv  (buffer, P));
        if constexpr (P == glf::Buffer::Parameter::StorageFlags) return static_cast<glf::Buffer::StorageFlags>        (get_buffer_parameter_iv  (buffer, P));
        if constexpr (P == glf::Buffer::Parameter::IsMapped)     return static_cast<gl ::bool_t>                      (get_buffer_parameter_iv  (buffer, P));
        if constexpr (P == glf::Buffer::Parameter::MapOffset)    return static_cast<gl ::uint64_t>                    (get_buffer_parameter_i64v(buffer, P));
        if constexpr (P == glf::Buffer::Parameter::MapLength)    return static_cast<gl ::uint64_t>                    (get_buffer_parameter_i64v(buffer, P));

        throw std::invalid_argument{ "Invalid Parameter!" };
    }

    //!
    
    
    
    template<glf::Data D>
    static auto get_v()
    {
        constexpr auto uv = gl::to_underlying(D);



        if constexpr (D == glf::Data::PatchDefaultOuterLevel)
        {
            std::array<gl::float32_t, 4> values{};
            glGetFloatv(uv, values.data());

            return gl::Vector4f{ values.at(0), values.at(1), values.at(2), values.at(3) };
        }
        if constexpr (D == glf::Data::PatchDefaultInnerLevel)
        {
            std::array<gl::float32_t, 2> values{};
            glGetFloatv(uv, values.data());

            return gl::Vector2f{ values.at(0), values.at(1) };
        }

        if constexpr (D == glf::Data::IndexArrayBufferBinding)        return static_cast<gl::uint32_t>(gl::get_integer(D));
                                                                      
        if constexpr (D == glf::Data::ArrayBufferBinding)             return static_cast<gl::uint32_t>(gl::get_integer(D));
        if constexpr (D == glf::Data::DrawIndirectBufferBinding)      return static_cast<gl::uint32_t>(gl::get_integer(D));
        if constexpr (D == glf::Data::VertexArrayBinding)             return static_cast<gl::uint32_t>(gl::get_integer(D));
        if constexpr (D == glf::Data::ParameterBufferBinding)         return static_cast<gl::uint32_t>(gl::get_integer(D));
                                                                      
        if constexpr (D == glf::Data::PrimitiveRestartIndex)          return static_cast<gl::uint32_t>(gl::get_integer(D));
                                                                      
        if constexpr (D == glf::Data::ClipOrigin)                     return glf::Clip::Origin{ gl::get_integer(D) };
        if constexpr (D == glf::Data::ClipDepthMode)                  return glf::Clip::DepthMode{ gl::get_integer(D) };

        if constexpr (D == glf::Data::TransformFeedbackBinding)       return static_cast<gl::uint32_t>(gl::get_integer(D));
        if constexpr (D == glf::Data::TransformFeedbackBufferBinding) return static_cast<gl::uint32_t>(gl::get_integer(D));











        if constexpr (D == glf::Data::MaximumVertexAttributeBindings) return static_cast<gl::uint32_t>(gl::get_integer(D));
        if constexpr (D == glf::Data::MaximumVertexAttributes)        return static_cast<gl::uint32_t>(gl::get_integer(D));


        if constexpr (D == glf::Data::MaximumViewports)               return static_cast<gl::uint32_t>(gl::get_integer(D));






        if constexpr (D == glf::Data::ResetNotificationStrategy)      return  glf::Context::ResetStrategy{ gl::get_integer(D) };





        if constexpr (D == glf::Data::ActiveTexture)                     return gl::get_integer(D);
        if constexpr (D == glf::Data::AliasedLineWidthRange) 
        {
            std::array<gl::float32_t, 2> values{};
            glGetFloatv(uv, values.data());

            return gl::Vector2f{ values.at(0), values.at(1) };
        }
        if constexpr (D == glf::Data::ArrayBufferBinding)                return gl::get_integer(D);
        if constexpr (D == glf::Data::BlendColor)
        {
            std::array<gl::float32_t, 4> values{};
            glGetFloatv(uv, values.data());

            return gl::Vector4f{ values.at(0), values.at(1), values.at(2), values.at(3) };
        }
        if constexpr (D == glf::Data::BlendEquationAlpha)                return glf::Blending::Factor{ gl::get_integer(D) };
        if constexpr (D == glf::Data::BlendDestinationRGB)               return glf::Blending::Factor{ gl::get_integer(D) };
        if constexpr (D == glf::Data::BlendEquationAlpha)                return glf::Blending::Equation{ gl::get_integer(D) };
        if constexpr (D == glf::Data::BlendEquationRGB)                  return glf::Blending::Equation{ gl::get_integer(D) };
        if constexpr (D == glf::Data::Blending)                          return gl::get_boolean(D);
        if constexpr (D == glf::Data::BlendSourceAlpha)                  return glf::Blending::Factor{ gl::get_integer(D) };
        if constexpr (D == glf::Data::BlendSourceRGB)                    return glf::Blending::Factor{ gl::get_integer(D) };
        if constexpr (D == glf::Data::ColorClearValue)
        {
            std::array<gl::float32_t, 4> values{};
            glGetFloatv(uv, values.data());

            return gl::Vector4f{ values.at(0), values.at(1), values.at(2), values.at(3) };
        }
        if constexpr (D == glf::Data::ColorLogicOperation)               return gl::get_boolean(D);
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
        if constexpr (D == glf::Data::ContextFlags)                      return gl::get_integer(D);
        if constexpr (D == glf::Data::ContextFlags)                      return gl::get_integer(D);
        if constexpr (D == glf::Data::FaceCulling)                       return gl::get_boolean(D);




        if constexpr (D == glf::Data::MaximumComputeShaderStorageBlocks) return gl::get_integer(D);



        if constexpr (D == glf::Data::NumberCompressedTextureFormats) return gl::get_integer(D);








        throw std::invalid_argument{ "" };
    }
    template<glf::Data D, gl::uint32_t I>
    static auto get_v()
    {
        const auto& uv = gl::to_underlying(D);

        if constexpr (
            D == glf::Data::VertexBindingOffset  ||
            D == glf::Data::VertexBindingStride  ||
            D == glf::Data::VertexBindingDivisor ||
            D == glf::Data::VertexBindingBuffer  )
        {
            if (I >= gl::get_v<glf::Data::MaximumVertexAttributeBindings>()) throw std::invalid_argument{ "Index out of range!" };

            return gl::get_integer64(D, I);
        }
        if constexpr (D == glf::Data::Viewport)
        {
            if (I >= gl::get_v<glf::Data::MaximumViewports>()) throw std::invalid_argument{ "Index out of range!" };

            std::array<gl::float32_t, 4> values{};
            glGetFloati_v(uv, I, values.data());

            return gl::area_t{ values.at(0), values.at(1), values.at(2), values.at(3) };
        }
        if constexpr (D == glf::Data::DepthRange)
        {
            if (I >= gl::get_v<glf::Data::MaximumViewports>()) throw std::invalid_argument{ "Index out of range!" };

            std::array<gl::float64_t, 2> values{};
            glGetDoublei_v(uv, I, values.data());

            return gl::range_t{ values.at(0), values.at(1) };
        }
    }



    //ch4
    static auto get_query(glf::Query::Target target, glf::Query::TargetParameter parameter, std::optional<gl::uint32_t> index = std::nullopt)
    {
        gl::int32_t value{};
        glGetQueryIndexediv(gl::to_underlying(target), index.value_or(gl::uint32_t{ 0 }), gl::to_underlying(parameter), &value);

        return value;
    }

    //ch7
    template<glf::Shader::Parameter P>
    static auto                            get_shader_v(gl::handle_t shader)
    {
        const auto& get_shader_iv = [](gl::handle_t shader, glf::Shader::Parameter parameter)
            {
                gl::int32_t value{};
                glGetShaderiv(gl::to_underlying(shader), gl::to_underlying(parameter), &value);

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
                glGetProgramiv(gl::to_underlying(program), gl::to_underlying(parameter), &value);

                return value;
            };

        if constexpr (P == glf::Program::Parameter::IsSeparable)                           return static_cast<gl::bool_t>  (program_iv(program, P));
        if constexpr (P == glf::Program::Parameter::DeleteStatus)                          return static_cast<gl::bool_t>  (program_iv(program, P));
        if constexpr (P == glf::Program::Parameter::LinkStatus)                            return static_cast<gl::bool_t>  (program_iv(program, P));
        if constexpr (P == glf::Program::Parameter::ValidateStatus)                        return static_cast<gl::bool_t>  (program_iv(program, P));
        if constexpr (P == glf::Program::Parameter::AttachedShaders)                       return static_cast<gl::sizei_t>(program_iv(program, P));
        if constexpr (P == glf::Program::Parameter::InfoLogLength)                         return static_cast<gl::sizei_t>(program_iv(program, P));
        if constexpr (P == glf::Program::Parameter::BinaryLength)                          return static_cast<gl::sizei_t>(program_iv(program, P));
        if constexpr (P == glf::Program::Parameter::IsBinaryRetrievable)                   return static_cast<gl::bool_t>  (program_iv(program, P));
        if constexpr (P == glf::Program::Parameter::ComputeWorkGroupSize)
        {
            std::array<gl::int32_t, 3> values{};
            glGetProgramiv(gl::to_underlying(program), gl::to_underlying(P), values.data());

            return gl::Vector3u{ values.at(0), values.at(1), values.at(2) };
        }
        if constexpr (P == glf::Program::Parameter::ActiveUniforms)                        return static_cast<gl::sizei_t>(program_iv(program, P));
        if constexpr (P == glf::Program::Parameter::ActiveUniformMaximumLength)            return static_cast<gl::sizei_t>(program_iv(program, P));
        if constexpr (P == glf::Program::Parameter::ActiveAttributes)                      return static_cast<gl::sizei_t>(program_iv(program, P));
        if constexpr (P == glf::Program::Parameter::ActiveAttributeMaximumLength)          return static_cast<gl::sizei_t>(program_iv(program, P));
        if constexpr (P == glf::Program::Parameter::GeometryVerticesOut)                   return static_cast<gl::sizei_t>(program_iv(program, P));
        if constexpr (P == glf::Program::Parameter::GeometryInputType)                     return glf::Geometry::InputPrimitive{ program_iv(program, P) };
        if constexpr (P == glf::Program::Parameter::GeometryOutputType)                    return glf::Geometry::OutputPrimitive{ program_iv(program, P) };
        if constexpr (P == glf::Program::Parameter::GeometryShaderInvocations)             return static_cast<gl::sizei_t>(program_iv(program, P));
        if constexpr (P == glf::Program::Parameter::TransformFeedbackBufferMode)           return glf::TransformFeedback::BufferMode{ program_iv(program, P) };
        if constexpr (P == glf::Program::Parameter::TransformFeedbackVaryings)             return static_cast<gl::sizei_t>(program_iv(program, P));
        if constexpr (P == glf::Program::Parameter::TransformFeedbackVaryingMaximumLength) return static_cast<gl::sizei_t>(program_iv(program, P));
        if constexpr (P == glf::Program::Parameter::ActiveUniformBlocks)                   return static_cast<gl::sizei_t>(program_iv(program, P));
        if constexpr (P == glf::Program::Parameter::ActiveUniformBlockMaximumNameLength)   return static_cast<gl::sizei_t>(program_iv(program, P));
        if constexpr (P == glf::Program::Parameter::TessellationControlOutputVertices)     return static_cast<gl::sizei_t>(program_iv(program, P));
        if constexpr (P == glf::Program::Parameter::TessellationGenerationMode)            return glf::Tessellation::GenerationMode{ program_iv(program, P) };
        if constexpr (P == glf::Program::Parameter::TessellationGenerationSpacing)         return glf::Tessellation::Spacing{ program_iv(program, P) };
        if constexpr (P == glf::Program::Parameter::TessellationGenerationVertexOrder)     return glf::Tessellation::VertexOrder{ program_iv(program, P) };
        if constexpr (P == glf::Program::Parameter::TessellationGenerationPointMode)       return static_cast<gl::bool_t>(program_iv(program, P));
        if constexpr (P == glf::Program::Parameter::ActiveAtomicCounterBuffers)            return static_cast<gl::sizei_t>(program_iv(program, P));
    }
    static auto                            get_program_pipeline_v(gl::handle_t pipeline, glf::Program::Pipeline::Property property)
    {
        gl::int32_t value{};
        glGetProgramPipelineiv(gl::to_underlying(pipeline), gl::to_underlying(property), &value);

        return static_cast<gl::uint32_t>(value);
    }

    template<glf::Program::StageProperty P>
    static auto                            get_program_stage_v(gl::handle_t program, glf::Shader::Type type)
    {
        gl::int32_t value{};
        glGetProgramStageiv(gl::to_underlying(program), gl::to_underlying(type), gl::to_underlying(P), &value);

        return static_cast<gl::uint32_t>(value);
    }



    //ch7
    template<glf::Program::Interface I, glf::Program::Property P>
    static auto                            get_program_interface_v(gl::handle_t program)
    {
        const auto& get_program_interface_iv = [](gl::handle_t program, glf::Program::Interface interface, glf::Program::Property property) -> gl::int32_t
            {
                gl::int32_t value{};
                glGetProgramInterfaceiv(gl::to_underlying(program), gl::to_underlying(interface), gl::to_underlying(property), &value);

                return value;
            };

        if constexpr (
            P == glf::Program::Property::ActiveResources) return get_program_interface_iv(program, I, P);
        if constexpr (
            P == glf::Program::Property::MaximumNameLength && (
                I != glf::Program::Interface::AtomicCounterBuffer ||
                I != glf::Program::Interface::TransformFeedbackBuffer)) return get_program_interface_iv(program, I, P);
        if constexpr (
            P == glf::Program::Property::MaximumNumberActiveVariables && (
                I == glf::Program::Interface::AtomicCounterBuffer ||
                I == glf::Program::Interface::UniformBlock ||
                I == glf::Program::Interface::ShaderStorageBlock ||
                I == glf::Program::Interface::TransformFeedbackBuffer)) return get_program_interface_iv(program, I, P);
        if constexpr (
            P == glf::Program::Property::MaximumNumberCompatibleSubroutines && (
                I == glf::Program::Interface::VertexSubroutineUniform ||
                I == glf::Program::Interface::TessellationControlSubroutineUniform ||
                I == glf::Program::Interface::TessellationEvaluationSubroutineUniform ||
                I == glf::Program::Interface::GeometrySubroutineUniform ||
                I == glf::Program::Interface::FragmentSubroutineUniform ||
                I == glf::Program::Interface::ComputeSubroutineUniform ||
                I == glf::Program::Interface::ShaderStorageBlock)) return get_program_interface_iv(program, I, P);
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
            gl::uint32_t value = glGetProgramResourceIndex(gl::to_underlying(program), gl::to_underlying(I), cstr);

            return value;
        }
    }
    template<glf::Program::Interface I>
    static auto                            get_program_resource_name(gl::handle_t program, gl::uint32_t index)
    {
        if constexpr (
            I != glf::Program::Interface::AtomicCounterBuffer &&
            I != glf::Program::Interface::TransformFeedbackBuffer)
        {
            const auto& maximumLength = gl::get_program_interface_v<I, glf::Program::Property::MaximumNameLength>();

            std::string name{};
            gl::sizei_t  length{};

            name.resize(maximumLength);

            glGetProgramResourceName(gl::to_underlying(program), gl::to_underlying(I), index, maximumLength, &length, name.data());

            if (length < maximumLength) name.resize(static_cast<std::size_t>(length) - 1u);
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
                R == glf::Program::Resource::NameLength && (
                    I != glf::Program::Interface::AtomicCounterBuffer &&
                    I != glf::Program::Interface::TransformFeedbackBuffer)) return gl::True;
            if constexpr (
                R == glf::Program::Resource::Type && (
                    I == glf::Program::Interface::Uniform ||
                    I == glf::Program::Interface::ProgramInput ||
                    I == glf::Program::Interface::ProgramOutput ||
                    I == glf::Program::Interface::TransformFeedbackVarying ||
                    I == glf::Program::Interface::BufferVariable)) return gl::True;
            if constexpr (
                R == glf::Program::Resource::ArraySize && (
                    I == glf::Program::Interface::Uniform ||
                    I == glf::Program::Interface::BufferVariable ||
                    I == glf::Program::Interface::ProgramInput ||
                    I == glf::Program::Interface::ProgramOutput ||
                    I == glf::Program::Interface::VertexSubroutineUniform ||
                    I == glf::Program::Interface::TessellationControlSubroutineUniform ||
                    I == glf::Program::Interface::TessellationEvaluationSubroutineUniform ||
                    I == glf::Program::Interface::GeometrySubroutineUniform ||
                    I == glf::Program::Interface::FragmentSubroutineUniform ||
                    I == glf::Program::Interface::ComputeSubroutineUniform ||
                    I == glf::Program::Interface::TransformFeedbackVarying)) return gl::True;
            if constexpr (
                R == glf::Program::Resource::Offset && (
                    I == glf::Program::Interface::Uniform ||
                    I == glf::Program::Interface::BufferVariable ||
                    I == glf::Program::Interface::TransformFeedbackVarying)) return gl::True;
            if constexpr (
                R == glf::Program::Resource::BlockIndex && (
                    I == glf::Program::Interface::Uniform ||
                    I == glf::Program::Interface::BufferVariable)) return gl::True;
            if constexpr (
                R == glf::Program::Resource::ArrayStride && (
                    I == glf::Program::Interface::Uniform ||
                    I == glf::Program::Interface::BufferVariable)) return gl::True;
            if constexpr (
                R == glf::Program::Resource::MatrixStride && (
                    I == glf::Program::Interface::Uniform ||
                    I == glf::Program::Interface::BufferVariable)) return gl::True;
            if constexpr (
                R == glf::Program::Resource::IsRowMajor && (
                    I == glf::Program::Interface::Uniform ||
                    I == glf::Program::Interface::BufferVariable)) return gl::True;
            if constexpr (
                R == glf::Program::Resource::AtomicCounterBufferIndex && (
                    I == glf::Program::Interface::Uniform)) return gl::True;
            if constexpr (
                R == glf::Program::Resource::TextureBuffer)                                  return gl::False;
            if constexpr (
                R == glf::Program::Resource::BufferBinding && (
                    I == glf::Program::Interface::UniformBlock ||
                    I == glf::Program::Interface::AtomicCounterBuffer ||
                    I == glf::Program::Interface::ShaderStorageBlock ||
                    I == glf::Program::Interface::TransformFeedbackBuffer)) return gl::True;
            if constexpr (
                R == glf::Program::Resource::BufferDataSize && (
                    I == glf::Program::Interface::UniformBlock ||
                    I == glf::Program::Interface::AtomicCounterBuffer ||
                    I == glf::Program::Interface::ShaderStorageBlock)) return gl::True;
            if constexpr (
                R == glf::Program::Resource::NumberActiveVariables && (
                    I == glf::Program::Interface::UniformBlock ||
                    I == glf::Program::Interface::AtomicCounterBuffer ||
                    I == glf::Program::Interface::ShaderStorageBlock ||
                    I == glf::Program::Interface::TransformFeedbackBuffer)) return gl::True;
            if constexpr (
                R == glf::Program::Resource::ActiveVariables && (
                    I == glf::Program::Interface::UniformBlock ||
                    I == glf::Program::Interface::AtomicCounterBuffer ||
                    I == glf::Program::Interface::ShaderStorageBlock ||
                    I == glf::Program::Interface::TransformFeedbackBuffer)) return gl::True;
            if constexpr (
                R == glf::Program::Resource::ReferencedByVertexShader && (
                    I == glf::Program::Interface::Uniform ||
                    I == glf::Program::Interface::UniformBlock ||
                    I == glf::Program::Interface::AtomicCounterBuffer ||
                    I == glf::Program::Interface::ShaderStorageBlock ||
                    I == glf::Program::Interface::BufferVariable ||
                    I == glf::Program::Interface::ProgramInput ||
                    I == glf::Program::Interface::ProgramOutput)) return gl::True;
            if constexpr (
                R == glf::Program::Resource::ReferencedByTessellationControlShader && (
                    I == glf::Program::Interface::Uniform ||
                    I == glf::Program::Interface::UniformBlock ||
                    I == glf::Program::Interface::AtomicCounterBuffer ||
                    I == glf::Program::Interface::ShaderStorageBlock ||
                    I == glf::Program::Interface::BufferVariable ||
                    I == glf::Program::Interface::ProgramInput ||
                    I == glf::Program::Interface::ProgramOutput)) return gl::True;
            if constexpr (
                R == glf::Program::Resource::ReferencedByTessellationEvaluationShader && (
                    I == glf::Program::Interface::Uniform ||
                    I == glf::Program::Interface::UniformBlock ||
                    I == glf::Program::Interface::AtomicCounterBuffer ||
                    I == glf::Program::Interface::ShaderStorageBlock ||
                    I == glf::Program::Interface::BufferVariable ||
                    I == glf::Program::Interface::ProgramInput ||
                    I == glf::Program::Interface::ProgramOutput)) return gl::True;
            if constexpr (
                R == glf::Program::Resource::ReferencedByGeometryShader && (
                    I == glf::Program::Interface::Uniform ||
                    I == glf::Program::Interface::UniformBlock ||
                    I == glf::Program::Interface::AtomicCounterBuffer ||
                    I == glf::Program::Interface::ShaderStorageBlock ||
                    I == glf::Program::Interface::BufferVariable ||
                    I == glf::Program::Interface::ProgramInput ||
                    I == glf::Program::Interface::ProgramOutput)) return gl::True;
            if constexpr (
                R == glf::Program::Resource::ReferencedByFragmentShader && (
                    I == glf::Program::Interface::Uniform ||
                    I == glf::Program::Interface::UniformBlock ||
                    I == glf::Program::Interface::AtomicCounterBuffer ||
                    I == glf::Program::Interface::ShaderStorageBlock ||
                    I == glf::Program::Interface::BufferVariable ||
                    I == glf::Program::Interface::ProgramInput ||
                    I == glf::Program::Interface::ProgramOutput)) return gl::True;
            if constexpr (
                R == glf::Program::Resource::ReferencedByComputeShader && (
                    I == glf::Program::Interface::Uniform ||
                    I == glf::Program::Interface::UniformBlock ||
                    I == glf::Program::Interface::AtomicCounterBuffer ||
                    I == glf::Program::Interface::ShaderStorageBlock ||
                    I == glf::Program::Interface::BufferVariable ||
                    I == glf::Program::Interface::ProgramInput ||
                    I == glf::Program::Interface::ProgramOutput)) return gl::True;
            if constexpr (
                R == glf::Program::Resource::NumberCompatibleSubroutines && (
                    I == glf::Program::Interface::VertexSubroutineUniform ||
                    I == glf::Program::Interface::TessellationControlSubroutineUniform ||
                    I == glf::Program::Interface::TessellationEvaluationSubroutineUniform ||
                    I == glf::Program::Interface::GeometrySubroutineUniform ||
                    I == glf::Program::Interface::FragmentSubroutineUniform ||
                    I == glf::Program::Interface::ComputeSubroutineUniform)) return gl::True;
            if constexpr (
                R == glf::Program::Resource::CompatibleSubroutines && (
                    I == glf::Program::Interface::VertexSubroutineUniform ||
                    I == glf::Program::Interface::TessellationControlSubroutineUniform ||
                    I == glf::Program::Interface::TessellationEvaluationSubroutineUniform ||
                    I == glf::Program::Interface::GeometrySubroutineUniform ||
                    I == glf::Program::Interface::FragmentSubroutineUniform ||
                    I == glf::Program::Interface::ComputeSubroutineUniform)) return gl::True;
            if constexpr (
                R == glf::Program::Resource::TopLevelArraySize && (
                    I == glf::Program::Interface::BufferVariable)) return gl::True;
            if constexpr (
                R == glf::Program::Resource::TopLevelArrayStride && (
                    I == glf::Program::Interface::BufferVariable)) return gl::True;
            if constexpr (
                R == glf::Program::Resource::Location && (
                    I == glf::Program::Interface::Uniform ||
                    I == glf::Program::Interface::ProgramInput ||
                    I == glf::Program::Interface::ProgramOutput ||
                    I == glf::Program::Interface::VertexSubroutineUniform ||
                    I == glf::Program::Interface::TessellationControlSubroutineUniform ||
                    I == glf::Program::Interface::TessellationEvaluationSubroutineUniform ||
                    I == glf::Program::Interface::GeometrySubroutineUniform ||
                    I == glf::Program::Interface::FragmentSubroutineUniform ||
                    I == glf::Program::Interface::ComputeSubroutineUniform)) return gl::True;
            if constexpr (
                R == glf::Program::Resource::LocationIndex && (
                    I == glf::Program::Interface::ProgramOutput)) return gl::True;
            if constexpr (
                R == glf::Program::Resource::IsPerPatch && (
                    I == glf::Program::Interface::ProgramInput ||
                    I == glf::Program::Interface::ProgramOutput)) return gl::True;
            if constexpr (
                R == glf::Program::Resource::LocationComponent && (
                    I == glf::Program::Interface::ProgramInput ||
                    I == glf::Program::Interface::ProgramOutput)) return gl::True;
            if constexpr (
                R == glf::Program::Resource::TransformFeedbackBufferIndex && (
                    I == glf::Program::Interface::TransformFeedbackVarying)) return gl::True;
            if constexpr (
                R == glf::Program::Resource::TransformFeedbackBufferStride && (
                    I == glf::Program::Interface::TransformFeedbackBuffer)) return gl::True;

            else                                                                             return gl::False;
        };
        if constexpr ((is_supported_resource.template operator() < I, R > () && ...))
        {
            constexpr auto resourceCount = sizeof...(R);
            constexpr std::array<gl::enum_t, resourceCount> resources{ gl::to_underlying(R)... };
            std::array<gl::int32_t, resourceCount> values{};

            glGetProgramResourceiv(
                gl::to_underlying(program),
                gl::to_underlying(I),
                index,
                static_cast<gl::sizei_t>(resources.size()), resources.data(),
                static_cast<gl::sizei_t>(values.size()), nullptr, values.data());

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
            gl::int32_t value = glGetProgramResourceLocation(gl::to_underlying(program), gl::to_underlying(I), cstr);

            if (value == -1) throw std::invalid_argument{ "Identifier does not match an active variable or does not have a valid location assigned!" };

            return value;
        }
    }
    static auto                            get_program_resource_location_index(gl::handle_t program, const std::string& identifier)
    {
        const auto* cstr = identifier.c_str();
        gl::int32_t value = glGetProgramResourceLocationIndex(gl::to_underlying(program), gl::to_underlying(glf::Program::Interface::ProgramOutput), cstr);

        if (value == -1) throw std::invalid_argument{ "Identifier does not match an active variable or does not have a valid location assigned!" };

        return value;
    }



    template<glf::Uniform::Property P, gl::uint32_t N>
    static auto                            get_active_uniforms_v(gl::handle_t program, std::span<const gl::uint32_t, N> indices)
    {
        const auto& get_active_uniforms_iv = [](gl::handle_t program, glf::Uniform::Property property, std::span<gl::uint32_t, N> indices) -> std::array<gl::int32_t, N>
            {
                std::array<gl::int32_t, N> values{};
                glGetActiveUniformsiv(gl::to_underlying(program), static_cast<gl::sizei_t>(indices.size()), indices.data(), gl::to_underlying(property), values.data());

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

        if constexpr (P == glf::Uniform::Property::Type)                     return get_active_uniforms_iv_and_transform.template operator() < glf::Uniform::Type > (program, P, indices);
        if constexpr (P == glf::Uniform::Property::Size)                     return get_active_uniforms_iv_and_transform.template operator() < gl::uint32_t > (program, P, indices);
        if constexpr (P == glf::Uniform::Property::NameLength)               return get_active_uniforms_iv_and_transform.template operator() < gl::uint32_t > (program, P, indices);
        if constexpr (P == glf::Uniform::Property::BlockIndex)               return get_active_uniforms_iv(program, P, indices);
        if constexpr (P == glf::Uniform::Property::Offset)                   return get_active_uniforms_iv(program, P, indices);
        if constexpr (P == glf::Uniform::Property::ArrayStride)              return get_active_uniforms_iv(program, P, indices);
        if constexpr (P == glf::Uniform::Property::MatrixStride)             return get_active_uniforms_iv(program, P, indices);
        if constexpr (P == glf::Uniform::Property::IsRowMajor)               return get_active_uniforms_iv_and_transform.template operator() < gl::bool_t > (program, P, indices);
        if constexpr (P == glf::Uniform::Property::AtomicCounterBufferIndex) return get_active_uniforms_iv_and_transform.template operator() < gl::uint32_t > (program, P, indices);
    }


    template<glf::UniformBlock::Info I>
    static auto                            get_active_uniform_block_v(gl::handle_t program, gl::uint32_t index)
    {
        const auto& get_active_uniform_block_iv = [](gl::handle_t program, glf::UniformBlock::Info info, gl::uint32_t index)
            {
                gl::int32_t value{};
                glGetActiveUniformBlockiv(gl::to_underlying(program), index, gl::to_underlying(info), &value);

                return value;
            };

        const auto& numUniformBlocks = gl::get_program_v<glf::Program::Parameter::ActiveUniformBlocks>(program);
        if (std::cmp_greater_equal(index, numUniformBlocks)) throw std::invalid_argument{ "Index is greater than the amount of uniform blocks!" };

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

            glGetActiveUniformBlockiv(gl::to_underlying(program), index, gl::to_underlying(I), values.data());

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
                glGetActiveAtomicCounterBufferiv(gl::to_underlying(program), index, gl::to_underlying(info), &value);

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


    template<glf::Shader::SubroutineParameter P>
    static auto                            get_active_subroutine_uniform_v(gl::handle_t program, glf::Shader::Type type, gl::uint32_t index)
    {
        const auto& uv = gl::to_underlying(P);

        if constexpr (
            P == glf::Shader::SubroutineParameter::NumberCompatibleSubroutines ||
            P == glf::Shader::SubroutineParameter::UniformSize                 ||
            P == glf::Shader::SubroutineParameter::UniformNameLength            )
        {
            gl::int32_t value{};
            glGetActiveSubroutineUniformiv(gl::to_underlying(program), gl::to_underlying(type), index, uv, &value);

            return static_cast<gl::uint32_t>(value);
        }
        if constexpr (P == glf::Shader::SubroutineParameter::CompatibleSubroutines)
        {
            const auto& numberCompatibleSubroutines = gl::get_active_subroutine_uniform_v<glf::Shader::SubroutineParameter::NumberCompatibleSubroutines>(program, type, index);

            std::vector<gl::uint32_t> value{};

            value.resize(numberCompatibleSubroutines);

            glGetActiveSubroutineUniformiv(gl::to_underlying(program), gl::to_underlying(type), index, uv, value.data());

            return value;
        }
    }

    static auto                            uniform_subroutines_v(glf::Shader::Type type, std::span<const gl::uint32_t> indices)
    {
        glUniformSubroutinesuiv(gl::to_underlying(type), static_cast<gl::sizei_t>(indices.size()), indices.data());
    }




    template<glf::DataType D, gl::sizei_t C>
    static auto                            get_uniform_v(gl::handle_t program, gl::int32_t location)
    {
        const auto& uv = gl::to_underlying(program);

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
        glGetUniformSubroutineuiv(gl::to_underlying(type), location, &value);

        return value;
    }



    //ch8
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
                glGetSamplerParameteriv(gl::to_underlying(sampler), gl::to_underlying(parameter), &value);

                return value;
            };
        const auto& get_sampler_parameter_fv = [](gl::handle_t sampler, glf::Sampler::Parameter parameter)
            {
                gl::float32_t value{};
                glGetSamplerParameterfv(gl::to_underlying(sampler), gl::to_underlying(parameter), &value);

                return value;
            };

        if constexpr (P == glf::Sampler::Parameter::BorderColor)
        {
            std::array<gl::float32_t, 4> values{};

            glGetSamplerParameterfv(gl::to_underlying(sampler), gl::to_underlying(P), values.data());

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
            P == glf::Sampler::Parameter::WrappingR)                   return glf::Texture::Wrapping{ get_sampler_parameter_iv(sampler, P) };
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


    static auto                           get_named_frame_buffer_parameter_v() { throw std::logic_error{ "The method or operation has not been implemented!" }; }
    static auto                           get_named_frame_buffer_parameter_attachment_v() { throw std::logic_error{ "The method or operation has not been implemented!" }; }


    static auto                           get_render_buffer_parameter_v() { throw std::logic_error{ "The method or operation has not been implemented!" }; }




    template<glf::VertexArray::Parameter P>
    static auto                           vertex_array_v(gl::handle_t vertexArray)
    {
        const auto& get_vertex_array_iv = [](gl::handle_t vertexArray, glf::VertexArray::Parameter parameter)
            {
                gl::int32_t value{};
                glGetVertexArrayiv(gl::to_underlying(vertexArray), gl::to_underlying(parameter), &value);

                return value;
            };

        if constexpr (P == glf::VertexArray::Parameter::ElementArrayBufferBinding) return gl::handle_t{ get_vertex_array_iv(vertexArray, P) };
    }
    template<glf::VertexArray::IndexedParameter P>
    static auto                           vertex_array_indexed_v(gl::handle_t vertexArray, gl::uint32_t index)
    {
        const auto& get_vertex_array_indexed_iv = [](gl::handle_t vertexArray, glf::VertexArray::IndexedParameter parameter, gl::uint32_t index)
            {
                gl::int32_t value{};
                glGetVertexArrayIndexediv(gl::to_underlying(vertexArray), index, gl::to_underlying(parameter), &value);

                return value;
            };
        const auto& get_vertex_array_indexed64_iv = [](gl::handle_t vertexArray, glf::VertexArray::IndexedParameter parameter, gl::uint32_t index)
            {
                gl::int64_t value{};
                glGetVertexArrayIndexed64iv(gl::to_underlying(vertexArray), index, gl::to_underlying(parameter), &value);

                return value;
            };

        if constexpr (P == glf::VertexArray::IndexedParameter::Enabled)        return static_cast<gl::bool_t>            (get_vertex_array_indexed_iv(vertexArray, P, index));
        if constexpr (P == glf::VertexArray::IndexedParameter::Stride)         return static_cast<gl::sizei_t>            (get_vertex_array_indexed_iv(vertexArray, P, index));
        if constexpr (P == glf::VertexArray::IndexedParameter::Size)           return static_cast<gl::sizei_t>            (get_vertex_array_indexed_iv(vertexArray, P, index));
        if constexpr (P == glf::VertexArray::IndexedParameter::Type)           return static_cast<glf::VertexArray::Type>(get_vertex_array_indexed_iv(vertexArray, P, index));
        if constexpr (P == glf::VertexArray::IndexedParameter::IsNormalized)   return static_cast<gl::bool_t>            (get_vertex_array_indexed_iv(vertexArray, P, index));
        if constexpr (P == glf::VertexArray::IndexedParameter::IsIntegerData)  return static_cast<gl::bool_t>            (get_vertex_array_indexed_iv(vertexArray, P, index));
        if constexpr (P == glf::VertexArray::IndexedParameter::IsLongData)     return static_cast<gl::bool_t>            (get_vertex_array_indexed_iv(vertexArray, P, index));
        if constexpr (P == glf::VertexArray::IndexedParameter::Divisor)        return static_cast<gl::uint32_t>          (get_vertex_array_indexed_iv(vertexArray, P, index));
        if constexpr (P == glf::VertexArray::IndexedParameter::RelativeOffset) return static_cast<gl::uint32_t>          (get_vertex_array_indexed_iv(vertexArray, P, index));

        if constexpr (P == glf::VertexArray::IndexedParameter::BindingOffset); return static_cast<gl::uint64_t>          (get_vertex_array_indexed64_iv(vertexArray, P, index));
    }
    template<glf::VertexAttribute::Parameter P>
    static auto                           vertex_attribute_v(gl::uint32_t index)
    {
        const auto& get_vertex_attribute_iv = [](glf::VertexAttribute::Parameter P, gl::uint32_t index)
            {
                gl::int32_t value{};
                glGetVertexAttribIiv(index, gl::to_underlying(P), &value);

                return value;
            };
        const auto& get_vertex_attribute_uiv = [](glf::VertexAttribute::Parameter P, gl::uint32_t index)
            {
                gl::uint32_t value{};
                glGetVertexAttribIuiv(index, gl::to_underlying(P), &value);

                return value;
            };

        if constexpr (P == glf::VertexAttribute::Parameter::Enabled)        return static_cast<gl::bool_t>   (get_vertex_attribute_iv(P, index));
        if constexpr (P == glf::VertexAttribute::Parameter::Size)           return static_cast<gl::int32_t>  (get_vertex_attribute_iv(P, index));
        if constexpr (P == glf::VertexAttribute::Parameter::Stride)         return static_cast<gl::uint32_t> (get_vertex_attribute_iv(P, index));
        if constexpr (P == glf::VertexAttribute::Parameter::Type)           return static_cast<glf::DataType>(get_vertex_attribute_iv(P, index));
        if constexpr (P == glf::VertexAttribute::Parameter::IsNormalized)   return static_cast<gl::bool_t>   (get_vertex_attribute_iv(P, index));
        if constexpr (P == glf::VertexAttribute::Parameter::IsIntegerData)  return static_cast<gl::bool_t>   (get_vertex_attribute_iv(P, index));
        if constexpr (P == glf::VertexAttribute::Parameter::IsLongData)     return static_cast<gl::bool_t>   (get_vertex_attribute_iv(P, index));
        if constexpr (P == glf::VertexAttribute::Parameter::Divisor)        return static_cast<gl::uint32_t> (get_vertex_attribute_iv(P, index));
        if constexpr (P == glf::VertexAttribute::Parameter::BufferBinding)  return static_cast<gl::uint32_t> (get_vertex_attribute_iv(P, index));
        if constexpr (P == glf::VertexAttribute::Parameter::Binding)        return static_cast<gl::uint32_t> (get_vertex_attribute_iv(P, index));
        if constexpr (P == glf::VertexAttribute::Parameter::RelativeOffset) return static_cast<gl::uint32_t> (get_vertex_attribute_iv(P, index));
    }






















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
    static void invalidate_buffer_data   (gl::handle_t buffer, gl::byterange_t range)
    {
        glInvalidateBufferSubData(gl::to_underlying(buffer), range.offset, range.size);
    }
    
    static void copy_buffer_sub_data     (gl::handle_t source, gl::handle_t destination, gl::byterange_t sourceRange, gl::offset_t destinationOffset)
    {
        glCopyNamedBufferSubData(gl::to_underlying(source), gl::to_underlying(destination), sourceRange.offset, destinationOffset, sourceRange.size);
    }
    
    template<typename T>
    static auto get_buffer_data          (gl::handle_t buffer, std::optional<gl::byterange_t> range)
    {
        const auto& size = gl::get_buffer_parameter_v<glf::Buffer::Parameter::Size>();

        std::vector<T> data{};

        if (range.has_value())
        {
            const auto& v = range.value();

            if (std::cmp_greater((v.offset + v.size) > size)) throw std::invalid_argument{ "The given size exceeds the buffer size!" };

            data.resize(v.size);
            glGetNamedBufferSubData(gl::to_underlying(buffer), v.offset, v.size, data.data());
        }
        else
        {
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

        const auto& binaryLength = gl::get_program_v<glf::Program::Parameter::BinaryLength>(program);
        binary.resize(static_cast<std::size_t>(binaryLength));

        glGetProgramBinary(gl::to_underlying(program), binaryLength, nullptr, &format, binary.data());

        struct result{ std::vector<gl::uint8_t> binary; gl::enum_t format; };
        return result{ binary, format };
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

        const auto& maximumLength = gl::get_program_v<glf::Program::Parameter::ActiveUniformMaximumLength>(program);
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

        const auto& maximumLength = gl::get_program_v<glf::Program::Parameter::ActiveUniformMaximumLength>(program);
        name.resize(maximumLength);

        glGetActiveUniform(gl::to_underlying(program), index, maximumLength, &length, &size, &type, name.data());

        if (std::cmp_less(length, maximumLength)) name.resize(static_cast<std::size_t>(length) - 1u);

        struct result{ std::string name; glf::DataType type; };
        return result{ name, glf::DataType{ type } };
    }

    static auto get_uniform_block_index(gl::handle_t program, const std::string& identifier)
    {
        const auto&  cstr  = identifier.c_str();
        gl::uint32_t value = glGetUniformBlockIndex(gl::to_underlying(program), cstr);

        return value;
    }
    static auto get_active_uniform_block_name(gl::handle_t program, gl::uint32_t index)
    {
        const auto& numUniformBlocks = gl::get_program_v<glf::Program::Parameter::ActiveUniformBlocks>(program);
        if (std::cmp_greater_equal(index, numUniformBlocks)) throw std::invalid_argument{ "Index is greater than the amount of uniform blocks!" };

        std::string name{};
        gl::sizei_t length{};

        const auto& maximumLength = gl::get_program_interface_v<glf::Program::Interface::UniformBlock, glf::Program::Property::MaximumNameLength>(program);
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

        const auto& maximumSize = gl::get_program_stage_v<glf::Program::StageProperty::ActiveSubroutineMaximumLength>(program, type);
        name.resize(maximumSize);

        glGetActiveSubroutineName(gl::to_underlying(program), gl::to_underlying(type), index, maximumSize, &length, name.data());

        if (std::cmp_less(length, maximumSize)) name.resize(static_cast<std::size_t>(length) - 1u);

        return name;
    }
    static auto get_active_subroutine_uniform_name(gl::handle_t program, glf::Shader::Type type, gl::uint32_t index)
    {
        std::string name{};
        gl::sizei_t length{};

        const auto& maximumSize = gl::get_program_stage_v<glf::Program::StageProperty::ActiveSubroutineUniformMaximumLength>(program, type);
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

        const auto& attachedShaders = gl::get_program_v<glf::Program::Parameter::AttachedShaders>(program);
        shaders.resize(attachedShaders);

        glGetAttachedShaders(gl::to_underlying(program), attachedShaders, nullptr, gl::to_underlying_ptr(shaders.data()));

        return shaders;
    }
    static auto shader_info_log(gl::handle_t shader)
    {
        std::string infoLog{};

        const auto& infoLogLength = get_shader_v<glf::Shader::Parameter::InfoLogLength>(shader);
        infoLog.resize(infoLogLength);

        glGetShaderInfoLog(gl::to_underlying(shader), infoLogLength, nullptr, infoLog.data());

        if (!infoLog.empty()) infoLog.resize(infoLog.size() - 1u);

        return infoLog;
    }
    static auto program_info_log(gl::handle_t program)
    {
        std::string infoLog{};

        const auto& infoLogLength = gl::get_program_v<glf::Program::Parameter::InfoLogLength>(program);
        infoLog.resize(infoLogLength);

        glGetProgramInfoLog(gl::to_underlying(program), infoLogLength, nullptr, infoLog.data());

        if (!infoLog.empty()) infoLog.resize(infoLog.size() - 1u);

        return infoLog;
    }
    static auto pipeline_info_log(gl::handle_t pipeline)
    {
        std::string infoLog{};

        const auto& infoLogLength = gl::get_program_pipeline_v(pipeline, glf::Program::Pipeline::Property::InfoLogLength);
        infoLog.resize(infoLogLength);

        glGetProgramPipelineInfoLog(gl::to_underlying(pipeline), infoLogLength, nullptr, infoLog.data());

        if (!infoLog.empty()) infoLog.resize(infoLog.size() - 1u);

        return infoLog;
    }
    static auto get_shader_source(gl::handle_t shader)
    {
        std::string source{};

        const auto& sourceLength = gl::get_shader_v<glf::Shader::Parameter::SourceLength>(shader);
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

            struct result{ std::array<gl::int32_t, 2> range{}; gl::int32_t precision{}; };
            return result{ range, precision };
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

    static void invalidate_texture_image(gl::handle_t texture, gl::uint32_t level)
    {
        glInvalidateTexImage(gl::to_underlying(texture), static_cast<gl::int32_t>(level));
    }
    static void invalidate_texture_sub_image(gl::handle_t texture, gl::uint32_t level, gl::volume_t<gl::uint32_t> volume)
    {
        glInvalidateTexSubImage(
            gl::to_underlying(texture), static_cast<gl::int32_t>(level),
            static_cast<gl::int32_t>(volume.origin.x), static_cast<gl::int32_t>(volume.origin.y), static_cast<gl::int32_t>(volume.origin.z),
            static_cast<gl::sizei_t>(volume.extent.x), static_cast<gl::sizei_t>(volume.extent.y), static_cast<gl::sizei_t>(volume.extent.z));
    }

    static void clear_texture_image_data(gl::handle_t texture, glf::Texture::BaseFormat format, glf::Texture::Type type, gl::uint32_t level, std::span<const gl::byte_t> data)
    {
        glClearTexImage(
            gl::to_underlying(texture), static_cast<gl::int32_t>(level), 
            gl::to_underlying(format), 
            gl::to_underlying(type),
            data.data());
    }
    static void clear_texture_sub_image_data(gl::handle_t texture, gl::volume_t<gl::uint32_t> volume, gl::uint32_t level, glf::Texture::BaseFormat format, glf::Texture::Type type, std::span<const gl::byte_t> data)
    {
        glClearTexSubImage(
            gl::to_underlying(texture),  static_cast<gl::int32_t>(level), 
            static_cast<gl::int32_t>(volume.origin.x), static_cast<gl::int32_t>(volume.origin.y), static_cast<gl::int32_t>(volume.origin.z),
            static_cast<gl::sizei_t>(volume.extent.x), static_cast<gl::sizei_t>(volume.extent.y), static_cast<gl::sizei_t>(volume.extent.z), 
            gl::to_underlying(format), 
            gl::to_underlying(type), 
            data.data());
    }

    static void bind_image_texture(gl::handle_t image, gl::handle_t texture, glf::Image::Format format, glf::Image::Access access, gl::uint32_t level, gl::bool_t isLayered, gl::uint32_t layer)
    {
        glBindImageTexture(
            gl::to_underlying(image), 
            gl::to_underlying(texture),
            static_cast<gl::int32_t>(level),
            isLayered, layer, 
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
        return glf::FrameBuffer::Status{ glCheckNamedFramebufferStatus(gl::to_underlying(frameBuffer), gl::to_underlying(glf::FrameBuffer::Target::FrameBuffer)) };
    }




    //Chapter 10 - Vertex Specification and Drawing Commands
    static void patch_parameter_separate(glf::Patch::Parameter parameter, gl::int32_t value)
    {
        glPatchParameteri(gl::to_underlying(parameter), value);
    }

    template<typename T, gl::uint32_t N, gl::bool_t NORM = gl::False>
    static void vertex_attribute(gl::uint32_t index, const gl::Vector<T, N>& value)
    {
        const auto& maximumAttributes = gl::get_v<glf::Data::MaximumVertexAttributes>();
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
        const auto& maximumVertexAttributes = gl::get_v<glf::Data::MaximumVertexAttributes>();
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
    static void draw_arrays_instanced_base_instance(glf::Draw::Mode mode, gl::range_t range, gl::sizei_t instanceCount, gl::uint32_t baseInstance)
    {
        glDrawArraysInstancedBaseInstance(gl::to_underlying(mode), static_cast<gl::int32_t>(range.offset), static_cast<gl::sizei_t>(range.count), instanceCount, baseInstance);
    }
    static void draw_arrays_instanced(glf::Draw::Mode mode, gl::range_t range, gl::sizei_t instanceCount)
    {
        glDrawArraysInstanced(gl::to_underlying(mode), range.offset, range.count, instanceCount);
    }
    static void draw_elements(glf::Draw::Mode mode, glf::Draw::Type type, gl::count_t count)
    {
        glDrawElements(gl::to_underlying(mode), static_cast<gl::sizei_t>(count), gl::to_underlying(type), nullptr);
    }
    static void draw_elements_instanced_base_instance(glf::Draw::Mode mode, glf::Draw::Type type, gl::sizei_t count, gl::uint32_t instanceCount, gl::uint32_t baseInstance)
    {
        glDrawElementsInstancedBaseInstance(gl::to_underlying(mode), static_cast<gl::sizei_t>(count), gl::to_underlying(type), nullptr, static_cast<gl::sizei_t>(instanceCount), baseInstance);
    }
    static void draw_elements_instanced(glf::Draw::Mode mode, glf::Draw::Type type, gl::uint32_t count, gl::uint32_t instanceCount)
    {
        glDrawElementsInstanced(gl::to_underlying(mode), static_cast<gl::sizei_t>(count), gl::to_underlying(type), nullptr, static_cast<gl::sizei_t>(instanceCount));
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

        const auto& maximumLength = gl::get_program_v<glf::Program::Parameter::ActiveAttributeMaximumLength>(program);
        name.resize(maximumLength);

        glGetActiveAttrib(gl::to_underlying(program), index, maximumLength, &length, &size, &type, name.data());

        if (std::cmp_less(length, maximumLength)) name.resize(static_cast<std::size_t>(length) - 1u);

        struct result{ std::string name; glf::DataType type; gl::sizei_t size; };
        return result{ name, glf::DataType{ type }, size };
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
        const auto& maximumIndex = gl::get_program_v<glf::Program::Parameter::TransformFeedbackVaryings>(program);
        if (std::cmp_greater_equal(index, maximumIndex)) throw std::invalid_argument{ "The given index is out of range!" };

        std::string name{};
        gl::sizei_t length{};
        gl::int32_t size{};
        gl::enum_t  type{};

        const auto& maximumLength = gl::get_program_v<glf::Program::Parameter::TransformFeedbackVaryingMaximumLength>(program);
        name.resize(maximumLength);

        glGetTransformFeedbackVarying(gl::to_underlying(program), index, maximumLength, &length, &size, &type, name.data());

        if (std::cmp_less(length, maximumLength)) name.resize(static_cast<std::size_t>(length) - 1u);

        struct result{ std::string identifier; glf::DataType type; gl::sizei_t size; };
        return result{ name, glf::DataType{ type }, size };
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

    static void draw_transform_feedback(gl::handle_t transformFeedback, glf::Draw::Mode mode)
    {
        glDrawTransformFeedback(gl::to_underlying(mode), gl::to_underlying(transformFeedback));
    }
    static void draw_transform_feedback_instanced(gl::handle_t transformFeedback, glf::Draw::Mode mode, gl::uint32_t count)
    {
        glDrawTransformFeedbackInstanced(gl::to_underlying(mode), gl::to_underlying(transformFeedback), static_cast<gl::sizei_t>(count));
    }
    static void draw_transform_feedback_stream(gl::handle_t transformFeedback, glf::Draw::Mode mode, gl::uint32_t stream)
    {
        glDrawTransformFeedbackStream(gl::to_underlying(mode), gl::to_underlying(transformFeedback), stream);
    }
    static void draw_transform_feedback_stream_instanced(gl::handle_t transformFeedback, glf::Draw::Mode mode, gl::uint32_t stream, gl::uint32_t count)
    {
        glDrawTransformFeedbackStreamInstanced(gl::to_underlying(mode), gl::to_underlying(transformFeedback), stream, static_cast<gl::sizei_t>(count));
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
    static void polygon_offset(gl::float32_t factor, gl::float32_t units, gl::float32_t clamp = {})
    {
        glPolygonOffsetClamp(factor, units, clamp);
    }

    static void scissor(const gl::area_t<gl::uint32_t>& area)
    {
        glScissor(
            static_cast<gl::int32_t>(area.origin.x), static_cast<gl::int32_t>(area.origin.y), 
            static_cast<gl::sizei_t>(area.extent.x), static_cast<gl::sizei_t>(area.extent.y));
    }
    

    
    //Chapter 15 - Programmable Fragment Processing
    static void bind_frag_data_location(gl::handle_t program, gl::uint32_t index, gl::uint32_t binding, const std::string& identifier)
    {
        const auto* cstr = identifier.c_str();
        glBindFragDataLocationIndexed(gl::to_underlying(program), binding, index, cstr);
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
            const auto& v = area.value();
            glInvalidateNamedFramebufferSubData(
                gl::to_underlying(frameBuffer), 
                static_cast<gl::sizei_t>(attachments.size()), gl::to_underlying_ptr(attachments.data()), 
                static_cast<gl::int32_t>(v.origin.x), static_cast<gl::int32_t>(v.origin.y), 
                static_cast<gl::sizei_t>(v.extent.x), static_cast<gl::sizei_t>(v.extent.y));
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
            sourceVolume.origin.x,           sourceVolume.origin.y,                 sourceVolume.origin.z,
            gl::to_underlying(destination), gl::to_underlying(destinationTarget), destinationLevel,
            destinationVolume.origin.x,      destinationVolume.origin.y,            destinationVolume.origin.z, 
            sourceVolume.extent.x,           sourceVolume.extent.y,                 sourceVolume.extent.z);
    }



    //Chapter 19 - Compute Shaders
    static void dispatch_compute(const gl::Vector3u& groups)
    {
        glDispatchCompute(groups.x, groups.y, groups.z);
    }
    static void dispatch_compute_indirect(gl::offset_t offset)
    {
        glDispatchComputeIndirect(offset);
    }



    //Chapter 20 - Debug Output
    static void                           debug_callback(gl::enum_t source, gl::enum_t type, gl::uint32_t id, gl::enum_t severity, gl::sizei_t length, const gl::char_t* message, const void* parameter)
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
        glDebugMessageControl(gl::to_underlying(source), gl::to_underlying(type), gl::to_underlying(severity), 0, nullptr, state);
    }
    static void                           debug_message_insert(gl::uint32_t id, glf::Debug::Type type, glf::Debug::Severity severity, std::string_view message)
    {
        glDebugMessageInsert(GL_DEBUG_SOURCE_APPLICATION, gl::to_underlying(type), id, gl::to_underlying(severity), static_cast<gl::sizei_t>(message.length()), message.data());
    }
    static void                           push_debug_group(gl::uint32_t id, std::string_view message)
    {
        glPushDebugGroup(GL_DEBUG_SOURCE_APPLICATION, id, static_cast<gl::sizei_t>(message.length()), message.data());
    }
    static void                           pop_debug_group()
    {
        glPopDebugGroup();
    }
    static void                           object_label(gl::handle_t handle, glf::Object::Type type, const std::string& identifier)
    {
        const auto* cstr = identifier.c_str();
        glObjectLabel(gl::to_underlying(type), gl::to_underlying(handle), static_cast<gl::sizei_t>(identifier.length()), cstr);
    }
    static void                           object_pointer_label(gl::sync_t sync, const std::string& identifier)
    {
        const auto* cstr = identifier.c_str();
        glObjectPtrLabel(sync, static_cast<gl::sizei_t>(identifier.length()), cstr);
    }
    static void                           get_debug_message_log()
    {
        __debugbreak();
        //glGetDebugMessageLog()
    }
    static void                           get_object_label()
    {
        __debugbreak();
        //glGetObjectLabel();
    }
    static void                           get_object_pointer_label()
    {
        __debugbreak();
        //glGetObjectPtrLabel();
    }



    //[21.5.0] Hints
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
