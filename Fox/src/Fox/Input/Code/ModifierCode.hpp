#pragma once

#include "stdafx.hpp"

namespace hlx
{
    using ModifierCode = int;

    class Modifier
    {
    public:
        enum : ModifierCode
        {
            Shift    =  1,
            Ctrl     =  2, 
            Alt      =  4, 
            Super    =  8, 
            CapsLock = 16, 
            NumLock  = 32, 
        };

        static constexpr int min = Shift;
        static constexpr int max = NumLock;
    };
}
