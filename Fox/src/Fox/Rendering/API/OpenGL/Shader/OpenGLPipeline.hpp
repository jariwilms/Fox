#pragma once

#include "Fox/Rendering/API/OpenGL/GL.hpp"
#include "Fox/Rendering/API/OpenGL/Shader/OpenGLShader.hpp"
#include "Fox/Rendering/Shader/Pipeline.hpp"

namespace fox::gfx::api::gl
{
    class OpenGLPipeline : public api::Pipeline, public gl::Object
    {
    public:
        using shader_t = OpenGLShader;
        using Manifest = Manifest<shader_t>;

        OpenGLPipeline(Manifest shaders)
            : m_shaders{ shaders }
        {
            m_handle = gl::create_program_pipeline();

            throw std::runtime_error{ "Id method for shaders has not been implemented!" };
            //if (const auto& shader = m_shaders.vertexShader; shader)                 gl::use_program_stages(m_handle, shader->expose_internals().glId, gl::map_shader_stage(shader->stage()));
            //if (const auto& shader = m_shaders.tessellationControlShader; shader)    gl::use_program_stages(m_handle, shader->expose_internals().glId, gl::map_shader_stage(shader->stage()));
            //if (const auto& shader = m_shaders.tessellationEvaluationShader; shader) gl::use_program_stages(m_handle, shader->expose_internals().glId, gl::map_shader_stage(shader->stage()));
            //if (const auto& shader = m_shaders.geometryShader; shader)               gl::use_program_stages(m_handle, shader->expose_internals().glId, gl::map_shader_stage(shader->stage()));
            //if (const auto& shader = m_shaders.fragmentShader; shader)               gl::use_program_stages(m_handle, shader->expose_internals().glId, gl::map_shader_stage(shader->stage()));
        }
        OpenGLPipeline(OpenGLPipeline&& other) noexcept
        {
            *this = std::move(other);
        }
        ~OpenGLPipeline()
        {
            gl::delete_program_pipeline(m_handle);
        }

        void bind()
        {
            gl::bind_program_pipeline(m_handle);
        }

        const Manifest& shaders() const
        {
            return m_shaders;
        }

        OpenGLPipeline& operator=(OpenGLPipeline&& other) noexcept
        {
            m_handle  = other.m_handle;
            m_shaders = other.m_shaders;

            other.m_handle  = {};
            other.m_shaders = {};

            return *this;
        }

    private:
        Manifest m_shaders{};
    };
}
