#pragma once

#include "stdafx.hpp"

#include "Fox/Rendering/Renderer/Renderer.hpp"
#include "Fox/Rendering/Using.hpp"
#include "Fox/Rendering/Utility/Utility.hpp"
#include "Fox/Rendering/RenderInfo/RenderInfo.hpp"
#include "Fox/Rendering/Geometry/Geometry.hpp"

namespace fox::gfx::api
{
    class OpenGLRenderer : public api::Renderer
    {
    public:
        static void init()
        {
            const fox::uint8_t  samples{ 4u };
            const fox::uint32_t lightCount{ 32u };
            const fox::Vector2u dimensions{ 1280u, 720u };
            const fox::Vector2u shadowMapDimensions{ 1024u, 1024u };

            std::array<api::FrameBuffer::Manifest, 5> gBufferManifest
            {
                gfx::FrameBuffer::Manifest{ "Position", gfx::FrameBuffer::Attachment::Color, gfx::FrameBuffer::Resample::Yes, gfx::TextureBlueprint{ gfx::Texture::Format::RGB16_SFLOAT, gfx::Texture::Filter::Trilinear, gfx::Texture::Wrapping::Repeat } },
                gfx::FrameBuffer::Manifest{ "Albedo",   gfx::FrameBuffer::Attachment::Color, gfx::FrameBuffer::Resample::Yes, gfx::TextureBlueprint{ gfx::Texture::Format::RGBA8_SRGB,   gfx::Texture::Filter::Trilinear, gfx::Texture::Wrapping::Repeat } },
                gfx::FrameBuffer::Manifest{ "Normal",   gfx::FrameBuffer::Attachment::Color, gfx::FrameBuffer::Resample::Yes, gfx::TextureBlueprint{ gfx::Texture::Format::RGB16_SFLOAT, gfx::Texture::Filter::Trilinear, gfx::Texture::Wrapping::Repeat } },
                gfx::FrameBuffer::Manifest{ "ARM",      gfx::FrameBuffer::Attachment::Color, gfx::FrameBuffer::Resample::Yes, gfx::TextureBlueprint{ gfx::Texture::Format::RGB16_UNORM,  gfx::Texture::Filter::Trilinear, gfx::Texture::Wrapping::Repeat } },

                gfx::FrameBuffer::Manifest{ "DepthStencil", gfx::FrameBuffer::Attachment::DepthStencil, gfx::FrameBuffer::Resample::No, gfx::TextureBlueprint{ Texture::Format::D24_UNORM_S8_UINT } },
            };
            std::array<gfx::FrameBuffer::Manifest, 1> sBufferManifest
            {
                gfx::FrameBuffer::Manifest{ "Depth", gfx::FrameBuffer::Attachment::Depth, gfx::FrameBuffer::Resample::Yes, gfx::TextureBlueprint{ Texture::Format::D24_UNORM } },
            };
            std::array<gfx::FrameBuffer::Manifest, 2> ppBufferManifest
            {
                gfx::FrameBuffer::Manifest{ "Color", gfx::FrameBuffer::Attachment::Color,        gfx::FrameBuffer::Resample::Yes, gfx::TextureBlueprint{ Texture::Format::RGB16_UNORM } },
                gfx::FrameBuffer::Manifest{ "Depth", gfx::FrameBuffer::Attachment::DepthStencil, gfx::FrameBuffer::Resample::No,  gfx::TextureBlueprint{ Texture::Format::D24_UNORM_S8_UINT } },
            };

            s_gBuffer            = std::make_unique<gfx::FrameBuffer>(dimensions, gBufferManifest);
            s_gBufferMultisample = std::make_unique<gfx::FrameBufferMultisample>(dimensions, samples, gBufferManifest);
            s_sBuffer            = std::make_unique<gfx::FrameBuffer>(shadowMapDimensions, sBufferManifest);
            for (auto& ppBuffer : s_ppBuffers)
            {
                ppBuffer = std::make_unique<gl::FrameBuffer<AntiAliasing::None>>(dimensions, ppBufferManifest);
            }

            

            s_matricesBuffer = std::make_unique<gfx::UniformBuffer<UMatrices>>();
            s_materialBuffer = std::make_unique<gfx::UniformBuffer<UMaterial>>();
            s_cameraBuffer   = std::make_unique<gfx::UniformBuffer<UCamera>>();
            s_lightBuffer    = std::make_unique<gfx::UniformArrayBuffer<api::Buffer::Access::Dynamic, ULight>>(32u);



            const auto& meshShaders     = api::shaders_from_binaries<gfx::Shader>("shaders/compiled/mesh.vert.spv",                 "shaders/compiled/mesh.frag.spv");
            const auto& lightingShaders = api::shaders_from_binaries<gfx::Shader>("shaders/compiled/lighting_blinn-phong.vert.spv", "shaders/compiled/lighting_blinn-phong.frag.spv");
            const auto& skyboxShaders   = api::shaders_from_binaries<gfx::Shader>("shaders/compiled/skybox.vert.spv",               "shaders/compiled/skybox.frag.spv");
            //const auto& shadowShaders   = shaders_from_binaries("shaders/compiled/shadow.vert.spv",               "shaders/compiled/shadow.frag.spv");

            s_pipelines.emplace("Mesh",     std::make_unique<gfx::Pipeline>(gfx::Pipeline::Layout{ .vertexShader = meshShaders.at(0),     .fragmentShader = meshShaders.at(1) }));
            s_pipelines.emplace("Lighting", std::make_unique<gfx::Pipeline>(gfx::Pipeline::Layout{ .vertexShader = lightingShaders.at(0), .fragmentShader = lightingShaders.at(1) }));
            s_pipelines.emplace("Skybox",   std::make_unique<gfx::Pipeline>(gfx::Pipeline::Layout{ .vertexShader = skyboxShaders.at(0),   .fragmentShader = skyboxShaders.at(1) }));
            //s_pipelines.emplace("Shadow",   std::make_unique<Pipeline>(Pipeline::Manifest{ .vertexShader = shadowShaders.at(0),   .fragmentShader = shadowShaders.at(0) }));

            gl::RenderState::apply<api::RenderState::Parameter::ClearColor>(Vector4f{ 0.0f, 0.0f, 0.0f, 1.0f });
            //gl::RenderState::apply<api::RenderState::Parameter::DepthFunction>(RenderState::DepthFunction::LessEqual);
            //gl::RenderState::apply<api::RenderState::Parameter::FaceCullingAlpha>(true);
            //gl::RenderState::apply<api::RenderState::Parameter::FaceCulling>(RenderState::FaceCulling::Back);
            gl::RenderState::apply<api::RenderState::Parameter::FrontFace>(RenderState::FrontFace::CounterClockwise);
        }

