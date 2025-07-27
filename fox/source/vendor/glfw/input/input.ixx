export module vendor.glfw.input;

import std;
import <glfw/glfw3.h>;
import fox.core.types;
import fox.core.utility;
import fox.input.code.button;
import fox.input.code.controller;
import fox.input.code.key;
import fox.input.code.modifier;
import vendor.glfw.functions;
import vendor.glfw.types;

export namespace vendor::glfw
{
    class input_handler
    {
    public:
        void capture                   ()
        {
            lastActiveKeys_     = activeKeys_;
            lastActiveButtons_  = activeButtons_;
            lastCursorPosition_ = cursorPosition_;
            lastScrollWheel_    = scrollWheel_;
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

        auto any_key_active            () const -> fox::bool_t
        {
            return activeKeys_.any();
        }
        auto any_button_active         () const -> fox::bool_t
        {
            return activeButtons_.any();
        }

        auto key_active                (fox::input::key_e    code) const -> fox::bool_t
        {
            return activeKeys_.test(std::to_underlying(code));
        }
        auto key_pressed               (fox::input::key_e    code) const -> fox::bool_t
        {
            return activeKeys_.test(std::to_underlying(code)) && !lastActiveKeys_.test(std::to_underlying(code));
        }
        auto key_released              (fox::input::key_e    code) const -> fox::bool_t
        {
            return !activeKeys_.test(std::to_underlying(code)) && lastActiveKeys_.test(std::to_underlying(code));
        }

        auto button_active             (fox::input::button_e code) const -> fox::bool_t
        {
            return activeButtons_.test(std::to_underlying(code));
        }
        auto button_pressed            (fox::input::button_e code) const -> fox::bool_t
        {
            return activeButtons_.test(std::to_underlying(code)) && !lastActiveButtons_.test(std::to_underlying(code));
        }
        auto button_released           (fox::input::button_e code) const -> fox::bool_t
        {
            return !activeButtons_.test(std::to_underlying(code)) && lastActiveButtons_.test(std::to_underlying(code));
        }

        auto cursor_position           () const -> fox::vector2f
        {
            return cursorPosition_;
        }
        auto cursor_position_delta     () const -> fox::vector2f
        {
            return cursorPosition_ - lastCursorPosition_;
        }

        auto scroll_wheel              () const -> fox::vector2f
        {
            return scrollWheel_;
        }
        auto scroll_wheel_delta        () const -> fox::vector2f
        {
            return lastScrollWheel_ - scrollWheel_;
        }

        void input_key_callback        (glfw::window_t*, fox::input::key_e    key   , fox::int32_t, fox::int32_t action, fox::input::modifier_e)
        {
            if (fox::compare_enum<std::less>(key, fox::input::key_min) || fox::compare_enum<std::greater>(key, fox::input::key_max)) 
                return;

            switch (glfw::input_action_e{ action })
            {
                case glfw::input_action_e::release: activeKeys_.set(std::to_underlying(key), fox::false_); break;
                case glfw::input_action_e::press  : activeKeys_.set(std::to_underlying(key), fox::true_ ); break;
                case glfw::input_action_e::repeat :                                                        break;
            }
        }
        void input_button_callback     (glfw::window_t*, fox::input::button_e button,               fox::int32_t action, fox::input::modifier_e)
        {
            if (fox::compare_enum<std::less>(button, fox::input::button_min) || fox::compare_enum<std::greater>(button, fox::input::button_max)) 
                return;

            switch (glfw::input_action_e{ action })
            {
                case glfw::input_action_e::release: activeButtons_.set(std::to_underlying(button), fox::false_); break;
                case glfw::input_action_e::press  : activeButtons_.set(std::to_underlying(button), fox::true_ ); break;
                case glfw::input_action_e::repeat :                                                              break;
            }
        }
        void input_cursor_callback     (glfw::window_t*, fox::float64_t  x, fox::float64_t y)
        {
            cursorPosition_ = fox::vector2f{ static_cast<fox::float32_t>(x), static_cast<fox::float32_t>(y) };
        }
        void input_scroll_callback     (glfw::window_t*, fox::float64_t  x, fox::float64_t y)
        {
            scrollWheel_ = fox::vector2f{ static_cast<fox::float32_t>(x), static_cast<fox::float32_t>(y) };
        }

    private:
        std::bitset<std::to_underlying(fox::input::key_max   )> activeKeys_;
        std::bitset<std::to_underlying(fox::input::key_max   )> lastActiveKeys_;
        std::bitset<std::to_underlying(fox::input::button_max)> activeButtons_;
        std::bitset<std::to_underlying(fox::input::button_max)> lastActiveButtons_;

        fox::vector2f                                           cursorPosition_;
        fox::vector2f                                           lastCursorPosition_;
        fox::vector2f                                           scrollWheel_;
        fox::vector2f                                           lastScrollWheel_;
    };
}

