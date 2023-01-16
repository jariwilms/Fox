#include "stdafx.hpp"

#include "Window.hpp"
#include "Platform/Windows/WindowsWindow.hpp"
//#include "Platform/Windows/LinuxWindow.hpp"
//#include "Platform/Windows/MacOSWindow.hpp"

namespace hlx
{
	Window::Window(const Window::Properties& properties)
		: m_properties{ properties } {}

	std::shared_ptr<Window> Window::create(const Window::Properties& properties)
	{
		return std::make_shared<WindowsWindow>(properties);
	}

	const Window::Properties& Window::properties()
	{
		return m_properties;
	}
}