export module fox.input.code.button;

import std;
import fox.core.types;

export namespace fox::input
{
    enum class button : fox::int32_t
    {
        button1 = 0, 
        button2 = 1, 
        button3 = 2, 
        button4 = 3, 
        button5 = 4, 
        button6 = 5,
        button7 = 6,
        button8 = 7,

        left_mouse   = button1, 
        right_mouse  = button2, 
        middle_mouse = button3, 
        back         = button4, 
        forward      = button5, 
    };

    constexpr auto button_min = input::button::button1;
    constexpr auto button_max = input::button::button8;
}
