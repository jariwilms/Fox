export module vendor.glfw.window;

import std;
import fox.config;
import fox.core.types;
import fox.rendering.api.opengl;
import fox.rendering.api.opengl.context;
import vendor.glad;
import vendor.glfw.functions;
import vendor.glfw.input;
import vendor.glfw.types;

export namespace vendor::glfw
{
    class window
    {
    public:
        enum class mode_e
        {
            windowed,
            borderless,
            fullscreen,
        };
        struct user_data
        {
            std::shared_ptr<glfw::input_handler> input;
        };

         window(const std::string& title, const fox::vector2u& dimensions)
            : title_{ title }, dimensions_{ dimensions }, mode_{ mode_e::windowed }, user_data_{ input_ }
        {
            glfw::initialize();
            glfw::window_hint(glfw::hint_e::context_version_major, glfw::hint_value_e::opengl_version_major_4);
            glfw::window_hint(glfw::hint_e::context_version_minor, glfw::hint_value_e::opengl_version_minor_6);
            glfw::window_hint(glfw::hint_e::opengl_profile       , glfw::hint_value_e::opengl_core_profile   );
            glfw::window_hint(glfw::hint_e::refresh_rate         , glfw::hint_value_e::dont_care             );

            if constexpr (fox::cfg::build_configuration == fox::cfg::build_configuration_e::debug)
                glfw::window_hint(glfw::hint_e::opengl_debug_context , fox::true_);

            window_ = glfw::create_window(title_, dimensions_);
            //TODO: window mode

            glfw::make_context_current(window_);
            glfw::swap_interval(fox::uint32_t{ 0u });

            vendor::glad::initialize();
            
            fox::gfx::api::gl::context::init();




            input_ = std::make_shared<glfw::input_handler>();
            user_data_ = user_data{ input_ };

            glfwSetWindowUserPointer(window_, &user_data_);

            glfw::set_error_callback            (         [](                         fox::int32_t   error , const fox::char_t* description)
                {
                    std::print("[GLFW_ERROR] {0}: {1}\n", error, description);
                });
            glfw::set_key_callback              (window_, [](glfw::window_t*  window, fox::int32_t   key   , fox::int32_t   scancode, fox::int32_t action, fox::int32_t modifiers) 
                { 
                    const auto* userData = static_cast<user_data*>(::glfwGetWindowUserPointer(window));
                    userData->input->glfw_input_key_callback(window, fox::input::key_e{ key }, scancode, action, fox::input::modifier_e{ modifiers });
                });
            glfw::set_mouse_button_callback     (window_, [](glfw::window_t*  window, fox::int32_t   button,                          fox::int32_t action, fox::int32_t modifiers)
                {
                    const auto* userData = static_cast<user_data*>(::glfwGetWindowUserPointer(window));
                    userData->input->glfw_input_button_callback(window, fox::input::button_e{ button }, action, fox::input::modifier_e{ modifiers });
                });
            glfw::set_cursor_position_callback  (window_, [](glfw::window_t*  window, fox::float64_t x     , fox::float64_t y       )
                {
                    const auto* userData = static_cast<user_data*>(::glfwGetWindowUserPointer(window));
                    userData->input->glfw_input_cursor_callback(window, x, y);
                });
            glfw::set_scroll_callback           (window_, [](glfw::window_t*  window, fox::float64_t x     , fox::float64_t y       )
                {
                    const auto* userData = static_cast<user_data*>(::glfwGetWindowUserPointer(window));
                    userData->input->glfw_input_scroll_callback(window, x, y);
                });
            glfw::set_frame_buffer_size_callback(window_, [](glfw::window_t*        , fox::int32_t   width , fox::int32_t   height  )
                {
                    using namespace fox::gfx::api;
                    gl::viewport(gl::vector2u{ static_cast<gl::uint32_t>(width), static_cast<gl::uint32_t>(height) });
                });
        }
        ~window()
        {
            glfw::destroy_window(window_);
            glfw::terminate();
        }

        void poll_events ()
        {
            input_->update();
            glfw::poll_events();
        }
        void swap_buffers()
        {
            glfw::swap_buffers(window_);
        }

        void rename(const std::string  & title     )
        {
            glfw::set_window_title(window_, title.c_str());
        }
        void resize(const fox::vector2u& dimensions)
        {
            glfw::set_window_size(window_, dimensions);
            dimensions_ = dimensions;
        }

        void        close() const
        {
            glfw::set_window_should_close(window_, fox::true_);
        }
        auto should_close() const -> fox::bool_t
        {
            return glfw::window_should_close(window_);
        }

        auto handle       () const -> glfw::window_t* const
        {
            return window_;
        }
        auto input_handler() const -> std::shared_ptr<const glfw::input_handler>
        {
            return input_;
        }
        auto input_handler() -> std::shared_ptr<glfw::input_handler>
        {
            return input_;
        }

    private:
        glfw::window_t*                      window_; //make unique_ptr
        std::shared_ptr<glfw::input_handler> input_;
        std::string                          title_;
        fox::vector2u                        dimensions_;
        mode_e                               mode_;
        user_data                            user_data_;
    };
}
