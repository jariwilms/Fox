#include "stdafx.hpp"

#include "Fox/Application.hpp"

int main(int argc, char** argv)
{
    auto application = std::make_unique<fox::Application>(argc, argv);
    
    return application->run();
}
