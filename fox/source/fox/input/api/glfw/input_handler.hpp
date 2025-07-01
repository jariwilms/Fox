#pragma once

#include <stdafx.hpp>

#include <glfw/glfw3.h>

#include <fox/input/code/button.hpp>
#include <fox/input/code/key.hpp>
#include <fox/input/code/modifier.hpp>

namespace fox::input::api::glfw
{
    class InputHandler
    {
    public:
        void update                    ()
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
            modifiers_        .reset();

            cursorPosition_     = {};
            lastCursorPosition_ = {};
        }

        auto any_key_active            ()                     const -> fox::bool_t
        {
            return activeKeys_.any();
        }
        auto any_button_active         ()                     const -> fox::bool_t
        {
            return activeButtons_.any();
        }

        auto key_active                (input::key_t    code) const -> fox::bool_t
        {
            return activeKeys_.test(code);
        }
        auto key_pressed               (input::key_t    code) const -> fox::bool_t
        {
            return activeKeys_.test(code) and !lastActiveKeys_.test(code);
        }
        auto key_released              (input::key_t    code) const -> fox::bool_t
        {
            return !activeKeys_.test(code) and lastActiveKeys_.test(code);
        }

        auto button_active             (input::button_t code) const -> fox::bool_t
        {
            return activeButtons_.test(code);
        }
        auto button_pressed            (input::button_t code) const -> fox::bool_t
        {
            return activeButtons_.test(code) and !lastActiveButtons_.test(code);
        }
        auto button_released           (input::button_t code) const -> fox::bool_t
        {
            return !activeButtons_.test(code) and lastActiveButtons_.test(code);
        }

        auto cursor_position           ()                     const -> fox::Vector2f
        {
            return cursorPosition_;
        }
        auto cursor_position_delta     ()                     const -> fox::Vector2f
        {
            return cursorPosition_ - lastCursorPosition_;
        }

        auto scroll_wheel              ()                     const -> fox::Vector2f
        {
            return scrollWheel_;
        }
        auto scroll_wheel_delta        ()                     const -> fox::Vector2f
        {
            return lastScrollWheel_ - scrollWheel_;
        }

        void glfw_input_key_callback   (GLFWwindow* window, fox::int32_t   key   , fox::int32_t   scancode, fox::int32_t action, fox::int32_t mods)
        {
            if (std::cmp_less(key, key::min) or std::cmp_greater(key, key::max)) return;

            switch (action)
            {
                case GLFW_RELEASE: activeKeys_.set(key, fox::False); break;
                case GLFW_PRESS  : activeKeys_.set(key, fox::True ); break;
                case GLFW_REPEAT :                                    break;
            }
        }
        void glfw_input_button_callback(GLFWwindow* window, fox::int32_t   button,                          fox::int32_t action, fox::int32_t mods)
        {
            if (std::cmp_less(button, button::min) or std::cmp_greater(button, button::max)) return;

            switch (action)
            {
                case GLFW_RELEASE: activeButtons_.set(button, fox::False); break;
                case GLFW_PRESS  : activeButtons_.set(button, fox::True ); break;
                case GLFW_REPEAT :                                          break;
            }
        }
        void glfw_input_cursor_callback(GLFWwindow* window, fox::float64_t x     , fox::float64_t y                                               )
        {
            cursorPosition_ = fox::Vector2f{ static_cast<fox::float32_t>(x), static_cast<fox::float32_t>(y) };
        }
        void glfw_input_scroll_callback(GLFWwindow* window, fox::float64_t x     , fox::float64_t y                                               )
        {
            scrollWheel_ = fox::Vector2f{ static_cast<fox::float32_t>(x), static_cast<fox::float32_t>(y) };
        }
    
    protected:
        std::bitset<key     ::max> activeKeys_{};
        std::bitset<key     ::max> lastActiveKeys_{};
        std::bitset<button  ::max> activeButtons_{};
        std::bitset<button  ::max> lastActiveButtons_{};
        std::bitset<modifier::max> modifiers_{};

        fox::Vector2f              cursorPosition_{};
        fox::Vector2f              lastCursorPosition_{};
        fox::Vector2f              scrollWheel_{};
        fox::Vector2f              lastScrollWheel_{};
    };
}
