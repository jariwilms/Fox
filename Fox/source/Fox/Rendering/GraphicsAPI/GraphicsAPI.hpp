#pragma once

#define FOX_GRAPHICS_API_DIRECTX 1
#define FOX_GRAPHICS_API_OPENGL  2
#define FOX_GRAPHICS_API_VULKAN  3

#ifndef FOX_GRAPHICS_API
#define FOX_GRAPHICS_API FOX_GRAPHICS_API_OPENGL
#endif

#include <fox/core/types/rendering/rendering.hpp>

#if FOX_GRAPHICS_API == FOX_GRAPHICS_API_OPENGL
#include <fox/rendering/graphicsapi/opengl/buffer/buffer.hpp>
#include <fox/rendering/graphicsapi/opengl/buffer/vertexarray.hpp>
#include <fox/rendering/graphicsapi/opengl/framebuffer/framebuffer.hpp>
#include <fox/rendering/graphicsapi/opengl/opengl.hpp>
#include <fox/rendering/graphicsapi/opengl/renderbuffer/renderbuffer.hpp>
#include <fox/rendering/graphicsapi/opengl/shader/pipeline.hpp>
#include <fox/rendering/graphicsapi/opengl/shader/shader.hpp>
#include <fox/rendering/graphicsapi/opengl/texture/cubemap.hpp>
#include <fox/rendering/graphicsapi/opengl/texture/texture.hpp>
#endif

namespace fox::gfx
{
    namespace api
    {
        namespace dx {}
        namespace gl {}
        namespace vk {}
    }


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
