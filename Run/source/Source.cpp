#include <stdafx.hpp>

#include <fox/application.hpp>
#include <fox/rendering/rendering.hpp>

int main(int argc, char** argv)
{
    auto application = std::make_unique<fox::Application>(argc, argv);

    return application->run();
}
