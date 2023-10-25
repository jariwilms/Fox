#pragma once

#include "Helix/Experimental/Rendering/API/OpenGL/OpenGL.hpp"
#include "Helix/Experimental/Rendering/API/OpenGL/Texture/OpenGLTexture.hpp"

namespace hlx::gfx::api
{
    template<AntiAliasing A>
    using GRenderBuffer = const GTexture<GraphicsAPI::OpenGL, Dimensions::_2D, A>;
}
