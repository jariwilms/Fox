export module fox.input.code.modifier;

import std;
import fox.core.types;

export namespace fox::input
{
    enum class modifier : fox::int32_t
    {
        none      = 0x0, 

        shift     = 0x1 << 0u, 
        control   = 0x1 << 1u, 
        alt       = 0x1 << 2u, 
        super     = 0x1 << 3u, 
        caps_lock = 0x1 << 4u, 
        num_lock  = 0x1 << 5u, 
    };
    
    constexpr auto modifier_min = input::modifier::shift   ;
    constexpr auto modifier_max = input::modifier::num_lock;
}
