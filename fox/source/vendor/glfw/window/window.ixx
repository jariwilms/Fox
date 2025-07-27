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
        enum class display_mode_e
        {
            windowed,
            borderless,
            fullscreen,
        };
        struct user_data
        {
            std::shared_ptr<glfw::input> input;
            fox::vector2u* dimensions;
        };

         window(const std::string& title, const fox::vector2u& dimensions)
            : title_{ title }, dimensions_{ dimensions }, displayMode_{ display_mode_e::windowed }
        {
            glfw::initialize();
            glfw::window_hint(glfw::hint_e::context_version_major, glfw::hint_value_e::opengl_version_major_4);
            glfw::window_hint(glfw::hint_e::context_version_minor, glfw::hint_value_e::opengl_version_minor_6);
            glfw::window_hint(glfw::hint_e::opengl_profile       , glfw::hint_value_e::opengl_core_profile   );
            glfw::window_hint(glfw::hint_e::refresh_rate         , glfw::hint_value_e::dont_care             );
            glfw::window_hint(glfw::hint_e::visible              , glfw::hint_value_e::false_);

            if constexpr (fox::cfg::build_configuration == fox::cfg::build_configuration_e::debug)
                glfw::window_hint(glfw::hint_e::opengl_debug_context , glfw::hint_value_e::true_);

            window_ = std::unique_ptr<glfw::window_t, decltype([](auto* window)
                {
                    vendor::glfw::destroy_window(window);
                    vendor::glfw::terminate();
                })>{ glfw::create_window(title_, dimensions_) };

            glfw::make_context_current(window_.get());
            glfw::swap_interval(fox::uint32_t{ 0u });
            glfw::set_window_monitor(window_.get(), nullptr, dimensions_);
            glfw::show_window(window_.get());
            
            vendor::glad::initialize();
            fox::gfx::api::gl::context::initialize();



            input_ = std::make_shared<glfw::input>();
            user_data_ = user_data{ input_, &dimensions_ };
            glfwSetWindowUserPointer(window_.get(), &user_data_);



            glfw::set_error_callback            (         [](                         fox::int32_t   error , const fox::char_t* description)
                {
                    std::print("[GLFW_ERROR] {}: {}\n", error, description);
                });
            glfw::set_key_callback              (window_.get(), [](glfw::window_t*  window, fox::int32_t   key   , fox::int32_t   scancode, fox::int32_t action, fox::int32_t modifiers) 
                { 
                    const auto* userData = static_cast<user_data*>(::glfwGetWindowUserPointer(window));
                    userData->input->input_key_callback(window, fox::input::key_e{ key }, scancode, action, fox::input::modifier_e{ modifiers });
                });
            glfw::set_mouse_button_callback     (window_.get(), [](glfw::window_t*  window, fox::int32_t   button,                          fox::int32_t action, fox::int32_t modifiers)
                {
                    const auto* userData = static_cast<user_data*>(::glfwGetWindowUserPointer(window));
                    userData->input->input_button_callback(window, fox::input::button_e{ button }, action, fox::input::modifier_e{ modifiers });
                });
            glfw::set_cursor_position_callback  (window_.get(), [](glfw::window_t*  window, fox::float64_t x     , fox::float64_t y       )
                {
                    const auto* userData = static_cast<user_data*>(::glfwGetWindowUserPointer(window));
                    userData->input->input_cursor_callback(window, x, y);
                });
            glfw::set_scroll_callback           (window_.get(), [](glfw::window_t*  window, fox::float64_t x     , fox::float64_t y       )
                {
                    const auto* userData = static_cast<user_data*>(::glfwGetWindowUserPointer(window));
                    userData->input->input_scroll_callback(window, x, y);
                });
            glfw::set_frame_buffer_size_callback(window_.get(), [](glfw::window_t*  window, fox::int32_t   width , fox::int32_t   height  )
                {
                    auto* userData = static_cast<user_data*>(::glfwGetWindowUserPointer(window));
                    *userData->dimensions = fox::vector2u{ width, height };
                });
        }

        void poll_events  ()
        {
            input_->capture();
            glfw::poll_events();
        }
        void swap_buffers ()
        {
            glfw::swap_buffers(window_.get());
        }

        void rename       (const std::string  & title     )
        {
            glfw::set_window_title(window_.get(), title.c_str());
        }
        void resize       (const fox::vector2u& dimensions)
        {
            glfw::set_window_size(window_.get(), dimensions);
            dimensions_ = dimensions;
        }

        void change_display_mode(display_mode_e display_mode)
        {
            auto monitor = static_cast<glfw::monitor_t*>(nullptr);
            if (display_mode == display_mode_e::fullscreen) monitor = glfw::get_primary_monitor();

            glfw::set_window_monitor(window_.get(), monitor, fox::vector2u{ 1280, 720 });
        }

        void        close () const
        {
            glfw::set_window_should_close(window_.get(), fox::true_);
        }
        auto should_close () const -> fox::bool_t
        {
            return glfw::window_should_close(window_.get());
        }

        auto title        () const -> const std::string&
        {
            return title_;
        }
        auto dimensions   () const -> const fox::vector2u&
        {
            return dimensions_;
        }
        auto display_mode () const -> display_mode_e
        {
            return displayMode_;
        }

        auto input_handler() const -> std::shared_ptr<const glfw::input>
        {
            return input_;
        }
        auto input_handler() -> std::shared_ptr<glfw::input>
        {
            return input_;
        }

    private:
        using window_ptr = std::unique_ptr<glfw::window_t, std::function<void(glfw::window_t*)>>;
        using input_ptr  = std::shared_ptr<glfw::input>;
        
        window_ptr     window_;
        input_ptr      input_;
        std::string    title_;
        fox::vector2u  dimensions_;
        display_mode_e displayMode_;
        user_data      user_data_;
    };
}
