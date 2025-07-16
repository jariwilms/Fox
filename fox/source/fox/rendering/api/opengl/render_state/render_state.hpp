#pragma once

#include <stdafx.hpp>

#include <fox/rendering/base/render_state/render_state.hpp>

import fox.rendering.api.opengl;
import fox.rendering.api.opengl.mapping;

namespace fox::gfx::api::gl
{
    class RenderState : public api::RenderState
    {
    public:
        RenderState() = delete;

        static void init()
        {
            //cullingFaceAlpha_  = gl::False;
            //depthTestingAlpha_ = gl::False;
            //faceCulling_       = FaceCulling::Back;
            //depthFunction_     = DepthFunction::Less;
            //frontFace_         = FrontFace::CounterClockwise;
            //clearColor_        = fox::Vector4f{ 0.0f };
        }
    };
}
