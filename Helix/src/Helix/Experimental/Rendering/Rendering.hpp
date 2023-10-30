#pragma once

#include "stdafx.hpp"

#define HLX_GRAPHICS_API OpenGL
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
    using Buffer                 = api::Buffer;

    using VertexArray            = api::GVertexArray<api::GRAPHICS_API>;
    template<Buffer::Access ACCESS, typename T>         
    using VertexBuffer           = api::GBuffer<api::GRAPHICS_API, api::Buffer::Type::Vertex, ACCESS, T>;
    template<Buffer::Access ACCESS>
    using IndexBuffer            = api::GBuffer<api::GRAPHICS_API, api::Buffer::Type::Index, ACCESS, u32>;
    template<typename T>         
    using UniformBuffer          = api::GBuffer<api::GRAPHICS_API, api::Buffer::Type::Uniform, api::Buffer::Access::Static, T>;
    template<Buffer::Access ACCESS, typename T>
    using UniformArrayBuffer     = api::GBuffer<api::GRAPHICS_API, api::Buffer::Type::UniformArray, ACCESS, T>;

    using FrameBuffer            = api::GFrameBuffer<api::GRAPHICS_API, api::AntiAliasing::None>;
    using FrameBufferMultisample = api::GFrameBuffer<api::GRAPHICS_API, api::AntiAliasing::MSAA>;

    template<typename T, u32 COUNT>
    using Layout                 = api::Layout<T, COUNT>;
    template<typename... T>
    using VertexLayout           = api::VertexLayout<api::GRAPHICS_API, T...>;


    //template<>
    //class api::GShader<api::GraphicsAPI::OpenGL>;

    using Pipeline               = api::GPipeline<api::GRAPHICS_API>;
    using Shader                 = api::GShader<api::GRAPHICS_API>;
                                 








    using Texture                = api::Texture;
    using Texture1D              = api::GTexture<api::GRAPHICS_API, api::Dimensions::_1D, api::AntiAliasing::None>;
    using Texture2D              = api::GTexture<api::GRAPHICS_API, api::Dimensions::_2D, api::AntiAliasing::None>;
    using Texture2DMultisample   = api::GTexture<api::GRAPHICS_API, api::Dimensions::_2D, api::AntiAliasing::MSAA>;
    using Texture3D              = api::GTexture<api::GRAPHICS_API, api::Dimensions::_3D, api::AntiAliasing::None>;
    using Texture3DMultisample   = api::GTexture<api::GRAPHICS_API, api::Dimensions::_3D, api::AntiAliasing::MSAA>;
}
