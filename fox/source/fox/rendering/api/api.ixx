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
        using handle_t             = api::gl::handle_t;
        using binding_t            = api::gl::binding_t;
        using index_t              = api::gl::index_t;
        using range                = api::gl::range;
        using length_t             = api::gl::length_t;
        using area_t               = api::gl::area_t;
        using volume_t             = api::gl::volume_t;
            
        template<typename T>
        using vertex_buffer        = api::gl::buffer<T>;
        using index_buffer         = api::gl::buffer<fox::index_t>;
        template<typename T>
        using uniform_buffer       = api::gl::uniform_buffer<T>;
        template<typename T, fox::uint64_t N>
        using uniform_array_buffer = api::gl::uniform_array_buffer<T, N>;
            
        using vertex_array         = api::gl::vertex_array;
            
        using texture1d            = api::gl::texture1d;
        using texture2d            = api::gl::texture2d;
        using texture3d            = api::gl::texture3d;
        using texture2d_ms         = api::gl::texture2d_ms;
        using texture3d_ms         = api::gl::texture3d_ms;
            
        using cubemap              = api::gl::cubemap;
            
        using render_buffer        = api::gl::render_buffer;
        using render_buffer_ms     = api::gl::render_buffer_ms;
            
        using frame_buffer         = api::gl::frame_buffer;
        using frame_buffer_ms      = api::gl::frame_buffer_ms;
            
        using shader               = api::gl::shader;
        template<typename T>
        using pipeline             = api::gl::pipeline<T>;
    }

    using handle_t  = fox::alias<fox::handle_t , impl::handle_t >;
    using binding_t = fox::alias<fox::binding_t, impl::binding_t>;
}
