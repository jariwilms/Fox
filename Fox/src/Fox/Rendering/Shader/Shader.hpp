#pragma once

#include "stdafx.hpp"

namespace fox::gfx::api
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
        Shader(Shader&& other) noexcept = default;
        ~Shader() = default;

        Shader& operator=(Shader&& other) noexcept = default;

        Stage m_stage{};
    };
}
