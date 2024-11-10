#pragma once

#include "stdafx.hpp"

#include "glad/glad.h"
#include "glfw/glfw3.h"

#include "Fox/Rendering/API/OpenGL/GL.hpp"
#include "Fox/Rendering/API/OpenGL/GLMappings.hpp"
#include "Fox/Rendering/RenderState/RenderState.hpp"

namespace fox::gfx::api::gl
{
    class OpenGLRenderState : public api::RenderState
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

        template<api::RenderState::Parameter PARAM, typename... Args>
        static auto query(Args... args) = delete;
        template<api::RenderState::Parameter PARAM, typename... Args>
        static auto apply(Args... args) = delete;

        template<> static auto query<api::RenderState::Parameter::ClearColor>()
        {
            return s_clearColor;
        }
        template<> static auto apply<api::RenderState::Parameter::ClearColor>(Vector4f clearColor)
        {
            if (s_clearColor == clearColor) return;

            s_clearColor = clearColor;
            glClearColor(s_clearColor.r, s_clearColor.g, s_clearColor.b, s_clearColor.a);
        }

        template<> static auto query<api::RenderState::Parameter::DepthFunction>()
        {
            return s_depthFunction;
        }
        template<> static auto apply<api::RenderState::Parameter::DepthFunction>(api::RenderState::DepthFunction depthFunction)
        {
            if (s_depthFunction == depthFunction) return;

            s_depthFunction = depthFunction;
            const auto& glDepthFunction = gl::map_depth_function(depthFunction);
            glDepthFunc(glDepthFunction);
        }

        template<> static auto query<api::RenderState::Parameter::FaceCullingAlpha>()
        {
            return s_cullingFaceAlpha;
        }
        template<> static auto apply<api::RenderState::Parameter::FaceCullingAlpha>(bool alpha)
        {
            if (s_cullingFaceAlpha == alpha) return;

            s_cullingFaceAlpha = alpha;
            s_cullingFaceAlpha ? glEnable(GL_CULL_FACE) : glDisable(GL_CULL_FACE);
        }

        template<> static auto query<api::RenderState::Parameter::FaceCulling>()
        {
            return s_faceCulling;
        }
        template<> static auto apply<api::RenderState::Parameter::FaceCulling>(api::RenderState::FaceCulling faceCulling)
        {
            if (s_faceCulling == faceCulling) return;

            s_faceCulling = faceCulling;
            const auto& glFaceCulling = gl::map_culling_face(s_faceCulling);
            glCullFace(glFaceCulling);
        }

        template<> static auto query<api::RenderState::Parameter::FrontFace>()
        {
            return s_faceCulling;
        }
        template<> static auto apply<api::RenderState::Parameter::FrontFace>(api::RenderState::FrontFace frontFace)
        {
            if (s_frontFace == frontFace) return;

            s_frontFace = frontFace;
            s_frontFace == api::RenderState::FrontFace::Clockwise ? glFrontFace(GL_CW) : glFrontFace(GL_CCW);
        }

        template<> static auto query<api::RenderState::Parameter::DepthTestingAlpha>()
        {
            return s_depthTestingAlpha;
        }
        template<> static auto apply<api::RenderState::Parameter::DepthTestingAlpha>(bool alpha)
        {
            if (s_depthTestingAlpha == alpha) return;

            s_depthTestingAlpha = alpha;
            s_depthTestingAlpha ? glEnable(GL_DEPTH_TEST) : glDisable(GL_DEPTH_TEST);
        }

    private:
        OpenGLRenderState() = delete;
    };
}
