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
            CullingFaceAlpha, 
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
        enum class CullingFace
        {
            Front, 
            Back, 
            FrontBack, 
        };
        enum class FrontFace
        {
            Clockwise, 
            CounterClockwise, 
        };

    protected:
        RenderState() = default;

        static inline bool          s_faceCullingAlpha{};
        static inline CullingFace   s_cullingFace{};
        static inline DepthFunction s_depthFunction{};
        static inline FrontFace     s_frontFace{};
        static inline Vector4f      s_clearColor{};
    };
}
