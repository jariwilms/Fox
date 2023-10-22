#pragma once

#include "stdafx.hpp"

#include "Helix/Experimental/Rendering/Base.hpp"
#include "Helix/Experimental/Rendering/Texture/Texture.hpp"

namespace hlx::gfx::api
{
    template<AntiAliasing A>
    class FrameBuffer
    {
    public:
        enum class Target
        {
            Read, 
            Write, 
        };
        enum class Attachment
        {
            Color, 
            Depth, 
            Stencil, 
            DepthStencil, 
        };
        struct Manifest
        {
            FrameBuffer::Attachment attachment;
            const GTexture<GraphicsAPI::OpenGL, Dimensions::_2D, A>& texture;
        };
    };

    template<GraphicsAPI, AntiAliasing>
    class GFrameBuffer;
};
