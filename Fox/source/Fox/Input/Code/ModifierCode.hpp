#pragma once

#include "stdafx.hpp"

namespace fox::input::mod
{
    using modifier_t = fox::int32_t;

    enum : modifier_t
    {
        Shift    = 0x1 << 0,
        Ctrl     = 0x1 << 1,
        Alt      = 0x1 << 2,
        Super    = 0x1 << 3,
        CapsLock = 0x1 << 4,
        NumLock  = 0x1 << 5,
    };
    
    static constexpr modifier_t min{ Shift };
    static constexpr modifier_t max{ NumLock };
}
