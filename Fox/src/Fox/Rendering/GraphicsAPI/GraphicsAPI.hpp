#pragma once

#define FOX_GRAPHICS_API_DIRECTX 1
#define FOX_GRAPHICS_API_OPENGL  2
#define FOX_GRAPHICS_API_VULKAN  3

#ifndef FOX_GRAPHICS_API
#define FOX_GRAPHICS_API FOX_GRAPHICS_API_OPENGL
#endif

#if FOX_GRAPHICS_API == FOX_GRAPHICS_API_OPENGL
#include "Fox/Rendering/GraphicsAPI/OpenGL/OpenGL.hpp"
#include "Fox/Rendering/GraphicsAPI/OpenGL/FrameBuffer/FrameBuffer.hpp"
#include "Fox/Rendering/GraphicsAPI/OpenGL/Buffer/Buffer.hpp"
#include "Fox/Rendering/GraphicsAPI/OpenGL/Buffer/VertexArray.hpp"
#include "Fox/Rendering/GraphicsAPI/OpenGL/RenderBuffer/RenderBuffer.hpp"
#include "Fox/Rendering/GraphicsAPI/OpenGL/Texture/Texture.hpp"
#include "Fox/Rendering/GraphicsAPI/OpenGL/Texture/Cubemap.hpp"
#include "Fox/Rendering/GraphicsAPI/OpenGL/Shader/Shader.hpp"
#include "Fox/Rendering/GraphicsAPI/OpenGL/Shader/Pipeline.hpp"
#endif

namespace fox::gfx
{
    namespace api
    {
        namespace dx {}
        namespace gl {}
        namespace vk {}
    }

    enum class handle_t : fox::uint32_t {};

    namespace impl
    {
#if FOX_GRAPHICS_API == FOX_GRAPHICS_API_DIRECTX
#endif
#if FOX_GRAPHICS_API == FOX_GRAPHICS_API_OPENGL
    using handle_t                = api::gl::handle_t;
    using binding_t               = api::gl::binding_t;
    using index_t                 = api::gl::index_t;
    using range_t                 = api::gl::range_t;
    using length_t                = api::gl::length_t;
    using area_t                  = api::gl::area_t;
    using volume_t                = api::gl::volume_t;

    template<typename T>
    using VertexBuffer            = api::gl::Buffer<T>;
    using IndexBuffer             = api::gl::Buffer<fox::index_t>;
    template<typename T>
    using UniformBuffer           = api::gl::UniformBuffer<T>;
    template<typename T, fox::uint64_t N>
    using UniformArrayBuffer      = api::gl::UniformArrayBuffer<T, N>;

    using VertexArray             = api::gl::VertexArray;

    using Texture1D               = api::gl::Texture1D;
    using Texture2D               = api::gl::Texture2D;
    using Texture3D               = api::gl::Texture3D;
    using Texture2DMultisample    = api::gl::Texture2DMultisample;
    using Texture3DMultisample    = api::gl::Texture3DMultisample;
    
    using Cubemap                 = api::gl::Cubemap;
    
    using RenderBuffer            = api::gl::RenderBuffer;
    using RenderBufferMultisample = api::gl::RenderBufferMultisample;

    using FrameBuffer             = api::gl::FrameBuffer;
    using FrameBufferMultisample  = api::gl::FrameBufferMultisample;

    using Shader                  = api::gl::Shader;
    template<typename T>
    using Pipeline                = api::gl::Pipeline<T>;
#endif
#if FOX_GRAPHICS_API == FOX_GRAPHICS_API_VULKAN
#endif
    }
}
