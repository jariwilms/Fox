#include "stdafx.hpp"

#include "GLFWInputHandler.hpp"
#include "Helix/Window/API/GLFW/GLFWWindow.hpp"

namespace hlx
{
    GLFWInputHandler::GLFWInputHandler()
    {

    }
    GLFWInputHandler::~GLFWInputHandler()
    {

    }

    void GLFWInputHandler::update()
    {
        m_lastActiveKeys = m_activeKeys;
        m_lastActiveButtons = m_activeButtons;
    }
    void GLFWInputHandler::reset()
    {
        m_activeKeys.reset();
        m_lastActiveKeys.reset();

        m_activeButtons.reset();
        m_lastActiveButtons.reset();

        m_cursorPosition = glm::vec2{};
        m_lastCursorPosition = glm::vec2{};
    }

    bool GLFWInputHandler::any_pressed()
    {
        return m_activeKeys.any() || m_activeButtons.any();
    }
    bool GLFWInputHandler::any_down()
    {
        return false;
    }
    bool GLFWInputHandler::any_up()
    {
        return false;
    }

    bool GLFWInputHandler::key_pressed(KeyCode code)
    {
        return m_activeKeys.test(code);
    }
    bool GLFWInputHandler::key_down(KeyCode code)
    {
        return m_activeKeys.test(code) && !m_lastActiveKeys.test(code);
    }
    bool GLFWInputHandler::key_up(KeyCode code)
    {
        return !m_activeKeys.test(code) && m_lastActiveKeys.test(code);
    }

    bool GLFWInputHandler::button_pressed(ButtonCode code)
    {
        return m_activeButtons.test(code);
    }
    bool GLFWInputHandler::button_down(ButtonCode code)
    {
        return m_activeButtons.test(code) && !m_lastActiveButtons.test(code);
    }
    bool GLFWInputHandler::button_up(ButtonCode code)
    {
        return !m_activeButtons.test(code) && m_lastActiveButtons.test(code);
    }

    bool GLFWInputHandler::scrolling()
    {
        return false;
    }
    bool GLFWInputHandler::scrolling_vertical()
    {
        return false;
    }
    bool GLFWInputHandler::scrolling_horizontal()
    {
        return false;
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
        m_cursorPosition = glm::vec2{ x, y };
    }
    void GLFWInputHandler::glfw_input_scroll_callback(GLFWwindow* window, double x, double y)
    {
        
    }
}
