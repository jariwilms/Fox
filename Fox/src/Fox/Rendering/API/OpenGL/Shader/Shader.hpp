#pragma once

#include "stdafx.hpp"

#include "Fox/Rendering/API/OpenGL/OpenGL.hpp"
#include "Fox/Rendering/Shader/Shader.hpp"

namespace fox::gfx::api::gl
{
    class Shader : public api::Shader, public gl::Object
    {
    public:
        Shader(Stage stage, std::span<const fox::byte_t> binary)
            : api::Shader{ stage }
        {
            m_handle = gl::create_program();

            const auto& type   = gl::map_shader_type(stage);
            const auto& shader = gl::create_shader(type);

            gl::program_specification(m_handle, glf::Program::Specification::Separable, gl::True);
            gl::shader_binary(shader, binary);
            gl::specialize_shader(shader, "main");

            const auto& compileStatus = gl::shader_iv<glf::Shader::Parameter::CompileStatus>(shader);
            if (compileStatus != gl::True) throw std::runtime_error{ gl::shader_infolog(shader) };
            
            gl::attach_shader(m_handle, shader);
            gl::link_program(m_handle);

            const auto& linkStatus = gl::get_program_v<glf::Program::Parameter::LinkStatus>(m_handle);
            if (linkStatus != gl::True) throw std::runtime_error{ gl::program_infolog(m_handle) };

            gl::detach_shader(m_handle, shader);
            gl::delete_shader(shader);
        }
        Shader(Shader&&) noexcept = default;
        ~Shader()
        {
            gl::delete_program(m_handle);
        }

        Shader& operator=(Shader&&) noexcept = default;
    };
}
