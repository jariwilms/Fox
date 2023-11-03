#pragma once

#include "Helix/Rendering/API/OpenGL/OpenGL.hpp"
#include "Helix/Rendering/API/OpenGL/Shader/OpenGLShader.hpp"
#include "Helix/Rendering/API/Implementation/GPipeline.hpp"
#include "Helix/Rendering/Shader/Pipeline.hpp"

namespace hlx::gfx::imp::api
{
    template<>
    class GPipeline<gfx::api::GraphicsAPI::OpenGL> final : public gfx::api::Pipeline
    {
    public:
        GPipeline(std::initializer_list<const std::shared_ptr<GShader<gfx::api::GraphicsAPI::OpenGL>>> shaders)
        {
            m_glId = gl::create_program_pipeline();
            
            std::ranges::for_each(shaders, [this](const std::shared_ptr<GShader<gfx::api::GraphicsAPI::OpenGL>>& shader)
                {
                    gl::use_program_stages(m_glId, shader->expose_internals().glId, gl::shader_stage(shader->stage()));

                    switch (shader->stage())
                    {
                        case gfx::api::Shader::Stage::Vertex:                 m_shaders.at(0) = shader; break;
                        case gfx::api::Shader::Stage::TessellationControl:    m_shaders.at(1) = shader; break;
                        case gfx::api::Shader::Stage::TessellationEvaluation: m_shaders.at(2) = shader; break;
                        case gfx::api::Shader::Stage::Geometry:               m_shaders.at(3) = shader; break;
                        case gfx::api::Shader::Stage::Fragment:               m_shaders.at(4) = shader; break;

                        default: throw std::invalid_argument{ "Invalid shader stage!" };
                    }
                });
        }
        ~GPipeline()
        {
            gl::delete_program_pipeline(m_glId);
        }

        void bind()
        {
            gl::bind_program_pipeline(m_glId);
        }

        GLuint id() const
        {
            return m_glId;
        }

    private:
        GLuint m_glId{};

        std::array<std::shared_ptr<GShader<gfx::api::GraphicsAPI::OpenGL>>, 5> m_shaders{};
    };
}
