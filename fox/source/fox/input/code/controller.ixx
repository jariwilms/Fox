export module fox.input.code.controller;

import fox.core.types;

export namespace fox::input
{
    using controller_t = fox::int32_t;

    namespace controller
    {
        enum : input::controller_t
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

        constexpr input::controller_t min{ HatCentered };
        constexpr input::controller_t max{ HatLeft     };
    }
}
