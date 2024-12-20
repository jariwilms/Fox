#pragma once

#include "stdafx.hpp"

namespace fox::input::mod
{
    using mod_t = fox::int32_t;

    enum : mod_t
    {
        Shift    =  1,
        Ctrl     =  2, 
        Alt      =  4, 
        Super    =  8, 
        CapsLock = 16, 
        NumLock  = 32, 
    };

    static constexpr mod_t min{ Shift };
    static constexpr mod_t max{ NumLock };
}
