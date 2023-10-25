#pragma once

#include "Helix/Experimental/Rendering/API/OpenGL/OpenGL.hpp"
#include "Helix/Experimental/Rendering/API/OpenGL/Shader/OpenGLShader.hpp"
#include "Helix/Experimental/Rendering/Shader/Pipeline.hpp"

namespace hlx::gfx::api
{
    template<>
    class GPipeline<GraphicsAPI::OpenGL> : public Pipeline
    {
    public:
        GPipeline(std::initializer_list<const std::shared_ptr<GShader<GraphicsAPI::OpenGL>>> shaders)
        {
            m_glId = gl::create_program_pipeline();
            
            std::ranges::for_each(shaders, [this](const std::shared_ptr<GShader<GraphicsAPI::OpenGL>>& shader)
                {
                    gl::use_program_stages(m_glId, shader->id(), gl::shader_stage(shader->stage()));

                    switch (shader->stage())
                    {
                        case Shader::Stage::Vertex:                 m_shaders.at(0) = shader; break;
                        case Shader::Stage::TessellationControl:    m_shaders.at(1) = shader; break;
                        case Shader::Stage::TessellationEvaluation: m_shaders.at(2) = shader; break;
                        case Shader::Stage::Geometry:               m_shaders.at(3) = shader; break;
                        case Shader::Stage::Fragment:               m_shaders.at(4) = shader; break;

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

        std::array<std::shared_ptr<GShader<GraphicsAPI::OpenGL>>, 5> m_shaders{};
    };
}
