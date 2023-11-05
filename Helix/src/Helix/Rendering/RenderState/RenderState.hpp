#pragma once

#include "stdafx.hpp"

namespace hlx::gfx::api
{
    class RenderState
    {
    public:
        enum class Parameter
        {
            ClearColor, 
            DepthFunction, 
            CullingFace, 
            FrontFace, 
        };

    protected:
        RenderState() = default;
    };
}
