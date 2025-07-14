#pragma once

#define FOX_INPUT_API_GLFW 1
#define FOX_INPUT_API_SDL  2

#ifndef FOX_INPUT_API
#define FOX_INPUT_API FOX_INPUT_API_GLFW
#endif

#include <stdafx.hpp>

#include <fox/input/code/button.hpp>
#include <fox/input/code/controller.hpp>
#include <fox/input/code/key.hpp>
#include <fox/input/code/modifier.hpp>

#if FOX_INPUT_API == FOX_INPUT_API_GLFW
#include <fox/input/api/glfw/input_handler.hpp>
#endif

import fox.core.types.math.linear_algebra.vector;

namespace fox::input::api
{
#if FOX_INPUT_API == FOX_INPUT_API_GLFW
    using handler_t = glfw::InputHandler;
#endif

    inline std::shared_ptr<api::handler_t> handler;
}
