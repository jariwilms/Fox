#pragma once

#include "stdafx.hpp"

#include "Fox/Rendering/API/OpenGL/GL.hpp"
#include "Fox/Rendering/Shader/Shader.hpp"

namespace fox::gfx::api::gl
{
    class OpenGLShader : public api::Shader, public gl::Object
    {
    public:
        OpenGLShader(Shader::Stage stage, std::span<const byte> binary)
            : Shader{ stage }
        {
            m_handle  = gl::create_program();
            m_glType  = gl::map_shader_type(stage);
            m_glStage = gl::map_shader_stage(stage);

            const auto& glShader = gl::create_shader(m_glType);

            gl::program_parameter(m_handle, GL_PROGRAM_SEPARABLE, GL_TRUE);
            gl::shader_binary(glShader, binary);
            gl::specialize_shader(glShader, "main");

            if (gl::shader_iv(glShader, GL_COMPILE_STATUS) != GL_TRUE) throw std::runtime_error{ gl::shader_infolog(glShader) };

            gl::attach_shader(m_handle, glShader);
            gl::link_program(m_handle);

            if (gl::program_iv(m_handle, GL_LINK_STATUS) != GL_TRUE) throw std::runtime_error{ gl::program_infolog(m_handle) };

            gl::detach_shader(m_handle, glShader);
            gl::delete_shader(glShader);
        }
        OpenGLShader(OpenGLShader&& other) noexcept
            : Shader{ std::move(other) }
        {
            *this = std::move(other);
        }
        ~OpenGLShader()
        {
            gl::delete_program(m_handle);
        }

        OpenGLShader& operator=(OpenGLShader&& other) noexcept
        {
            m_handle  = other.m_handle;
            m_glType  = other.m_glType;
            m_glStage = other.m_glStage;

            other.m_handle  = {};
            other.m_glType  = {};
            other.m_glStage = {};

            return *this;
        }

    private:
        enum_t m_glType{};
        enum_t m_glStage{};
    };
}
