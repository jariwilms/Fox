module;

#include <fox/rendering/api/api.hpp>
#include <fox/rendering/buffer/buffer.hpp>
#include <fox/rendering/buffer/vertex_array.hpp>
#include <fox/rendering/frame_buffer/frame_buffer.hpp>
#include <fox/rendering/geometry/geometry.hpp>
#include <fox/rendering/render_info/render_info.hpp>
#include <fox/rendering/shader/pipeline.hpp>
#include <fox/rendering/shader/shader.hpp>

export module fox.rendering;

import std;

import fox.rendering.uniform;
import fox.rendering.cubemap;
import fox.rendering.texture;
import fox.rendering.material;
import fox.rendering.mesh;
import fox.rendering.model;
import fox.rendering.render_buffer;

export namespace fox::gfx
{
    inline void copy_texture(std::shared_ptr<gfx::Texture2D> source, std::shared_ptr<gfx::Texture2D> destination)
    {
        impl::copy_texture(source->impl(), destination->impl());
    }
}
