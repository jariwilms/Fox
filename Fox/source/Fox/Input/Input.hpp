#pragma once

#include <stdafx.hpp>

#include <fox/input/api/api.hpp>

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

