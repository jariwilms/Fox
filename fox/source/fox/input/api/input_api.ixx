export module fox.input.api;
export import fox.input.code.button;
export import fox.input.code.controller;
export import fox.input.code.key;
export import fox.input.code.modifier;

import std;

#define FOX_INPUT_API_GLFW 1
#define FOX_INPUT_API_SDL  2

#ifndef FOX_INPUT_API
#define FOX_INPUT_API FOX_INPUT_API_GLFW
#endif

#if FOX_INPUT_API == FOX_INPUT_API_GLFW
import fox.input.api.glfw;
#endif

export namespace fox::input::api
{
#if FOX_INPUT_API == FOX_INPUT_API_GLFW
    using handler_t = glfw::InputHandler;
#endif

    inline std::shared_ptr<api::handler_t> handler;
}
