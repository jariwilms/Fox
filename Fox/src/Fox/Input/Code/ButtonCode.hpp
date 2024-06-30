#pragma once

#include "stdafx.hpp"

namespace fox
{
    using ButtonCode = int;

    class Button
    {
    public:
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

        static constexpr int min = Button0;
        static constexpr int max = Button7;
    };
}
