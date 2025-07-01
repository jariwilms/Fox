#pragma once

#include <fox/rendering/api/opengl/opengl.hpp>
#include <fox/rendering/api/opengl/shader/shader.hpp>
#include <fox/rendering/base/shader/pipeline.hpp>

namespace fox::gfx::api::gl
{
    template<typename S>
    class Pipeline : public api::Pipeline, public gl::Object
    {
    public:
        using Layout = Layout<S>;

        Pipeline(const Layout& layout)
            : layout_{ layout }
        {
            handle_ = gl::create_program_pipeline();

            if (const auto& shader = layout_.vertex;                 shader) gl::use_program_stages(handle_, shader->handle(), gl::map_program_stage(shader->stage()));
            if (const auto& shader = layout_.tessellationControl;    shader) gl::use_program_stages(handle_, shader->handle(), gl::map_program_stage(shader->stage()));
            if (const auto& shader = layout_.tessellationEvaluation; shader) gl::use_program_stages(handle_, shader->handle(), gl::map_program_stage(shader->stage()));
            if (const auto& shader = layout_.geometry;               shader) gl::use_program_stages(handle_, shader->handle(), gl::map_program_stage(shader->stage()));
            if (const auto& shader = layout_.fragment;               shader) gl::use_program_stages(handle_, shader->handle(), gl::map_program_stage(shader->stage()));
        }
        ~Pipeline()
        {
            gl::delete_program_pipeline(handle_);
        }

        void bind()
        {
            gl::bind_program_pipeline(handle_);
        }

        const Layout& layout() const
        {
            return layout_;
        }

    private:
        Layout layout_{};
    };
}
