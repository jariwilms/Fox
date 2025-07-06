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
    };
}
