#pragma once

#include "stdafx.hpp"

#include "Helix/Experimental/Rendering/API/API.hpp"

#include "Helix/Experimental/Rendering/Buffer/Buffer.hpp"
#include "Helix/Experimental/Rendering/Buffer/VertexArray.hpp"
#include "Helix/Experimental/Rendering/Buffer/FrameBuffer.hpp"
#include "Helix/Experimental/Rendering/Layout/VertexLayout.hpp"
#include "Helix/Experimental/Rendering/Shader/Pipeline.hpp"
#include "Helix/Experimental/Rendering/Shader/Shader.hpp"
#include "Helix/Experimental/Rendering/Texture/Texture.hpp"
#include "Helix/Experimental/Rendering/Uniform/Uniform.hpp"

#include "Helix/Core/Library/Transform/Transform.hpp"
#include "Helix/Rendering/Model/Model.hpp"
#include "Helix/Rendering/Mesh/Mesh.hpp"

namespace hlx::gfx
{
    using Buffer                 = api::Buffer;
    template<Buffer::Access ACCESS, typename T>
    using VertexBuffer           = api::GBuffer<api::GRAPHICS_API, api::Buffer::Type::Vertex, ACCESS, T>;
    template<Buffer::Access ACCESS>
    using IndexBuffer            = api::GBuffer<api::GRAPHICS_API, api::Buffer::Type::Index, ACCESS, u32>;
    template<typename T>
    using UniformBuffer          = api::GBuffer<api::GRAPHICS_API, api::Buffer::Type::Uniform, api::Buffer::Access::Static, T>;
    template<Buffer::Access ACCESS, typename T>
    using UniformArrayBuffer     = api::GBuffer<api::GRAPHICS_API, api::Buffer::Type::UniformArray, ACCESS, T>;
    using VertexArray            = api::GVertexArray<api::GRAPHICS_API>;

    template<typename T, u32 COUNT>
    using Layout                 = api::Layout<T, COUNT>;
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
