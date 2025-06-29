#pragma once

#include <fox/rendering/api/shader/pipeline.hpp>
#include <fox/rendering/graphics_api/opengl/opengl.hpp>
#include <fox/rendering/graphics_api/opengl/shader/shader.hpp>

namespace fox::gfx::api::gl
{
    template<typename S>
    class Pipeline : public api::Pipeline, public gl::Object
    {
    public:
        using Layout = Layout<S>;

        Pipeline(const Layout& layout)
            : m_layout{ layout }
        {
            m_handle = gl::create_program_pipeline();

            if (const auto& shader = m_layout.vertex;                 shader) gl::use_program_stages(m_handle, shader->handle(), gl::map_program_stage(shader->stage()));
            if (const auto& shader = m_layout.tessellationControl;    shader) gl::use_program_stages(m_handle, shader->handle(), gl::map_program_stage(shader->stage()));
            if (const auto& shader = m_layout.tessellationEvaluation; shader) gl::use_program_stages(m_handle, shader->handle(), gl::map_program_stage(shader->stage()));
            if (const auto& shader = m_layout.geometry;               shader) gl::use_program_stages(m_handle, shader->handle(), gl::map_program_stage(shader->stage()));
            if (const auto& shader = m_layout.fragment;               shader) gl::use_program_stages(m_handle, shader->handle(), gl::map_program_stage(shader->stage()));
        }
        ~Pipeline()
        {
            gl::delete_program_pipeline(m_handle);
        }

        void bind()
        {
            gl::bind_program_pipeline(m_handle);
        }

        const Layout& layout() const
        {
            return m_layout;
        }

    private:
        Layout m_layout{};
    };
}
