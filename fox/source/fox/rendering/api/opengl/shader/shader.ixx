export module fox.rendering.api.opengl.shader;

import std;
import <glad/gl.h>;
import fox.rendering.api.opengl;
import fox.rendering.base.shader;

export namespace fox::gfx::api::gl
{
    class shader : public gl::object
    {
    public:
        using stage_e = api::shader::stage_e;

        shader(stage_e stage_e, std::span<const gl::byte_t> binary)
            : gl::object{ gl::create_program(), [](auto* handle) { gl::delete_program(*handle); }}
            , stage_{ stage_e }
        {
            auto type   = gl::map_shader_type(stage_e);
            auto shader = gl::create_shader  (type );

            gl::program_parameter<gl::program_specification_e::separable>(handle(), gl::true_);
            gl::shader_binary(shader, GL_SHADER_BINARY_FORMAT_SPIR_V, binary);
            gl::specialize_shader(shader, "main");

            auto compileStatus = gl::get_shader_value<gl::shader_parameter_e::compile_status>(shader);
            if (compileStatus != gl::true_) throw std::runtime_error{ gl::get_shader_info_log(shader) };
            
            gl::attach_shader(handle(), shader);
            gl::link_program (handle());

            auto linkStatus = gl::get_program_value<gl::program_parameter_e::link_status>(handle());
            if (linkStatus != gl::true_) throw std::runtime_error{ gl::get_program_info_log(handle()) };

            gl::detach_shader(handle(), shader);
            gl::delete_shader(         shader);
        }

        auto stage() const -> stage_e
        {
            return stage_;
        }

    private:
        stage_e stage_;
    };
}
