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
    
    auto get_primary_monitor           () -> glfw::monitor_t*
    {
        return ::glfwGetPrimaryMonitor();
    }
    auto get_video_mode                (glfw::monitor_t* monitor) -> const glfw::video_mode_t*
    {
        return ::glfwGetVideoMode(monitor);
    }

    void window_hint                   (glfw::hint_e hint, glfw::hint_value_e value)
    {
        ::glfwWindowHint(std::to_underlying(hint), std::to_underlying(value));
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
    auto window_should_close           (glfw::window_t* window) -> fox::bool_t
    {
        return ::glfwWindowShouldClose(window);
    }
    auto get_window_size               (glfw::window_t* window) -> fox::vector2u
    {
        auto dimensions = fox::vector2i{};
        ::glfwGetWindowSize(window, &dimensions.x, &dimensions.y);

        return std::bit_cast<fox::vector2u>(dimensions);
    }
    auto get_monitor_size              (glfw::monitor_t* monitor) -> fox::vector2u
    {
        auto dimensions = fox::vector2i{};
        ::glfwGetMonitorPhysicalSize(monitor, &dimensions.x, &dimensions.y);

        return std::bit_cast<fox::vector2u>(dimensions);
    }
    auto get_frame_buffer_size         (glfw::window_t* window) -> fox::vector2u
    {
        auto dimensions = fox::vector2i{};
        ::glfwGetFramebufferSize(window, &dimensions.x, &dimensions.y);

        return std::bit_cast<fox::vector2u>(dimensions);
    }
    void set_window_should_close       (glfw::window_t* window, fox::bool_t value)
    {
        ::glfwSetWindowShouldClose(window, value);
    }
    void set_window_size               (glfw::window_t* window, const fox::vector2u& dimensions)
    {
        ::glfwSetWindowSize(
            window                                  , 
            static_cast<fox::int32_t>(dimensions.x) , 
            static_cast<fox::int32_t>(dimensions.y));
    }
    void set_window_title              (glfw::window_t* window, const std::string& title)
    {
        ::glfwSetWindowTitle(window, title.c_str());
    }
    void set_window_monitor            (glfw::window_t* window, glfw::monitor_t* monitor, fox::vector2u dimensions)
    {
        const auto video_mode         = glfw::get_video_mode(monitor ? monitor : glfw::get_primary_monitor());
        const auto monitor_resolution = fox::vector2u{ video_mode->width, video_mode->height };
        const auto window_center      = fox::vector2u{  glfw::get_window_size (window) / 2u  };
        const auto monitor_center     = fox::vector2u{              monitor_resolution / 2u  };
        const auto top_left           = fox::vector2u{        monitor_center - window_center };

        ::glfwSetWindowMonitor(
            window, monitor, 
            static_cast<fox::int32_t>(top_left  .x), static_cast<fox::int32_t>(top_left  .y), 
            static_cast<fox::int32_t>(dimensions.x), static_cast<fox::int32_t>(dimensions.y), fox::int32_t{ 0 });
    }
    void show_window                   (glfw::window_t* window)
    {
        ::glfwShowWindow(window);
    }
    void hide_window                   (glfw::window_t* window)
    {
        ::glfwHideWindow(window);
    }

    void poll_events                   ()
    {
        ::glfwPollEvents();
    }
    void wait_events                   ()
    {
        glfwWaitEvents();
    }
    void swap_interval                 (fox::uint32_t interval)
    {
        ::glfwSwapInterval(static_cast<fox::int32_t>(interval));
    }
    void make_context_current          (glfw::window_t* window)
    {
        ::glfwMakeContextCurrent(window);
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
