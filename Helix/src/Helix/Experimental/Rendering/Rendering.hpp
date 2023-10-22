#pragma once

#include "stdafx.hpp"

#include "Helix/Experimental/Rendering/Base.hpp"

#include "Helix/Experimental/Rendering/API/OpenGL/Buffer/OpenGLBuffer.hpp"
#include "Helix/Experimental/Rendering/API/OpenGL/Buffer/OpenGLVertexArray.hpp"
#include "Helix/Experimental/Rendering/API/OpenGL/Texture/OpenGLTexture.hpp"

namespace hlx::gfx
{
    //Buffer
    using VertexArray   = api::GVertexArray<api::GRAPHICS_API>;
    template<typename T>
    using VertexBuffer  = api::GBuffer<api::GRAPHICS_API, api::Buffer::Type::Vertex, T>;
    using IndexBuffer   = api::GBuffer<api::GRAPHICS_API, api::Buffer::Type::Index, unsigned int>;
    template<typename T>
    using UniformBuffer = api::GBuffer<api::GRAPHICS_API, api::Buffer::Type::Uniform, T>;

    //Texture
    using Texture       = api::Texture;
    using Texture1D     = api::GTexture<api::GRAPHICS_API, api::Dimensions::_1D, api::AntiAliasing::None>;
    using Texture2D     = api::GTexture<api::GRAPHICS_API, api::Dimensions::_2D, api::AntiAliasing::None>;
    using Texture2D_AA  = api::GTexture<api::GRAPHICS_API, api::Dimensions::_2D, api::AntiAliasing::MSAA>;
    using Texture3D     = api::GTexture<api::GRAPHICS_API, api::Dimensions::_3D, api::AntiAliasing::None>;

    void a()
    {
        UniformBuffer<float> ub{ 2.0f };
    }
}
