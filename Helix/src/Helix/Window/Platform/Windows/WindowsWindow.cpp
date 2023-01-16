#include "stdafx.hpp"

#include "WindowsWindow.hpp"

namespace hlx
{
	WindowsWindow::WindowsWindow(const Window::Properties& properties)
		: Window{ properties }
	{
		const auto init = glfwInit();
		if (!init) throw std::runtime_error{ "Failed to initialize GLFW!" };

		const auto title  = properties.title.c_str();
		const auto width  = static_cast<int>(properties.dimensions.x);
		const auto height = static_cast<int>(properties.dimensions.y);
		
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_REFRESH_RATE, GLFW_DONT_CARE);
#ifdef HLX_DEBUG
		glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);
#endif // HLX_DEBUG



		m_nativeWindow = glfwCreateWindow(width, height, title, nullptr, nullptr);
		if (!m_nativeWindow) throw std::runtime_error{ "Failed to create GLFW window!" };
		
		glfwMakeContextCurrent(m_nativeWindow);

		const auto load = gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress));
		if (!load) throw std::runtime_error{ "Failed to initialize GLAD!" };



		//callbacks here
#ifdef HLX_DEBUG
		glEnable(GL_DEBUG_OUTPUT);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		glDebugMessageCallback(_windowDebugCallback, nullptr);
#endif // HLX_DEBUG

		glfwSetErrorCallback(_windowErrorCallback);
		

		
		RenderContext::create();
	}
	WindowsWindow::~WindowsWindow()
	{
		glfwDestroyWindow(m_nativeWindow);
		glfwTerminate();
	}

	void WindowsWindow::refresh()
	{
		glfwSwapBuffers(m_nativeWindow);
		glfwPollEvents();
	}
	void WindowsWindow::rename(std::string_view title)
	{
		glfwSetWindowTitle(m_nativeWindow, std::string{ title }.c_str());      //TODO: cursed
	}
	void WindowsWindow::resize(const glm::vec2& dimensions)
	{
		const auto width = static_cast<int>(dimensions.x);
		const auto height = static_cast<int>(dimensions.y);
		glfwSetWindowSize(m_nativeWindow, width, height);

		m_properties.dimensions = dimensions;
	}
	void WindowsWindow::switch_mode(const DisplayMode& displayMode)
	{
		throw std::logic_error{ "The method or operation is not implemented." };
	}

	Window::NativeWindow WindowsWindow::native_window() const
	{
		return m_nativeWindow;
	}
}
