#include "stdafx.hpp"

#include "Window.hpp"
#include "Helix/Window/API/GLFW/GLFWWindow.hpp"

namespace hlx
{
	Window::Window(const std::string& title, const Vector2u& dimensions)
		: m_title{ title }, m_dimensions{ dimensions } {}

	std::shared_ptr<Window> Window::create(const std::string& title, const Vector2u& dimensions)
	{
		return std::make_shared<GLFWWindow>(title, dimensions);
	}

    NativeWindow* Window::native_window()
    {
		return s_nativeWindow;
    }
}
