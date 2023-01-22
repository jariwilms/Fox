#pragma once

#include "stdafx.hpp"

namespace hlx
{
    using ButtonCode = int;

    class Button
    {
    public:
        static constexpr int min = 0;
        static constexpr int max = 7;

        enum : ButtonCode
        {
            Button0      =       0, 
            Button1      =       1, 
            Button2      =       2, 
            Button3      =       3, 
            Button4      =       4, 
            Button5      =       5, 
            Button6      =       6, 
            Button7      =       7, 

            ButtonLast   = Button7, 
            ButtonLeft   = Button0, 
            ButtonRight  = Button1, 
            ButtonMiddle = Button2, 
        };
    };
}
