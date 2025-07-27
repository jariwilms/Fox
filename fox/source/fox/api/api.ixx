export module fox.api;

import std;
import fox.core.types;
import vendor.glfw;

       namespace fox::api
{
    using window_t = vendor::glfw::window;
    using input_t  = vendor::glfw::input;

    auto window_   = std::shared_ptr<api::window_t>{};
    auto input_    = std::shared_ptr<api::input_t >{};
}
export namespace fox::api
{
    void initialize()
    {
        api::window_ = std::make_shared<api::window_t>("Fox", fox::vector2u{ 1280u, 720u });
        api::input_  = window_->input_handler();
    }

    const auto& window = api::window_;
    const auto& input  = api::input_;
}
