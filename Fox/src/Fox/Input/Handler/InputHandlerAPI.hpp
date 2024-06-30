#pragma once

#include "stdafx.hpp"

#include "Fox/Input/Code/KeyCode.hpp"
#include "Fox/Input/Code/ButtonCode.hpp"
#include "Fox/Input/Code/ModifierCode.hpp"

namespace fox
{
    class InputHandlerAPI
    {
    public:
        virtual ~InputHandlerAPI() = default;

        virtual void update() = 0;
        virtual void reset() = 0;

        virtual bool any_pressed() const = 0;
        virtual bool any_down() const = 0;
        virtual bool any_up() const = 0;

        virtual bool key_pressed(KeyCode code) const = 0;
        virtual bool key_down(KeyCode code) const = 0;
        virtual bool key_up(KeyCode code) const = 0;

        virtual bool button_pressed(ButtonCode code) const = 0;
        virtual bool button_down(ButtonCode code) const = 0;
        virtual bool button_up(ButtonCode code) const = 0;

        virtual bool scrolling() const = 0;
        virtual bool scrolling_vertical() const = 0;
        virtual bool scrolling_horizontal() const = 0;

        virtual bool modifier(ModifierCode code) const = 0;

        virtual Vector2f cursor_position() const = 0;
        virtual Vector2f cursor_position_relative() const = 0;

    protected:
        InputHandlerAPI() = default;

        std::bitset<Key::max> m_activeKeys{};
        std::bitset<Key::max> m_lastActiveKeys{};

        std::bitset<Button::max> m_activeButtons{};
        std::bitset<Button::max> m_lastActiveButtons{};

        std::bitset<Modifier::max> m_modifiers{};

        Vector2f m_cursorPosition{};
        Vector2f m_lastCursorPosition{};
    };
}
