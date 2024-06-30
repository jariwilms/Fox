#pragma once

#include "Fox/Window/Window.hpp"

namespace fox
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
