export module fox.input.code.controller;

import std;
import fox.core.types;

export namespace fox::input
{
    enum class controller : fox::int32_t
    {
        HatCentered  = 0x0 << 0u, 
        HatUp        = 0x1 << 0u, 
        HatRight     = 0x1 << 1u, 
        HatDown      = 0x1 << 2u, 
        HatLeft      = 0x1 << 3u, 

        HatRightUp   = HatRight | HatUp  , 
        HatRightDown = HatRight | HatDown, 
        HatLeftUp    = HatLeft  | HatUp  , 
        HatLeftDown  = HatLeft  | HatDown,  
    };

    constexpr auto controller_min = input::controller::HatCentered;
    constexpr auto controller_max = input::controller::HatLeft    ;
}
