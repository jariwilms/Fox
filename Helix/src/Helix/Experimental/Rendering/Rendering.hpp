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

#include "Helix/Core/Library/Transform/Transform.hpp"
#include "Helix/Rendering/Model/Model.hpp"
#include "Helix/Rendering/Mesh/Mesh.hpp"

namespace hlx::gfx
{
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

    using Pipeline               = api::GPipeline<api::GRAPHICS_API>;
    using Shader                 = api::GShader<api::GRAPHICS_API>;
                                 
    using Texture                = api::Texture;
    using Texture1D              = api::GTexture<api::GRAPHICS_API, api::Dimensions::_1D, api::AntiAliasing::None>;
    using Texture2D              = api::GTexture<api::GRAPHICS_API, api::Dimensions::_2D, api::AntiAliasing::None>;
    using Texture2DMultisample   = api::GTexture<api::GRAPHICS_API, api::Dimensions::_2D, api::AntiAliasing::MSAA>;
    using Texture3D              = api::GTexture<api::GRAPHICS_API, api::Dimensions::_3D, api::AntiAliasing::None>;
    using Texture3DMultisample   = api::GTexture<api::GRAPHICS_API, api::Dimensions::_3D, api::AntiAliasing::MSAA>;
}
