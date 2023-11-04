#pragma once

#include "stdafx.hpp"

#include "Helix/Rendering/Internal/InternalView.hpp"
#include "Helix/Rendering/API/OpenGL/OpenGL.hpp"
#include "Helix/Rendering/API/Implementation/GBuffer.hpp"
#include "Helix/Rendering/API/Implementation/GShader.hpp"
#include "Helix/Rendering/API/Implementation/GTexture.hpp"
#include "Helix/Rendering/API/Implementation/GRenderBuffer.hpp"

namespace hlx::gfx::imp::api
{
    template<Buffer::Type TYPE, Buffer::Access ACCESS, typename T>
    struct InternalView<imp::GBuffer<gfx::api::GraphicsAPI::OpenGL, TYPE, ACCESS, T>>
    {
        const GLuint& glId;
    };

    template<>
    struct InternalView<imp::GShader<gfx::api::GraphicsAPI::OpenGL>>
    {
        const GLuint& glId;
    };

    template<Dimensions DIMS, AntiAliasing AA>
    struct InternalView<imp::GTexture<gfx::api::GraphicsAPI::OpenGL, DIMS, AA>>
    {
        const GLuint& glId;
        const GLuint& glFormat;
        const GLuint& glMinFilter;
        const GLuint& glMagFilter;
        const GLuint& glWrapping;
    };

    template<AntiAliasing AA>
    struct InternalView<imp::GRenderBuffer<gfx::api::GraphicsAPI::OpenGL, AA>>
    {
        const GLuint& glId;
    };
}
