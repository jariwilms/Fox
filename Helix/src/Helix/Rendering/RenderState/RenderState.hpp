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
        enum class DepthFunction
        {
            Never, 
            Less, 
            Equal, 
            LessEqual, 
            Greater, 
            NotEqual, 
            GreaterEqual, 
            Always, 
        };

    protected:
        RenderState() = default;
    };
}
