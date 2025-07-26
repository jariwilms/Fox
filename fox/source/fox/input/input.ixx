export module fox.input;
export import fox.input.code.button;
export import fox.input.code.controller;
export import fox.input.code.key;
export import fox.input.code.modifier;

import std;
import fox.api;
import fox.core.types;

export namespace fox::input
{
    auto any_key_active       () -> fox::bool_t
    {
        return fox::api::input->any_key_active();
    }
    auto any_button_active    () -> fox::bool_t
    {
        return fox::api::input->any_button_active();
    }

    auto key_active           (input::key_e    code) -> fox::bool_t
    {
        return fox::api::input->key_active(code);
    }
    auto key_pressed          (input::key_e    code) -> fox::bool_t
    {
        return fox::api::input->key_pressed(code);
    }
    auto key_released         (input::key_e    code) -> fox::bool_t
    {
        return fox::api::input->key_released(code);
    }

    auto button_active        (input::button_e code) -> fox::bool_t
    {
        return fox::api::input->button_active(code);
    }
    auto button_pressed       (input::button_e code) -> fox::bool_t
    {
        return fox::api::input->button_pressed(code);
    }
    auto button_released      (input::button_e code) -> fox::bool_t
    {
        return fox::api::input->button_released(code);
    }

    auto cursor_position      () -> fox::vector2f
    {
        return fox::api::input->cursor_position();
    }
    auto cursor_position_delta() -> fox::vector2f
    {
        return fox::api::input->cursor_position_delta();
    }

    auto scroll_wheel         () -> fox::vector2f
    {
        return fox::api::input->scroll_wheel();
    }
    auto scroll_wheel_delta   () -> fox::vector2f
    {
        return fox::api::input->scroll_wheel_delta();
    }
}
