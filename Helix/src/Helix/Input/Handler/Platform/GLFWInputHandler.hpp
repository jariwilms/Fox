#pragma once

#include "stdafx.hpp"

#include "glad/glad.h"
#include "glfw/glfw3.h"

#include "Helix/Input/Handler/InputHandlerAPI.hpp"

namespace hlx
{
    class GLFWInputHandler : public InputHandlerAPI
    {
    public:
        GLFWInputHandler();
        ~GLFWInputHandler() override;

        void update() override;
        void reset() override;

        bool any_pressed() override;
        bool any_down() override;
        bool any_up() override;

        bool key_pressed(KeyCode code) override;
        bool key_down(KeyCode code) override;
        bool key_up(KeyCode code) override;

        bool button_pressed(ButtonCode code) override;
        bool button_down(ButtonCode code) override;
        bool button_up(ButtonCode code) override;

        bool scrolling() override;
        bool scrolling_vertical() override;
        bool scrolling_horizontal() override;

        void glfw_input_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
        void glfw_input_button_callback(GLFWwindow* window, int button, int action, int mods);
        void glfw_input_cursor_callback(GLFWwindow* window, double x, double y);
        void glfw_input_scroll_callback(GLFWwindow* window, double x, double y);
    };
}
