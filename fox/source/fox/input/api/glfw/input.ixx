export module fox.input.api.glfw;

import std;
import fox.core.types;
import fox.core.utility;
import fox.input.code.button;
import fox.input.code.controller;
import fox.input.code.key;
import fox.input.code.modifier;
import vendor.glfw;

export namespace fox::input::api::glfw
{
    class input_handler
    {
    public:
        void update                    ()
        {
            lastActiveKeys_     = activeKeys_    ;
            lastActiveButtons_  = activeButtons_ ;
            lastCursorPosition_ = cursorPosition_;
            lastScrollWheel_    = scrollWheel_   ;
        }
        void reset                     ()
        {
            activeKeys_       .reset();
            lastActiveKeys_   .reset();
            activeButtons_    .reset();
            lastActiveButtons_.reset();

            cursorPosition_     = {};
            lastCursorPosition_ = {};
            scrollWheel_        = {};
            lastScrollWheel_    = {};
        }

        auto any_key_active            ()                   const -> fox::bool_t
        {
            return activeKeys_.any();
        }
        auto any_button_active         ()                   const -> fox::bool_t
        {
            return activeButtons_.any();
        }

        auto key_active                (input::key_e    code) const -> fox::bool_t
        {
            return activeKeys_.test(std::to_underlying(code));
        }
        auto key_pressed               (input::key_e    code) const -> fox::bool_t
        {
            return activeKeys_.test(std::to_underlying(code)) && !lastActiveKeys_.test(std::to_underlying(code));
        }
        auto key_released              (input::key_e    code) const -> fox::bool_t
        {
            return !activeKeys_.test(std::to_underlying(code)) && lastActiveKeys_.test(std::to_underlying(code));
        }

        auto button_active             (input::button_e code) const -> fox::bool_t
        {
            return activeButtons_.test(std::to_underlying(code));
        }
        auto button_pressed            (input::button_e code) const -> fox::bool_t
        {
            return activeButtons_.test(std::to_underlying(code)) && !lastActiveButtons_.test(std::to_underlying(code));
        }
        auto button_released           (input::button_e code) const -> fox::bool_t
        {
            return !activeButtons_.test(std::to_underlying(code)) && lastActiveButtons_.test(std::to_underlying(code));
        }

        auto cursor_position           ()                   const -> fox::vector2f
        {
            return cursorPosition_;
        }
        auto cursor_position_delta     ()                   const -> fox::vector2f
        {
            return cursorPosition_ - lastCursorPosition_;
        }

        auto scroll_wheel              ()                   const -> fox::vector2f
        {
            return scrollWheel_;
        }
        auto scroll_wheel_delta        ()                   const -> fox::vector2f
        {
            return lastScrollWheel_ - scrollWheel_;
        }

        void glfw_input_key_callback   (::glfw::window_t*, input::key_e      key   , fox::int32_t    , fox::int32_t action, input::modifier_e)
        {
            if (fox::compare_enum<std::less>(key, input::key_min) || fox::compare_enum<std::greater>(key, input::key_max)) return;
            switch (::glfw::input_action_e{ action })
            {
                case ::glfw::input_action_e::release: activeKeys_.set(std::to_underlying(key), fox::false_); break;
                case ::glfw::input_action_e::press  : activeKeys_.set(std::to_underlying(key), fox::true_ ); break;
                case ::glfw::input_action_e::repeat :                                                       break;
            }
        }
        void glfw_input_button_callback(::glfw::window_t*, input::button_e   button,                   fox::int32_t action, input::modifier_e)
        {
            if (fox::compare_enum<std::less>(button, input::button_min) || fox::compare_enum<std::greater>(button, input::button_max)) return;
            switch (::glfw::input_action_e{ action })
            {
                case ::glfw::input_action_e::release: activeButtons_.set(std::to_underlying(button), fox::false_); break;
                case ::glfw::input_action_e::press  : activeButtons_.set(std::to_underlying(button), fox::true_ ); break;
                case ::glfw::input_action_e::repeat :                                                             break;
            }
        }
        void glfw_input_cursor_callback(::glfw::window_t*, fox::float64_t  x     , fox::float64_t y                                      )
        {
            cursorPosition_ = fox::vector2f{ static_cast<fox::float32_t>(x), static_cast<fox::float32_t>(y) };
        }
        void glfw_input_scroll_callback(::glfw::window_t*, fox::float64_t  x     , fox::float64_t y                                      )
        {
            scrollWheel_ = fox::vector2f{ static_cast<fox::float32_t>(x), static_cast<fox::float32_t>(y) };
        }
    
    private:
        std::bitset<std::to_underlying(input::key_max   )> activeKeys_        ;
        std::bitset<std::to_underlying(input::key_max   )> lastActiveKeys_    ;
        std::bitset<std::to_underlying(input::button_max)> activeButtons_     ;
        std::bitset<std::to_underlying(input::button_max)> lastActiveButtons_ ;

        fox::vector2f                                      cursorPosition_    ;
        fox::vector2f                                      lastCursorPosition_;
        fox::vector2f                                      scrollWheel_       ;
        fox::vector2f                                      lastScrollWheel_   ;
    };
}
