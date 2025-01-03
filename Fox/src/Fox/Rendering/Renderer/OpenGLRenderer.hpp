#pragma once

#include "stdafx.hpp"

#include "Fox/Rendering/Geometry/Geometry.hpp"
#include "Fox/Rendering/Renderer/Renderer.hpp"
#include "Fox/Rendering/Renderer/RenderMode.hpp"
#include "Fox/Rendering/RenderInfo/RenderInfo.hpp"
#include "Fox/Rendering/Using.hpp"
#include "Fox/Rendering/Utility/Utility.hpp"

namespace fox::gfx::api
{
    class OpenGLRenderer : public api::Renderer
    {
    public:
        static void init()
        {
            using FM = gfx::FrameBuffer::Manifest;
            using FA = gfx::FrameBuffer::Attachment;
            using FR = gfx::FrameBuffer::Resample;
            using TB = gfx::TextureBlueprint;
            using TF = gfx::Texture::Format;
            using RF = gfx::RenderBuffer::Format;



            const fox::uint8_t  samples{ 4u };
            const fox::uint32_t lightCount{ 32u };
            const fox::Vector2u dimensions{ 1280u, 720u };
            const fox::Vector2u shadowMapDimensions{ 1024u, 1024u };



            std::array<FM, 5> gBufferManifest
            {
                FM{ "Position",     TF::RGB16_SFLOAT },
                FM{ "Albedo",       TF::RGBA8_UNORM  },
                FM{ "Normal",       TF::RGB16_SFLOAT },
                FM{ "ARM",          TF::RGB16_UNORM  },

                FM{ "DepthStencil", RF::D24_UNORM_S8_UINT },
            };
            std::array<FM, 1> sBufferManifest
            {
                FM{ "Depth",        TF::D24_UNORM },
            };
            std::array<FM, 2> ppBufferManifest
            {
                FM{ "Color",        TF::RGB16_UNORM },
                FM{ "Depth",        RF::D24_UNORM_S8_UINT },
            };

            s_gBuffer            = std::make_unique<gfx::FrameBuffer>(dimensions, gBufferManifest);
            //s_gBufferMultisample = std::make_unique<gfx::FrameBufferMultisample>(dimensions, samples, gBufferManifest);
            //s_sBuffer            = std::make_unique<gfx::FrameBuffer>(shadowMapDimensions, sBufferManifest);
            //s_ppBuffers.at(0)    = std::make_unique<gfx::FrameBuffer>(dimensions, ppBufferManifest);
            //s_ppBuffers.at(1)    = std::make_unique<gfx::FrameBuffer>(dimensions, ppBufferManifest);

            s_matricesBuffer     = std::make_unique<gfx::UniformBuffer<UMatrices>>();
            s_materialBuffer     = std::make_unique<gfx::UniformBuffer<UMaterial>>();
            s_cameraBuffer       = std::make_unique<gfx::UniformBuffer<UCamera>>();
            s_lightBuffer        = std::make_unique<gfx::UniformArrayBuffer<ULight>>(lightCount);

            s_INDEXBUFFER        = std::make_unique<gfx::UniformBuffer<fox::int32_t>>();
            




            const auto& meshShaders     = api::shaders_from_binaries<gfx::Shader>("shaders/compiled/mesh_deferred.vert.spv",                         "shaders/compiled/mesh_deferred.frag.spv");
            const auto& blitShaders     = api::shaders_from_binaries<gfx::Shader>("shaders/compiled/render_gbuffer_texture.vert.spv",                "shaders/compiled/render_gbuffer_texture.frag.spv");
            const auto& lightingShaders = api::shaders_from_binaries<gfx::Shader>("shaders/compiled/lighting_blinn-phong_sphere.vert.spv", "shaders/compiled/lighting_blinn-phong_sphere.frag.spv");
            const auto& debugShaders    = api::shaders_from_binaries<gfx::Shader>("shaders/compiled/debug.vert.spv",                                 "shaders/compiled/debug.frag.spv");

            s_pipelines.emplace("Mesh",     std::make_unique<gfx::Pipeline>(gfx::Pipeline::Layout{ .vertex = meshShaders.at(0),     .fragment = meshShaders.at(1) }));
            s_pipelines.emplace("Blit",     std::make_unique<gfx::Pipeline>(gfx::Pipeline::Layout{ .vertex = blitShaders.at(0),     .fragment = blitShaders.at(1) }));
            s_pipelines.emplace("Lighting", std::make_unique<gfx::Pipeline>(gfx::Pipeline::Layout{ .vertex = lightingShaders.at(0), .fragment = lightingShaders.at(1) }));
            s_pipelines.emplace("Debug",    std::make_unique<gfx::Pipeline>(gfx::Pipeline::Layout{ .vertex = debugShaders.at(0),    .fragment = debugShaders.at(1) }));
        }

