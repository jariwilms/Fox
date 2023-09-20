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

        template<Option O, typename... Args> static auto query(Args... args) = delete;
        template<> static auto query<Option::ClearColor>()
        {
            return Vector4f{ 0.0f };
        }
        template<> static auto query<Option::CullingFace>()
        {
            return CullingFace::Back;
        }

        template<Option O, typename... Args> static auto apply(Args... args) = delete;
        template<> static auto apply<Option::ClearColor>(const Vector4f& value)
        {
            return 2;
        }

    private:
        static inline std::unique_ptr<RenderStateAPI> s_renderStateAPI{};
    };
}
