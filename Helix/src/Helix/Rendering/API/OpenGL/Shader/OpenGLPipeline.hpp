#pragma once

#include "Helix/Rendering/API/OpenGL/GL.hpp"
#include "Helix/Rendering/API/OpenGL/Shader/OpenGLShader.hpp"
#include "Helix/Rendering/API/Implementation/GPipeline.hpp"
#include "Helix/Rendering/Shader/Pipeline.hpp"

namespace hlx::gfx::imp::api
{
    template<>
    class GPipeline<gfx::api::GraphicsAPI::OpenGL> final : public gfx::api::Pipeline
    {
    public:
        using shader_t = GShader<gfx::api::GraphicsAPI::OpenGL>;
        using Manifest = Manifest<shader_t>;

        GPipeline(Manifest shaders)
            : m_shaders{ shaders }
        {
            m_glId = gl::create_program_pipeline();

            if (const auto& shader = m_shaders.vertexShader; shader)                 gl::use_program_stages(m_glId, shader->expose_internals().glId, gl::shader_stage(shader->stage()));
            if (const auto& shader = m_shaders.tessellationControlShader; shader)    gl::use_program_stages(m_glId, shader->expose_internals().glId, gl::shader_stage(shader->stage()));
            if (const auto& shader = m_shaders.tessellationEvaluationShader; shader) gl::use_program_stages(m_glId, shader->expose_internals().glId, gl::shader_stage(shader->stage()));
            if (const auto& shader = m_shaders.geometryShader; shader)               gl::use_program_stages(m_glId, shader->expose_internals().glId, gl::shader_stage(shader->stage()));
            if (const auto& shader = m_shaders.fragmentShader; shader)               gl::use_program_stages(m_glId, shader->expose_internals().glId, gl::shader_stage(shader->stage()));
        }
        GPipeline(GPipeline&& other) noexcept
        {
            *this = std::move(other);
        }
        ~GPipeline()
        {
            if (m_glId) gl::delete_program_pipeline(m_glId);
        }

        void bind()
        {
            gl::bind_program_pipeline(m_glId);
        }

        const Manifest& shaders() const
        {
            return m_shaders;
        }

        GPipeline& operator=(GPipeline&& other) noexcept
        {
            m_glId    = other.m_glId;
            m_shaders = other.m_shaders;

            other.m_glId    = 0u;
            other.m_shaders = {};

            return *this;
        }

    private:
        GLuint m_glId{};

        Manifest m_shaders{};
    };
}
