export module fox.input.code.controller;

import std;
import fox.core.types;

export namespace fox::input
{
    enum class controller : fox::int32_t
    {
        hat_centered  = 0x0 << 0u, 
        hat_up        = 0x1 << 0u, 
        hat_right     = 0x1 << 1u, 
        hat_down      = 0x1 << 2u, 
        hat_left      = 0x1 << 3u, 

        hat_right_up   = hat_right | hat_up  , 
        hat_right_down = hat_right | hat_down, 
        hat_left_up    = hat_left  | hat_up  , 
        hat_left_down  = hat_left  | hat_down, 
    };

    constexpr auto controller_min = input::controller::hat_centered;
    constexpr auto controller_max = input::controller::hat_left    ;
}
