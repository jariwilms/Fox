export module fox.window.api.glfw;

import std;
import fox.core.types;
import fox.input.api.glfw;
import fox.input;
import fox.rendering.api.opengl.context;
import fox.rendering.api.opengl;
import fox.window.base;
import vendor.glad;
import vendor.glfw;

export namespace fox::interface::api::glfw
{
	class Window
	{
	public:
		using Mode = api::Window::Mode;

        Window(const std::string& title, const fox::Vector2u& dimensions)
            : title_{ title }, dimensions_{ dimensions }, mode_{ Mode::Windowed }
        {
            ::glfw::initialize();

            ::glfw::window_hint(::glfw::hint::context_version_major, ::glfw::hint_value::opengl_version_major_4);
            ::glfw::window_hint(::glfw::hint::context_version_minor, ::glfw::hint_value::opengl_version_minor_6);
            ::glfw::window_hint(::glfw::hint::opengl_profile       , ::glfw::hint_value::opengl_core_profile);
            ::glfw::window_hint(::glfw::hint::refresh_rate         , ::glfw::hint_value::dont_care);
#ifdef FOX_DEBUG
            ::glfw::window_hint(::glfw::hint::opengl_debug_context , fox::True);
#endif

            handle_ = ::glfw::create_window(title_, dimensions);
            ::glfw::make_context_current(handle_);
            ::glfw::swap_interval(fox::uint32_t{ 0u });

            ::glad::initialize();





            using namespace gfx::api;
            gl::Context::init();

            input::api::handler = std::make_shared<input::api::glfw::InputHandler>();

            ::glfw::set_error_callback            (         [](                         fox::int32_t error   , const fox::char_t* description)
                {
                    std::print("[GLFW_ERROR] {0}: {1}\n", error, description);
                });
            ::glfw::set_key_callback              (handle_, [](::glfw::window*  window, fox::int32_t   key   , fox::int32_t   scancode, fox::int32_t action  , fox::int32_t mods  ) 
                { 
                    input::api::handler->glfw_input_key_callback(window, key, scancode, action, mods); 
                });
            ::glfw::set_mouse_button_callback     (handle_, [](::glfw::window*  window, fox::int32_t   button, fox::int32_t   action  , fox::int32_t mods    )
                {
                    input::api::handler->glfw_input_button_callback(window, button, action, mods);
                });
            ::glfw::set_cursor_position_callback  (handle_, [](::glfw::window*  window, fox::float64_t x     , fox::float64_t y       )
                {
                    input::api::handler->glfw_input_cursor_callback(window, x, y);
                });
            ::glfw::set_scroll_callback           (handle_, [](::glfw::window*  window, fox::float64_t x     , fox::float64_t y       )
                {
                    input::api::handler->glfw_input_scroll_callback(window, x, y);
                });
            ::glfw::set_frame_buffer_size_callback(handle_, [](::glfw::window*  window, fox::int32_t   width , fox::int32_t   height  )
                {
                    gl::viewport(gl::Vector2u{ static_cast<gl::uint32_t>(width), static_cast<gl::uint32_t>(height) });
                });
        }
        ~Window()
        {
            ::glfw::destroy_window(handle_);
            ::glfw::terminate();
        }

		void poll_events ()
		{
			input::api::handler->update();
			::glfw::poll_events();
		}
		void swap_buffers()
		{
			::glfw::swap_buffers(handle_);
		}

		void rename(const std::string  & title     )
		{
			::glfw::set_window_title(handle_, title.c_str());
		}
		void resize(const fox::Vector2u& dimensions)
		{
			::glfw::set_window_size(handle_, dimensions);
			dimensions_ = dimensions;
		}

		void        close() const
		{
			glfwSetWindowShouldClose(handle_, fox::True);
		}
		auto should_close() const -> fox::bool_t
		{
			return ::glfw::window_should_close(handle_);
		}

		auto handle() const -> ::glfw::window* const
		{
			return handle_;
		}

	private:
		::glfw::window* handle_    ;
		std::string     title_     ;
		fox::Vector2u   dimensions_;
		Mode            mode_      ;
	};
}
