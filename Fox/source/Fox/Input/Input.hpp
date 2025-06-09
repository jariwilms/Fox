#pragma once

#define FOX_INPUT_GLFW 1

#ifndef FOX_INPUT
#define FOX_INPUT FOX_INPUT_GLFW
#endif

#include "stdafx.hpp"

#include "Fox/Input/API/GLFWInputHandler.hpp"
#include "Fox/Input/Code/Button.hpp"
#include "Fox/Input/Code/Key.hpp"
#include "Fox/Input/Code/Modifier.hpp"

namespace fox::input::api
{
#if FOX_INPUT == FOX_INPUT_GLFW
    using handler_t = api::GLFWInputHandler;
#endif

    inline std::shared_ptr<handler_t> handler;// = std::make_shared<handler_t>();
}
namespace fox::input
{
    static auto any_pressed             () -> fox::bool_t
    {
        return api::handler->any_pressed();
    }
    static auto any_down                () -> fox::bool_t
    {
        return api::handler->any_down();
    }
    static auto any_up                  () -> fox::bool_t
    {
        return api::handler->any_up();
    }

    static auto key_pressed             (input::key_t    code) -> fox::bool_t
    {
        return api::handler->key_pressed(code);
    }
    static auto key_down                (input::key_t    code) -> fox::bool_t
    {
        return api::handler->key_down(code);
    }
    static auto key_up                  (input::key_t    code) -> fox::bool_t
    {
        return api::handler->key_up(code);
    }

    static auto button_pressed          (input::button_t code) -> fox::bool_t
    {
        return api::handler->button_pressed(code);
    }
    static auto button_down             (input::button_t code) -> fox::bool_t
    {
        return api::handler->button_down(code);
    }
    static auto button_up               (input::button_t code) -> fox::bool_t
    {
        return api::handler->button_up(code);
    }

    static auto is_scrolling            () -> fox::bool_t
    {
        return api::handler->is_scrolling();
    }
    static auto is_scrolling_vertical   () -> fox::bool_t
    {
        return api::handler->is_scrolling_vertical();
    }
    static auto is_scrolling_horizontal () -> fox::bool_t
    {
        return api::handler->is_scrolling_horizontal();
    }

    static auto cursor_position         () -> fox::Vector2f
    {
        return api::handler->cursor_position();
    }
    static auto cursor_position_relative() -> fox::Vector2f
    {
        return api::handler->cursor_position_relative();
    }
}
