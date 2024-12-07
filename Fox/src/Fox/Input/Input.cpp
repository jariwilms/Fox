#include "stdafx.hpp"

#include "Input.hpp"

namespace fox::inp::api
{
    void init(const std::shared_ptr<InputHandlerAPI> handler)
    {
        inputHandler = handler;
    }
}
namespace fox::inp
{
    fox::bool_t   any_pressed()
    {
        return api::inputHandler->any_pressed();
    }
    fox::bool_t   any_down()
    {
        return api::inputHandler->any_down();
    }
    fox::bool_t   any_up()
    {
        return api::inputHandler->any_up();
    }
                  
    fox::bool_t   key_pressed(key::key_t code)
    {
        return api::inputHandler->key_pressed(code);
    }
    fox::bool_t   key_down(key::key_t code)
    {
        return api::inputHandler->key_down(code);
    }
    fox::bool_t   key_up(key::key_t code)
    {
        return api::inputHandler->key_up(code);
    }
                  
    fox::bool_t   button_pressed(btn::btn_t code)
    {
        return api::inputHandler->button_pressed(code);
    }
    fox::bool_t   button_down(btn::btn_t code)
    {
        return api::inputHandler->button_down(code);
    }
    fox::bool_t   button_up(btn::btn_t code)
    {
        return api::inputHandler->button_up(code);
    }
                  
    fox::bool_t   scrolling()
    {
        return api::inputHandler->scrolling();
    }
    fox::bool_t   scrolling_vertical()
    {
        return api::inputHandler->scrolling_vertical();
    }
    fox::bool_t   scrolling_horizontal()
    {
        return api::inputHandler->scrolling_horizontal();
    }

    fox::Vector2f cursor_position()
    {
        return api::inputHandler->cursor_position();
    }
    fox::Vector2f cursor_position_relative()
    {
        return api::inputHandler->cursor_position_relative();
    }
}
