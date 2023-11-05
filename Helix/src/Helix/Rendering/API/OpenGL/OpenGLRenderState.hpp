#pragma once

#include "stdafx.hpp"

#include "glad/glad.h"
#include "glfw/glfw3.h"

#include "Helix/Rendering/RenderState/RenderState.hpp"
#include "Helix/Rendering/API/Implementation/GRenderState.hpp"

namespace hlx::gfx::imp::api
{
    template<>
    class GRenderState<gfx::api::GraphicsAPI::OpenGL> final : public gfx::api::RenderState
    {
    public:
        template<RenderState::Parameter PARAM, typename... Args>
        auto query(Args... args) = delete;
        template<RenderState::Parameter PARAM, typename... Args>
        auto apply(Args... args) = delete;

        template<> auto query<RenderState::Parameter::ClearColor>()
        {
            return m_clearColor;
        }
        template<> auto apply<RenderState::Parameter::ClearColor>(Vector4f clearColor)
        {
            m_clearColor = clearColor;
        }




    private:
        Vector4f m_clearColor{};
    };
}