        static void start(const gfx::RenderInfo& renderInfo)
        {
            gl::clear(gl::Flags::Buffer::Mask::All);
            return;

            const auto& [camera, transform] = renderInfo.camera;
            const auto& viewMatrix          = glm::lookAt(transform.position, transform.position + transform.forward(), transform.up());
            const auto& projectionMatrix    = camera.projection().matrix();

            std::array<gfx::ULight, 32> uLights{};
            const auto lights = renderInfo.lights;
            std::transform(lights.begin(), lights.end(), uLights.begin(), [](const std::tuple<fox::Light, fox::Vector3f>& _)
                {
                    const auto& [light, position] = _;

                    return gfx::ULight
                    {
                        fox::Vector4f{ position, 0.0f },
                        fox::Vector4f{ light.color, 0.0f },
                    };
                });

            s_matricesBuffer->copy_tuple(offsetof(gfx::UMatrices, view), std::make_tuple(viewMatrix, projectionMatrix));
            s_cameraBuffer->copy(gfx::UCamera{ Vector4f{ transform.position, 0.0f } });
            s_lightBuffer->copy(uLights);



            s_mmt.clear();



            s_gBufferMultisample->bind(FrameBuffer::Target::Write);

            gl::clear(gl::Flags::Buffer::Mask::All);
            gfx::RenderState::apply<RenderState::Parameter::DepthTestingAlpha>(true);
            gfx::RenderState::apply<RenderState::Parameter::FaceCullingAlpha>(true);
        }
        static void finish()
        {
            //s_pipelines.at("Mesh")->bind();
            //for (auto& mmt : s_mmt)
            //{
            //    const auto& [mesh, material, transform] = mmt;
            //    const auto& vao                         = mesh->vertex_array();
            //    const auto& ind                         = vao->index_buffer();

            //    s_matricesBuffer->copy_tuple(offsetof(gfx::UMatrices, model),  std::make_tuple(transform.matrix()));
            //    s_matricesBuffer->copy_tuple(offsetof(gfx::UMatrices, normal), std::make_tuple(glm::transpose(glm::inverse(transform.matrix()))));

            //    vao->bind();
            //    if (vao->is_indexed()) ind->bind();

            //    s_materialBuffer->copy(gfx::UMaterial{ material->color, material->roughness, material->metallic });
            //    material->albedoMap->bind(0);
            //    material->normalMap->bind(1);
            //    material->armMap->bind(2);
            //    material->emissionMap->bind(3);

            //    glDrawElements(GL_TRIANGLES, static_cast<gl::sizeptr_t>(ind->count()), GL_UNSIGNED_INT, nullptr);
            //}



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
            glDisable(GL_BLEND);

            s_pipelines.at("Lighting")->bind();
            s_ppBuffers[0]->bind(gfx::FrameBuffer::Target::Write);
            s_gBuffer->bind_texture("Position", 0);
            s_gBuffer->bind_texture("Albedo", 1);
            s_gBuffer->bind_texture("Normal", 2);
            s_gBuffer->bind_texture("ARM", 3);

            glFrontFace(GL_CCW);
            glCullFace(GL_BACK);

            glDisable(GL_DEPTH_TEST);
            gfx::Geometry::Plane::mesh()->vertexArray->bind();
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
            glEnable(GL_BLEND);





            // blit to default framebuffer. Note that this may or may not work as the internal formats of both the FBO and default framebuffer have to match.
            // the internal formats are implementation defined. This works on all of my systems, but if it doesn't on yours you'll likely have to write to the 		
            // depth buffer in another shader stage (or somehow see to match the default framebuffer's internal format with the FBO's internal format).
            glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0); // write to default framebuffer
            glBlitFramebuffer(0, 0, 1280, 720, 0, 0, 1280, 720, GL_COLOR_BUFFER_BIT, GL_NEAREST);


        }

