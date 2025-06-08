#pragma once

#include "stdafx.hpp"

#include "Fox/Input/Code/KeyCode.hpp"
#include "Fox/Input/Code/ButtonCode.hpp"
#include "Fox/Input/Code/ModifierCode.hpp"

namespace fox::input
{
    class InputHandlerAPI
    {
    public:
        virtual ~InputHandlerAPI() = default;

        virtual void          update()                              = 0;
        virtual void          reset()                               = 0;

        virtual fox::bool_t   any_pressed()                   const = 0;
        virtual fox::bool_t   any_down()                      const = 0;
        virtual fox::bool_t   any_up()                        const = 0;
                              
        virtual fox::bool_t   key_pressed(key::key_t code)    const = 0;
        virtual fox::bool_t   key_down(key::key_t code)       const = 0;
        virtual fox::bool_t   key_up(key::key_t code)         const = 0;
                              
        virtual fox::bool_t   button_pressed(btn::btn_t code) const = 0;
        virtual fox::bool_t   button_down(btn::btn_t code)    const = 0;
        virtual fox::bool_t   button_up(btn::btn_t code)      const = 0;
                              
        virtual fox::bool_t   scrolling()                     const = 0;
        virtual fox::bool_t   scrolling_vertical()            const = 0;
        virtual fox::bool_t   scrolling_horizontal()          const = 0;
                              
        virtual fox::bool_t   modifier(mod::mod_t code)       const = 0;

        virtual fox::Vector2f cursor_position()               const = 0;
        virtual fox::Vector2f cursor_position_relative()      const = 0;

    protected:
        InputHandlerAPI() = default;

        std::bitset<key::max> m_activeKeys{};
        std::bitset<key::max> m_lastActiveKeys{};
        std::bitset<btn::max> m_activeButtons{};
        std::bitset<btn::max> m_lastActiveButtons{};
        std::bitset<mod::max> m_modifiers{};

        fox::Vector2f         m_cursorPosition{};
        fox::Vector2f         m_lastCursorPosition{};
    };
}
