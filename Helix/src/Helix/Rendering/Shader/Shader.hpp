#pragma once

#include "stdafx.hpp"

#include "Helix/Rendering/API/GraphicsAPI.hpp"

namespace hlx::gfx::api
{
    class Shader
    {
    public:
        enum class Stage
        {
            Vertex,
            TessellationControl,
            TessellationEvaluation,
            Geometry,
            Fragment,

            Compute,

        };

        Stage stage() const
        {
            return m_stage;
        }

    protected:
        Shader(Stage stage)
            : m_stage{ stage } {}

        Stage m_stage{};
    };

    template<GraphicsAPI>
    class GShader;
}
