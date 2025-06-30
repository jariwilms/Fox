#pragma once

#include <fox/core/types/math/linear_algebra/vector.hpp>

namespace fox::gfx::api
{
    class RenderState
    {
    public:
        enum class Parameter
        {
            ClearColor, 
            DepthFunction, 
            DepthTestingAlpha, 
            FaceCulling, 
            FaceCullingAlpha, 
            FrontFace, 
        };
        enum class DepthFunction
        {
            Always, 
            Never, 

            Equal, 
            NotEqual, 

            Less, 
            LessEqual, 

            Greater, 
            GreaterEqual, 
        };
        enum class FaceCulling
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

        static inline bool          depthTestingAlpha_{};
        static inline bool          cullingFaceAlpha_{};
        static inline FaceCulling   faceCulling_{};
        static inline DepthFunction depthFunction_{};
        static inline FrontFace     frontFace_{};
        static inline Vector4f      clearColor_{};
    };
}
