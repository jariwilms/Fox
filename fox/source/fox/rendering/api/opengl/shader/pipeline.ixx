export module fox.rendering.api.opengl.pipeline;

import std;

import fox.rendering.api.opengl;
import fox.rendering.api.opengl.shader;
import fox.rendering.base.pipeline;
import fox.rendering.base.shader;

export namespace fox::gfx::api::gl
{
    template<typename T = gl::Shader>
    class Pipeline : public gl::Object
    {
    public:
        using Layout = api::Pipeline::Layout<T>;

        explicit Pipeline(const Layout& layout)
            : gl::Object{ gl::create_program_pipeline(), [](auto* handle) { gl::delete_program_pipeline(*handle); }}
            , layout_{ layout }
        {
            if (auto shader = layout_.vert; shader) gl::use_program_stages(handle_, shader->handle(), gl::map_program_stage(shader->stage()));
            if (auto shader = layout_.tesc; shader) gl::use_program_stages(handle_, shader->handle(), gl::map_program_stage(shader->stage()));
            if (auto shader = layout_.tese; shader) gl::use_program_stages(handle_, shader->handle(), gl::map_program_stage(shader->stage()));
            if (auto shader = layout_.geom; shader) gl::use_program_stages(handle_, shader->handle(), gl::map_program_stage(shader->stage()));
            if (auto shader = layout_.frag; shader) gl::use_program_stages(handle_, shader->handle(), gl::map_program_stage(shader->stage()));
        }

        void bind()
        {
            gl::bind_program_pipeline(handle_);
        }

        auto layout() const -> const Layout&
        {
            return layout_;
        }

    private:
        Layout layout_;
    };
}
