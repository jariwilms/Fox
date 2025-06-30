#pragma once

#include <stdafx.hpp>

#include <glad/gl.h>
#include <glfw/glfw3.h>

#include <fox/rendering/api/opengl/core/mapping.hpp>
#include <fox/rendering/api/opengl/opengl.hpp>
#include <fox/rendering/base/render_state/render_state.hpp>

namespace fox::gfx::api::gl
{
    class RenderState : public api::RenderState
    {
    public:
        RenderState() = delete;
        ~RenderState() = delete;

        static void init()
        {
            s_cullingFaceAlpha  = false;
            s_depthTestingAlpha = false;
            s_faceCulling       = FaceCulling::Back;
            s_depthFunction     = DepthFunction::Less;
            s_frontFace         = FrontFace::CounterClockwise;
            s_clearColor        = fox::Vector4f{ 0.0f };
        }
    };
}
