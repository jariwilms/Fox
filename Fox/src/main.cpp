#include "stdafx.hpp"

#include "Fox/Application.hpp"
#include "Fox/Rendering/Rendering.hpp"
#include "Fox/Rendering/Create.hpp"
#include "Fox/Rendering/Renderer.hpp"

#include "Fox/Rendering/RenderInfo/RenderInfo.hpp"

using namespace fox;

int main(int argc, char* argv[])
{
    Camera camera;
    Transform t{};
    std::array<std::tuple<Light, Vector3f>, 32> lights{};



    Application application{ argc, argv };



    gfx::RenderInfo ri{ std::make_tuple(camera, t), lights };

    gfx::Renderer::init();
    gfx::Renderer::start(ri);
    gfx::Renderer::finish();



    application.run();



    return EXIT_SUCCESS;
}
