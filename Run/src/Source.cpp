#include "stdafx.hpp"

#include "Fox/Application.hpp"
#include "Fox/Rendering/Rendering.hpp"

int main(int argc, char** argv)
{
    auto application = std::make_unique<fox::Application>(argc, argv);

    using namespace fox::gfx::api;



    return application->run();
}
