export module fox.rendering.post_processing;

export namespace fox::gfx
{
    enum class post_processing_e
    {
        ambient_occlusion, 
        anti_aliasing, 
        auto_exposure, 
        bloom, 
        channel_mixer, 
        chromatic_aberration, 
        color_adjustment, 
        color_curve, 
        fog, 
        depth_of_field, 
        film_grain, 
        lens_distortion, 
        //lift_gamma_gain, 
        motion_blur, 
        //panini_projection, 
        screen_space_reflection, 
        //shadows_mid_tones_highlights, 
        //split_toning, 
        tone_mapping, 
        vignette, 
        white_balance, 
    };
}
