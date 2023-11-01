#pragma once

#include "stdafx.hpp"

#include "Helix/Rendering/API/GraphicsAPI.hpp"

#include "Helix/Rendering/Buffer/Buffer.hpp"
#include "Helix/Rendering/Buffer/VertexArray.hpp"
#include "Helix/Rendering/Buffer/FrameBuffer.hpp"
#include "Helix/Rendering/Layout/Layout.hpp"
#include "Helix/Rendering/Shader/Pipeline.hpp"
#include "Helix/Rendering/Shader/Shader.hpp"
#include "Helix/Rendering/Texture/Texture.hpp"
#include "Helix/Rendering/Uniform/Uniform.hpp"

namespace hlx::gfx
{
    using Buffer                 = api::Buffer;

    template<Buffer::Access ACCESS, typename T>
    using VertexBuffer           = api::GBuffer<api::GRAPHICS_API, Buffer::Type::Vertex, ACCESS, T>;
    template<Buffer::Access ACCESS>
    using IndexBuffer            = api::GBuffer<api::GRAPHICS_API, Buffer::Type::Index, ACCESS, u32>;
    template<typename T>
    using UniformBuffer          = api::GBuffer<api::GRAPHICS_API, Buffer::Type::Uniform, Buffer::Access::Static, T>;
    template<Buffer::Access ACCESS, typename T>
    using UniformArrayBuffer     = api::GBuffer<api::GRAPHICS_API, Buffer::Type::UniformArray, ACCESS, T>;
    using VertexArray            = api::GVertexArray<api::GRAPHICS_API>;

    template<typename... T>
    using VertexLayout           = api::GVertexLayout<api::GRAPHICS_API, T...>;

    using FrameBuffer            = api::GFrameBuffer<api::GRAPHICS_API, api::AntiAliasing::None>;
    using FrameBufferMultisample = api::GFrameBuffer<api::GRAPHICS_API, api::AntiAliasing::MSAA>;

    using Pipeline               = api::GPipeline<api::GRAPHICS_API>;
    using Shader                 = api::GShader<api::GRAPHICS_API>;

    using Texture                = api::Texture;
    using Texture1D              = api::GTexture<api::GRAPHICS_API, api::Dimensions::_1D, api::AntiAliasing::None>;
    using Texture2D              = api::GTexture<api::GRAPHICS_API, api::Dimensions::_2D, api::AntiAliasing::None>;
    using Texture2DMultisample   = api::GTexture<api::GRAPHICS_API, api::Dimensions::_2D, api::AntiAliasing::MSAA>;
    using Texture3D              = api::GTexture<api::GRAPHICS_API, api::Dimensions::_3D, api::AntiAliasing::None>;
    using Texture3DMultisample   = api::GTexture<api::GRAPHICS_API, api::Dimensions::_3D, api::AntiAliasing::MSAA>;
}
