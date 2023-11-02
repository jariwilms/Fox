#pragma once

#include "stdafx.hpp"

#include "Helix/Rendering/Internal/InternalView.hpp"
#include "Helix/Rendering/API/OpenGL/OpenGL.hpp"
#include "Helix/Rendering/Texture/Texture.hpp"
#include "Helix/Rendering/Buffer/Buffer.hpp"

namespace hlx::gfx::api
{
    template<Buffer::Type TYPE, Buffer::Access ACCESS, typename T>
    struct InternalView<GBuffer<GraphicsAPI::OpenGL, TYPE, ACCESS, T>>
    {
        const GLuint& glId;
    };

    template<Dimensions DIMS, AntiAliasing AA>
    struct InternalView<GTexture<GraphicsAPI::OpenGL, DIMS, AA>>
    {
        const GLuint& glId;
        const GLuint& glFormat;
        const GLuint& glMinFilter;
        const GLuint& glMagFilter;
        const GLuint& glWrapping;
    };
}
