export module fox.rendering.base.render_state;

export namespace fox::gfx::api
{
    class RenderState
    {
    public:
        RenderState() = delete;

        enum class Parameter
        {
            ClearColor, 
            DepthFunction, 
            DepthTestingAlpha, 
            FaceCulling, 
            FaceCullingAlpha, 
            FrontFace, 
        };
        enum class DepthFunction
        {
            Always, 
            Never, 

            Equal, 
            NotEqual, 

            Less, 
            LessEqual, 

            Greater, 
            GreaterEqual, 
        };
        enum class FaceCulling
        {
            Front, 
            Back, 
            FrontBack, 
        };
        enum class FrontFace
        {
            Clockwise, 
            CounterClockwise, 
        };
    };
}
