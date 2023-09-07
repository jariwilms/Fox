#pragma once

#include "stdafx.hpp"

#include "Helix/Rendering/API/RenderStateAPI.hpp"
#include "Helix/Rendering/API/OpenGL/OpenGLRenderState.hpp"

namespace hlx
{
    class RenderState
    {
    public:
        enum class CullingFace
        {
            Front, 
            Back, 
            FrontBack, 
        };
        enum class Option
        {
            ClearColor, 
            CullingFace, 
            WindingOrder, 
        };

        static void init()
        {
            s_renderStateAPI = std::make_unique<OpenGLRenderState>();
        }

        template<Option option> static auto query() = delete;
        template<> static auto query<Option::ClearColor>()
        {
            return Vector4f{ 1.0f, 1.0f, 1.0f, 1.0f };
        }
        template<> static auto query<Option::CullingFace>()
        {
            return CullingFace::Back;
        }

        static bool dirty()
        {
            return s_dirty;
        }

    private:
        static inline std::unique_ptr<RenderStateAPI> s_renderStateAPI{};
        static inline bool s_dirty{};
    };
}
