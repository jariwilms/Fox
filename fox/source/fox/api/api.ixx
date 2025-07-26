export module fox.api;

import std;
import fox.core.types;
import fox.input.api;
import fox.window.api;

       namespace fox::api
{
    auto window_ = std::shared_ptr<window::api::window_t >{};
    auto input_  = std::shared_ptr<input ::api::handler_t>{};
}
export namespace fox::api
{
    void initialize()
    {
        api::window_ = std::make_shared<window::api::window_t>("Fox", fox::vector2u{ 1280u, 720u });
        api::input_  = window_->input_handler();
    }

    const auto& window = api::window_;
    const auto& input  = api::input_;
}
