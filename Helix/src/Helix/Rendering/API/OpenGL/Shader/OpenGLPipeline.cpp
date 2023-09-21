#include "stdafx.hpp"

#include "OpenGLPipeline.hpp"

namespace hlx
{
	OpenGLPipeline::OpenGLPipeline()
	{
		m_id = OpenGL::create_program_pipeline();
	}
	OpenGLPipeline::OpenGLPipeline(std::initializer_list<const std::shared_ptr<Shader>> shaders)
		: OpenGLPipeline{}
	{
		std::for_each(shaders.begin(), shaders.end(), [this](const auto& shader) 
			{ 
				stage(shader); 
			});
	}
	OpenGLPipeline::~OpenGLPipeline()
	{
		OpenGL::delete_program_pipeline(m_id);
	}

	void OpenGLPipeline::bind() const
	{
		OpenGL::bind_program_pipeline(m_id);
	}

	void OpenGLPipeline::stage(const std::shared_ptr<Shader> shader)
	{
		const auto& glShader = std::static_pointer_cast<OpenGLShader>(shader);
		OpenGL::use_program_stages(m_id, glShader->id(), glShader->internal_stage());

		switch (shader->stage())
		{
			case Shader::Stage::Vertex:                 m_shaders.at(0) = glShader; break;
			case Shader::Stage::TessellationControl:    m_shaders.at(1) = glShader; break;
			case Shader::Stage::TessellationEvaluation: m_shaders.at(2) = glShader; break;
			case Shader::Stage::Geometry:               m_shaders.at(3) = glShader; break;
			case Shader::Stage::Fragment:               m_shaders.at(4) = glShader; break;

			default: throw std::invalid_argument{ "Invalid shader stage!" };
		}
	}

    const std::shared_ptr<hlx::Shader> OpenGLPipeline::shader(Shader::Stage stage) const
    {
        switch (stage)
        {
            case Shader::Stage::Vertex:                 return m_shaders.at(0);
            case Shader::Stage::TessellationControl:	return m_shaders.at(1);
            case Shader::Stage::TessellationEvaluation: return m_shaders.at(2);
            case Shader::Stage::Geometry:			    return m_shaders.at(3);
            case Shader::Stage::Fragment:			    return m_shaders.at(4);

            default: throw std::invalid_argument{ "Invalid stage!" };
        }
    }
}
