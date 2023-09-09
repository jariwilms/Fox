#include "stdafx.hpp"

#include "GLFWWindow.hpp"
#include "Helix/Window/WindowManager.hpp"

namespace hlx
{
	GLFWWindow::GLFWWindow(const std::string& title, const Vector2u& dimensions)
        : Window{ title, dimensions }
	{
		const auto init = glfwInit();
		if (!init) throw std::runtime_error{ "Failed to initialize GLFW!" };



		//TODO: let context handle this
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_REFRESH_RATE, GLFW_DONT_CARE);
        glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);
        //Note to self: do not enable Multisampling, it will not work. Off-screen MSAA is used

		m_glfwWindow = glfwCreateWindow(static_cast<int>(dimensions.x), static_cast<int>(dimensions.y), m_title.c_str(), nullptr, nullptr);
		if (!m_glfwWindow) throw std::runtime_error{ "Failed to create GLFW window!" };

		glfwMakeContextCurrent(m_glfwWindow);
        glfwSwapInterval(0);

        const auto load = gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress));
        if (!load) throw std::runtime_error{ "Failed to initialize GLAD!" };

        //TODO: move above context into these classes
        m_userPointer = std::make_shared<UserPointer>();
        m_userPointer->glfwWindow = std::shared_ptr<GLFWWindow>(this, [](const GLFWWindow* window) {});
        m_userPointer->renderContext = std::make_shared<OpenGLRenderContext>();
        m_userPointer->inputHandler  = std::make_shared<GLFWInputHandler>();
        glfwSetWindowUserPointer(m_glfwWindow, m_userPointer.get());

        m_nativeWindow = m_glfwWindow;



        static const auto user_pointer = [this]() -> GLFWWindow::UserPointer*
        {
            const auto glfwWindow = reinterpret_cast<GLFWwindow*>(WindowManager::find(this)->native_window());
            const auto userPointer = static_cast<GLFWWindow::UserPointer*>(glfwGetWindowUserPointer(glfwWindow));
            
            return userPointer;
        };
        const auto forward_glfw_error_callback        = [](int error, const char* description)
        {
            const auto& window = user_pointer()->glfwWindow;
            window->glfw_error_callback(error, description);
        };
        const auto forward_gl_debug_callback          = [](GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* param)
        {
            const auto& context = user_pointer()->renderContext;
            context->gl_debug_callback(source, type, id, severity, length, message, param);
        };
        const auto forward_glfw_input_key_callback    = [](GLFWwindow* window, int key, int scancode, int action, int mods)
        {
            const auto& handler = user_pointer()->inputHandler;
            handler->glfw_input_key_callback(window, key, scancode, action, mods);
        };
        const auto forward_glfw_button_callback       = [](GLFWwindow* window, int button, int action, int mods)
        {
            const auto& handler = user_pointer()->inputHandler;
            handler->glfw_input_button_callback(window, button, action, mods);
        };
        const auto forward_glfw_input_cursor_callback = [](GLFWwindow* window, double x, double y)
        {
            const auto& handler = user_pointer()->inputHandler;
            handler->glfw_input_cursor_callback(window, x, y);
        };
        const auto forward_glfw_input_scroll_callback = [](GLFWwindow* window, double x, double y)
        {
            const auto& handler = user_pointer()->inputHandler;
            handler->glfw_input_scroll_callback(window, x, y);
        };

        glfwSetErrorCallback(forward_glfw_error_callback);
        glfwSetKeyCallback(m_glfwWindow, forward_glfw_input_key_callback);
        glfwSetMouseButtonCallback(m_glfwWindow, forward_glfw_button_callback);
        glfwSetCursorPosCallback(m_glfwWindow, forward_glfw_input_cursor_callback);
        glfwSetScrollCallback(m_glfwWindow, forward_glfw_input_scroll_callback);



		RenderContext::init(m_userPointer->renderContext);
		Input::init(m_userPointer->inputHandler);
	}
	GLFWWindow::~GLFWWindow()
	{
		glfwDestroyWindow(m_glfwWindow);
		glfwTerminate();
	}

	void GLFWWindow::refresh()
	{
        m_userPointer->inputHandler->update();

		glfwSwapBuffers(m_glfwWindow);
		glfwPollEvents();
	}

	void GLFWWindow::rename(const std::string& title)
	{
		glfwSetWindowTitle(m_glfwWindow, title.c_str());
	}
	void GLFWWindow::resize(const Vector2f& dimensions)
	{
        glfwSetWindowSize(m_glfwWindow, static_cast<int>(dimensions.x), static_cast<int>(dimensions.y));
		m_dimensions = dimensions;
	}

    void GLFWWindow::glfw_error_callback(int error, const char* description)
    {
        std::cout << std::format("[GLFW_ERROR] {0}: {1}\n", error, description);
    }
}
