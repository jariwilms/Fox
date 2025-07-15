module;

#include <fox/rendering/api/api.hpp>
#include <fox/rendering/buffer/buffer.hpp>
#include <fox/rendering/buffer/vertex_array.hpp>

export module fox.rendering;

import std;

import fox.rendering.uniform;
import fox.rendering.cubemap;
import fox.rendering.texture;
import fox.rendering.material;
import fox.rendering.mesh;
import fox.rendering.model;
import fox.rendering.render_buffer;
import fox.rendering.pipeline;
import fox.rendering.shader;
import fox.rendering.render_info;
import fox.rendering.geometry;
import fox.rendering.frame_buffer;

export namespace fox::gfx
{
    inline void copy_texture(std::shared_ptr<gfx::Texture2D> source, std::shared_ptr<gfx::Texture2D> destination)
    {
        impl::copy_texture(source->impl(), destination->impl());
    }
}
