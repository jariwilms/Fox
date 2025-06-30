#pragma once

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

        auto stage() const -> Stage
        {
            return stage_;
        }

    protected:
        Shader(Stage stage)
            : stage_{ stage } {}

        Stage stage_{};
    };
}
