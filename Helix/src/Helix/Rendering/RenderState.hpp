#pragma once

#include "stdafx.hpp"

#include "Helix/Rendering/Rendering.hpp"
#include "Helix/Rendering/RenderState/RenderState.hpp"
#include "Helix/Rendering/API/OpenGL/OpenGLRenderState.hpp"

namespace hlx::gfx
{
    class RenderState : public api::RenderState
    {
    public:
        static void init()
        {
            s_renderState = std::make_unique<imp::GRenderState<api::GRAPHICS_API>>();
        }

        template<Parameter PARAM, typename... Args>
        static auto query(Args... args)
        {
            return s_renderState->query<PARAM>(std::forward<Args>(args)...);
        }
        template<Parameter PARAM, typename... Args>
        static auto apply(Args... args)
        {
            return s_renderState->apply<PARAM>(std::forward<Args>(args)...);
        }

    private:
        static inline std::unique_ptr<imp::GRenderState<api::GRAPHICS_API>> s_renderState{};
    };
}
