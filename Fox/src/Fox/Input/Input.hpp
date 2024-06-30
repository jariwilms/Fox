#pragma once

#include "stdafx.hpp"

#include "Code/KeyCode.hpp"
#include "Code/ButtonCode.hpp"

#include "Helix/Input/Handler/InputHandlerAPI.hpp"

namespace hlx
{
    class Input
    {
    public:
        static void init(const std::shared_ptr<InputHandlerAPI> inputHandler);

        static bool any_pressed();
        static bool any_down();
        static bool any_up();

        static bool key_pressed(KeyCode code);
        static bool key_down(KeyCode code);
        static bool key_up(KeyCode code);

        static bool button_pressed(ButtonCode code);
        static bool button_down(ButtonCode code);
        static bool button_up(ButtonCode code);

        static bool scrolling();
        static bool scrolling_vertical();
        static bool scrolling_horizontal();

        static Vector2f cursor_position();
        static Vector2f cursor_position_relative();

    private:
        static inline std::shared_ptr<InputHandlerAPI> s_inputHandler{};
    };
}
