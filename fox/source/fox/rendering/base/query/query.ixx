export module fox.rendering.base.query;

export namespace fox::gfx::api
{
    struct query
    {
        enum class target_e
        {
            any_samples_passed,
            any_samples_passed_conservative,
            clipping_input_primitives,
            clipping_output_primitives,
            compute_shader_invocations,
            fragment_shader_invocations,
            geometry_shader_invocations,
            geometry_shader_primitives_emitted,
            primitives_generated,
            primitives_submitted,
            samples_passed,
            tessellation_control_shader_patches,
            tessellation_evaluation_shader_invocations,
            time_elapsed,
            timestamp, 
            transform_feedback_overflow,
            transform_feedback_primitives_written,
            transform_feedback_stream_overflow,
            vertex_shader_invocations,
            vertices_submitted,
        };
    };
}
