#pragma once

#include "Fox/Rendering/API/OpenGL/OpenGL.hpp"
#include "Fox/Rendering/API/OpenGL/Shader/Shader.hpp"
#include "Fox/Rendering/Shader/Pipeline.hpp"

namespace fox::gfx::api::gl
{
    class Pipeline : public api::Pipeline, public gl::Object
    {
    public:
        using Layout = Layout<gl::Shader>;

        Pipeline(Layout shaders)
            : m_layout{ shaders }
        {
            m_handle = gl::create_program_pipeline();

            if (const auto& shader = m_layout.vertex;                 shader) gl::use_program_stages(m_handle, shader->handle(), gl::map_shader_stage(shader->stage()));
            if (const auto& shader = m_layout.tessellationControl;    shader) gl::use_program_stages(m_handle, shader->handle(), gl::map_shader_stage(shader->stage()));
            if (const auto& shader = m_layout.tessellationEvaluation; shader) gl::use_program_stages(m_handle, shader->handle(), gl::map_shader_stage(shader->stage()));
            if (const auto& shader = m_layout.geometry;               shader) gl::use_program_stages(m_handle, shader->handle(), gl::map_shader_stage(shader->stage()));
            if (const auto& shader = m_layout.fragment;               shader) gl::use_program_stages(m_handle, shader->handle(), gl::map_shader_stage(shader->stage()));
        }
        Pipeline(Pipeline&& other) noexcept = default;
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

        Pipeline& operator=(Pipeline&& other) noexcept = default;

    private:
        Layout m_layout{};
    };
}
