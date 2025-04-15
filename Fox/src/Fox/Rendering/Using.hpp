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
#include "Fox/Rendering/API/OpenGL/Texture/Cubemap.hpp"
#include "Fox/Rendering/API/OpenGL/Texture/Texture.hpp"
#include "Fox/Rendering/Layout/Layout.hpp"
#include "Fox/Rendering/RenderBuffer/RenderBuffer.hpp"
#include "Fox/Rendering/Uniform/Uniform.hpp"

namespace fox::gfx
{
	using Buffer                 = api::Buffer;
    template<typename T>
    using VertexBuffer           = api::gl::StaticBuffer<api::Buffer::Type::Vertex, T>;
    using IndexBuffer            = api::gl::StaticBuffer<api::Buffer::Type::Index,  fox::uint32_t>;
    template<typename T>
    using DynamicVertexBuffer    = api::gl::DynamicBuffer<api::Buffer::Type::Vertex, T>;
    using DynamicIndexBuffer     = api::gl::DynamicBuffer<api::Buffer::Type::Index,  fox::uint32_t>;
    template<typename T>
    using UniformBuffer          = api::gl::UniformBuffer<T>;
    template<typename T, fox::count_t N>
    using UniformArrayBuffer     = api::gl::UniformArrayBuffer<T, N>;

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
    using Cubemap                = api::gl::Cubemap;

    using RenderBuffer           = api::RenderBuffer;

    using RenderState            = api::gl::RenderState;
}

#endif

#if FOX_GRAPHICS_API == Vulkan
#endif

#if FOX_GRAPHICS_API == Direct3D
#endif
