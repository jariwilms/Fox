#pragma once

#include "stdafx.hpp"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "Fox/Input/Handler/InputHandlerAPI.hpp"

namespace fox::ipt
{
    class GLFWInputHandler : public InputHandlerAPI
    {
    public:
        GLFWInputHandler() = default;
        ~GLFWInputHandler() override = default;

        void        update()                              override;
        void        reset()                               override;

        fox::bool_t any_pressed()                   const override;
        fox::bool_t any_down()                      const override;
        fox::bool_t any_up()                        const override;

        fox::bool_t key_pressed(key::key_t code)    const override;
        fox::bool_t key_down(key::key_t code)       const override;
        fox::bool_t key_up(key::key_t code)         const override;

        fox::bool_t button_pressed(btn::btn_t code) const override;
        fox::bool_t button_down(btn::btn_t code)    const override;
        fox::bool_t button_up(btn::btn_t code)      const override;

        fox::bool_t scrolling()                     const override;
        fox::bool_t scrolling_vertical()            const override;
        fox::bool_t scrolling_horizontal()          const override;

        fox::bool_t modifier(mod::mod_t code)       const override;

        fox::Vector2f cursor_position()             const override;
        fox::Vector2f cursor_position_relative()    const override;

        void glfw_input_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
        void glfw_input_button_callback(GLFWwindow* window, int button, int action, int mods);
        void glfw_input_cursor_callback(GLFWwindow* window, double x, double y);
        void glfw_input_scroll_callback(GLFWwindow* window, double x, double y);
    };
}
