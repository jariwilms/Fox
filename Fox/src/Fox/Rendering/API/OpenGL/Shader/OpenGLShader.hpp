#pragma once

#include "stdafx.hpp"

#include "Fox/Rendering/API/OpenGL/GL.hpp"
#include "Fox/Rendering/Shader/Shader.hpp"

namespace fox::gfx::api::gl
{
    class OpenGLShader : public api::Shader
    {
    public:
        OpenGLShader(Shader::Stage stage, std::span<const byte> binary)
            : Shader{ stage }
        {
            m_glId    = gl::create_program();
            m_glType  = gl::map_shader_type(stage);
            m_glStage = gl::map_shader_stage(stage);

            const auto& glShader = gl::create_shader(m_glType);

            gl::program_parameter(m_glId, GL_PROGRAM_SEPARABLE, GL_TRUE);
            gl::shader_binary(glShader, binary);
            gl::specialize_shader(glShader, "main");

            if (gl::shader_iv(glShader, GL_COMPILE_STATUS) != GL_TRUE) throw std::runtime_error{ gl::shader_infolog(glShader) };

            gl::attach_shader(m_glId, glShader);
            gl::link_program(m_glId);

            if (gl::program_iv(m_glId, GL_LINK_STATUS) != GL_TRUE) throw std::runtime_error{ gl::program_infolog(m_glId) };

            gl::detach_shader(m_glId, glShader);
            gl::delete_shader(glShader);
        }
        OpenGLShader(OpenGLShader&& other) noexcept
            : Shader{ std::move(other) }
        {
            *this = std::move(other);
        }
        ~OpenGLShader()
        {
            if (m_glId) gl::delete_program(m_glId);
        }

        OpenGLShader& operator=(OpenGLShader&& other) noexcept
        {
            m_glId    = other.m_glId;
            m_glType  = other.m_glType;
            m_glStage = other.m_glStage;

            other.m_glId    = 0u;
            other.m_glType  = {};
            other.m_glStage = {};

            return *this;
        }

    private:
        GLuint m_glId{};
        GLenum m_glType{};
        GLenum m_glStage{};
    };
}
