export module fox.rendering.base.shader;

export namespace fox::gfx::api
{
    struct shader
    {
        enum class stage_e
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
