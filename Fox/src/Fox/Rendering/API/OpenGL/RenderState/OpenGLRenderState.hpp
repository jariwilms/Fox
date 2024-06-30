#pragma once

#include "stdafx.hpp"

#include "glad/glad.h"
#include "glfw/glfw3.h"

#include "Helix/Rendering/API/OpenGL/GLMappings.hpp"
#include "Helix/Rendering/RenderState/RenderState.hpp"
#include "Helix/Rendering/API/Implementation/GRenderState.hpp"

namespace hlx::gfx::imp::api
{
    template<>
    class GRenderState<gfx::api::GraphicsAPI::OpenGL> final : public gfx::api::RenderState
    {
    public:
        static void init()
        {
            s_cullingFaceAlpha  = false;
            s_depthTestingAlpha = false;
            s_faceCulling       = FaceCulling::Back;
            s_depthFunction     = DepthFunction::Less;
            s_frontFace         = FrontFace::CounterClockwise;
            s_clearColor        = Vector4f{ 0.0f };
        }

        template<RenderState::Parameter PARAM, typename... Args>
        static auto query(Args... args) = delete;
        template<RenderState::Parameter PARAM, typename... Args>
        static auto apply(Args... args) = delete;

        template<> static auto query<RenderState::Parameter::ClearColor>()
        {
            return s_clearColor;
        }
        template<> static auto apply<RenderState::Parameter::ClearColor>(Vector4f clearColor)
        {
            if (s_clearColor == clearColor) return;

            s_clearColor = clearColor;
            glClearColor(s_clearColor.r, s_clearColor.g, s_clearColor.b, s_clearColor.a);
        }

        template<> static auto query<RenderState::Parameter::DepthFunction>()
        {
            return s_depthFunction;
        }
        template<> static auto apply<RenderState::Parameter::DepthFunction>(RenderState::DepthFunction depthFunction)
        {
            if (s_depthFunction == depthFunction) return;

            s_depthFunction = depthFunction;
            const auto& glDepthFunction = gl::map_depth_function(depthFunction);
            glDepthFunc(glDepthFunction);
        }

        template<> static auto query<RenderState::Parameter::FaceCullingAlpha>()
        {
            return s_cullingFaceAlpha;
        }
        template<> static auto apply<RenderState::Parameter::FaceCullingAlpha>(bool alpha)
        {
            if (s_cullingFaceAlpha == alpha) return;

            s_cullingFaceAlpha = alpha;
            s_cullingFaceAlpha ? glEnable(GL_CULL_FACE) : glDisable(GL_CULL_FACE);
        }

        template<> static auto query<RenderState::Parameter::FaceCulling>()
        {
            return s_faceCulling;
        }
        template<> static auto apply<RenderState::Parameter::FaceCulling>(FaceCulling faceCulling)
        {
            if (s_faceCulling == faceCulling) return;

            s_faceCulling = faceCulling;
            const auto& glFaceCulling = gl::map_culling_face(s_faceCulling);
            glCullFace(glFaceCulling);
        }

        template<> static auto query<RenderState::Parameter::FrontFace>()
        {
            return s_faceCulling;
        }
        template<> static auto apply<RenderState::Parameter::FrontFace>(FrontFace frontFace)
        {
            if (s_frontFace == frontFace) return;

            s_frontFace = frontFace;
            s_frontFace == RenderState::FrontFace::Clockwise ? glFrontFace(GL_CW) : glFrontFace(GL_CCW);
        }

        template<> static auto query<RenderState::Parameter::DepthTestingAlpha>()
        {
            return s_depthTestingAlpha;
        }
        template<> static auto apply<RenderState::Parameter::DepthTestingAlpha>(bool alpha)
        {
            if (s_depthTestingAlpha == alpha) return;

            s_depthTestingAlpha = alpha;
            s_depthTestingAlpha ? glEnable(GL_DEPTH_TEST) : glDisable(GL_DEPTH_TEST);
        }

    private:
        GRenderState() = delete;
    };
}
