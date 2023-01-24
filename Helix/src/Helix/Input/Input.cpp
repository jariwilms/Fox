#include "stdafx.hpp"

#include "Input.hpp"
#include "Helix/Input/Handler/Platform/GLFWInputHandler.hpp"

namespace hlx
{
    void Input::init(const std::shared_ptr<InputHandlerAPI> inputHandler)
    {
        s_inputHandler = inputHandler;
    }
 
    bool Input::any_pressed()
    {
        return s_inputHandler->any_pressed();
    }
    bool Input::any_down()
    {
        return s_inputHandler->any_down();
    }
    bool Input::any_up()
    {
        return s_inputHandler->any_up();
    }

    bool Input::key_pressed(KeyCode code)
    {
        return s_inputHandler->key_pressed(code);
    }
    bool Input::key_down(KeyCode code)
    {
        return s_inputHandler->key_down(code);
    }
    bool Input::key_up(KeyCode code)
    {
        return s_inputHandler->key_up(code);
    }

    bool Input::button_pressed(ButtonCode code)
    {
        return s_inputHandler->button_pressed(code);
    }
    bool Input::button_down(ButtonCode code)
    {
        return s_inputHandler->button_down(code);
    }
    bool Input::button_up(ButtonCode code)
    {
        return s_inputHandler->button_up(code);
    }

    bool Input::scrolling()
    {
        return s_inputHandler->scrolling();
    }
    bool Input::scrolling_vertical()
    {
        return s_inputHandler->scrolling_vertical();
    }
    bool Input::scrolling_horizontal()
    {
        return s_inputHandler->scrolling_horizontal();
    }

    glm::vec2 Input::cursor_position()
    {
        return s_inputHandler->cursor_position();
    }
    glm::vec2 Input::cursor_position_relative()
    {
        return s_inputHandler->cursor_position_relative();
    }
}
