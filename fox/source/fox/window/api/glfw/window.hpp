#pragma once

#include <stdafx.hpp>

#include <glfw/glfw3.h>

#include <fox/core/types/math/linear_algebra/vector.hpp>
#include <fox/input/api/glfw/input_handler.hpp>
#include <fox/input/input.hpp>
#include <fox/window/base/window.hpp>

namespace fox::interface::api::glfw
{
	class Window
	{
	public:
		using Mode = api::Window::Mode;

		Window(const std::string& name, const fox::Vector2u& dimensions);
		~Window();

		void poll_events ()
		{
			input::api::handler->update();
			glfwPollEvents();
		}
		void swap_buffers()
		{
			glfwSwapBuffers(handle_);
		}

		void rename(const std::string  & title     )
		{
			glfwSetWindowTitle(handle_, title.c_str());
		}
		void resize(const fox::Vector2u& dimensions)
		{
			glfwSetWindowSize(handle_, static_cast<fox::int32_t>(dimensions.x), static_cast<fox::int32_t>(dimensions.y));

			dimensions_ = dimensions;
		}

		void        close() const
		{
			glfwSetWindowShouldClose(handle_, fox::True);
		}
		auto should_close() const -> fox::bool_t
		{
			return glfwWindowShouldClose(handle_);
		}

		auto handle() const -> GLFWwindow* const
		{
			return handle_;
		}

	private:
		std::string   name_      ;
		fox::Vector2u dimensions_;
		Mode          mode_      ;
		GLFWwindow*   handle_    ;
	};
}
