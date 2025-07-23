export module fox.input.code.key;

import std;
import fox.core.types;

export namespace fox::input
{
    enum class key : fox::int32_t
    {
        space        =  32, apostrophe    =  39, 
        comma        =  44, minus         =  45, 
        period       =  46, slash         =  47, 
        
        d0           =  48, d1            =  49, 
        d2           =  50, d3            =  51, 
        d4           =  52, d5            =  53, 
        d6           =  54, d7            =  55, 
        d8           =  56, d9            =  57, 
        
        semicolon    =  59, equal         =  61, 
        
        a            =  65, b             =  66, 
        c            =  67, d             =  68, 
        e            =  69, f             =  70, 
        g            =  71, h             =  72, 
        i            =  73, j             =  74, 
        k            =  75, l             =  76, 
        m            =  77, n             =  78, 
        o            =  79, p             =  80, 
        q            =  81, r             =  82, 
        s            =  83, t             =  84, 
        u            =  85, v             =  86, 
        w            =  87, x             =  88, 
        y            =  89, z             =  90, 
        
        leftbracket  =  91, backslash     =  92, 
        rightbracket =  93, graveaccent   =  96, 

        world1       = 161, world2        = 162, 
        
        escape       = 256, enter         = 257, 
        tab          = 258, backspace     = 259, 
        insert       = 260, delete_       = 261, 
        right        = 262, left          = 263, 
        down         = 264, up            = 265, 
        pageup       = 266, pagedown      = 267, 
        home         = 268, end           = 269, 
        capslock     = 280, scrolllock    = 281, 
        numlock      = 282, printscreen   = 283, 
        pause        = 284, 
        
        f1           = 290, f2            = 291, 
        f3           = 292, f4            = 293, 
        f5           = 294, f6            = 295, 
        f7           = 296, f8            = 297, 
        f9           = 298, f10           = 299, 
        f11          = 300, f12           = 301, 
        f13          = 302, f14           = 303, 
        f15          = 304, f16           = 305, 
        f17          = 306, f18           = 307, 
        f19          = 308, f20           = 309, 
        f21          = 310, f22           = 311, 
        f23          = 312, f24           = 313, 
        f25          = 314, 
        
        kp0          = 320, kp1           = 321, 
        kp2          = 322, kp3           = 323, 
        kp4          = 324, kp5           = 325, 
        kp6          = 326, kp7           = 327, 
        kp8          = 328, kp9           = 329, 
        kp_decimal   = 330, kp_divide     = 331, 
        kp_multiply  = 332, kp_subtract   = 333, 
        kp_add       = 334, kp_enter      = 335, 
        kp_equal     = 336, 
        
        left_shift   = 340, left_control  = 341, 
        left_alt     = 342, left_super    = 343, 
        right_shift  = 344, right_control = 345, 
        right_alt    = 346, right_super   = 347, 
        menu         = 348, 
    };

    constexpr auto key_min = input::key::space;
    constexpr auto key_max = input::key::menu ;
}
