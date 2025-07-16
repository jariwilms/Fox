module;

#include <fox/rendering/base/render_state/render_state.hpp>

export module fox.rendering.api.opengl.render_state;

import std;

import fox.rendering.api.opengl;

export namespace fox::gfx::api::gl
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
