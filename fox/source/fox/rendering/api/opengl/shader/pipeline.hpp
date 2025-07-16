#pragma once

#include <fox/rendering/api/opengl/opengl.hpp>
#include <fox/rendering/api/opengl/shader/shader.hpp>
#include <fox/rendering/base/shader/pipeline.hpp>

import fox.rendering.api.opengl.mapping;
import fox.rendering.api.opengl.object;

namespace fox::gfx::api::gl
{
    template<typename T = gl::Shader>
    class Pipeline : public gl::Object
    {
    public:
        using Layout = api::Pipeline::Layout<T>;

        Pipeline(const Layout& layout)
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
