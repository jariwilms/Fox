#include "Helix/Core/Using.hpp"
#include "Helix/Rendering/Rendering.hpp"
#include "Helix/Rendering/Renderer.hpp"

static int test()
{
    using namespace hlx::gfx;

    RenderInfo* ri;

    Renderer::init();
    Renderer::start(*ri);
    Renderer::finish();





    return 0;
}
