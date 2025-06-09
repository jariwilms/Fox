#pragma once

#define FOX_INPUT_GLFW 1

#ifndef FOX_INPUT
#define FOX_INPUT FOX_INPUT_GLFW
#endif

#include "stdafx.hpp"

#include "Fox/Input2/API/GLFWInputHandler.hpp"
#include "Fox/Input2/Code/Button.hpp"
#include "Fox/Input2/Code/Key.hpp"
#include "Fox/Input2/Code/Modifier.hpp"

namespace fox::input::api
{
#if FOX_INPUT == FOX_INPUT_GLFW
    using handler_t = api::GLFWInputHandler;
#endif

    static auto handler = std::make_unique<handler_t>();
}
namespace fox::input
{
    static auto any_pressed             ()
    {
        return api::handler->any_pressed();
    }
    static auto any_down                ()
    {
        return api::handler->any_down();
    }
    static auto any_up                  ()
    {
        return api::handler->any_up();
    }

    static auto key_pressed             (input::key_t    code)
    {
        return api::handler->key_pressed(code);
    }
    static auto key_down                (input::key_t    code)
    {
        return api::handler->key_down(code);
    }
    static auto key_up                  (input::key_t    code)
    {
        return api::handler->key_up(code);
    }

    static auto button_pressed          (input::button_t code)
    {
        return api::handler->button_pressed(code);
    }
    static auto button_down             (input::button_t code)
    {
        return api::handler->button_down(code);
    }
    static auto button_up               (input::button_t code)
    {
        return api::handler->button_up(code);
    }

    static auto is_scrolling            ()
    {
        return api::handler->is_scrolling();
    }
    static auto is_scrolling_vertical   ()
    {
        return api::handler->is_scrolling_vertical();
    }
    static auto is_scrolling_horizontal ()
    {
        return api::handler->is_scrolling_horizontal();
    }

    static auto cursor_position         ()
    {
        return api::handler->cursor_position();
    }
    static auto cursor_position_relative()
    {
        return api::handler->cursor_position_relative();
    }
}
