#pragma once

#ifndef FOX_GRAPHICS_API
#define FOX_GRAPHICS_API OpenGL
#endif

#if FOX_GRAPHICS_API == OpenGL

//TODO: check if all includes present/correct
#include "Fox/Rendering/API/OpenGL/Buffer/Buffer.hpp"
#include "Fox/Rendering/API/OpenGL/Buffer/VertexArray.hpp"
#include "Fox/Rendering/API/OpenGL/FrameBuffer/FrameBuffer.hpp"
#include "Fox/Rendering/API/OpenGL/RenderState/RenderState.hpp"
#include "Fox/Rendering/API/OpenGL/Shader/Pipeline.hpp"
#include "Fox/Rendering/API/OpenGL/Shader/Shader.hpp"
#include "Fox/Rendering/API/OpenGL/Texture/CubemapTexture.hpp"
#include "Fox/Rendering/API/OpenGL/Texture/Texture.hpp"
#include "Fox/Rendering/Layout/Layout.hpp"
#include "Fox/Rendering/RenderBuffer/RenderBuffer.hpp"
#include "Fox/Rendering/Uniform/Uniform.hpp"

namespace fox::gfx
{
	using Buffer                 = api::Buffer;
    template<Buffer::Access ACCESS, typename T>
    using VertexBuffer           = api::gl::Buffer<api::Buffer::Type::Vertex, ACCESS, T>;
    template<Buffer::Access ACCESS>
    using IndexBuffer            = api::gl::Buffer<api::Buffer::Type::Index, ACCESS, fox::uint32_t>;
    template<typename T>
    using UniformBuffer          = api::gl::Buffer<api::Buffer::Type::Uniform, Buffer::Access::Dynamic, T>;
    template<typename T>
    using UniformArrayBuffer     = api::gl::Buffer<api::Buffer::Type::UniformArray, Buffer::Access::Dynamic, T>;

    using VertexArray            = api::gl::VertexArray;

    using FrameBuffer            = api::gl::FrameBuffer<AntiAliasing::None>;
    using FrameBufferMultisample = api::gl::FrameBuffer<AntiAliasing::MSAA>;

    using Pipeline               = api::gl::Pipeline;
    using Shader                 = api::gl::Shader;

    using Texture                = api::Texture;
    using Texture1D              = api::gl::Texture<Dimensions::_1D, AntiAliasing::None>;
    using Texture2D              = api::gl::Texture<Dimensions::_2D, AntiAliasing::None>;
    using Texture3D              = api::gl::Texture<Dimensions::_3D, AntiAliasing::None>;
    using Texture2DMultisample   = api::gl::Texture<Dimensions::_2D, AntiAliasing::MSAA>;
    using Texture3DMultisample   = api::gl::Texture<Dimensions::_3D, AntiAliasing::MSAA>;
    using CubemapTexture         = api::gl::CubemapTexture;

    using RenderBuffer           = api::RenderBuffer;

    using RenderState            = api::gl::RenderState;
}

#endif

#if FOX_GRAPHICS_API == Vulkan
#endif

#if FOX_GRAPHICS_API == Direct3D
#endif
