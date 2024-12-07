#include "stdafx.hpp"

#include "GLFWWindow.hpp"

#include "Fox/Window/WindowManager.hpp"
#include "Fox/Rendering/API/OpenGL/OpenGL.hpp"

namespace fox::wnd::api
{
	GLFWWindow::GLFWWindow(const std::string& name, const fox::Vector2u& dimensions)
        : Window{ name, dimensions }
	{
        //Initialize GLFW
		const auto& isInitialized = glfwInit();
		if (isInitialized != GLFW_TRUE) throw std::runtime_error{ "Failed to initialize GLFW!" };

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_REFRESH_RATE, GLFW_DONT_CARE);
#ifdef FOX_DEBUG
        glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);
#endif

        m_glfwWindow = glfwCreateWindow(static_cast<fox::int32_t>(dimensions.x), static_cast<fox::int32_t>(dimensions.y), m_name.c_str(), nullptr, nullptr);
		if (!m_glfwWindow) throw std::runtime_error{ "Failed to create GLFW window!" };

		glfwMakeContextCurrent(m_glfwWindow);
        glfwSwapInterval(0);



        //Initialize GLAD
        const auto& isLoaded = gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress));
        if (!isLoaded) throw std::runtime_error{ "Failed to initialize GLAD!" };

        m_userPointer                = std::make_shared<UserPointer>();
        m_userPointer->glfwWindow    = std::shared_ptr<GLFWWindow>(this, [](const GLFWWindow* window) {}); //?
        m_userPointer->inputHandler  = std::make_shared<inp::GLFWInputHandler>();
        glfwSetWindowUserPointer(m_glfwWindow, m_userPointer.get());

        m_nativeWindow = m_glfwWindow;



        //Set up debug message output
        namespace gl = gfx::api::gl;
        if (auto flags = gl::integer_v(gl::Flags::Data::ContextFlags); flags & gl::Flags::Context::DebugBit)
        {
            gl::enable(gl::Flags::Capability::DebugOutput);
            gl::enable(gl::Flags::Capability::DebugOutputSynchronous);

            gl::debug_message_callback(gl::debug_callback);
            gl::debug_message_control(gl::True, gl::Flags::Debug::Source::DontCare, gl::Flags::Debug::Type::DontCare, gl::Flags::Debug::Severity::DontCare);
        }



        //Set up event callbacks
        static const auto& user_pointer                       = [this]() -> GLFWWindow::UserPointer*
        {
            const auto& glfwWindow  = reinterpret_cast<GLFWwindow*>(WindowManager::find(this)->native_handle());
            const auto& userPointer = static_cast<GLFWWindow::UserPointer*>(glfwGetWindowUserPointer(glfwWindow));
            
            return userPointer;
        };
               const auto& forward_glfw_error_callback        = [](fox::int32_t error, const fox::char_t* description)
        {
            const auto& window = user_pointer()->glfwWindow;
            window->glfw_error_callback(error, description);
        };
               const auto& forward_gl_debug_callback          = [](gl::enum_t source, gl::enum_t type, gl::uint32_t id, gl::enum_t severity, gl::size_t length, const gl::char_t* message, const void* parameters)
        {
            //TODO: Make like this?
            //const auto& context = user_pointer()->renderContext; //(Points to something defined in GL.hpp?)
            //context->gl_debug_callback(source, type, id, severity, length, message, param);

            gl::debug_callback(source, type, id, severity, length, message, parameters);
        };
               const auto& forward_glfw_input_key_callback    = [](GLFWwindow* window, fox::int32_t key, fox::int32_t scancode, fox::int32_t action, fox::int32_t mods)
        {
            const auto& handler = user_pointer()->inputHandler;
            handler->glfw_input_key_callback(window, key, scancode, action, mods);
        };
               const auto& forward_glfw_button_callback       = [](GLFWwindow* window, fox::int32_t button, fox::int32_t action, fox::int32_t mods)
        {
            const auto& handler = user_pointer()->inputHandler;
            handler->glfw_input_button_callback(window, button, action, mods);
        };
               const auto& forward_glfw_input_cursor_callback = [](GLFWwindow* window, fox::float64_t x, fox::float64_t y)
        {
            const auto& handler = user_pointer()->inputHandler;
            handler->glfw_input_cursor_callback(window, x, y);
        };
               const auto& forward_glfw_input_scroll_callback = [](GLFWwindow* window, fox::float64_t x, fox::float64_t y)
        {
            const auto& handler = user_pointer()->inputHandler;
            handler->glfw_input_scroll_callback(window, x, y);
        };

        glfwSetErrorCallback(                    forward_glfw_error_callback);
        glfwSetKeyCallback(        m_glfwWindow, forward_glfw_input_key_callback);
        glfwSetMouseButtonCallback(m_glfwWindow, forward_glfw_button_callback);
        glfwSetCursorPosCallback(  m_glfwWindow, forward_glfw_input_cursor_callback);
        glfwSetScrollCallback(     m_glfwWindow, forward_glfw_input_scroll_callback);



		inp::api::init(m_userPointer->inputHandler);
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
