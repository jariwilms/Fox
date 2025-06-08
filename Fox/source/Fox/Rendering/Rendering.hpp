#pragma once

#include "Fox/Rendering/GraphicsAPI/GraphicsAPI.hpp"

#include "Fox/Rendering/AABB/AABB.hpp"
#include "Fox/Rendering/Buffer/Buffer.hpp"
#include "Fox/Rendering/Buffer/VertexArray.hpp"
#include "Fox/Rendering/FrameBuffer/FrameBuffer.hpp"
#include "Fox/Rendering/Geometry/Geometry.hpp"
#include "Fox/Rendering/Material/Material.hpp"
#include "Fox/Rendering/Mesh/Mesh.hpp"
#include "Fox/Rendering/Model/Model.hpp"
#include "Fox/Rendering/Projection/Projection.hpp"
#include "Fox/Rendering/RenderBuffer/RenderBuffer.hpp"
#include "Fox/Rendering/RenderInfo/RenderInfo.hpp"
#include "Fox/Rendering/Shader/Pipeline.hpp"
#include "Fox/Rendering/Shader/Shader.hpp"
#include "Fox/Rendering/Texture/Cubemap.hpp"
#include "Fox/Rendering/Texture/Texture.hpp"
#include "Fox/Rendering/Uniform/Uniform.hpp"

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
