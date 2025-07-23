export module fox.rendering.api;

import std;
import fox.core.meta;
import fox.core.types;
import fox.core.utility;
import fox.rendering.api.gl;

export namespace fox::gfx
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
        using VertexBuffer            = api::gl::buffer<T>;
        using IndexBuffer             = api::gl::buffer<fox::index_t>;
        template<typename T>
        using UniformBuffer           = api::gl::uniform_buffer<T>;
        template<typename T, fox::uint64_t N>
        using UniformArrayBuffer      = api::gl::uniform_array_buffer<T, N>;
            
        using VertexArray             = api::gl::vertex_array;
            
        using Texture1D               = api::gl::texture1d;
        using Texture2D               = api::gl::texture2d;
        using Texture3D               = api::gl::texture3d;
        using Texture2DMultisample    = api::gl::texture2d_ms;
        using Texture3DMultisample    = api::gl::texture3d_ms;
            
        using Cubemap                 = api::gl::cubemap;
            
        using RenderBuffer            = api::gl::render_buffer;
        using RenderBufferMultisample = api::gl::render_buffer_ms;
            
        using FrameBuffer             = api::gl::frame_buffer;
        using FrameBufferMultisample  = api::gl::frame_buffer_ms;
            
        using Shader                  = api::gl::shader;
        template<typename T>
        using Pipeline                = api::gl::pipeline<T>;
    }

    using handle_t  = fox::alias<fox::handle_t , impl::handle_t >;
    using binding_t = fox::alias<fox::binding_t, impl::binding_t>;
}
