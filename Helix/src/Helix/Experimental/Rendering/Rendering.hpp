#pragma once

#include "stdafx.hpp"

#include "Helix/Experimental/Rendering/Base.hpp"

//#include "Helix/Experimental/Rendering/Buffer/Buffer.hpp"
//#include "Helix/Experimental/Rendering/Buffer/VertexArray.hpp"
//#include "Helix/Experimental/Rendering/Buffer/FrameBuffer.hpp"
//#include "Helix/Experimental/Rendering/Texture/Texture.hpp"

#include "Helix/Experimental/Rendering/API/OpenGL/Buffer/OpenGLBuffer.hpp"
#include "Helix/Experimental/Rendering/API/OpenGL/Buffer/OpenGLVertexArray.hpp"
#include "Helix/Experimental/Rendering/API/OpenGL/Texture/OpenGLTexture.hpp"
#include "Helix/Experimental/Rendering/API/OpenGL/Layout/OpenGLVertexLayout.hpp"
#include "Helix/Experimental/Rendering/API/OpenGL/Buffer/OpenGLFrameBuffer.hpp"

namespace hlx::gfx
{
    //Buffer
    using VertexArray            = api::GVertexArray<api::GRAPHICS_API>;
    template<typename T>         
    using VertexBuffer           = api::GBuffer<api::GRAPHICS_API, api::Buffer::Type::Vertex, T>;
    using IndexBuffer            = api::GBuffer<api::GRAPHICS_API, api::Buffer::Type::Index, u32>;
    template<typename T>         
    using UniformBuffer          = api::GBuffer<api::GRAPHICS_API, api::Buffer::Type::Uniform, T>;

    using FrameBuffer            = api::GFrameBuffer<api::GRAPHICS_API, api::AntiAliasing::None>;
    using FrameBufferMultisample = api::GFrameBuffer<api::GRAPHICS_API, api::AntiAliasing::MSAA>;

    template<typename T, u32 C>
    using Layout                 = api::Layout<T, C>;
    template<typename... T>
    using VertexLayout           = api::VertexLayout<api::GRAPHICS_API, T...>;

    ////Texture
    //using Texture              = api::Texture;
    //using Texture1D            = api::GTexture<api::GRAPHICS_API, api::Dimensions::_1D, api::AntiAliasing::None>;
    //using Texture2D            = api::GTexture<api::GRAPHICS_API, api::Dimensions::_2D, api::AntiAliasing::None>;
    //using Texture2DMultisample = api::GTexture<api::GRAPHICS_API, api::Dimensions::_2D, api::AntiAliasing::MSAA>;
    //using Texture3D            = api::GTexture<api::GRAPHICS_API, api::Dimensions::_3D, api::AntiAliasing::None>;
}
