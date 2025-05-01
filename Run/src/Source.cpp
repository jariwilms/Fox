#include "stdafx.hpp"

#include "Fox/Application.hpp"

int main(int argc, char** argv)
{
    auto application = std::make_unique<fox::Application>(argc, argv);
    
    std::vector<int> a{};

    return application->run();
}
