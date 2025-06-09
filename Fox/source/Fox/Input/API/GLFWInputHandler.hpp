#pragma once

#include "stdafx.hpp"

#include "glad/gl.h"
#include "glfw/glfw3.h"

#include "Fox/Input/Code/Button.hpp"
#include "Fox/Input/Code/Key.hpp"
#include "Fox/Input/Code/Modifier.hpp"

namespace fox::input::api
{
    class GLFWInputHandler
    {
    public:
        void update                    ()
        {
            m_lastActiveKeys     = m_activeKeys;
            m_lastActiveButtons  = m_activeButtons;
            m_lastCursorPosition = m_cursorPosition;
        }
        void reset                     ()
        {
            m_activeKeys       .reset();
            m_lastActiveKeys   .reset();
            m_activeButtons    .reset();
            m_lastActiveButtons.reset();
            m_modifiers        .reset();

            m_cursorPosition     = {};
            m_lastCursorPosition = {};
        }

        auto any_pressed               ()                       const -> fox::bool_t
        {
            return m_activeKeys.any() or m_activeButtons.any();
        }
        auto any_down                  ()                       const -> fox::bool_t
        {
            return fox::False;
        }
        auto any_up                    ()                       const -> fox::bool_t
        {
            return fox::False;
        }

        auto key_pressed               (input::key_t    code)   const -> fox::bool_t
        {
            return m_activeKeys.test(code);
        }
        auto key_down                  (input::key_t    code)   const -> fox::bool_t
        {
            return m_activeKeys.test(code) and !m_lastActiveKeys.test(code);
        }
        auto key_up                    (input::key_t    code)   const -> fox::bool_t
        {
            return !m_activeKeys.test(code) and m_lastActiveKeys.test(code);
        }

        auto button_pressed            (input::button_t code)   const -> fox::bool_t
        {
            return m_activeButtons.test(code);
        }
        auto button_down               (input::button_t code)   const -> fox::bool_t
        {
            return m_activeButtons.test(code) and !m_lastActiveButtons.test(code);
        }
        auto button_up                 (input::button_t code)   const -> fox::bool_t
        {
            return !m_activeButtons.test(code) and m_lastActiveButtons.test(code);
        }

        auto is_scrolling              ()                       const -> fox::bool_t
        {
            return fox::False;
        }
        auto is_scrolling_vertical     ()                       const -> fox::bool_t
        {
            return fox::False;
        }
        auto is_scrolling_horizontal   ()                       const -> fox::bool_t
        {
            return fox::False;
        }

        auto cursor_position           ()                       const -> fox::Vector2f
        {
            return m_cursorPosition;
        }
        auto cursor_position_relative  ()                       const -> fox::Vector2f
        {
            return m_cursorPosition - m_lastCursorPosition;
        }

        void glfw_input_key_callback   (GLFWwindow* window, fox::int32_t key   , fox::int32_t   scancode, fox::int32_t action, fox::int32_t mods)
        {
            if (std::cmp_less(key, key::min) or std::cmp_greater(key, key::max)) return;

            switch (action)
            {
                case GLFW_RELEASE: m_activeKeys.set(key, fox::False); break;
                case GLFW_PRESS  : m_activeKeys.set(key, fox::True ); break;
                case GLFW_REPEAT :                                    break;
            }
        }
        void glfw_input_button_callback(GLFWwindow* window, fox::int32_t button,                          fox::int32_t action, fox::int32_t mods)
        {
            if (std::cmp_less(button, button::min) or std::cmp_greater(button, button::max)) return;

            switch (action)
            {
                case GLFW_RELEASE: m_activeButtons.set(button, fox::False); break;
                case GLFW_PRESS  : m_activeButtons.set(button, fox::True ); break;
                case GLFW_REPEAT :                                          break;
            }
        }
        void glfw_input_cursor_callback(GLFWwindow* window, fox::float64_t x   , fox::float64_t y                                               )
        {
            m_cursorPosition = fox::Vector2f{ static_cast<fox::float32_t>(x), static_cast<fox::float32_t>(y) };
        }
        void glfw_input_scroll_callback(GLFWwindow* window, fox::float64_t x   , fox::float64_t y                                               )
        {
            
        }
    
    protected:
        std::bitset<key     ::max> m_activeKeys{};
        std::bitset<key     ::max> m_lastActiveKeys{};
        std::bitset<button  ::max> m_activeButtons{};
        std::bitset<button  ::max> m_lastActiveButtons{};
        std::bitset<modifier::max> m_modifiers{};

        fox::Vector2f              m_cursorPosition{};
        fox::Vector2f              m_lastCursorPosition{};
    };
}
