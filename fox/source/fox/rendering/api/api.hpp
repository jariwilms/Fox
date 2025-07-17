#pragma once

#include <fox/rendering/api/opengl/gl.hpp>

import std;
import fox.core.meta;
import fox.core.types;
import fox.core.utility;

namespace fox::gfx
{
    namespace impl
    {
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
    }

    using handle_t  = fox::alias_t<fox::handle_t , impl::handle_t >;
    using binding_t = fox::alias_t<fox::binding_t, impl::binding_t>;
}
