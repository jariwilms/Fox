#pragma once

#include "stdafx.hpp"

#include "Fox/Rendering/API/OpenGL/OpenGL.hpp"
#include "Fox/Rendering/Shader/Shader.hpp"

namespace fox::gfx::api::gl
{
    class Shader : public api::Shader, public gl::Object
    {
    public:
        Shader(Stage stage, std::span<const fox::byte> binary)
            : api::Shader{ stage }
        {
            m_handle = gl::create_program();

            const auto& type = gl::map_shader_type(stage);
            const auto& shader = gl::create_shader(type);

            gl::program_parameter(m_handle, gl::Flags::Program::Parameter::Separable, gl::True);
            gl::shader_binary(shader, binary);
            gl::specialize_shader(shader, "main");

            const auto& compileStatus = gl::shader_iv(shader, gl::Flags::Shader::Parameter::CompileStatus);
            if (compileStatus != gl::True) throw std::runtime_error{ gl::shader_infolog(shader) };

            gl::attach_shader(m_handle, shader);
            gl::link_program(m_handle);

            const auto& linkStatus = gl::program_iv(m_handle, gl::Flags::Program::Parameter::LinkStatus);
            if (linkStatus != gl::True) throw std::runtime_error{ gl::program_infolog(m_handle) };

            gl::detach_shader(m_handle, shader);
            gl::delete_shader(shader);
        }
        Shader(Shader&& other) noexcept
            : api::Shader{ std::move(other) }
        {
            *this = std::move(other);
        }
        ~Shader()
        {
            gl::delete_program(m_handle);
        }

        Shader& operator=(Shader&& other) noexcept
        {
            m_handle  = other.m_handle;

            other.m_handle  = {};

            return *this;
        }
    };
}
