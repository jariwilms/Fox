#pragma once

#include "stdafx.hpp"

#include "Helix/Rendering/API/GraphicsAPI.hpp"

#include "Helix/Rendering/Buffer/Buffer.hpp"
#include "Helix/Rendering/Buffer/FrameBuffer.hpp"
#include "Helix/Rendering/Buffer/VertexArray.hpp"
#include "Helix/Rendering/Layout/Layout.hpp"
#include "Helix/Rendering/Shader/Pipeline.hpp"
#include "Helix/Rendering/Shader/Shader.hpp"
#include "Helix/Rendering/Texture/Texture.hpp"
#include "Helix/Rendering/Uniform/Uniform.hpp"

#include "Helix/Rendering/API/Implementation/GBuffer.hpp"
#include "Helix/Rendering/API/Implementation/GFrameBuffer.hpp"
#include "Helix/Rendering/API/Implementation/GPipeline.hpp"
#include "Helix/Rendering/API/Implementation/GRenderState.hpp"
#include "Helix/Rendering/API/Implementation/GShader.hpp"
#include "Helix/Rendering/API/Implementation/GTexture.hpp"
#include "Helix/Rendering/API/Implementation/GVertexArray.hpp"
#include "Helix/Rendering/API/Implementation/GVertexLayout.hpp"

namespace hlx::gfx
{
    using Buffer                 = api::Buffer;

    template<Buffer::Access ACCESS, typename T>
    using VertexBuffer           = imp::GBuffer<api::GRAPHICS_API, Buffer::Type::Vertex, ACCESS, T>;
    template<Buffer::Access ACCESS>
    using IndexBuffer            = imp::GBuffer<api::GRAPHICS_API, Buffer::Type::Index, ACCESS, std::uint32_t>;
    template<typename T>
    using UniformBuffer          = imp::GBuffer<api::GRAPHICS_API, Buffer::Type::Uniform, Buffer::Access::Dynamic, T>;
    template<Buffer::Access ACCESS, typename T>
    using UniformArrayBuffer     = imp::GBuffer<api::GRAPHICS_API, Buffer::Type::UniformArray, ACCESS, T>;
    using VertexArray            = imp::GVertexArray<api::GRAPHICS_API>;

    template<typename... T>
    using VertexLayout           = imp::GVertexLayout<api::GRAPHICS_API, T...>;

    using FrameBuffer            = imp::GFrameBuffer<api::GRAPHICS_API, api::AntiAliasing::None>;
    using FrameBufferMultisample = imp::GFrameBuffer<api::GRAPHICS_API, api::AntiAliasing::MSAA>;

    using Pipeline               = imp::GPipeline<api::GRAPHICS_API>;
    using Shader                 = imp::GShader<api::GRAPHICS_API>;

    using Texture                = api::Texture;
    using Texture1D              = imp::GTexture<api::GRAPHICS_API, api::Dimensions::_1D, api::AntiAliasing::None>;
    using Texture2D              = imp::GTexture<api::GRAPHICS_API, api::Dimensions::_2D, api::AntiAliasing::None>;
    using Texture2DMultisample   = imp::GTexture<api::GRAPHICS_API, api::Dimensions::_2D, api::AntiAliasing::MSAA>;
    using Texture3D              = imp::GTexture<api::GRAPHICS_API, api::Dimensions::_3D, api::AntiAliasing::None>;
    using Texture3DMultisample   = imp::GTexture<api::GRAPHICS_API, api::Dimensions::_3D, api::AntiAliasing::MSAA>;

    using TextureBlueprint       = api::TextureBlueprint;

    using Dimensions             = api::Dimensions;
    using AntiAliasing           = api::AntiAliasing;

    using RenderState            = imp::GRenderState<api::GRAPHICS_API>;
}
