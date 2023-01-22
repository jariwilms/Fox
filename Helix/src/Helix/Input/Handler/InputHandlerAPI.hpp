#pragma once

#include "stdafx.hpp"

#include "glm/glm.hpp"

#include "Helix/Window/Window.hpp"
#include "Helix/Input/Code/KeyCode.hpp"
#include "Helix/Input/Code/ButtonCode.hpp"

namespace hlx
{
    class InputHandlerAPI
    {
    public:
        virtual ~InputHandlerAPI() = default;

        virtual void update() = 0;
        virtual void reset() = 0;

        virtual bool any_pressed() = 0;
        virtual bool any_down() = 0;
        virtual bool any_up() = 0;

        virtual bool key_pressed(KeyCode code) = 0;
        virtual bool key_down(KeyCode code) = 0;
        virtual bool key_up(KeyCode code) = 0;

        virtual bool button_pressed(ButtonCode code) = 0;
        virtual bool button_down(ButtonCode code) = 0;
        virtual bool button_up(ButtonCode code) = 0;

        virtual bool scrolling() = 0;
        virtual bool scrolling_vertical() = 0;
        virtual bool scrolling_horizontal() = 0;

    protected:
        InputHandlerAPI() = default;

        std::bitset<Key::max> m_activeKeys{};
        std::bitset<Key::max> m_lastActiveKeys{};

        std::bitset<Button::max> m_activeButtons{};
        std::bitset<Button::max> m_lastActiveButtons{};

        glm::vec2 m_cursorPosition{};
        glm::vec2 m_lastCursorPosition{};
    };
}
