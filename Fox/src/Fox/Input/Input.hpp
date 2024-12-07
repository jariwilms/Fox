#pragma once

#include "stdafx.hpp"

#include "Fox/Input/Code/ButtonCode.hpp"
#include "Fox/Input/Code/KeyCode.hpp"
#include "Fox/Input/Code/ModifierCode.hpp"

#include "Fox/Input/Handler/InputHandlerAPI.hpp"

namespace fox::ipt::api
{
    void init(const std::shared_ptr<InputHandlerAPI> inputHandler);

    inline std::shared_ptr<InputHandlerAPI> inputHandler{};
}
namespace fox::ipt
{
    fox::bool_t   any_pressed();
    fox::bool_t   any_down();
    fox::bool_t   any_up();
              
    fox::bool_t   key_pressed(key::key_t code);
    fox::bool_t   key_down(key::key_t code);
    fox::bool_t   key_up(key::key_t code);
              
    fox::bool_t   button_pressed(btn::btn_t code);
    fox::bool_t   button_down(btn::btn_t code);
    fox::bool_t   button_up(btn::btn_t code);
              
    fox::bool_t   scrolling();
    fox::bool_t   scrolling_vertical();
    fox::bool_t   scrolling_horizontal();

    fox::Vector2f cursor_position();
    fox::Vector2f cursor_position_relative();
}
