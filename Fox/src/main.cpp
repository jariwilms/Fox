#include "stdafx.hpp"

#include "Fox/Application.hpp"
#include "Fox/Rendering/Rendering.hpp"
#include "Fox/Rendering/Create.hpp"
#include "Fox/Rendering/Renderer.hpp"
#include "Fox/Window/WindowManager.hpp"
#include "Fox/IO/IO.hpp"

#include "Fox/Rendering/RenderInfo/RenderInfo.hpp"

using namespace fox;

int main(int argc, char* argv[])
{
    const auto& application = std::make_unique<Application>(argc, argv);

    try
    {
        application->run();
    }
    catch (const std::exception& e)
    {
        std::cerr << "An error occurred: " << e.what() << std::endl;

        return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}
