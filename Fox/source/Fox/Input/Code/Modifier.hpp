#pragma once

#include "stdafx.hpp"

namespace fox::input
{
    using modifier_t = fox::int32_t;

    namespace modifier
    {
        enum : modifier_t
        {
            None     = 0x0, 

            Shift    = 0x1 << 0u, 
            Control  = 0x1 << 1u, 
            Alt      = 0x1 << 2u, 
            Super    = 0x1 << 3u, 
            CapsLock = 0x1 << 4u, 
            NumLock  = 0x1 << 5u, 
        };
    
        static constexpr modifier_t min{ Shift };
        static constexpr modifier_t max{ NumLock };
    }
}
