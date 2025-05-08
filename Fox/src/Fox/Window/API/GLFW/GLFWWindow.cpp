#include "stdafx.hpp"

#include "GLFWWindow.hpp"

#include "Fox/Window/WindowManager.hpp"
#include "Fox/Rendering/GraphicsAPI/OpenGL/OpenGL.hpp"
#include "Fox/Rendering/GraphicsAPI/OpenGL/Context/Context.hpp"

namespace fox::wnd::api
{
    static void debug_callback(gfx::api::gl::enum_t source, gfx::api::gl::enum_t type, gfx::api::gl::uint32_t id, gfx::api::gl::enum_t severity, gfx::api::gl::sizei_t length, const gfx::api::gl::char_t* message, const void* parameter)
    {
        const auto& sourceMessage = [source]() -> std::string
            {
                switch (source)
                {
                    case GL_DEBUG_SOURCE_API:             return "API";
                    case GL_DEBUG_SOURCE_WINDOW_SYSTEM:   return "WINDOW_SYSTEM";
                    case GL_DEBUG_SOURCE_SHADER_COMPILER: return "SHADER_COMPILER";
                    case GL_DEBUG_SOURCE_THIRD_PARTY:     return "THIRD_PARTY";
                    case GL_DEBUG_SOURCE_APPLICATION:     return "APPLICATION";
                    case GL_DEBUG_SOURCE_OTHER:           return "OTHER";

                    default:                              throw std::invalid_argument{ "Invalid source!" };
                }
            }();
        const auto& typeMessage = [type]() -> std::string
            {
                switch (type)
                {
                    case GL_DEBUG_TYPE_ERROR:               return "ERROR";
                    case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: return "DEPRECATED_BEHAVIOR";
                    case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:  return "UNDEFINED_BEHAVIOR";
                    case GL_DEBUG_TYPE_PORTABILITY:         return "PORTABILITY";
                    case GL_DEBUG_TYPE_PERFORMANCE:         return "PERFORMANCE";
                    case GL_DEBUG_TYPE_MARKER:              return "MARKER";
                    case GL_DEBUG_TYPE_OTHER:               return "OTHER";

                    default:                                throw std::invalid_argument{ "Invalid type!" };
                }
            }();
        const auto& severityMessage = [severity]() -> std::string
            {
                switch (severity)
                {
                    case GL_DEBUG_SEVERITY_NOTIFICATION: return "NOTIFICATION";
                    case GL_DEBUG_SEVERITY_LOW:          return "LOW";
                    case GL_DEBUG_SEVERITY_MEDIUM:       return "MEDIUM";
                    case GL_DEBUG_SEVERITY_HIGH:         return "HIGH";

                    default:                             throw std::invalid_argument{ "Invalid severity!" };
                }
            }();

        if (severityMessage == "NOTIFICATION") return;

        std::cout << std::format("[GL_DEBUG] {0}, {1}, {2}, {3}: {4}", sourceMessage, typeMessage, severityMessage, id, message) << std::endl;
    }



	GLFWWindow::GLFWWindow(const std::string& name, const fox::Vector2u& dimensions)
        : Window{ name, dimensions }
	{
		const auto& isInitialized = glfwInit();
		if (isInitialized != GLFW_TRUE) throw std::runtime_error{ "Failed to initialize GLFW!" };

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_REFRESH_RATE, GLFW_DONT_CARE);
        glfwWindowHint(GLFW_SAMPLES, 4);
#ifdef FOX_DEBUG
        glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);
