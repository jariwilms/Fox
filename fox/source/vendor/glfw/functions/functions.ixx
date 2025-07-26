export module vendor.glfw.functions;

import std;
import <glfw/glfw3.h>;
import fox.core.types;
import vendor.glfw.types;

export namespace vendor::glfw
{
    void initialize                    ()
    {
        if (!::glfwInit()) throw std::runtime_error{ "Failed to initialize GLFW!" };
    }
    void terminate                     ()
    {
        ::glfwTerminate();
    }
    
    auto create_window                 (const std::string& title, fox::vector2u dimensions) -> glfw::window_t*
    {
        auto handle = ::glfwCreateWindow(
            static_cast<fox::int32_t>(dimensions.x), 
            static_cast<fox::int32_t>(dimensions.y), 
            title.c_str(), nullptr, nullptr)       ;

        if (!handle) throw std::runtime_error{ "Failed to create GLFW window!" };
        return handle;
    }
    void destroy_window                (glfw::window_t* window)
    {
        ::glfwDestroyWindow(window);
    }
    void window_hint                   (glfw::hint_e hint, fox::int32_t       value)
    {
        ::glfwWindowHint(std::to_underlying(hint), value);
    }
    void window_hint                   (glfw::hint_e hint, glfw::hint_value_e value)
    {
        ::glfwWindowHint(std::to_underlying(hint), std::to_underlying(value));
    }

    void set_window_title              (glfw::window_t* window, const std::string& title)
    {
        ::glfwSetWindowTitle(window, title.c_str());
    }
    void set_window_size               (glfw::window_t* window, const fox::vector2u& dimensions)
    {
        ::glfwSetWindowSize(
            window                                  , 
            static_cast<fox::int32_t>(dimensions.x) , 
            static_cast<fox::int32_t>(dimensions.y));
    }
    void set_window_should_close       (glfw::window_t* window, fox::bool_t value)
    {
        ::glfwSetWindowShouldClose(window, value);
    }
    auto window_should_close           (glfw::window_t* window) -> fox::bool_t
    {
        return ::glfwWindowShouldClose(window);
    }

    void make_context_current          (glfw::window_t* window)
    {
        ::glfwMakeContextCurrent(window);
    }
    void swap_interval                 (fox::uint32_t interval)
    {
        ::glfwSwapInterval(static_cast<fox::int32_t>(interval));
    }
    void poll_events                   ()
    {
        ::glfwPollEvents();
    }
    void swap_buffers                  (glfw::window_t* window)
    {
        ::glfwSwapBuffers(window);
    }

    void set_error_callback            (                        auto lambda)
    {
        ::glfwSetErrorCallback(lambda);
    }
    void set_key_callback              (glfw::window_t* window, auto lambda)
    {
        ::glfwSetKeyCallback(window, lambda);
    }
    void set_mouse_button_callback     (glfw::window_t* window, auto lambda)
    {
        ::glfwSetMouseButtonCallback(window, lambda);
    }
    void set_cursor_position_callback  (glfw::window_t* window, auto lambda)
    {
        ::glfwSetCursorPosCallback(window, lambda);
    }
    void set_scroll_callback           (glfw::window_t* window, auto lambda)
    {
        ::glfwSetScrollCallback(window, lambda);
    }
    void set_frame_buffer_size_callback(glfw::window_t* window, auto lambda)
    {
        ::glfwSetFramebufferSizeCallback(window, lambda);
    }

    constexpr auto function_address = ::glfwGetProcAddress;
}
