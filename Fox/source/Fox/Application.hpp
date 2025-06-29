#pragma once

#include <fox/window/using.hpp>

namespace fox
{
    class Application
    {
    public:
        Application(int argc, char** argv);
        virtual ~Application();

        int run();

    private:
        std::shared_ptr<wnd::Window> m_window{};
    };
}
