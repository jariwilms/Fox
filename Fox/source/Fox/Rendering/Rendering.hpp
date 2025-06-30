#pragma once

#include <fox/rendering/buffer/buffer.hpp>
#include <fox/rendering/buffer/vertex_array.hpp>
#include <fox/rendering/frame_buffer/frame_buffer.hpp>
#include <fox/rendering/geometry/geometry.hpp>
#include <fox/rendering/api/api.hpp>
#include <fox/rendering/material/material.hpp>
#include <fox/rendering/mesh/mesh.hpp>
#include <fox/rendering/model/model.hpp>
#include <fox/rendering/render_buffer/render_buffer.hpp>
#include <fox/rendering/render_info/render_info.hpp>
#include <fox/rendering/shader/pipeline.hpp>
#include <fox/rendering/shader/shader.hpp>
#include <fox/rendering/texture/cubemap.hpp>
#include <fox/rendering/texture/texture.hpp>
#include <fox/rendering/uniform/uniform.hpp>

namespace fox::gfx
{
    namespace api::gl
    {
#if FOX_GRAPHICS_API == FOX_GRAPHICS_API_OPENGL
        static void copy_texture(std::shared_ptr<gl::Texture2D> source, std::shared_ptr<gl::Texture2D> destination)
        {
            //static std::unique_ptr<gfx::FrameBuffer> frameBuffer{};
        
            source->bind(gl::binding_t{ 0u });
            //frameBuffer->attach("Destination", gfx::FrameBuffer::Attachment::Color0, destination);
            const auto& pva = gfx::Geometry::Plane::mesh()->vertexArray;

            api::gl::clear(api::glf::Buffer::Mask::Color | api::glf::Buffer::Mask::Depth);
            api::gl::draw_elements(api::glf::Draw::Mode::Triangles, api::glf::Draw::Type::UnsignedInt, pva->index_count());
        }
#endif
    }
    static void copy_texture(std::shared_ptr<gfx::Texture2D> source, std::shared_ptr<gfx::Texture2D> destination)
    {
		api::gl::copy_texture(source->impl(), destination->impl());
    }

}
