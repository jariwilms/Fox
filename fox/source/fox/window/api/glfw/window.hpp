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
        struct Context
        {
			std::shared_ptr<Window>                         window{};
			std::shared_ptr<input::api::glfw::InputHandler> input {};
        };

		Window(const std::string& name, const fox::Vector2u& dimensions);
		~Window();

		void poll_events ()
		{
			context_->input->update();
			glfwPollEvents();
		}
		void swap_buffers()
		{
			glfwSwapBuffers(instance_);
		}

		void rename(const std::string  & title     )
		{
			glfwSetWindowTitle(instance_, title.c_str());
		}
		void resize(const fox::Vector2u& dimensions)
		{
			glfwSetWindowSize(instance_, static_cast<fox::int32_t>(dimensions.x), static_cast<fox::int32_t>(dimensions.y));

			dimensions_ = dimensions;
		}

		void        close() const
		{
			glfwSetWindowShouldClose(instance_, fox::True);
		}
		auto should_close() const -> fox::bool_t
		{
			return glfwWindowShouldClose(instance_);
		}

		auto handle() const -> GLFWwindow* const
		{
			return instance_;
		}

	private:
        void glfw_error_callback(fox::int32_t error, const fox::char_t* description);

		std::string              name_      ;
		fox::Vector2u            dimensions_;
		Mode                     mode_      ;
		GLFWwindow*              instance_  ;
		std::shared_ptr<Context> context_   ;
	};
}
