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
    class window
    {
    public:
        using mode_e = api::window::mode_e;

        window(const std::string& title, const fox::vector2u& dimensions)
            : title_{ title }, dimensions_{ dimensions }, mode_{ mode_e::windowed }
        {
            ::glfw::initialize();

            ::glfw::window_hint(::glfw::e_hint::context_version_major, ::glfw::e_hint_value::opengl_version_major_4);
            ::glfw::window_hint(::glfw::e_hint::context_version_minor, ::glfw::e_hint_value::opengl_version_minor_6);
            ::glfw::window_hint(::glfw::e_hint::opengl_profile       , ::glfw::e_hint_value::opengl_core_profile   );
            ::glfw::window_hint(::glfw::e_hint::refresh_rate         , ::glfw::e_hint_value::dont_care             );
#ifdef FOX_DEBUG
            ::glfw::window_hint(::glfw::e_hint::opengl_debug_context , fox::true_);
#endif

            handle_ = ::glfw::create_window(title_, dimensions);
            ::glfw::make_context_current(handle_);
            ::glfw::swap_interval(fox::uint32_t{ 0u });

            ::glad::initialize();





            using namespace gfx::api;
            gl::context::init();

            input::api::handler = std::make_unique<input::api::glfw::input_handler>();

            ::glfw::set_error_callback            (         [](                         fox::int32_t error   , const fox::char_t* description)
                {
                    std::print("[GLFW_ERROR] {0}: {1}\n", error, description);
                });
            ::glfw::set_key_callback              (handle_, [](::glfw::window_t*  window, fox::int32_t   key   , fox::int32_t   scancode, fox::int32_t action, fox::int32_t modifiers) 
                { 
                    input::api::handler->glfw_input_key_callback(window, input::key{ key }, scancode, action, input::modifier{ modifiers }); 
                });
            ::glfw::set_mouse_button_callback     (handle_, [](::glfw::window_t*  window, fox::int32_t   button,                          fox::int32_t action, fox::int32_t modifiers)
                {
                    input::api::handler->glfw_input_button_callback(window, input::button{ button }, action, input::modifier{ modifiers });
                });
            ::glfw::set_cursor_position_callback  (handle_, [](::glfw::window_t*  window, fox::float64_t x     , fox::float64_t y       )
                {
                    input::api::handler->glfw_input_cursor_callback(window, x, y);
                });
            ::glfw::set_scroll_callback           (handle_, [](::glfw::window_t*  window, fox::float64_t x     , fox::float64_t y       )
                {
                    input::api::handler->glfw_input_scroll_callback(window, x, y);
                });
            ::glfw::set_frame_buffer_size_callback(handle_, [](::glfw::window_t*        , fox::int32_t   width , fox::int32_t   height  )
                {
                    gl::viewport(gl::Vector2u{ static_cast<gl::uint32_t>(width), static_cast<gl::uint32_t>(height) });
                });
        }
        ~window()
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
        void resize(const fox::vector2u& dimensions)
        {
            ::glfw::set_window_size(handle_, dimensions);
            dimensions_ = dimensions;
        }

        void        close() const
        {
            ::glfw::set_window_should_close(handle_, fox::true_);
        }
        auto should_close() const -> fox::bool_t
        {
            return ::glfw::window_should_close(handle_);
        }

        auto handle() const -> ::glfw::window_t* const
        {
            return handle_;
        }

    private:
        ::glfw::window_t* handle_  ;
        std::string     title_     ;
        fox::vector2u   dimensions_;
        mode_e          mode_      ;
    };
}
