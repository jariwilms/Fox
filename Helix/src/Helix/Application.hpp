#pragma once

#include "Helix/Window/Window.hpp"

namespace hlx
{
    class Application
    {
    public:
        Application(int argc, char* argv[]);
        virtual ~Application();

        int run();

    private:
        std::shared_ptr<Window> m_window{};
    };
}
