#pragma once

#include "stdafx.hpp"

#include "Fox/Rendering/API/OpenGL/Types.hpp"
#include "Fox/Rendering/API/OpenGL/Mapping.hpp"

namespace fox::gfx::api::gl
{
    //Buffer
    static gl::handle_t                   create_buffer()
    {
        gl::uint32_t handle{};
        glCreateBuffers(1, &handle);

        return gl::handle_t{ handle };
    }
    static void                           delete_buffer(gl::handle_t buffer)
    {
        glDeleteBuffers(1, reinterpret_cast<gl::uint32_t*>(&buffer));
    }
    static void                           bind_buffer_base(gl::handle_t buffer, gl::Flags::Buffer::TargetBase target, gl::index_t index)
    {
        glBindBufferBase(static_cast<gl::enum_t>(target), static_cast<gl::uint32_t>(index), static_cast<gl::uint32_t>(buffer));
    }
    static void                           bind_buffer_range(gl::handle_t buffer, gl::Flags::Buffer::TargetRange target, gl::index_t index, gl::sizeptr_t size, gl::intptr_t offset)
    {
        glBindBufferRange(static_cast<gl::enum_t>(target), static_cast<gl::uint32_t>(index), static_cast<gl::uint32_t>(buffer), offset, size);
    }
    static void                           buffer_storage(gl::handle_t buffer, gl::Flags::Buffer::StorageFlags flags, gl::sizeptr_t size)
    {
        glNamedBufferStorage(static_cast<gl::uint32_t>(buffer), size, nullptr, static_cast<gl::bitfield_t>(flags));
    }
    template<typename T>                  
    static void                           buffer_storage(gl::handle_t buffer, gl::Flags::Buffer::StorageFlags flags, std::span<const T> data)
    {
        glNamedBufferStorage(static_cast<gl::uint32_t>(buffer), static_cast<gl::sizeptr_t>(data.size_bytes()), data.data(), flags);
    }
    template<typename T>                  
    static void                           buffer_sub_data(gl::handle_t buffer, gl::intptr_t offset, std::span<const T> data)
    {
        glNamedBufferSubData(static_cast<gl::uint32_t>(buffer), offset, static_cast<gl::sizeptr_t>(data.size_bytes()), data.data());
    }
    static void                           copy_buffer_sub_data(gl::handle_t source, gl::handle_t destination, gl::sizeptr_t size, gl::sizeptr_t sourceOffset, gl::sizeptr_t destinationOffset)
    {
        glCopyNamedBufferSubData(static_cast<gl::uint32_t>(source), static_cast<gl::uint32_t>(destination), sourceOffset, destinationOffset, size);
    }
    static void*                          map_buffer(gl::handle_t buffer, gl::size_t size) //TODO: Keep mapped buffer data in context and return reference to that data, allows better management of memory
    {
        return glMapNamedBuffer(static_cast<gl::uint32_t>(buffer), GL_READ_WRITE);
    }
    static void*                          map_buffer_range(gl::handle_t buffer, gl::enum_t access, gl::sizeptr_t size, gl::intptr_t offset) //TODO: inptr_t correct for offset?
    {
        return glMapNamedBufferRange(static_cast<gl::uint32_t>(buffer), offset, size, access);
    }
    static void                           unmap_buffer(gl::handle_t buffer)
    {
        const auto& isValidState = glUnmapNamedBuffer(static_cast<gl::uint32_t>(buffer));
        if (isValidState != gl::True) throw std::runtime_error{ "Buffer data store may be undefined!" };
    }
    static void                           invalidate_buffer_data(gl::handle_t buffer)
    {
        glInvalidateBufferData(static_cast<gl::uint32_t>(buffer));
    }
    static void                           invalidate_buffer_sub_data(gl::handle_t buffer, gl::intptr_t size, gl::sizeptr_t offset)
    {
        glInvalidateBufferSubData(static_cast<gl::int32_t>(buffer), offset, size);
    }

