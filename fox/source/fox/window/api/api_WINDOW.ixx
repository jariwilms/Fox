module;

export module fox.window.api;

#define FOX_WINDOW_API_GLFW 1
#define FOX_WINDOW_API_SDL  2

#ifndef FOX_WINDOW_API
#define FOX_WINDOW_API FOX_WINDOW_API_GLFW
#endif

import std;

#if FOX_WINDOW_API == FOX_WINDOW_API_GLFW
import fox.window.api.glfw;
#endif

import fox.core.types.window;

export namespace fox::interface
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
