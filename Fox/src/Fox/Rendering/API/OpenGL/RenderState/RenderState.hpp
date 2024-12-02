#pragma once

#include "stdafx.hpp"

#include "glad/glad.h"
#include "glfw/glfw3.h"

#include "Fox/Rendering/API/OpenGL/OpenGL.hpp"
#include "Fox/Rendering/API/OpenGL/Mapping.hpp"
#include "Fox/Rendering/RenderState/RenderState.hpp"

namespace fox::gfx::api::gl
{
    class RenderState : public api::RenderState
    {
    public:
        static void init()
        {
            s_cullingFaceAlpha  = false;
            s_depthTestingAlpha = false;
            s_faceCulling       = FaceCulling::Back;
            s_depthFunction     = DepthFunction::Less;
            s_frontFace         = FrontFace::CounterClockwise;
            s_clearColor        = fox::Vector4f{ 0.0f };
        }

        template<api::RenderState::Parameter PARAM, typename... Args>
        static auto query(Args... args) = delete;
        template<api::RenderState::Parameter PARAM, typename... Args>
        static auto apply(Args... args) = delete;

        template<> static auto query<api::RenderState::Parameter::ClearColor>()
        {
            return s_clearColor;
        }
        template<> static auto apply<api::RenderState::Parameter::ClearColor>(fox::Vector4f clearColor)
        {
            if (s_clearColor == clearColor) return;

            gl::clear_color(clearColor);
            s_clearColor = clearColor;
        }

        template<> static auto query<api::RenderState::Parameter::DepthFunction>()
        {
            return s_depthFunction;
        }
        template<> static auto apply<api::RenderState::Parameter::DepthFunction>(api::RenderState::DepthFunction depthFunction)
        {
            if (s_depthFunction == depthFunction) return;

            const auto& _ = gl::map_depth_function(depthFunction);
            gl::depth_function(_);
            s_depthFunction = depthFunction;
        }

        template<> static auto query<api::RenderState::Parameter::FaceCullingAlpha>()
        {
            return s_cullingFaceAlpha;
        }
        template<> static auto apply<api::RenderState::Parameter::FaceCullingAlpha>(fox::bool_t state)
        {
            if (s_cullingFaceAlpha == state) return;

            if (s_cullingFaceAlpha) gl::enable (gl::Flags::Capability::FaceCulling);
            else                    gl::disable(gl::Flags::Capability::FaceCulling);
            s_cullingFaceAlpha = state;
        }

        template<> static auto query<api::RenderState::Parameter::FaceCulling>()
        {
            return s_faceCulling;
        }
        template<> static auto apply<api::RenderState::Parameter::FaceCulling>(api::RenderState::FaceCulling faceCulling)
        {
            if (s_faceCulling == faceCulling) return;

            const auto& _ = gl::map_culling_face(s_faceCulling);
            gl::face_culling(_);
            s_faceCulling = faceCulling;
        }

        template<> static auto query<api::RenderState::Parameter::FrontFace>()
        {
            return s_faceCulling;
        }
        template<> static auto apply<api::RenderState::Parameter::FrontFace>(api::RenderState::FrontFace frontFace)
        {
            if (s_frontFace == frontFace) return;

            if (s_frontFace == api::RenderState::FrontFace::Clockwise) gl::front_face(Flags::Orientation::Clockwise);
            else                                                       gl::front_face(Flags::Orientation::CounterClockwise);
            s_frontFace = frontFace;
        }

        template<> static auto query<api::RenderState::Parameter::DepthTestingAlpha>()
        {
            return s_depthTestingAlpha;
        }
        template<> static auto apply<api::RenderState::Parameter::DepthTestingAlpha>(fox::bool_t state)
        {
            if (s_depthTestingAlpha == state) return;

            if (s_depthTestingAlpha) gl::enable (Flags::Capability::DepthTest);
            else                     gl::disable(Flags::Capability::DepthTest);
            s_depthTestingAlpha = state;
        }

    private:
        RenderState() = delete;
    };
}
