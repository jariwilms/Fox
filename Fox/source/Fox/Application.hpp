#pragma once

#include <fox/window/window.hpp>

namespace fox
{
    class Application
    {
    public:
        Application(fox::int32_t argc, fox::char_t* argv[]);

        auto run() -> fox::int32_t;

    private:
        std::shared_ptr<interface::Window> window_{};
    };
}