#endif

        m_glfwWindow = glfwCreateWindow(static_cast<fox::int32_t>(dimensions.x), static_cast<fox::int32_t>(dimensions.y), m_name.c_str(), nullptr, nullptr);
		if (!m_glfwWindow) throw std::runtime_error{ "Failed to create GLFW window!" };

		glfwMakeContextCurrent(m_glfwWindow);
        glfwSwapInterval(0);



        const auto& version = gladLoadGL(glfwGetProcAddress);
        if (version == 0) throw std::runtime_error{ "Failed to initialize GLAD!" };

        m_userPointer                = std::make_shared<UserPointer>();
        m_userPointer->glfwWindow    = std::shared_ptr<GLFWWindow>(this, [](const GLFWWindow* window) {}); //?
        m_userPointer->inputHandler  = std::make_shared<input::GLFWInputHandler>();
        glfwSetWindowUserPointer(m_glfwWindow, m_userPointer.get());

        m_nativeWindow = m_glfwWindow;



        namespace gl = gfx::api::gl;
        gl::Context::init();



        //Set up event callbacks
        static const auto& user_pointer = [this]() -> GLFWWindow::UserPointer*
        {
            const auto& glfwWindow  = reinterpret_cast<GLFWwindow*>(WindowManager::find(this)->native_handle());
            const auto& userPointer = static_cast<GLFWWindow::UserPointer*>(glfwGetWindowUserPointer(glfwWindow));
            
            return userPointer;
        };

        const auto& glfw_error_callback               = [](fox::int32_t error, const fox::char_t* description)
            {
                const auto& window = user_pointer()->glfwWindow;
                window->glfw_error_callback(error, description);
            };
        const auto& gl_debug_callback                 = [](gl::enum_t source, gl::enum_t type, gl::uint32_t id, gl::enum_t severity, gl::sizei_t length, const gl::char_t* message, const void* parameters)
            {
                //TODO: Make like this?
                //const auto& context = user_pointer()->renderContext; //(Points to something defined in GL.hpp?)
                //context->gl_debug_callback(source, type, id, severity, length, message, param);

                debug_callback(source, type, id, severity, length, message, parameters);
            };
        const auto& glfw_input_key_callback           = [](GLFWwindow* window, fox::int32_t key, fox::int32_t scancode, fox::int32_t action, fox::int32_t mods)
            {
                const auto& handler = user_pointer()->inputHandler;
                handler->glfw_input_key_callback(window, key, scancode, action, mods);
            };
        const auto& glfw_button_callback              = [](GLFWwindow* window, fox::int32_t button, fox::int32_t action, fox::int32_t mods)
            {
                const auto& handler = user_pointer()->inputHandler;
                handler->glfw_input_button_callback(window, button, action, mods);
            };
        const auto& glfw_input_cursor_callback        = [](GLFWwindow* window, fox::float64_t x, fox::float64_t y)
            {
                const auto& handler = user_pointer()->inputHandler;
                handler->glfw_input_cursor_callback(window, x, y);
            };
        const auto& glfw_input_scroll_callback        = [](GLFWwindow* window, fox::float64_t x, fox::float64_t y)
            {
                const auto& handler = user_pointer()->inputHandler;
                handler->glfw_input_scroll_callback(window, x, y);
            };
        const auto& glfw_frame_buffer_resize_callback = [](GLFWwindow* window, fox::int32_t width, fox::int32_t height)
            {
                gl::viewport({ {}, { width, height } });
            };

        glfwSetErrorCallback(                        glfw_error_callback);
        glfwSetKeyCallback(            m_glfwWindow, glfw_input_key_callback);
        glfwSetMouseButtonCallback(    m_glfwWindow, glfw_button_callback);
        glfwSetCursorPosCallback(      m_glfwWindow, glfw_input_cursor_callback);
        glfwSetScrollCallback(         m_glfwWindow, glfw_input_scroll_callback);
        glfwSetFramebufferSizeCallback(m_glfwWindow, glfw_frame_buffer_resize_callback);

		input::api::init(m_userPointer->inputHandler);
	}
	GLFWWindow::~GLFWWindow()
	{
        glfwDestroyWindow(m_glfwWindow);
		glfwTerminate();
	}

    void GLFWWindow::poll_events()
    {
        m_userPointer->inputHandler->update();
        glfwPollEvents();
    }
    void GLFWWindow::swap_buffers()
	{
		glfwSwapBuffers(m_glfwWindow);
	}

	void GLFWWindow::rename(const std::string& title)
	{
		glfwSetWindowTitle(m_glfwWindow, title.c_str());
	}
	void GLFWWindow::resize(const fox::Vector2f& dimensions)
	{
        glfwSetWindowSize(m_glfwWindow, static_cast<fox::int32_t>(dimensions.x), static_cast<fox::int32_t>(dimensions.y));

		m_dimensions = dimensions;
	}

    void GLFWWindow::close() const
    {
        glfwSetWindowShouldClose(m_glfwWindow, true);
    }
    fox::bool_t GLFWWindow::should_close() const
    {
        return glfwWindowShouldClose(m_glfwWindow);
    }

    void GLFWWindow::glfw_error_callback(fox::int32_t error, const fox::char_t* description)
    {
        std::cout << std::format("[GLFW_ERROR] {0}: {1}\n", error, description);
    }
}
