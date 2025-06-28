#pragma once

#define FOX_INPUT_GLFW 1
#define FOX_INPUT_SDL  2

#ifndef FOX_INPUT
#define FOX_INPUT FOX_INPUT_GLFW
#endif

#include <stdafx.hpp>

#include <fox/input/api/glfw_input_handler.hpp>
#include <fox/input/code/button.hpp>
#include <fox/input/code/controller.hpp>
#include <fox/input/code/key.hpp>
#include <fox/input/code/modifier.hpp>

namespace fox::input::api
{
#if FOX_INPUT == FOX_INPUT_GLFW
    using handler_t = api::GLFWInputHandler;
#endif

    inline std::shared_ptr<api::handler_t> handler;
}
namespace fox::input
{
    static auto any_key_active       () -> fox::bool_t
    {
        return api::handler->any_key_active();
    }
    static auto any_button_active    () -> fox::bool_t
    {
        return api::handler->any_button_active();
    }

    static auto key_active           (input::key_t    code) -> fox::bool_t
    {
        return api::handler->key_active(code);
    }
    static auto key_pressed          (input::key_t    code) -> fox::bool_t
    {
        return api::handler->key_pressed(code);
    }
    static auto key_released         (input::key_t    code) -> fox::bool_t
    {
        return api::handler->key_released(code);
    }

    static auto button_active        (input::button_t code) -> fox::bool_t
    {
        return api::handler->button_active(code);
    }
    static auto button_pressed       (input::button_t code) -> fox::bool_t
    {
        return api::handler->button_pressed(code);
    }
    static auto button_released      (input::button_t code) -> fox::bool_t
    {
        return api::handler->button_released(code);
    }

    static auto cursor_position      () -> fox::Vector2f
    {
        return api::handler->cursor_position();
    }
    static auto cursor_position_delta() -> fox::Vector2f
    {
        return api::handler->cursor_position_delta();
    }

    static auto scroll_wheel         () -> fox::Vector2f
    {
        return api::handler->scroll_wheel();
    }
    static auto scroll_wheel_delta   () -> fox::Vector2f
    {
        return api::handler->scroll_wheel_delta();
    }
}

