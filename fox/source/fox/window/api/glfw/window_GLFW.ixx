module;

#include <glad/gl.h>
#include <glfw/glfw3.h>

export module fox.window.api.glfw;

import std;

import fox.core.types;
import fox.window.base;
import fox.input;
import fox.input.api.glfw;
import fox.rendering.api.opengl;
import fox.rendering.api.opengl.context;

export namespace fox::interface::api::glfw
{
	class Window
	{
	public:
		using Mode = api::Window::Mode;

        Window(const std::string& name, const fox::Vector2u& dimensions)
            : name_{ name }, dimensions_{ dimensions }, mode_{ Mode::Windowed }
        {
            if (glfwInit() != GLFW_TRUE) throw std::runtime_error{ "Failed to initialize GLFW!" };

            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4                       );
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6                       );
            glfwWindowHint(GLFW_OPENGL_PROFILE       , GLFW_OPENGL_CORE_PROFILE);
            glfwWindowHint(GLFW_REFRESH_RATE         , GLFW_DONT_CARE          );
#ifdef FOX_DEBUG
            glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT , fox::True               );
#endif





            handle_ = glfwCreateWindow(static_cast<fox::int32_t>(dimensions.x), static_cast<fox::int32_t>(dimensions.y), name_.c_str(), nullptr, nullptr);
            if (!handle_) throw std::runtime_error{ "Failed to create GLFW window!" };

            glfwMakeContextCurrent(handle_);
            glfwSwapInterval(0);

            auto version = gladLoadGL(glfwGetProcAddress);
            if (!version) throw std::runtime_error{ "Failed to initialize GLAD!" };





            using namespace gfx::api;
            gl::Context::init();

            input::api::handler = std::make_shared<input::api::glfw::InputHandler>();

            glfwSetErrorCallback          (         [](fox::int32_t error , const fox::char_t* description)
                {
                    std::print("[GLFW_ERROR] {0}: {1}\n", error, description);
                });
            glfwSetKeyCallback            (handle_, [](GLFWwindow*  window, fox::int32_t   key   , fox::int32_t   scancode, fox::int32_t action  , fox::int32_t mods  ) 
                { 
                    input::api::handler->glfw_input_key_callback(window, key, scancode, action, mods); 
                });
            glfwSetMouseButtonCallback    (handle_, [](GLFWwindow*  window, fox::int32_t   button, fox::int32_t   action  , fox::int32_t mods    )
                {
                    input::api::handler->glfw_input_button_callback(window, button, action, mods);
                });
            glfwSetCursorPosCallback      (handle_, [](GLFWwindow*  window, fox::float64_t x     , fox::float64_t y       )
                {
                    input::api::handler->glfw_input_cursor_callback(window, x, y);
                });
            glfwSetScrollCallback         (handle_, [](GLFWwindow*  window, fox::float64_t x     , fox::float64_t y       )
                {
                    input::api::handler->glfw_input_scroll_callback(window, x, y);
                });
            glfwSetFramebufferSizeCallback(handle_, [](GLFWwindow*  window, fox::int32_t   width , fox::int32_t   height  )
                {
                    gl::viewport(gl::Vector2u{ static_cast<gl::uint32_t>(width), static_cast<gl::uint32_t>(height) });
                });
        }
        ~Window()
        {
            glfwDestroyWindow(handle_);
            glfwTerminate();
        }

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
