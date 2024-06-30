#include "stdafx.hpp"

#include "Helix/Application.hpp"
#include "Helix/Rendering/Rendering.hpp"
#include "Helix/Rendering/Create.hpp"
#include "Helix/Rendering/Renderer.hpp"

#include "Helix/Rendering/RenderInfo/RenderInfo.hpp"

using namespace hlx;

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
