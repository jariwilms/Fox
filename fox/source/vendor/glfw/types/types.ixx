export module vendor.glfw.types;

import <glfw/glfw3.h>;

export namespace vendor::glfw
{
    using window_t     = GLFWwindow;
    using monitor_t    = GLFWmonitor;
    using video_mode_t = GLFWvidmode;

    enum class hint_e
    {
        context_version_major = GLFW_CONTEXT_VERSION_MAJOR, 
        context_version_minor = GLFW_CONTEXT_VERSION_MINOR, 
        opengl_debug_context  = GLFW_OPENGL_DEBUG_CONTEXT, 
        opengl_profile        = GLFW_OPENGL_PROFILE, 
        refresh_rate          = GLFW_REFRESH_RATE, 
        visible               = GLFW_VISIBLE, 
    };
    enum class hint_value_e
    {
        true_                  = GLFW_TRUE, 
        false_                 = GLFW_FALSE, 
        dont_care              = GLFW_DONT_CARE, 
        opengl_core_profile    = GLFW_OPENGL_CORE_PROFILE, 
        opengl_version_major_4 = 4,
        opengl_version_minor_6 = 6,
    };
    enum class input_action_e
    {
        release = GLFW_RELEASE, 
        press   = GLFW_PRESS, 
        repeat  = GLFW_REPEAT, 
    };
    enum class result_e
    {
        failure = GLFW_FALSE, 
        success = GLFW_TRUE, 
    };
}
