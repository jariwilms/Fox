export module fox.input.api;

#define FOX_INPUT_API_GLFW 1
#define FOX_INPUT_API_SDL  2

#ifndef FOX_INPUT_API
#define FOX_INPUT_API FOX_INPUT_API_GLFW
#endif

import std;

import fox.input.code.button;
import fox.input.code.controller;
import fox.input.code.key;
import fox.input.code.modifier;

#if FOX_INPUT_API == FOX_INPUT_API_GLFW
import fox.input.api.glfw;
#endif

import fox.core.types.math.linear_algebra.vector;

export namespace fox::input::api
{
#if FOX_INPUT_API == FOX_INPUT_API_GLFW
    using handler_t = glfw::InputHandler;
#endif

    inline std::shared_ptr<api::handler_t> handler;
}
