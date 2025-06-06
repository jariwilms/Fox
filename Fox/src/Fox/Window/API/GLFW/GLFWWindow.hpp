#pragma once

#include "stdafx.hpp"

#include "Fox/Input/Handler/Platform/GLFWInputHandler.hpp"
#include "Fox/Input/Input.hpp"
#include "Fox/Window/Window.hpp"

namespace fox::wnd::api
{
	class GLFWWindow : public Window
	{
	public:
        struct UserPointer
        {
		public:
			std::shared_ptr<GLFWWindow>            glfwWindow{};
			std::shared_ptr<input::GLFWInputHandler> inputHandler{};
        };

		GLFWWindow(const std::string& name, const fox::Vector2u& dimensions);
		~GLFWWindow();

		void poll_events();
		void swap_buffers();

		void rename(const std::string& title);
		void resize(const fox::Vector2f& dimensions);

		void        close()        const;
		fox::bool_t should_close() const;

	private:
        void glfw_error_callback(fox::int32_t error, const fox::char_t* description);

		GLFWwindow*                  m_glfwWindow{};
		std::shared_ptr<UserPointer> m_userPointer{};
	};
}
