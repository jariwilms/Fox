#include "stdafx.hpp"

#include "GLFWInputHandler.hpp"
#include "Fox/Window/API/GLFW/GLFWWindow.hpp"

namespace fox::input
{
    void          GLFWInputHandler::update()
    {
        m_lastActiveKeys     = m_activeKeys;
        m_lastActiveButtons  = m_activeButtons;
        m_lastCursorPosition = m_cursorPosition;
    }
    void          GLFWInputHandler::reset()
    {
        m_activeKeys.reset();
        m_lastActiveKeys.reset();

        m_activeButtons.reset();
        m_lastActiveButtons.reset();

        m_cursorPosition     = fox::Vector2f{};
        m_lastCursorPosition = fox::Vector2f{};
    }
                  
    fox::bool_t   GLFWInputHandler::any_pressed()                   const
    {
        return m_activeKeys.any() || m_activeButtons.any();
    }
    fox::bool_t   GLFWInputHandler::any_down()                      const
    {
        return false;
    }
    fox::bool_t   GLFWInputHandler::any_up()                        const
    {
        return false;
    }
                  
    fox::bool_t   GLFWInputHandler::key_pressed(key::key_t code)    const
    {
        return m_activeKeys.test(code);
    }
    fox::bool_t   GLFWInputHandler::key_down(key::key_t code)       const
    {
        return m_activeKeys.test(code) && !m_lastActiveKeys.test(code);
    }
    fox::bool_t   GLFWInputHandler::key_up(key::key_t code)         const
    {
        return !m_activeKeys.test(code) && m_lastActiveKeys.test(code);
    }
                  
    fox::bool_t   GLFWInputHandler::button_pressed(btn::btn_t code) const
    {
        return m_activeButtons.test(code);
    }
    fox::bool_t   GLFWInputHandler::button_down(btn::btn_t code)    const
    {
        return m_activeButtons.test(code) && !m_lastActiveButtons.test(code);
    }
    fox::bool_t   GLFWInputHandler::button_up(btn::btn_t code)      const
    {
        return !m_activeButtons.test(code) && m_lastActiveButtons.test(code);
    }
                  
    fox::bool_t   GLFWInputHandler::scrolling()                     const
    {
        return false;
    }
    fox::bool_t   GLFWInputHandler::scrolling_vertical()            const
    {
        return false;
    }
    fox::bool_t   GLFWInputHandler::scrolling_horizontal()          const
    {
        return false;
    }
                  
    fox::bool_t   GLFWInputHandler::modifier(mod::mod_t code)       const
    {
        return false;
    }
    
    fox::Vector2f GLFWInputHandler::cursor_position()               const
    {
        return m_cursorPosition;
    }
    fox::Vector2f GLFWInputHandler::cursor_position_relative()      const
    {
        return m_cursorPosition - m_lastCursorPosition;
    }

    void          GLFWInputHandler::glfw_input_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
    {
        if (key < key::min || key > key::max) return;
        
        switch (action)
        {
            case GLFW_PRESS:   m_activeKeys.set(key, true);  break;
            case GLFW_RELEASE: m_activeKeys.set(key, false); break;
            case GLFW_REPEAT:  break;

            default:           throw std::invalid_argument{ "Invalid action!" };
        }
    }
    void          GLFWInputHandler::glfw_input_button_callback(GLFWwindow* window, int button, int action, int mods)
    {
        if (button < btn::min || button > btn::max) return;

        switch (action)
        {
            case GLFW_PRESS:   m_activeButtons.set(button, true);  break;
            case GLFW_RELEASE: m_activeButtons.set(button, false); break;
            case GLFW_REPEAT:  break;

            default:           throw std::invalid_argument{ "Invalid action!" };
        }
    }
    void          GLFWInputHandler::glfw_input_cursor_callback(GLFWwindow* window, double x, double y)
    {
        m_cursorPosition = fox::Vector2f{ x, y };
    }
    void          GLFWInputHandler::glfw_input_scroll_callback(GLFWwindow* window, double x, double y)
    {
        
    }
}
