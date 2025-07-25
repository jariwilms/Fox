export module fox.rendering.base.render_state;

export namespace fox::gfx::api
{
    struct render_state
    {
        enum class parameter
        {
            clear_color,
            depth_function,
            depth_testing_alpha,
            face_culling,
            face_culling_alpha,
            front_face,
        };
        enum class depth_function
        {
            always, 
            never, 
            equal, 
            notequal, 
            less, 
            greater, 
            lessequal, 
            greaterequal, 
        };
        enum class face_culling
        {
            front, 
            back, 
            front_back,
        };
        enum class front_face
        {
            clockwise, 
            counter_clockwise,
        };
    };
}
