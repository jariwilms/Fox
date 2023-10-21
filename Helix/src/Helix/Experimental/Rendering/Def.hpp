#pragma once

#include "stdafx.hpp"

#include "Helix/Experimental/Rendering/Base.hpp"

#include "Helix/Experimental/Rendering/API/OpenGL/Buffer/OpenGLBuffer.hpp"
#include "Helix/Experimental/Rendering/API/OpenGL/Buffer/OpenGLVertexArray.hpp"
#include "Helix/Experimental/Rendering/API/OpenGL/Texture/OpenGLTexture.hpp"

namespace hlx::gfx
{
    using namespace imp;

    //Buffer
    using VertexArray  = GVertexArray<GRAPHICS_API>;
    template<typename T>
    using VertexBuffer = GBuffer<GRAPHICS_API, Buffer::Type::Vertex, T>;
    using IndexBuffer  = GBuffer<GRAPHICS_API, Buffer::Type::Index, unsigned int>;

    //Texture
    using Texture      = Texture;
    using Texture1D    = GTexture<GRAPHICS_API, Dimensions::_1D, AntiAliasing::None>;
    using Texture2D    = GTexture<GRAPHICS_API, Dimensions::_2D, AntiAliasing::None>;
    using Texture2D_AA = GTexture<GRAPHICS_API, Dimensions::_2D, AntiAliasing::MSAA>;
    using Texture3D    = GTexture<GRAPHICS_API, Dimensions::_3D, AntiAliasing::None>;
}
