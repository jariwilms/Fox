#pragma once

#include <stdafx.hpp>

#include <fox/rendering/api/opengl/buffer/buffer.hpp>
#include <fox/rendering/api/opengl/buffer/vertex_array.hpp>
#include <fox/rendering/api/opengl/context/context.hpp>
#include <fox/rendering/api/opengl/frame_buffer/frame_buffer.hpp>
#include <fox/rendering/api/opengl/render_buffer/render_buffer.hpp>
#include <fox/rendering/api/opengl/render_state/render_state.hpp>
#include <fox/rendering/api/opengl/sampler/sampler.hpp>
#include <fox/rendering/api/opengl/shader/pipeline.hpp>
#include <fox/rendering/api/opengl/shader/shader.hpp>
#include <fox/rendering/api/opengl/texture/cubemap.hpp>
#include <fox/rendering/api/opengl/texture/texture.hpp>

import fox.rendering.api.opengl;
import fox.rendering.api.opengl.query;

namespace fox::gfx::api::gl
{
    namespace dtl
    {
        inline auto blit     = std::shared_ptr<gl::FrameBuffer>{};
        inline auto pipeline = std::shared_ptr<gl::Pipeline<>>{};
    }

    inline void init()
    {
        dtl::blit   = std::make_shared<gl::FrameBuffer>();
        auto layout = gl::Pipeline<>::Layout{};
    }

    inline void copy_texture(std::shared_ptr<gl::Texture2D> source, std::shared_ptr<gl::Texture2D> destination)
    {
        source->bind(gl::binding_t{ 0u });

        dtl::blit->attach("Destination", gl::FrameBuffer::Attachment::Color0, destination);
        dtl::blit->bind  (gl::FrameBuffer::Target::Write);



        //bind pipeline with shader...
        //get plane vertex array...
        //draw_elements(...);

        //const auto& pva = gfx::Geometry::Plane::mesh()->vertexArray;
        //api::gl::clear(api::glf::Buffer::Mask::Color | api::glf::Buffer::Mask::Depth);
        //api::gl::draw_elements(api::glf::Draw::Mode::Triangles, api::glf::Draw::Type::UnsignedInt, pva->index_count());
    }
}
