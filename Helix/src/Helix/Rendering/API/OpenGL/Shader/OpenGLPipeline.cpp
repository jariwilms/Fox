#include "stdafx.hpp"

#include "OpenGLPipeline.hpp"

namespace hlx
{
	OpenGLPipeline::OpenGLPipeline()
	{
		glCreateProgramPipelines(1, &m_internalProgram);
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
		glDeleteProgramPipelines(1, &m_internalProgram);
	}

	void OpenGLPipeline::bind() const
	{
		if (m_internalProgram == s_boundPipelineId) return;

		glBindProgramPipeline(m_internalProgram);
		s_boundPipelineId = m_internalProgram;
	}
	void OpenGLPipeline::unbind() const
	{
		if (m_internalProgram != s_boundPipelineId) return;
		
		glBindProgramPipeline(0);
	}
	bool OpenGLPipeline::is_bound() const
	{
		return m_internalProgram == s_boundPipelineId;
	}

	void OpenGLPipeline::stage(const std::shared_ptr<Shader> shader)
	{
		const auto& glShader = std::static_pointer_cast<OpenGLShader>(shader);
		glUseProgramStages(m_internalProgram, glShader->internal_stage(), glShader->internal_program());

		switch (shader->stage())
		{
			case Shader::Stage::Vertex:                 m_shaders.at(0) = shader; break;
			case Shader::Stage::TessellationControl:    m_shaders.at(1) = shader; break;
			case Shader::Stage::TessellationEvaluation: m_shaders.at(2) = shader; break;
			case Shader::Stage::Geometry:               m_shaders.at(3) = shader; break;
			case Shader::Stage::Fragment:               m_shaders.at(4) = shader; break;

			default: throw std::invalid_argument{ "Invalid shader stage!" };
		}
	}
}
