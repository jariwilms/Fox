#include "stdafx.hpp"

#include "OpenGLShader.hpp"

namespace hlx
{
	OpenGLShader::OpenGLShader(Type type, std::string_view source)
		: Shader{ type }
	{
		const auto sourcePtr = source.data();
		m_internalType = OpenGL::shader_type(type);
		m_id = glCreateShaderProgramv(m_internalType, 1, &sourcePtr);

		const auto isLinked = OpenGL::program_parameter(m_id, GL_LINK_STATUS);
		if (isLinked == GL_FALSE)
		{
			log_error();
			return;
		}

		m_valid = true;
	}
    OpenGLShader::~OpenGLShader()
	{
		glDeleteProgram(m_id);
	}

	void OpenGLShader::log_error()
	{
		GLint messageLength{};
		glGetProgramiv(m_id, GL_INFO_LOG_LENGTH, &messageLength);

		m_error.resize(messageLength);
		glGetProgramInfoLog(m_id, messageLength, nullptr, m_error.data());
	}
}
