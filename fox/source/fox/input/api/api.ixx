export module fox.input.api;
export import fox.input.code.button;
export import fox.input.code.controller;
export import fox.input.code.key;
export import fox.input.code.modifier;

import std;
import fox.input.api.glfw;

export namespace fox::input::api
{
    using handler_t = glfw::input_handler;
    auto  handler   = std::unique_ptr<api::handler_t>{};
}