        static void render(std::shared_ptr<const gfx::Mesh> mesh, std::shared_ptr<const gfx::Material> material, const fox::Transform& transform)
        {
            s_mmt.emplace_back(mesh, material, transform);
        }

    private:
        OpenGLRenderer() = delete;

        static inline std::unique_ptr<gfx::FrameBuffer> s_gBuffer{};
        static inline std::unique_ptr<gfx::FrameBuffer> s_sBuffer{};
        static inline std::array<std::unique_ptr<gfx::FrameBuffer>, 2> s_ppBuffers{};
        static inline std::unique_ptr<gfx::FrameBufferMultisample> s_gBufferMultisample{};
        
        static inline std::unique_ptr<gfx::UniformBuffer<gfx::UMatrices>> s_matricesBuffer{};
        static inline std::unique_ptr<gfx::UniformBuffer<gfx::UMaterial>> s_materialBuffer{};
        static inline std::unique_ptr<gfx::UniformBuffer<gfx::UCamera>> s_cameraBuffer{};
        static inline std::unique_ptr<gfx::UniformArrayBuffer<api::Buffer::Access::Dynamic, gfx::ULight>> s_lightBuffer{};

        static inline std::unordered_map<std::string, std::unique_ptr<gfx::Pipeline>> s_pipelines{};

        static inline std::vector<std::tuple<const std::shared_ptr<const gfx::Mesh>, const std::shared_ptr<const gfx::Material>, const fox::Transform&>> s_mmt{};
    };
}
