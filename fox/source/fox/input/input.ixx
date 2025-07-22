export module fox.input;
export import fox.input.api;
export import fox.input.code.button;
export import fox.input.code.controller;
export import fox.input.code.key;
export import fox.input.code.modifier;

import std;
import fox.core.types;

export namespace fox::input
{
    auto any_key_active       () -> fox::bool_t
    {
        return api::handler->any_key_active();
    }
    auto any_button_active    () -> fox::bool_t
    {
        return api::handler->any_button_active();
    }

    auto key_active           (input::key    code) -> fox::bool_t
    {
        return api::handler->key_active(code);
    }
    auto key_pressed          (input::key    code) -> fox::bool_t
    {
        return api::handler->key_pressed(code);
    }
    auto key_released         (input::key    code) -> fox::bool_t
    {
        return api::handler->key_released(code);
    }

    auto button_active        (input::button code) -> fox::bool_t
    {
        return api::handler->button_active(code);
    }
    auto button_pressed       (input::button code) -> fox::bool_t
    {
        return api::handler->button_pressed(code);
    }
    auto button_released      (input::button code) -> fox::bool_t
    {
        return api::handler->button_released(code);
    }

    auto cursor_position      () -> fox::vector2f
    {
        return api::handler->cursor_position();
    }
    auto cursor_position_delta() -> fox::vector2f
    {
        return api::handler->cursor_position_delta();
    }

    auto scroll_wheel         () -> fox::vector2f
    {
        return api::handler->scroll_wheel();
    }
    auto scroll_wheel_delta   () -> fox::vector2f
    {
        return api::handler->scroll_wheel_delta();
    }
}