        static void start(const gfx::RenderInfo& renderInfo)
        {
            const auto& lights              = renderInfo.lights;
            const auto& [camera, transform] = renderInfo.camera;
            const auto& viewMatrix          = glm::lookAt(transform.position, transform.position + transform.forward(), transform.up());
            const auto& projectionMatrix    = camera.projection().matrix();

            std::array<gfx::ULight, 32u> uLights{};
            std::transform(lights.begin(), lights.end(), uLights.begin(), [](const std::tuple<fox::Light, fox::Vector3f>& _)
                {
                    const auto& [light, position] = _;

                    return gfx::ULight
                    {
                        fox::Vector4f{ position,    0.0f },
                        fox::Vector4f{ light.color, 0.0f },
                        light.radius, 
                        0.1f, 
                        0.1f, 
                    };
                });





            //REMOVE
            s_lightsTEMP = uLights;





            s_matricesBuffer->copy_sub(offsetof(gfx::UMatrices, view), std::make_tuple(viewMatrix, projectionMatrix));
            s_cameraBuffer->copy(gfx::UCamera{ fox::Vector4f{ transform.position, 0.0f } });
            s_lightBuffer->copy(uLights);
            
            s_mmt.clear();
            s_debugTransforms.clear();
        }
        static void finish()
        {
            gl::enable(gl::Flags::Capability::DepthTest);
            gl::depth_function(gl::Flags::DepthFunction::Less);

            gl::enable(gl::Flags::Capability::FaceCulling);
            gl::face_culling(gl::Flags::FaceCulling::Back);
            gl::front_face(gl::Flags::Orientation::CounterClockwise);

            gl::disable(gl::Flags::Capability::Blending);



            s_matricesBuffer->bind_index(gl::index_t{ 1 });
            s_materialBuffer->bind_index(gl::index_t{ 3 });



            s_pipelines.at("Mesh")->bind();
            s_gBuffer->bind(gfx::FrameBuffer::Target::Write);
            gl::clear(gl::Flags::Buffer::Mask::All);

            for (auto& mmt : s_mmt)
            {
                const auto& [mesh, material, transform] = mmt;
                const auto& vao                         = mesh->vertexArray;
                const auto& ind                         = vao->index_buffer();

                const auto& modelMatrix  = transform.matrix();
                const auto& normalMatrix = glm::transpose(glm::inverse(fox::Matrix3f{ modelMatrix }));
                
                s_matricesBuffer->copy_sub(offsetof(gfx::UMatrices, model),  std::make_tuple(modelMatrix));
                s_materialBuffer->copy(gfx::UMaterial{ material->color, material->roughnessFactor, material->metallicFactor });

                vao->bind();

                material->albedo->bind(0);
                material->normal->bind(1);
                material->arm->bind(2);

                gl::draw_elements(gl::Flags::Draw::Mode::Triangles, gl::Flags::Draw::Type::UnsignedInt, ind->count());
            }



            gl::enable(gl::Flags::Capability::Blending);
            gl::blend_func(gl::Flags::Blending::Factor::SourceAlpha, gl::Flags::Blending::Factor::One);

            gl::disable(gl::Flags::Capability::DepthTest);
            gl::face_culling(gl::Flags::FaceCulling::Front);

            s_pipelines.at("Lighting")->bind();

            s_gBuffer->bind(gfx::FrameBuffer::Target::Read);
            s_gBuffer->bind_texture("Position", 0);
            s_gBuffer->bind_texture("Albedo",   1);
            s_gBuffer->bind_texture("Normal",   2);
            s_gBuffer->bind_texture("ARM",      3);

            s_lightBuffer->bind_index(gl::index_t{ 4 });
            s_cameraBuffer->bind_index(gl::index_t{ 2 });

            glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
            gl::clear(gl::Flags::Buffer::Mask::All);








            //s_TRANSFORMBUFFER->bind_index(gl::index_t{ 13 });
            //const auto& sva = gfx::Geometry::Sphere::mesh()->vertexArray;
            //sva->bind();

            //for (int i = 0; i < 2; ++i)
            //{
            //    const auto& light = s_lightsTEMP.at(i);
            //    auto sModel = fox::Transform{};
            //    sModel.position = light.position;
            //    sModel.dilate(fox::Vector3f{ light.radius });

            //    s_TRANSFORMBUFFER->copy_index(i, sModel.matrix());
            //}

            //gl::draw_elements_instanced(gl::Flags::Draw::Mode::Triangles, gl::Flags::Draw::Type::UnsignedInt, 2, sva->index_buffer()->count());






            
            s_INDEXBUFFER->bind_index(gl::index_t{ 12 });
            const auto& sva = gfx::Geometry::Sphere::mesh()->vertexArray;
            sva->bind();
            for (int i = 0; i < 2; ++i)
            {
                const auto& light = s_lightsTEMP.at(i);
                auto sModel = fox::Transform{};
                sModel.position = light.position;
                sModel.dilate(fox::Vector3f{ light.radius });

                s_matricesBuffer->copy_sub(offsetof(gfx::UMatrices, model), std::make_tuple(sModel.matrix()));
                s_INDEXBUFFER->copy(i);

                gl::draw_elements(gl::Flags::Draw::Mode::Triangles, gl::Flags::Draw::Type::UnsignedInt, sva->index_buffer()->count());
            }





            gl::disable(gl::Flags::Capability::Blending);
            gl::face_culling(gl::Flags::FaceCulling::Back);

#ifdef FOX_DEBUG
            s_pipelines.at("Debug")->bind();

            const auto& cva = gfx::Geometry::Cube::mesh()->vertexArray;
            cva->bind();

            for (const auto& transform : s_debugTransforms)
            {
                s_matricesBuffer->copy_sub(offsetof(gfx::UMatrices, model),  std::make_tuple(transform.matrix()));
                gl::draw_elements(gl::Flags::Draw::Mode::Triangles, gl::Flags::Draw::Type::UnsignedInt, cva->index_buffer()->count());
            }
#endif








            //gfx::RenderState::apply<api::RenderState::Parameter::FaceCullingAlpha>(false);

            ////Multisampled framebuffer textures can not be sampled like a regular framebuffer, they need to be drawn to a regular framebuffer first
            //const auto width{ 1280 };
            //const auto height{ 720 };
            //const auto& gBufferInternal   = static_cast<gl::uint32_t>(s_gBuffer->handle());
            //const auto& gBufferMsInternal = static_cast<gl::uint32_t>(s_gBufferMultisample->handle());

            //for (auto i{ 0u }; i < 4; ++i)
            //{
            //    glNamedFramebufferReadBuffer(gBufferMsInternal, GL_COLOR_ATTACHMENT0 + i);
            //    glNamedFramebufferDrawBuffer(gBufferInternal, GL_COLOR_ATTACHMENT0 + i);
            //    glBlitNamedFramebuffer(gBufferMsInternal, gBufferInternal, 0, 0, width, height, 0, 0, width, height, GL_COLOR_BUFFER_BIT, GL_NEAREST);
            //}
            //glBlitNamedFramebuffer(gBufferMsInternal, gBufferInternal, 0, 0, width, height, 0, 0, width, height, GL_DEPTH_BUFFER_BIT, GL_NEAREST);




            //Lighting pass render into ppBuffer
            //glDisable(GL_BLEND);

            //s_pipelines.at("Lighting")->bind();
            //s_ppBuffers[0]->bind(gfx::FrameBuffer::Target::Write);
            //s_gBuffer->bind_texture("Position", 0);
            //s_gBuffer->bind_texture("Albedo", 1);
            //s_gBuffer->bind_texture("Normal", 2);
            //s_gBuffer->bind_texture("ARM", 3);

            //glFrontFace(GL_CCW);
            //glCullFace(GL_BACK);

            //glDisable(GL_DEPTH_TEST);
            //gfx::Geometry::Plane::mesh()->vertexArray->bind();
            //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
            //glEnable(GL_BLEND);







            //glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0); // write to default framebuffer
            //glBlitFramebuffer(0, 0, 1280, 720, 0, 0, 1280, 720, GL_COLOR_BUFFER_BIT, GL_NEAREST);
        }

