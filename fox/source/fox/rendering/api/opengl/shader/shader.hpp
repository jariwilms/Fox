#pragma once

#include <stdafx.hpp>

#include <fox/rendering/api/opengl/opengl.hpp>
#include <fox/rendering/base/shader/shader.hpp>

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

            gl::program_parameter<glf::Program::Specification::Separable>(m_handle, gl::True);
            gl::shader_binary(shader, GL_SHADER_BINARY_FORMAT_SPIR_V, binary);
            gl::specialize_shader(shader, "main");

            const auto& compileStatus = gl::get_shader_value<glf::Shader::Parameter::CompileStatus>(shader);
            if (compileStatus != gl::True) throw std::runtime_error{ gl::get_shader_info_log(shader) };
            
            gl::attach_shader(m_handle, shader);
            gl::link_program(m_handle);

            const auto& linkStatus = gl::get_program_value<glf::Program::Parameter::LinkStatus>(m_handle);
            if (linkStatus != gl::True) throw std::runtime_error{ gl::get_program_info_log(m_handle) };

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
