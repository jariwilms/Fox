#pragma once

#include <stdafx.hpp>

#include <fox/core/types/math/linear_algebra/vector.hpp>
#include <fox/input/api/glfw/input_handler.hpp>
#include <fox/input/input.hpp>
#include <fox/window/api/window.hpp>

namespace fox::wnd::api::glfw
{
	class Window : public api::Window
	{
	public:
        struct UserPointer
        {
			std::shared_ptr<Window>                     glfwWindow  {};
			std::shared_ptr<input::api::glfw::InputHandler> inputHandler{};
        };

		Window(const std::string& name, const fox::Vector2u& dimensions);
		~Window();

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
