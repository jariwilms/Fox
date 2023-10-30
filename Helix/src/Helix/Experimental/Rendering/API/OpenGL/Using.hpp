#pragma once

#include "stdafx.hpp"

#include "Helix/Experimental/Rendering/API/API.hpp"

#include "Helix/Experimental/Rendering/API/OpenGL/Buffer/OpenGLBuffer.hpp"
#include "Helix/Experimental/Rendering/API/OpenGL/Buffer/OpenGLFrameBuffer.hpp"
#include "Helix/Experimental/Rendering/API/OpenGL/Buffer/OpenGLVertexArray.hpp"
#include "Helix/Experimental/Rendering/API/OpenGL/Layout/OpenGLVertexLayout.hpp"
#include "Helix/Experimental/Rendering/API/OpenGL/Shader/OpenGLPipeline.hpp"
#include "Helix/Experimental/Rendering/API/OpenGL/Shader/OpenGLShader.hpp"
#include "Helix/Experimental/Rendering/API/OpenGL/Texture/OpenGLTexture.hpp"

namespace hlx::gfx::api::gl
{
    using Buffer                 = api::Buffer;

    using VertexArray            = api::GVertexArray<GraphicsAPI::OpenGL>;
    template<Buffer::Access ACCESS, typename T>         
    using VertexBuffer           = api::GBuffer<GraphicsAPI::OpenGL, api::Buffer::Type::Vertex, ACCESS, T>;
    template<Buffer::Access ACCESS>
    using IndexBuffer            = api::GBuffer<GraphicsAPI::OpenGL, api::Buffer::Type::Index, ACCESS, u32>;
    template<typename T>         
    using UniformBuffer          = api::GBuffer<GraphicsAPI::OpenGL, api::Buffer::Type::Uniform, api::Buffer::Access::Static, T>;
    template<Buffer::Access ACCESS, typename T>
    using UniformArrayBuffer     = api::GBuffer<GraphicsAPI::OpenGL, api::Buffer::Type::UniformArray, ACCESS, T>;

    using FrameBuffer            = api::GFrameBuffer<GraphicsAPI::OpenGL, api::AntiAliasing::None>;
    using FrameBufferMultisample = api::GFrameBuffer<GraphicsAPI::OpenGL, api::AntiAliasing::MSAA>;

    template<typename T, u32 C>
    using Layout                 = api::Layout<T, C>;
    template<typename... T>
    using VertexLayout           = api::VertexLayout<GraphicsAPI::OpenGL, T...>;

    using Pipeline               = api::GPipeline<GraphicsAPI::OpenGL>;
    using Shader                 = api::GShader<GraphicsAPI::OpenGL>;

    using Texture                = api::Texture;
    using Texture1D              = api::GTexture<GraphicsAPI::OpenGL, api::Dimensions::_1D, api::AntiAliasing::None>;
    using Texture2D              = api::GTexture<GraphicsAPI::OpenGL, api::Dimensions::_2D, api::AntiAliasing::None>;
    using Texture2DMultisample   = api::GTexture<GraphicsAPI::OpenGL, api::Dimensions::_2D, api::AntiAliasing::MSAA>;
    using Texture3D              = api::GTexture<GraphicsAPI::OpenGL, api::Dimensions::_3D, api::AntiAliasing::None>;
    using Texture3DMultisample   = api::GTexture<GraphicsAPI::OpenGL, api::Dimensions::_3D, api::AntiAliasing::MSAA>;
}
