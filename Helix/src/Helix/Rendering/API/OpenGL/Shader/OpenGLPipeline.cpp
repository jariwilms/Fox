#include "stdafx.hpp"

#include "OpenGLPipeline.hpp"

namespace hlx
{
	OpenGLPipeline::OpenGLPipeline()
	{
		glCreateProgramPipelines(1, &m_id);
	}
	OpenGLPipeline::OpenGLPipeline(std::initializer_list<std::shared_ptr<Shader>> shaders)
	{
		glCreateProgramPipelines(1, &m_id);

		for (const auto& shader : shaders)
			stage(shader);
	}
	OpenGLPipeline::~OpenGLPipeline()
	{
		glDeleteProgramPipelines(1, &m_id);
	}

	void OpenGLPipeline::bind() const
	{
		//TODO before implementing: read https://www.khronos.org/opengl/wiki/Shader_Compilation#Program_pipelines
		glBindProgramPipeline(m_id);
	}
	void OpenGLPipeline::unbind() const
	{
		glBindProgramPipeline(0);
	}
	bool OpenGLPipeline::is_bound() const
	{
		return false;
	}

	void OpenGLPipeline::stage(std::shared_ptr<Shader> shader)
	{
		const auto stage = OpenGL::shader_stage(shader->type());
		glUseProgramStages(m_id, stage, shader->id());
	}

	void OpenGLPipeline::forward(std::string_view identifier, const bool& value)
	{
		glUniform1i(uniform_location(identifier), value);
	}
	void OpenGLPipeline::forward(std::string_view identifier, const int& value)
	{
		glUniform1i(uniform_location(identifier), value);
	}
	void OpenGLPipeline::forward(std::string_view identifier, const float& value)
	{
		glUniform1f(uniform_location(identifier), value);
	}
	void OpenGLPipeline::forward(std::string_view identifier, const glm::vec2& value)
	{
		glUniform2fv(uniform_location(identifier), 1, glm::value_ptr(value));
	}
	void OpenGLPipeline::forward(std::string_view identifier, const glm::vec3& value)
	{
		glUniform3fv(uniform_location(identifier), 1, glm::value_ptr(value));
	}
	void OpenGLPipeline::forward(std::string_view identifier, const glm::vec4& value)
	{
		glUniform4fv(uniform_location(identifier), 1, glm::value_ptr(value));
	}
	void OpenGLPipeline::forward(std::string_view identifier, const glm::mat2& value)
	{
		glUniformMatrix2fv(uniform_location(identifier), 1, GL_FALSE, glm::value_ptr(value));
	}
	void OpenGLPipeline::forward(std::string_view identifier, const glm::mat3& value)
	{
		glUniformMatrix3fv(uniform_location(identifier), 1, GL_FALSE, glm::value_ptr(value));
	}
	void OpenGLPipeline::forward(std::string_view identifier, const glm::mat4& value)
	{
		glUniformMatrix4fv(uniform_location(identifier), 1, GL_FALSE, glm::value_ptr(value));
	}

    void OpenGLPipeline::forward_uniform(std::string_view identifier, size_t size, const void* data)
    {

    }

	GLint OpenGLPipeline::uniform_location(std::string_view identifier)
    {
        std::string name{ identifier };

        return glGetUniformLocation(m_id, name.c_str());
    }
}
