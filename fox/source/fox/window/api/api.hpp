#pragma once

#define FOX_WINDOW_API_GLFW 1
#define FOX_WINDOW_API_SDL  2

#ifndef FOX_WINDOW_API
#define FOX_WINDOW_API FOX_WINDOW_API_GLFW
#endif

#include <stdafx.hpp>

#include <fox/input/input.hpp>

#if FOX_WINDOW_API == FOX_WINDOW_API_GLFW
#include <fox/window/api/glfw/window.hpp>
#endif

import fox.core.types.window;

namespace fox::interface
{
	namespace api
	{
		namespace glfw {}
	}

	namespace impl
	{
		#if FOX_WINDOW_API == FOX_WINDOW_API_GLFW
			using window_t = interface::api::glfw::Window;
		#endif
	}
}
