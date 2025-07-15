export module fox.input;

import std;
import fox.core.types;

export import fox.input.api;
export import fox.input.code.button;
export import fox.input.code.controller;
export import fox.input.code.key;
export import fox.input.code.modifier;

export namespace fox::input
{
    inline auto any_key_active       () -> fox::bool_t
    {
        return api::handler->any_key_active();
    }
    inline auto any_button_active    () -> fox::bool_t
    {
        return api::handler->any_button_active();
    }

    inline auto key_active           (input::key_t    code) -> fox::bool_t
    {
        return api::handler->key_active(code);
    }
    inline auto key_pressed          (input::key_t    code) -> fox::bool_t
    {
        return api::handler->key_pressed(code);
    }
    inline auto key_released         (input::key_t    code) -> fox::bool_t
    {
        return api::handler->key_released(code);
    }

    inline auto button_active        (input::button_t code) -> fox::bool_t
    {
        return api::handler->button_active(code);
    }
    inline auto button_pressed       (input::button_t code) -> fox::bool_t
    {
        return api::handler->button_pressed(code);
    }
    inline auto button_released      (input::button_t code) -> fox::bool_t
    {
        return api::handler->button_released(code);
    }

    inline auto cursor_position      () -> fox::Vector2f
    {
        return api::handler->cursor_position();
    }
    inline auto cursor_position_delta() -> fox::Vector2f
    {
        return api::handler->cursor_position_delta();
    }

    inline auto scroll_wheel         () -> fox::Vector2f
    {
        return api::handler->scroll_wheel();
    }
    inline auto scroll_wheel_delta   () -> fox::Vector2f
    {
        return api::handler->scroll_wheel_delta();
    }
}

