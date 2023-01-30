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

        bool any_pressed() const override;
        bool any_down() const override;
        bool any_up() const override;

        bool key_pressed(KeyCode code) const override;
        bool key_down(KeyCode code) const override;
        bool key_up(KeyCode code) const override;

        bool button_pressed(ButtonCode code) const override;
        bool button_down(ButtonCode code) const override;
        bool button_up(ButtonCode code) const override;

        bool scrolling() const override;
        bool scrolling_vertical() const override;
        bool scrolling_horizontal() const override;

        bool modifier(ModifierCode code) const override;

        Vector2f cursor_position() const override;
        Vector2f cursor_position_relative() const override;

        void glfw_input_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
        void glfw_input_button_callback(GLFWwindow* window, int button, int action, int mods);
        void glfw_input_cursor_callback(GLFWwindow* window, double x, double y);
        void glfw_input_scroll_callback(GLFWwindow* window, double x, double y);
    };
}
