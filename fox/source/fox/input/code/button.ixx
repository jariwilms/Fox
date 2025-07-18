export module fox.input.code.button;

import fox.core.types;

export namespace fox::input
{
    using button_t = fox::int32_t;

    namespace button
    {
        enum : input::button_t
        {
            Button1 = 0, 
            Button2 = 1, 
            Button3 = 2, 
            Button4 = 3, 
            Button5 = 4, 
            Button6 = 5,
            Button7 = 6,
            Button8 = 7,

            LeftMouse   = Button1, 
            RightMouse  = Button2, 
            MiddleMouse = Button3, 
            Back        = Button4, 
            Forward     = Button5, 
        };

        constexpr input::button_t min{ Button1 };
        constexpr input::button_t max{ Button8 };
    }
}