        static void render(std::shared_ptr<const gfx::Mesh> mesh, std::shared_ptr<const gfx::Material> material, const fox::Transform& transform)
        {
            s_mmt.emplace_back(mesh, material, transform);
        }
        static void render_debug(const fox::Transform& transform)
        {
            s_debugTransforms.emplace_back(transform);
        }

    private:
        OpenGLRenderer() = delete;

        static inline std::unique_ptr<gfx::FrameBuffer>                s_gBuffer{};
        static inline std::unique_ptr<gfx::FrameBuffer>                s_sBuffer{};
        static inline std::array<std::unique_ptr<gfx::FrameBuffer>, 2> s_ppBuffers{};
        static inline std::unique_ptr<gfx::FrameBufferMultisample>     s_gBufferMultisample{};
        
        static inline std::unique_ptr<gfx::UniformBuffer<gfx::UMatrices>>   s_matricesBuffer{};
        static inline std::unique_ptr<gfx::UniformBuffer<gfx::UMaterial>>   s_materialBuffer{};
        static inline std::unique_ptr<gfx::UniformBuffer<gfx::UCamera>>     s_cameraBuffer{};
        static inline std::unique_ptr<gfx::UniformArrayBuffer<gfx::ULight>> s_lightBuffer{};

        static inline std::unordered_map<std::string, std::unique_ptr<gfx::Pipeline>> s_pipelines{};

        static inline std::vector<std::tuple<std::shared_ptr<const gfx::Mesh>, std::shared_ptr<const gfx::Material>, fox::Transform>> s_mmt{};



        

        static inline std::unique_ptr<gfx::UniformBuffer<fox::int32_t>> s_INDEXBUFFER{};
        static inline std::array<gfx::ULight, 32u>                      s_lightsTEMP{};
        static inline std::vector<fox::Transform>                       s_debugTransforms{};
    };
}
