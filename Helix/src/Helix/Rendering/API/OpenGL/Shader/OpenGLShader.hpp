#pragma once

#include "stdafx.hpp"

#include "Helix/Rendering/API/OpenGL/OpenGL.hpp"
#include "Helix/Rendering/Shader/Shader.hpp"
#include "Helix/Rendering/API/Implementation/GShader.hpp"
#include "Helix/Rendering/API/OpenGL/Internal/InternalView.hpp"

namespace hlx::gfx::imp::api
{
    template<>
    class GShader<gfx::api::GraphicsAPI::OpenGL> final : public gfx::api::Shader
    {
    public:
        GShader(Shader::Stage stage, std::span<const byte> binary)
            : Shader{ stage }
        {
            m_glId    = gl::create_program();
            m_glType  = gl::shader_type(stage);
            m_glStage = gl::shader_stage(stage);

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
        GShader(GShader&& other) noexcept
            : Shader{ std::move(other) }
        {
            *this = std::move(other);
        }
        ~GShader()
        {
            if (m_glId) gl::delete_program(m_glId);
        }

        auto expose_internals() const
        {
            return InternalView<GShader<gfx::api::GraphicsAPI::OpenGL>>
            {
                m_glId
            };
        }

        GShader& operator=(GShader&& other) noexcept
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
