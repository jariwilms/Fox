export module fox.input.code.modifier;

import std;
import fox.core.types;

export namespace fox::input
{
    enum class modifier : fox::int32_t
    {
        None     = 0x0, 

        Shift    = 0x1 << 0u, 
        Control  = 0x1 << 1u, 
        Alt      = 0x1 << 2u, 
        Super    = 0x1 << 3u, 
        CapsLock = 0x1 << 4u, 
        NumLock  = 0x1 << 5u, 
    };
    
    constexpr auto modifier_min{ input::modifier::Shift   };
    constexpr auto modifier_max{ input::modifier::NumLock };
}
