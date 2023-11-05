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
        static void init()
        {

        }

        template<RenderState::Parameter PARAM, typename... Args>
        static auto query(Args... args) = delete;
        template<RenderState::Parameter PARAM, typename... Args>
        static auto apply(Args... args) = delete;

        template<> static auto query<RenderState::Parameter::ClearColor>()
        {
            return s_clearColor;
        }
        template<> static auto apply<RenderState::Parameter::ClearColor>(Vector4f clearColor)
        {
            if (s_clearColor == clearColor) return;

            s_clearColor = clearColor;
            glClearColor(s_clearColor.r, s_clearColor.g, s_clearColor.b, s_clearColor.a);
        }

        template<> static auto query<RenderState::Parameter::DepthFunction>()
        {
            return s_depthFunction;
        }
        template<> static auto apply<RenderState::Parameter::DepthFunction>(RenderState::DepthFunction depthFunction)
        {
            if (s_depthFunction == depthFunction) return;

            const auto& glDepthFunction = GL_NEVER;
            glDepthFunc(glDepthFunction);
        }

    private:
        GRenderState() = delete;

        static inline Vector4f      s_clearColor{};
        static inline DepthFunction s_depthFunction{};
    };
}
