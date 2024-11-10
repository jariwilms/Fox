#pragma once

#include "stdafx.hpp"

//#include "Fox/Rendering/API/GraphicsAPI.hpp"

//#include "Fox/Rendering/Uniform/Uniform.hpp"
//#include "Fox/Rendering/Texture/Texture.hpp"
//#include "Fox/Rendering/Shader/Shader.hpp"
//#include "Fox/Rendering/Shader/Pipeline.hpp"
//#include "Fox/Rendering/Layout/Layout.hpp"
//#include "Fox/Rendering/Buffer/VertexArray.hpp"
//#include "Fox/Rendering/Buffer/FrameBuffer.hpp"
//#include "Fox/Rendering/Buffer/Buffer.hpp"

//#include "Fox/Rendering/API/Implementation/GVertexLayout.hpp"
//#include "Fox/Rendering/API/Implementation/GVertexArray.hpp"
//#include "Fox/Rendering/API/Implementation/GTexture.hpp"
//#include "Fox/Rendering/API/Implementation/GShader.hpp"
//#include "Fox/Rendering/API/Implementation/GRenderState.hpp"
//#include "Fox/Rendering/API/Implementation/GPipeline.hpp"
//#include "Fox/Rendering/API/Implementation/GFrameBuffer.hpp"
//#include "Fox/Rendering/API/Implementation/GBuffer.hpp"

namespace fox::gfx
{
    //using Buffer                 = api::Buffer;

    //template<Buffer::Access ACCESS, typename T>
    //using VertexBuffer           = imp::GBuffer<api::GRAPHICS_API, Buffer::Type::Vertex, ACCESS, T>;
    //template<Buffer::Access ACCESS>
    //using IndexBuffer            = imp::GBuffer<api::GRAPHICS_API, Buffer::Type::Index, ACCESS, std::uint32_t>;
    //template<typename T>
    //using UniformBuffer          = imp::GBuffer<api::GRAPHICS_API, Buffer::Type::Uniform, Buffer::Access::Dynamic, T>;
    //template<Buffer::Access ACCESS, typename T>
    //using UniformArrayBuffer     = imp::GBuffer<api::GRAPHICS_API, Buffer::Type::UniformArray, ACCESS, T>;
    //using VertexArray            = imp::GVertexArray<api::GRAPHICS_API>;

    //template<typename... T>
    //using VertexLayout           = imp::GVertexLayout<api::GRAPHICS_API, T...>;

    //using FrameBuffer            = imp::GFrameBuffer<api::GRAPHICS_API, api::AntiAliasing::None>;
    //using FrameBufferMultisample = imp::GFrameBuffer<api::GRAPHICS_API, api::AntiAliasing::MSAA>;

    //using Pipeline               = imp::GPipeline<api::GRAPHICS_API>;
    //using Shader                 = imp::GShader<api::GRAPHICS_API>;

    //using Texture                = api::Texture;
    //using Texture1D              = imp::GTexture<api::GRAPHICS_API, api::Dimensions::_1D, api::AntiAliasing::None>;
    //using Texture2D              = imp::GTexture<api::GRAPHICS_API, api::Dimensions::_2D, api::AntiAliasing::None>;
    //using Texture2DMultisample   = imp::GTexture<api::GRAPHICS_API, api::Dimensions::_2D, api::AntiAliasing::MSAA>;
    //using Texture3D              = imp::GTexture<api::GRAPHICS_API, api::Dimensions::_3D, api::AntiAliasing::None>;
    //using Texture3DMultisample   = imp::GTexture<api::GRAPHICS_API, api::Dimensions::_3D, api::AntiAliasing::MSAA>;

    //using TextureBlueprint       = api::TextureBlueprint;

    //using Dimensions             = api::Dimensions;
    //using AntiAliasing           = api::AntiAliasing;

    //using RenderState            = imp::GRenderState<api::GRAPHICS_API>;
}
