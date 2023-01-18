#include "stdafx.hpp"

#include "OpenGLShader.hpp"

namespace hlx
{
	OpenGLShader::OpenGLShader(Type type, const std::span<byte>& binary)
        : Shader{ type }, m_internalStage{ OpenGL::shader_type(type) }
	{
        m_id = glCreateProgram();
        if (!m_id) throw std::runtime_error{ "Failed to create program!" };

        const auto shaderId = glCreateShader(m_internalStage);
        if (!shaderId) throw std::runtime_error{ "Failed to create shader!" };

        glProgramParameteri(m_id, GL_PROGRAM_SEPARABLE, GL_TRUE);
        glShaderBinary(1, &shaderId, GL_SHADER_BINARY_FORMAT_SPIR_V, binary.data(), binary.size());
        glSpecializeShader(shaderId, "main", 0, nullptr, nullptr);

        auto compiled = OpenGL::shader_parameter(shaderId, GL_COMPILE_STATUS);
        if (!compiled)
        {
            m_error = OpenGL::shader_infolog(shaderId);
            return;
        }

        glAttachShader(m_id, shaderId);
        glLinkProgram(m_id);

        auto linked = OpenGL::program_parameter(m_id, GL_LINK_STATUS);
        if (!linked)
        {
            m_error = OpenGL::program_infolog(m_id);
            return;
        }

        glDetachShader(m_id, shaderId);
        glDeleteShader(shaderId);

		m_valid = true;
	}
    OpenGLShader::~OpenGLShader()
	{
		glDeleteProgram(m_id);
	}

    void OpenGLShader::forward(const std::string& identifier, const bool& value)
    {
        glProgramUniform1i(m_id, OpenGL::program_uniform_location(m_id, identifier), value);
    }
    void OpenGLShader::forward(const std::string& identifier, const int& value)
    {
        glProgramUniform1iv(m_id, OpenGL::program_uniform_location(m_id, identifier), 1, &value);
    }
    void OpenGLShader::forward(const std::string& identifier, const float& value)
    {
        glProgramUniform1fv(m_id, OpenGL::program_uniform_location(m_id, identifier), 1, &value);
    }
    void OpenGLShader::forward(const std::string& identifier, const glm::vec2& value)
    {
        auto res = OpenGL::program_uniform_location(m_id, identifier);
        glProgramUniform2fv(m_id, res, 1, glm::value_ptr(value));
    }
    void OpenGLShader::forward(const std::string& identifier, const glm::vec3& value)
    {
        glProgramUniform3fv(m_id, OpenGL::program_uniform_location(m_id, identifier), 1, glm::value_ptr(value));
    }
    void OpenGLShader::forward(const std::string& identifier, const glm::vec4& value)
    {
        glProgramUniform4fv(m_id, OpenGL::program_uniform_location(m_id, identifier), 1, glm::value_ptr(value));
    }
    void OpenGLShader::forward(const std::string& identifier, const glm::mat2& value)
    {
        glProgramUniformMatrix2fv(m_id, OpenGL::program_uniform_location(m_id, identifier), 1, false, glm::value_ptr(value));
    }
    void OpenGLShader::forward(const std::string& identifier, const glm::mat3& value)
    {
        glProgramUniformMatrix3fv(m_id, OpenGL::program_uniform_location(m_id, identifier), 1, false, glm::value_ptr(value));
    }
    void OpenGLShader::forward(const std::string& identifier, const glm::mat4& value)
    {
        glProgramUniformMatrix4fv(m_id, OpenGL::program_uniform_location(m_id, identifier), 1, false, glm::value_ptr(value));
    }
}
