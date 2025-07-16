export module fox.rendering.base.shader;

export namespace fox::gfx::api
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
