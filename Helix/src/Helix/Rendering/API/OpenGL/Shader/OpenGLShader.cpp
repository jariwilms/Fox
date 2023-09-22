#include "stdafx.hpp"

#include "OpenGLShader.hpp"

#include "Helix/Rendering/API/OpenGL/OpenGL.hpp"

namespace hlx
{
	OpenGLShader::OpenGLShader(Stage stage, std::span<const byte> binary)
        : Shader{ stage }
	{
        m_id               = OpenGL::create_program();
        m_internalStage    = OpenGL::shader_stage(stage);
        m_internalType     = OpenGL::shader_type(stage);
        const auto& shader = OpenGL::create_shader(m_internalType);

        OpenGL::program_parameter(m_id, GL_PROGRAM_SEPARABLE, GL_TRUE);
        OpenGL::shader_binary(shader, binary);
        OpenGL::specialize_shader(shader, "main");

        const auto& compiled = OpenGL::shader_iv(shader, GL_COMPILE_STATUS);
        if (!compiled) throw std::runtime_error{ OpenGL::shader_infolog(shader) };

        OpenGL::attach_shader(m_id, shader);
        OpenGL::link_program(m_id);

        const auto& linked = OpenGL::program_iv(m_id, GL_LINK_STATUS);
        if (!linked) throw std::runtime_error{ OpenGL::program_infolog(m_id) };

        OpenGL::detach_shader(m_id, shader);
        OpenGL::delete_shader(shader);
	}
    OpenGLShader::~OpenGLShader()
	{
        OpenGL::delete_program(m_id);
	}
}
