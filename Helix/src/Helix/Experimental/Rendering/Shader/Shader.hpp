#pragma once

#include "stdafx.hpp"

#include "Helix/Experimental/Rendering/Base.hpp"

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

    template<GraphicsAPI G>
    class GShader;
}
