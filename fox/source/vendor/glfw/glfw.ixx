export module vendor.glfw;
export import <glfw/glfw3.h>;

import fox.core.types;

export namespace glfw
{
    using window = GLFWwindow;

    void input_key_callback   (glfw::window* window, fox::int32_t   key   , fox::int32_t   scancode, fox::int32_t action, fox::int32_t mods)
    {
        //glfw_input_key_callback(window, key, scancode, action, mods);
    }
    void input_button_callback(glfw::window* window, fox::int32_t   button,                          fox::int32_t action, fox::int32_t mods)
    {
        //glfw_input_button_callback(window, button, action, mods);
    }
    void input_cursor_callback(glfw::window* window, fox::float64_t x     , fox::float64_t y                                               )
    {
        //glfw_input_cursor_callback
    }
    void input_scroll_callback(glfw::window* window, fox::float64_t x     , fox::float64_t y                                               )
    {
        //glfw_input_scroll_callback
    }

    constexpr auto RELEASE = GLFW_RELEASE;
    constexpr auto PRESS   = GLFW_PRESS;
    constexpr auto REPEAT  = GLFW_REPEAT;
}