export module vendor.glfw;

import std;
import <glfw/glfw3.h>;
import fox.core.types;

export namespace glfw
{
    using window = GLFWwindow;

    enum class hint
    {
        context_version_major = GLFW_CONTEXT_VERSION_MAJOR, 
        context_version_minor = GLFW_CONTEXT_VERSION_MINOR, 
        opengl_debug_context  = GLFW_OPENGL_DEBUG_CONTEXT , 
        opengl_profile        = GLFW_OPENGL_PROFILE       , 
        refresh_rate          = GLFW_REFRESH_RATE         , 
    };
    enum class hint_value
    {
        dont_care              = GLFW_DONT_CARE          , 
        opengl_core_profile    = GLFW_OPENGL_CORE_PROFILE, 
        opengl_version_major_4 = 4                       ,
        opengl_version_minor_6 = 6                       ,
    };
    enum class input_action
    {
        release = GLFW_RELEASE, 
        press   = GLFW_PRESS  , 
        repeat  = GLFW_REPEAT , 
    };
    enum class result
    {
        failure = GLFW_FALSE, 
        success = GLFW_TRUE , 
    };

    void initialize                    ()
    {
        if (!::glfwInit()) throw std::runtime_error{ "Failed to initialize GLFW!" };
    }
    void terminate                     ()
    {
        ::glfwTerminate();
    }
    
    auto create_window                 (const std::string& title, fox::vector2u dimensions) -> glfw::window*
    {
        auto handle = ::glfwCreateWindow(
            static_cast<fox::int32_t>(dimensions.x), 
            static_cast<fox::int32_t>(dimensions.y), 
            title.c_str(), nullptr, nullptr)       ;

        if (!handle) throw std::runtime_error{ "Failed to create GLFW window!" };
        return handle;
    }
    void destroy_window                (glfw::window* window)
    {
        ::glfwDestroyWindow(window);
    }
    void window_hint                   (glfw::hint hint, fox::int32_t     value)
    {
        ::glfwWindowHint(std::to_underlying(hint), value);
    }
    void window_hint                   (glfw::hint hint, glfw::hint_value value)
    {
        ::glfwWindowHint(std::to_underlying(hint), std::to_underlying(value));
    }

    void set_window_title              (glfw::window* window, const std::string& title)
    {
        ::glfwSetWindowTitle(window, title.c_str());
    }
    void set_window_size               (glfw::window* window, const fox::vector2u& dimensions)
    {
        ::glfwSetWindowSize(
            window                                  , 
            static_cast<fox::int32_t>(dimensions.x) , 
            static_cast<fox::int32_t>(dimensions.y));
    }
    void set_window_should_close       (glfw::window* window, fox::bool_t value)
    {
        ::glfwSetWindowShouldClose(window, value);
    }
    auto window_should_close           (glfw::window* window) -> fox::bool_t
    {
        return ::glfwWindowShouldClose(window);
    }

    void make_context_current          (glfw::window* window)
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
    void swap_buffers                  (glfw::window* window)
    {
        ::glfwSwapBuffers(window);
    }

    void set_error_callback            (                      auto lambda)
    {
        ::glfwSetErrorCallback(lambda);
    }
    void set_key_callback              (glfw::window* window, auto lambda)
    {
        ::glfwSetKeyCallback(window, lambda);
    }
    void set_mouse_button_callback     (glfw::window* window, auto lambda)
    {
        ::glfwSetMouseButtonCallback(window, lambda);
    }
    void set_cursor_position_callback  (glfw::window* window, auto lambda)
    {
        ::glfwSetCursorPosCallback(window, lambda);
    }
    void set_scroll_callback           (glfw::window* window, auto lambda)
    {
        ::glfwSetScrollCallback(window, lambda);
    }
    void set_frame_buffer_size_callback(glfw::window* window, auto lambda)
    {
        ::glfwSetFramebufferSizeCallback(window, lambda);
    }

    constexpr auto function_address = ::glfwGetProcAddress;
}