    //Transform Feedback
    static gl::handle_t                   create_transform_feedback()
    {
        gl::uint32_t transformFeedback{};
        glCreateTransformFeedbacks(1, &transformFeedback);

        return gl::handle_t{ transformFeedback };
    }
    static void                           delete_transform_feedback(gl::handle_t transformFeedback)
    {
        glDeleteTransformFeedbacks(1, reinterpret_cast<gl::uint32_t*>(&transformFeedback));
    }
    static void                           bind_transform_feedback(gl::handle_t buffer)
    {
        glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, static_cast<gl::uint32_t>(buffer));
    }
    static void                           begin_transform_feedback(gl::Flags::TransformFeedback::PrimitiveMode mode)
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

    //VertexArray
    static gl::handle_t                   create_vertex_array()
    {
        gl::uint32_t vertexArray{};
        glCreateVertexArrays(1, &vertexArray);

        return gl::handle_t{ vertexArray };
    }
    static void                           delete_vertex_array(gl::handle_t vertexArray)
    {
        glDeleteVertexArrays(1, reinterpret_cast<gl::uint32_t*>(&vertexArray));
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
    static void                           vertex_array_attribute_format(gl::handle_t vertexArray, gl::uint32_t index, gl::uint32_t offset, gl::enum_t type, gl::int32_t count, gl::bool_t normalized)
    {
        glVertexArrayAttribFormat(static_cast<gl::uint32_t>(vertexArray), index, count, type, normalized, offset);
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



    //Texture
    static gl::handle_t                   create_texture(gl::enum_t target)
    {
        gl::uint32_t texture{};
        glCreateTextures(target, 1, &texture);

        return gl::handle_t{ texture };
    }
    static void                           delete_texture(gl::handle_t texture)
    {
        glDeleteTextures(1, reinterpret_cast<gl::uint32_t*>(&texture));
    }
    static void                           bind_texture_unit(gl::handle_t texture, gl::uint32_t slot)
    {
        glBindTextureUnit(static_cast<gl::uint32_t>(slot), static_cast<gl::uint32_t>(texture));
    }
    static void                           texture_parameter(gl::handle_t texture, gl::Flags::Texture::Parameter parameter, gl::int32_t value)
    {
        glTextureParameteri(static_cast<gl::uint32_t>(texture), static_cast<gl::enum_t>(parameter), value);
    }
    static void                           texture_storage_1d(gl::handle_t texture, gl::enum_t format, const fox::Vector1u& dimensions, gl::size_t levels)
    {
        glTextureStorage1D(static_cast<gl::uint32_t>(texture), levels, format, static_cast<gl::size_t>(dimensions.x));
    }
    static void                           texture_storage_2d(gl::handle_t texture, gl::enum_t format, const fox::Vector2u& dimensions, gl::size_t levels)
    {
        glTextureStorage2D(static_cast<gl::uint32_t>(texture), levels, format, static_cast<gl::size_t>(dimensions.x), static_cast<gl::size_t>(dimensions.y));
    }
    static void                           texture_storage_3d(gl::handle_t texture, gl::enum_t format, const fox::Vector3u& dimensions, gl::size_t levels)
    {
        glTextureStorage3D(static_cast<gl::uint32_t>(texture), levels, format, static_cast<gl::size_t>(dimensions.x), static_cast<gl::size_t>(dimensions.y), static_cast<gl::size_t>(dimensions.z));
    }
    static void                           texture_storage_2d_multisample(gl::handle_t texture, gl::enum_t format, const fox::Vector2u& dimensions, gl::size_t samples)
    {
        glTextureStorage2DMultisample(static_cast<gl::uint32_t>(texture), samples, format, static_cast<gl::size_t>(dimensions.x), static_cast<gl::size_t>(dimensions.y), GL_TRUE);
    }
    static void                           texture_storage_3d_multisample(gl::handle_t texture, gl::enum_t format, const fox::Vector3u& dimensions, gl::size_t samples)
    {
        glTextureStorage3DMultisample(static_cast<gl::uint32_t>(texture), samples, format, static_cast<gl::size_t>(dimensions.x), static_cast<gl::size_t>(dimensions.y), static_cast<gl::size_t>(dimensions.z), GL_TRUE);
    }
    static void                           texture_sub_image_1d(gl::handle_t texture, gl::enum_t format, const fox::Vector1u& dimensions, const fox::Vector1u& offset, gl::int32_t level, const void* data)
    {
        glTextureSubImage1D(static_cast<gl::uint32_t>(texture), level, static_cast<gl::int32_t>(offset.x), static_cast<gl::size_t>(dimensions.x), format, GL_UNSIGNED_BYTE, data);
    }
    static void                           texture_sub_image_2d(gl::handle_t texture, gl::enum_t format, const fox::Vector2u& dimensions, const fox::Vector2u& offset, gl::uint32_t level, const void* data)
    {
        glTextureSubImage2D(static_cast<gl::uint32_t>(texture), level, static_cast<gl::int32_t>(offset.x), static_cast<gl::int32_t>(offset.y), static_cast<gl::size_t>(dimensions.x), static_cast<gl::size_t>(dimensions.y), format, GL_UNSIGNED_BYTE, data);
    }
    static void                           texture_sub_image_3d(gl::handle_t texture, gl::enum_t format, const fox::Vector3u& dimensions, const fox::Vector3u& offset, gl::int32_t level, const void* data) //80 column rule my ass
    {
        glTextureSubImage3D(static_cast<gl::uint32_t>(texture), level, static_cast<gl::int32_t>(offset.x), static_cast<gl::int32_t>(offset.y), static_cast<gl::int32_t>(offset.z), static_cast<gl::size_t>(dimensions.x), static_cast<gl::size_t>(dimensions.y), static_cast<gl::size_t>(dimensions.z), format, GL_UNSIGNED_BYTE, data);
    }
    static void                           copy_texture_sub_image_2d(gl::handle_t texture, gl::int32_t level, const fox::Vector2u& sourceOffset, const fox::Vector4u& destinationArea)
    {
        const fox::Vector2u area{ destinationArea.z - destinationArea.x, destinationArea.w - destinationArea.y };

        glCopyTextureSubImage2D(
            static_cast<gl::uint32_t>(texture),
            level,
            destinationArea.x, destinationArea.y,
            sourceOffset.x,    sourceOffset.y,
            area.x,            area.y);
    }
    static void                           generate_texture_mipmap(gl::handle_t texture)
    {
        glGenerateTextureMipmap(static_cast<gl::uint32_t>(texture));
    }
    static void                           texture_barrier()
    {
        glTextureBarrier();
    }
    static void                           invalidate_texture_image(gl::handle_t texture, gl::int32_t level)
    {
        glInvalidateTexImage(static_cast<gl::uint32_t>(texture), level);
    }
    static void                           invalidate_texture_sub_image(gl::handle_t texture, gl::int32_t level, const fox::Vector3u& size, const fox::Vector3u& offset)
    {
        glInvalidateTexSubImage(static_cast<gl::uint32_t>(texture), level, offset.x, offset.y, offset.z, size.x, size.y, size.z);
    }

    //Texture Sampler
    static gl::handle_t                   create_sampler()
    {
        gl::uint32_t sampler{};
        glCreateSamplers(1, &sampler);

        return gl::handle_t{ sampler };
    }
    static void                           delete_sampler(gl::handle_t sampler)
    {
        glDeleteSamplers(1, reinterpret_cast<gl::uint32_t*>(&sampler));
    }
    static void                           bind_sampler(gl::handle_t sampler, gl::uint32_t slot)
    {
        glBindSampler(slot, static_cast<gl::uint32_t>(sampler));
    }
    static void                           bind_samplers(gl::uint32_t index, gl::size_t count, std::span<const gl::handle_t> samplers)
    {
        glBindSamplers(index, count, reinterpret_cast<const gl::uint32_t*>(samplers.data()));
    }
    static void                           sampler_parameter(gl::handle_t sampler, gl::Flags::Sampler::Parameter parameter, std::span<const gl::int32_t> value)
    {
        glSamplerParameteriv(static_cast<gl::uint32_t>(sampler), static_cast<gl::enum_t>(parameter), value.data());
    }

    //RenderBuffer
    static gl::handle_t                   create_render_buffer()
    {
        gl::uint32_t renderBuffer{};
        glCreateRenderbuffers(1, &renderBuffer);

        return gl::handle_t{ renderBuffer };
    }
    static void                           delete_render_buffer(gl::handle_t renderBuffer)
    {
        glDeleteRenderbuffers(1, reinterpret_cast<gl::uint32_t*>(&renderBuffer));
    }
    static void                           render_buffer_storage(gl::handle_t renderBuffer, gl::enum_t format, const fox::Vector2u& dimensions)
    {
        glNamedRenderbufferStorage(static_cast<gl::uint32_t>(renderBuffer), format, static_cast<gl::size_t>(dimensions.x), static_cast<gl::size_t>(dimensions.y));
    }
    static void                           render_buffer_storage_multisample(gl::handle_t renderBuffer, gl::enum_t format, const fox::Vector2u& dimensions, std::uint8_t samples)
    {
        glNamedRenderbufferStorageMultisample(static_cast<gl::uint32_t>(renderBuffer), samples, format, static_cast<gl::size_t>(dimensions.x), static_cast<gl::size_t>(dimensions.y));
    }



    //FrameBuffer
    static gl::handle_t                   create_frame_buffer()
    {
        gl::uint32_t frameBuffer{};
        glCreateFramebuffers(1, &frameBuffer);
        
        return gl::handle_t{ frameBuffer };
    }
    static void                           delete_frame_buffer(gl::handle_t frameBuffer)
    {
        glDeleteFramebuffers(1, reinterpret_cast<gl::uint32_t*>(&frameBuffer));
    }
    static void                           bind_frame_buffer(gl::handle_t frameBuffer, gl::Flags::FrameBuffer::Target target)
    {
        glBindFramebuffer(static_cast<gl::enum_t>(target), static_cast<gl::uint32_t>(frameBuffer));
    }
    static void                           frame_buffer_read_buffer(gl::handle_t frameBuffer, gl::Flags::FrameBuffer::Source source)
    {
        glNamedFramebufferReadBuffer(static_cast<gl::uint32_t>(frameBuffer), static_cast<gl::enum_t>(source));
    }
    static void                           frame_buffer_draw_buffer(gl::handle_t frameBuffer, gl::Flags::FrameBuffer::Source source)
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
    static void                           frame_buffer_render_buffer(gl::handle_t frameBuffer, gl::handle_t renderBuffer, gl::enum_t attachment)
    {
        glNamedFramebufferRenderbuffer(static_cast<gl::uint32_t>(frameBuffer), attachment, GL_RENDERBUFFER, static_cast<gl::uint32_t>(renderBuffer));
    }
    static gl::Flags::FrameBuffer::Status check_frame_buffer_status(gl::handle_t frameBuffer)
    {
        return gl::Flags::FrameBuffer::Status{ glCheckNamedFramebufferStatus(static_cast<gl::uint32_t>(frameBuffer), GL_FRAMEBUFFER) };
    }
    static void                           invalidate_frame_buffer(gl::handle_t frameBuffer, std::span<gl::enum_t> attachments)
    {
        glInvalidateNamedFramebufferData(static_cast<gl::uint32_t>(frameBuffer), static_cast<gl::size_t>(attachments.size()), attachments.data());
    }
    static void                           invalidate_frame_buffer_sub_data(gl::handle_t frameBuffer, std::span<gl::enum_t> attachments, const fox::Vector2u& position, const fox::Vector2u& size)
    {
        glInvalidateNamedFramebufferSubData(
            static_cast<gl::uint32_t>(frameBuffer), 
            static_cast<gl::size_t>(attachments.size()), attachments.data(),
            position.x, position.y, 
            size.x,     size.y);
    }



    //Shader
    static gl::handle_t                   create_shader(gl::Flags::Shader::Type type)
    {
        gl::uint32_t shader{};
        shader = glCreateShader(static_cast<gl::enum_t>(type));

        return gl::handle_t{ shader };
    }
    static void                           delete_shader(gl::handle_t shader)
    {
        glDeleteShader(static_cast<gl::uint32_t>(shader));
    }
    static void                           attach_shader(gl::handle_t program, gl::handle_t shader)
    {
        glAttachShader(static_cast<gl::uint32_t>(program), static_cast<gl::uint32_t>(shader));
    }
    static void                           detach_shader(gl::handle_t program, gl::handle_t shader)
    {
        glDetachShader(static_cast<gl::uint32_t>(program), static_cast<gl::uint32_t>(shader));
    }
    static void                           shader_binary(gl::handle_t shader, std::span<const fox::byte> binary)
    {
        glShaderBinary(1, reinterpret_cast<gl::uint32_t*>(&shader), GL_SHADER_BINARY_FORMAT_SPIR_V, binary.data(), static_cast<gl::size_t>(binary.size_bytes()));
    }
    static void                           specialize_shader(gl::handle_t shader, std::string_view entry)
    {
        glSpecializeShader(static_cast<gl::uint32_t>(shader), entry.data(), 0, nullptr, nullptr);
    }
    static gl::int32_t                    shader_iv(gl::handle_t shader, gl::Flags::Shader::Parameter parameter)
    {
        gl::int32_t result{};
        glGetShaderiv(static_cast<gl::uint32_t>(shader), static_cast<gl::enum_t>(parameter), &result);

        return result;
    }
    static std::string                    shader_infolog(gl::handle_t shader)
    {
        const auto& length = shader_iv(shader, gl::Flags::Shader::Parameter::InfoLogLength);

        std::string infolog{};
        infolog.resize(length);

        glGetShaderInfoLog(static_cast<gl::uint32_t>(shader), length, nullptr, infolog.data());

        return infolog;
    }

    //Program
    static gl::handle_t                   create_program()
    {
        return gl::handle_t{ glCreateProgram() };
    }
    static void                           delete_program(gl::handle_t program)
    {
        glDeleteProgram(static_cast<gl::uint32_t>(program));
    }
    static void                           link_program(gl::handle_t program)
    {
        glLinkProgram(static_cast<gl::uint32_t>(program));
    }
    static void                           program_parameter(gl::handle_t program, gl::Flags::Program::Parameter parameter, gl::int32_t value)
    {
        glProgramParameteri(static_cast<gl::uint32_t>(program), static_cast<gl::enum_t>(parameter), value);
    }
    static gl::int32_t                    program_iv(gl::handle_t program, gl::Flags::Program::Parameter parameter)
    {
        gl::int32_t result{};
        glGetProgramiv(static_cast<gl::uint32_t>(program), static_cast<gl::enum_t>(parameter), &result);

        return result;
    }
    static std::string                    program_infolog(gl::handle_t program)
    {
        std::string infolog{};
        const auto& infoLogLength = program_iv(program, gl::Flags::Program::Parameter::InfoLogLength);

        infolog.resize(infoLogLength);
        glGetProgramInfoLog(static_cast<gl::uint32_t>(program), infoLogLength, nullptr, infolog.data());

        return infolog;
    }

    //Pipeline
    static gl::handle_t                   create_program_pipeline()
    {
        gl::uint32_t pipeline{};
        glCreateProgramPipelines(1, &pipeline);

        return gl::handle_t{ pipeline };
    }
    static void                           delete_program_pipeline(gl::handle_t pipeline)
    {
        glDeleteProgramPipelines(1, reinterpret_cast<gl::uint32_t*>(&pipeline));
    }
    static void                           bind_program_pipeline(gl::handle_t pipeline)
    {
        glBindProgramPipeline(static_cast<gl::uint32_t>(pipeline));
    }
    static void                           use_program_stages(gl::handle_t pipeline, gl::handle_t program, gl::bitfield_t stages)
    {
        glUseProgramStages(static_cast<gl::uint32_t>(pipeline), stages, static_cast<gl::uint32_t>(program));
    }



    //Rendering
    static void                           draw_arrays(gl::Flags::Draw::Mode mode, gl::size_t first, gl::size_t vertices)
    {
        glDrawArrays(static_cast<gl::enum_t>(mode), first, vertices);
    }
    static void                           draw_elements(gl::Flags::Draw::Mode mode, gl::Flags::Draw::Type type, gl::size_t indices)
    {
        glDrawElements(static_cast<gl::enum_t>(mode), indices, static_cast<gl::enum_t>(type), nullptr);
    }
    static void                           draw_elements_base_vertex(gl::Flags::Draw::Mode mode, gl::Flags::Draw::Type type, gl::size_t indices, gl::uint32_t offset)
    {
        glDrawElementsBaseVertex(static_cast<gl::enum_t>(mode), indices, static_cast<gl::enum_t>(type), nullptr, offset);
    }
    static void                           draw_elements_range(gl::Flags::Draw::Mode mode, gl::Flags::Draw::Type type, const fox::Vector2u& range, gl::size_t indices)
    {
        glDrawRangeElements(static_cast<gl::enum_t>(mode), range.x, range.y, indices, static_cast<gl::enum_t>(type), nullptr);
    }
    static void                           draw_elements_range_base_vertex(gl::Flags::Draw::Mode mode, gl::Flags::Draw::Type type, const fox::Vector2u& range, gl::size_t indices, gl::uint32_t offset)
    {
        glDrawRangeElementsBaseVertex(static_cast<gl::enum_t>(mode), range.x, range.y, indices, static_cast<gl::enum_t>(type), nullptr, offset);
    }
    static void                           draw_transform_feedback(gl::handle_t transformFeedback, gl::Flags::Draw::Mode mode)
    {
        glDrawTransformFeedback(static_cast<gl::enum_t>(mode), static_cast<gl::uint32_t>(transformFeedback));
    }
    static void                           draw_transform_feedback_stream(gl::handle_t transformFeedback, gl::handle_t stream, gl::Flags::Draw::Mode mode)
    {
        glDrawTransformFeedbackStream(static_cast<gl::enum_t>(mode), static_cast<gl::uint32_t>(transformFeedback), static_cast<gl::uint32_t>(stream));
    }
    
    static void                           blit_framebuffer(gl::handle_t source, gl::handle_t destination, const fox::Vector4u& sourceArea, const fox::Vector4u& destinationArea, gl::bitfield_t mask, gl::Flags::FrameBuffer::Filter filter)
    {
        glBlitNamedFramebuffer(
            static_cast<gl::uint32_t>(source),
            static_cast<gl::uint32_t>(destination),
            sourceArea.x,      sourceArea.y,      sourceArea.z,      sourceArea.w,
            destinationArea.x, destinationArea.y, destinationArea.z, destinationArea.w,
            mask, static_cast<gl::enum_t>(filter));
    }

    //Conditional Rendering
    static void                           begin_conditional_render(gl::handle_t query, gl::Flags::Query::Mode mode)
    {
        glBeginConditionalRender(static_cast<gl::uint32_t>(query), static_cast<gl::enum_t>(mode));
    }
    static void                           end_conditional_render()
    {
        glEndConditionalRender();
    }

    //Compute
    static void                           dispatch_compute(const fox::Vector3u& groups)
    {
        glDispatchCompute(groups.x, groups.y, groups.z);
    }
    static void                           dispatch_compute_indirect(gl::intptr_t offset)
    {
        glDispatchComputeIndirect(offset);
    }



    //Query
    static gl::handle_t                   create_query(gl::Flags::Query::Target target)
    {
        gl::uint32_t query{};
        glCreateQueries(static_cast<gl::enum_t>(target), 1, &query);

        return gl::handle_t{ query };
    }
    static void                           delete_query(gl::handle_t query)
    {
        glDeleteQueries(1, reinterpret_cast<gl::uint32_t*>(&query));
    }
    static void                           begin_query(gl::handle_t query, gl::Flags::Query::Target target)
    {
        //TODO: make template function? => automatic target deduction
        glBeginQuery(static_cast<gl::enum_t>(target), static_cast<gl::uint32_t>(query));
    }
    static void                           begin_query_indexed(gl::handle_t query, gl::Flags::Query::Target target, gl::uint32_t index)
    {
        glBeginQueryIndexed(static_cast<gl::enum_t>(target), index, static_cast<gl::uint32_t>(query));
    }
    static void                           end_query(gl::Flags::Query::Target target)
    {
        glEndQuery(static_cast<gl::enum_t>(target));
    }
    static void                           end_query_indexed(gl::Flags::Query::Target target, gl::uint32_t index)
    {
        glEndQueryIndexed(static_cast<gl::enum_t>(target), index);
    }
    static void                           query_counter(gl::handle_t query)
    {
        glQueryCounter(static_cast<gl::uint32_t>(query), GL_TIMESTAMP);
    }
    static gl::int32_t                    get_query_iv(gl::Flags::Query::Target target)
    {
        gl::int32_t params{};
        glGetQueryiv(static_cast<gl::enum_t>(target), GL_CURRENT_QUERY, &params);

        return params;
    }
    static gl::int32_t                    get_query_object(gl::handle_t query, gl::Flags::Query::Parameter parameter)
    {
        gl::int32_t result{};
        glGetQueryObjectiv(static_cast<gl::uint32_t>(query), static_cast<gl::enum_t>(parameter), &result);

        return result;
    }



    //State
    static gl::int32_t                    integer_v(gl::Flags::Data flag)
    {
        gl::int32_t result{};
        glGetIntegerv(static_cast<gl::enum_t>(flag), &result);

        return result;
    }

    //Control
    static void                           enable(gl::Flags::Capability capability)
    {
        glEnable(static_cast<gl::enum_t>(capability));
    }
    static void                           disable(gl::Flags::Capability capability)
    {
        glDisable(static_cast<gl::enum_t>(capability));
    }

    static void                           blend_color(const fox::Vector4f& color)
    {
        glBlendColor(color.r, color.g, color.b, color.a);
    }
    static void                           blend_function(gl::Flags::Blending::Factor source, gl::Flags::Blending::Factor destination)
    {
        glBlendFunc(static_cast<gl::enum_t>(source), static_cast<gl::enum_t>(destination));
    }
    static void                           blend_function_separate(gl::Flags::Blending::Factor sourceRGB, gl::Flags::Blending::Factor sourceAlpha, gl::Flags::Blending::Factor destinationRGB, gl::Flags::Blending::Factor destinationAlpha)
    {
        glBlendFuncSeparate(static_cast<gl::enum_t>(sourceRGB), static_cast<gl::enum_t>(destinationRGB), static_cast<gl::enum_t>(sourceAlpha), static_cast<gl::enum_t>(destinationAlpha));
    }
    static void                           blend_equation(gl::Flags::Blending::Equation equation)
    {
        glBlendEquation(static_cast<gl::enum_t>(equation));
    }
    static void                           blend_equation_separate(gl::Flags::Blending::Equation equationRGB, gl::Flags::Blending::Equation equationAlpha)
    {
        glBlendEquationSeparate(static_cast<gl::enum_t>(equationRGB), static_cast<gl::enum_t>(equationAlpha));
    }

    static void                           depth_function(gl::Flags::DepthFunction depthFunction)
    {
        glDepthFunc(static_cast<gl::enum_t>(depthFunction));
    }
    static void                           depth_range(const fox::Vector2f& range)
    {
        glDepthRangef(range.x, range.y);
    }
    static void                           depth_mask(gl::bool_t flag)
    {
        glDepthMask(flag);
    }

    static void                           stencil_function(gl::Flags::Stencil::Function function, gl::int32_t value, gl::uint32_t mask)
    {
        glStencilFunc(static_cast<gl::enum_t>(function), value, mask);
    }
    static void                           stencil_function_separate(gl::Flags::Stencil::Face face, gl::Flags::Stencil::Function function, gl::int32_t value, gl::uint32_t mask)
    {
        glStencilFuncSeparate(static_cast<gl::enum_t>(face), static_cast<gl::enum_t>(function), value, mask);
    }
    static void                           stencil_mask(gl::uint32_t mask)
    {
        glStencilMask(mask);
    }
    static void                           stencil_mask_separate(gl::Flags::Stencil::Face face, gl::uint32_t mask)
    {
        glStencilMaskSeparate(static_cast<gl::enum_t>(face), mask);
    }
    static void                           stencil_operation(gl::Flags::Stencil::Action onStencilFail, gl::Flags::Stencil::Action onDepthFail, gl::Flags::Stencil::Action onDepthStencilPass)
    {
        glStencilOp(static_cast<gl::enum_t>(onStencilFail), static_cast<gl::enum_t>(onDepthFail), static_cast<gl::enum_t>(onDepthStencilPass));
    }
    static void                           stencil_operation_separate(gl::Flags::Stencil::Face face, gl::Flags::Stencil::Action onStencilFail, gl::Flags::Stencil::Action onDepthFail, gl::Flags::Stencil::Action onDepthStencilPass)
    {
        glStencilOpSeparate(static_cast<gl::enum_t>(face), static_cast<gl::enum_t>(onStencilFail), static_cast<gl::enum_t>(onDepthFail), static_cast<gl::enum_t>(onDepthStencilPass));
    }

    static void                           clear(gl::bitfield_t mask)
    {
        glClear(mask);
    }
    static void                           clear_color(const fox::Vector4f& color)
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
    
    static void                           scissor(const fox::Vector4u& area)
    {
        glScissor(area.x, area.y, area.z, area.w);
    }
    static void                           viewport(const fox::Vector4u& area)
    {
        glViewport(area.x, area.y, area.z, area.w);
    }

    static void                           polygon_mode(gl::Flags::Polygon::Mode mode)
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

    static void                           cull_face(gl::Flags::Culling::Face face)
    {
        glCullFace(static_cast<gl::enum_t>(face));
    }
    static void                           front_face(gl::Flags::Orientation orientation)
    {
        glFrontFace(static_cast<gl::enum_t>(orientation));
    }

    static void                           clip_control(gl::Flags::Clip::Origin origin, gl::Flags::Clip::DepthMode mode)
    {
        glClipControl(static_cast<gl::enum_t>(origin), static_cast<gl::enum_t>(mode));
    }

    static void                           clamp_color(gl::bool_t value)
    {
        glClampColor(GL_CLAMP_READ_COLOR, value);
    }

    static void                           provoking_vertex(gl::Flags::ProvokingVertex provokingVertex)
    {
        glProvokingVertex(static_cast<gl::enum_t>(provokingVertex));
    }
    static void                           primitive_restart_index(gl::uint32_t index)
    {
        glPrimitiveRestartIndex(index);
    }

    static void                           patch_parameter(gl::Flags::Patch::Parameter parameter, gl::int32_t value)
    {
        glPatchParameteri(static_cast<gl::enum_t>(parameter), value);
    }

    static void                           memory_barrier(gl::Flags::Memory::Barrier barrier)
    {
        glMemoryBarrier(static_cast<gl::bitfield_t>(barrier));
    }
    static void                           memory_barrier_by_region(gl::Flags::Memory::Barrier barrier)
    {
        glMemoryBarrierByRegion(static_cast<gl::bitfield_t>(barrier));
    }

    static void                           release_shader_compiler()
    {
        glReleaseShaderCompiler();
    }

    static void                           flush()
    {
        glFlush();
    }
    static void                           finish()
    {
        glFinish();
    }



    //Synchronization
    static void                           delete_sync(sync_t sync)
    {
        glDeleteSync(sync);
    }
    static void                           fence_sync()
    {
        glFenceSync(GL_SYNC_GPU_COMMANDS_COMPLETE, 0);
    }
    static void                           client_wait_sync(gl::sync_t sync, gl::uint64_t timeout)
    {
        glClientWaitSync(sync, GL_SYNC_FLUSH_COMMANDS_BIT, timeout);
    }
    static void                           server_wait_sync(gl::sync_t sync)
    {
        glWaitSync(sync, 0, GL_TIMEOUT_IGNORED);
    }



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

        //if (severityMessage != "NOTIFICATION") __debugbreak();
        std::cout << std::format("[GL_DEBUG] {0}, {1}, {2}, {3}: {4}", sourceMessage, typeMessage, severityMessage, id, message) << std::endl;
    }
    static void                           debug_message_callback(decltype(debug_callback) callback)
    {
        glDebugMessageCallback(callback, nullptr);
    }
    static void                           debug_message_control(gl::bool_t state, gl::Flags::Debug::Source source, gl::Flags::Debug::Type type, gl::Flags::Debug::Severity severity)
    {
        glDebugMessageControl(static_cast<gl::enum_t>(source), static_cast<gl::enum_t>(type), static_cast<gl::enum_t>(severity), 0, nullptr, state);
    }
    static void                           debug_message_insert(gl::uint32_t id, gl::Flags::Debug::Type type, gl::Flags::Debug::Severity severity, std::string_view message)
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
}
