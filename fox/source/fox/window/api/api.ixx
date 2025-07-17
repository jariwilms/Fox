export module fox.window.api;

//#define FOX_WINDOW_API_GLFW 1
//#define FOX_WINDOW_API_SDL  2
//#ifndef FOX_WINDOW_API
//#define FOX_WINDOW_API FOX_WINDOW_API_GLFW
//#endif
//#if FOX_WINDOW_API == FOX_WINDOW_API_GLFW
//#endif

import std;
import fox.window.api.glfw;
import fox.core.types.window;

export namespace fox::interface
{
	namespace impl
	{
		using window_t = interface::api::glfw::Window;
	}
}
