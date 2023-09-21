#include "stdafx.hpp"

#include "OpenGLShader.hpp"

#include "Helix/Rendering/API/OpenGL/OpenGL.hpp"

namespace hlx
{
	OpenGLShader::OpenGLShader(Stage stage, std::span<const byte> binary)
        : Shader{ stage }
	{
        m_id = glCreateProgram();
        m_internalStage   = OpenGL::shader_stage(stage);
        m_internalType    = OpenGL::shader_type(stage);
        m_internalShader  = glCreateShader(m_internalType);

        glProgramParameteri(m_id, GL_PROGRAM_SEPARABLE, GL_TRUE);
        glShaderBinary(1, &m_internalShader, GL_SHADER_BINARY_FORMAT_SPIR_V, binary.data(), static_cast<GLsizei>(binary.size()));
        glSpecializeShader(m_internalShader, "main", 0, nullptr, nullptr);

        const auto& compiled = OpenGL::shader_parameter(m_internalShader, GL_COMPILE_STATUS);
        if (!compiled) throw std::runtime_error{ OpenGL::shader_infolog(m_internalShader) };

        glAttachShader(m_id, m_internalShader);
        glLinkProgram(m_id);

        const auto& linked = OpenGL::program_parameter(m_id, GL_LINK_STATUS);
        if (!linked) throw std::runtime_error{ OpenGL::program_infolog(m_id) };

        glDetachShader(m_id, m_internalShader);
        glDeleteShader(m_internalShader);
	}
    OpenGLShader::~OpenGLShader()
	{
		glDeleteProgram(m_id);
	}
}
