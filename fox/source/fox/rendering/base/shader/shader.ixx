export module fox.rendering.base.shader;

export namespace fox::gfx::api
{
    struct shader
    {
        enum class stage
        {
            vertex, 
            tessellation_control,
            tessellation_evaluation,
            geometry, 
            fragment, 
            compute, 
        };
    };
}
