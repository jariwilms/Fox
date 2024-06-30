#include "stdafx.hpp"

#include "GLFWInputHandler.hpp"
#include "Helix/Window/API/GLFW/GLFWWindow.hpp"

namespace hlx
{
    void GLFWInputHandler::update()
    {
        m_lastActiveKeys = m_activeKeys;
        m_lastActiveButtons = m_activeButtons;
        m_lastCursorPosition = m_cursorPosition;
    }
    void GLFWInputHandler::reset()
    {
        m_activeKeys.reset();
        m_lastActiveKeys.reset();

        m_activeButtons.reset();
        m_lastActiveButtons.reset();

        m_cursorPosition = Vector2f{};
        m_lastCursorPosition = Vector2f{};
    }

    bool GLFWInputHandler::any_pressed() const
    {
        return m_activeKeys.any() || m_activeButtons.any();
    }
    bool GLFWInputHandler::any_down() const
    {
        return false;
    }
    bool GLFWInputHandler::any_up() const
    {
        return false;
    }

    bool GLFWInputHandler::key_pressed(KeyCode code) const
    {
        return m_activeKeys.test(code);
    }
    bool GLFWInputHandler::key_down(KeyCode code) const
    {
        return m_activeKeys.test(code) && !m_lastActiveKeys.test(code);
    }
    bool GLFWInputHandler::key_up(KeyCode code) const
    {
        return !m_activeKeys.test(code) && m_lastActiveKeys.test(code);
    }

    bool GLFWInputHandler::button_pressed(ButtonCode code) const
    {
        return m_activeButtons.test(code);
    }
    bool GLFWInputHandler::button_down(ButtonCode code) const
    {
        return m_activeButtons.test(code) && !m_lastActiveButtons.test(code);
    }
    bool GLFWInputHandler::button_up(ButtonCode code) const
    {
        return !m_activeButtons.test(code) && m_lastActiveButtons.test(code);
    }

    bool GLFWInputHandler::scrolling() const
    {
        return false;
    }
    bool GLFWInputHandler::scrolling_vertical() const
    {
        return false;
    }
    bool GLFWInputHandler::scrolling_horizontal() const
    {
        return false;
    }

    bool GLFWInputHandler::modifier(ModifierCode code) const
    {
        return false;
    }
    
    Vector2f GLFWInputHandler::cursor_position() const
    {
        return m_cursorPosition;
    }
    Vector2f GLFWInputHandler::cursor_position_relative() const
    {
        return m_cursorPosition - m_lastCursorPosition;
    }

    void GLFWInputHandler::glfw_input_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
    {
        if (key < Key::min || key > Key::max) return;

        switch (action)
        {
            case GLFW_PRESS:   m_activeKeys.set(key, true);  break;
            case GLFW_RELEASE: m_activeKeys.set(key, false); break;
            case GLFW_REPEAT:  break;

            default:           throw std::invalid_argument{ "Invalid action!" };
        }
    }
    void GLFWInputHandler::glfw_input_button_callback(GLFWwindow* window, int button, int action, int mods)
    {
        if (button < Button::min || button > Button::max) return;

        switch (action)
        {
            case GLFW_PRESS:   m_activeButtons.set(button, true);  break;
            case GLFW_RELEASE: m_activeButtons.set(button, false); break;
            case GLFW_REPEAT:  break;

            default:           throw std::invalid_argument{ "Invalid action!" };
        }
    }
    void GLFWInputHandler::glfw_input_cursor_callback(GLFWwindow* window, double x, double y)
    {
        m_cursorPosition = Vector2f{ x, y };
    }
    void GLFWInputHandler::glfw_input_scroll_callback(GLFWwindow* window, double x, double y)
    {
        
    }
}
