#pragma once

#include "stdafx.hpp"

#include "Helix/Rendering/Rendering.hpp"
#include "Helix/Rendering/Renderer/Renderer.hpp"
#include "Helix/Rendering/API/Implementation/GRenderer.hpp"
#include "Helix/Rendering/Mesh/Mesh.hpp"
#include "Helix/Rendering/Material/Material.hpp"
#include "Helix/Core/Library/Transform/Transform.hpp"
#include "Helix/Rendering/Utility/Utility.hpp"
#include "Helix/Rendering/RenderInfo/RenderInfo.hpp"

namespace hlx::gfx::imp::api
{
    template<>
    class GRenderer<gfx::api::GraphicsAPI::OpenGL> : public gfx::api::Renderer
    {
    public:
        static void init()
        {
            const u8 samples{ 4 };
            const u32 lightCount{ 32 };
            const Vector2u dimensions{ 1280, 720 };
            const Vector2u shadowMapDimensions{ 1024, 1024 };

            std::array<FrameBuffer::Manifest, 5> gBufferManifest
            {
                FrameBuffer::Manifest{ "Position",     FrameBuffer::Attachment::Color,        FrameBuffer::Resample::Yes, TextureBlueprint{ Texture::Format::RGB16_SFLOAT, Texture::Filter::Trilinear, Texture::Wrapping::Repeat } },
                FrameBuffer::Manifest{ "Albedo",       FrameBuffer::Attachment::Color,        FrameBuffer::Resample::Yes, TextureBlueprint{ Texture::Format::RGBA8_SRGB,   Texture::Filter::Trilinear, Texture::Wrapping::Repeat } },
                FrameBuffer::Manifest{ "Normal",       FrameBuffer::Attachment::Color,        FrameBuffer::Resample::Yes, TextureBlueprint{ Texture::Format::RGB16_SFLOAT, Texture::Filter::Trilinear, Texture::Wrapping::Repeat } },
                FrameBuffer::Manifest{ "ARM",          FrameBuffer::Attachment::Color,        FrameBuffer::Resample::Yes, TextureBlueprint{ Texture::Format::RGB16_UNORM,  Texture::Filter::Trilinear, Texture::Wrapping::Repeat } },

                FrameBuffer::Manifest{ "DepthStencil", FrameBuffer::Attachment::DepthStencil, FrameBuffer::Resample::No,  TextureBlueprint{ Texture::Format::D24_UNORM_S8_UINT } },
            };
            std::array<FrameBuffer::Manifest, 1> sBufferManifest
            {
                FrameBuffer::Manifest{ "Depth", FrameBuffer::Attachment::Depth, FrameBuffer::Resample::Yes, TextureBlueprint{ Texture::Format::D24_UNORM } },
            };
            std::array<FrameBuffer::Manifest, 2> ppBufferManifest
            {
                FrameBuffer::Manifest{ "Color", FrameBuffer::Attachment::Color,        FrameBuffer::Resample::Yes, TextureBlueprint{ Texture::Format::RGB16_UNORM } },
                FrameBuffer::Manifest{ "Depth", FrameBuffer::Attachment::DepthStencil, FrameBuffer::Resample::No,  TextureBlueprint{ Texture::Format::D24_UNORM_S8_UINT} },
            };

            s_gBuffer            = std::make_unique<FrameBuffer>(dimensions, gBufferManifest);
            s_gBufferMultisample = std::make_unique<FrameBufferMultisample>(dimensions, samples, gBufferManifest);
            s_sBuffer            = std::make_unique<FrameBuffer>(shadowMapDimensions, sBufferManifest);
            for (auto& ppBuffer : s_ppBuffers)
            {
                ppBuffer = std::make_unique<FrameBuffer>(dimensions, ppBufferManifest);
            }

            

            s_matricesBuffer = std::make_unique<UniformBuffer<UMatrices>>();
            s_materialBuffer = std::make_unique<UniformBuffer<UMaterial>>();
            s_cameraBuffer   = std::make_unique<UniformBuffer<UCamera>>();
            s_lightBuffer    = std::make_unique<UniformArrayBuffer<Buffer::Access::Dynamic, ULight>>(2u);



            const auto& meshShaders     = shaders_from_binaries("shaders/compiled/mesh.vert.spv",                 "shaders/compiled/mesh.frag.spv");
            const auto& lightingShaders = shaders_from_binaries("shaders/compiled/lighting_blinn-phong.vert.spv", "shaders/compiled/lighting_blinn-phong.frag.spv");
            const auto& skyboxShaders   = shaders_from_binaries("shaders/compiled/skybox.vert.spv",               "shaders/compiled/skybox.frag.spv");
            const auto& shadowShaders   = shaders_from_binaries("shaders/compiled/shadow.vert.spv",               "shaders/compiled/shadow.frag.spv");

            s_pipelines.emplace("Mesh",     std::make_unique<Pipeline>(Pipeline::Manifest{ .vertexShader = meshShaders.at(0),     .fragmentShader = meshShaders.at(0) }));
            s_pipelines.emplace("Lighting", std::make_unique<Pipeline>(Pipeline::Manifest{ .vertexShader = lightingShaders.at(0), .fragmentShader = lightingShaders.at(0) }));
            s_pipelines.emplace("Skybox",   std::make_unique<Pipeline>(Pipeline::Manifest{ .vertexShader = skyboxShaders.at(0),   .fragmentShader = skyboxShaders.at(0) }));
            s_pipelines.emplace("Shadow",   std::make_unique<Pipeline>(Pipeline::Manifest{ .vertexShader = shadowShaders.at(0),   .fragmentShader = shadowShaders.at(0) }));



            RenderState::apply<RenderState::Parameter::ClearColor>(Vector4f{ 0.0f, 0.0f, 0.0f, 1.0f });
            RenderState::apply<RenderState::Parameter::DepthFunction>(RenderState::DepthFunction::LessEqual);
            RenderState::apply<RenderState::Parameter::FaceCullingAlpha>(true);
            RenderState::apply<RenderState::Parameter::FaceCulling>(RenderState::FaceCulling::Back);
            RenderState::apply<RenderState::Parameter::FrontFace>(RenderState::FrontFace::CounterClockwise);
        }

        static void start(const RenderInfo& renderInfo)
        {
            const auto& [camera, transform] = renderInfo.camera;
            const auto& viewMatrix          = glm::lookAt(transform.position, transform.position + transform.forward(), transform.up());
            const auto& projectionMatrix    = camera.projection().matrix();

            std::array<ULight, 32> uLights{};
            const auto lights = renderInfo.lights;
            std::transform(lights.begin(), lights.end(), uLights.begin(), [](const std::tuple<Light, Vector3f>& _)
                {
                    const auto& [light, position] = _;

                    return ULight
                    {
                        Vector4f{ position, 0.0f },
                        Vector4f{ light.color, 0.0f },
                    };
                });

            s_matricesBuffer->copy_tuple(offsetof(UMatrices, view), std::make_tuple(viewMatrix, projectionMatrix));
            s_cameraBuffer->copy(UCamera{ Vector4f{ transform.position, 0.0f } });
            s_lightBuffer->copy(uLights);



            s_mmt.clear();



            s_gBufferMultisample->bind(FrameBuffer::Target::Write);

            gl::clear(gl::Buffer::Mask::All);
            RenderState::apply<RenderState::Parameter::DepthTestingAlpha>(true);
            RenderState::apply<RenderState::Parameter::FaceCullingAlpha>(true);
        }
        static void finish()
        {
            s_pipelines.at("Mesh")->bind();
            for (auto& mmt : s_mmt)
            {
                const auto& [mesh, material, transform] = mmt;
                const auto& vao                         = mesh->vertex_array();
                const auto& ind                         = vao->index_buffer();

                s_matricesBuffer->copy_tuple(offsetof(UMatrices, model),  std::make_tuple(transform.matrix()));
                s_matricesBuffer->copy_tuple(offsetof(UMatrices, normal), std::make_tuple(glm::transpose(glm::inverse(transform.matrix()))));

                vao->bind();
                if (vao->is_indexed()) ind->bind();

                s_materialBuffer->copy(UMaterial{ material->color, material->roughness, material->metallic });
                material->albedoMap->bind(0);
                material->normalMap->bind(1);
                material->armMap->bind(2);
                material->emissionMap->bind(3);

                glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(ind->count()), GL_UNSIGNED_INT, nullptr);
            }



            RenderState::apply<RenderState::Parameter::FaceCullingAlpha>(false);

            //Multisampled framebuffer textures can not be sampled like a regular framebuffer, so we have to copy it into a regular framebuffer
            const auto width{ 1280 };
            const auto height{ 720 };
            const auto& gBufferInternal   = s_gBuffer->expose_internals();
            const auto& gBufferMsInternal = s_gBufferMultisample->expose_internals();

            for (auto i{ 0u }; i < 4; ++i)
            {
                glNamedFramebufferReadBuffer(gBufferMsInternal.glId, GL_COLOR_ATTACHMENT0 + i);
                glNamedFramebufferDrawBuffer(gBufferInternal.glId, GL_COLOR_ATTACHMENT0 + i);
                glBlitNamedFramebuffer(gBufferMsInternal.glId, gBufferInternal.glId, 0, 0, width, height, 0, 0, width, height, GL_COLOR_BUFFER_BIT, GL_NEAREST);
            }
            glBlitNamedFramebuffer(gBufferMsInternal.glId, gBufferInternal.glId, 0, 0, width, height, 0, 0, width, height, GL_DEPTH_BUFFER_BIT, GL_NEAREST);




            ////Lighting pass render into ppBuffer
            //glDisable(GL_BLEND);

            //s_pipelines.at("Lighting")->bind();
            //s_ppBuffers[0]->bind(FrameBuffer::Target::Write);
            //s_gBuffer->bind_texture("Position", 0);
            //s_gBuffer->bind_texture("Albedo", 1);
            //s_gBuffer->bind_texture("Normal", 2);
            //s_gBuffer->bind_texture("ARM", 3);

            //glDisable(GL_DEPTH_TEST);
            //Geometry::Plane::mesh()->vertex_array()->bind();
            //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
            //glEnable(GL_BLEND);





        }

        static void render(std::shared_ptr<const Mesh> mesh, std::shared_ptr<const Material> material, const Transform& transform)
        {
            s_mmt.emplace_back(mesh, material, transform);
        }

    private:
        GRenderer() = delete;

        static inline std::unique_ptr<FrameBuffer> s_gBuffer{};
        static inline std::unique_ptr<FrameBuffer> s_sBuffer{};
        static inline std::array<std::unique_ptr<FrameBuffer>, 2> s_ppBuffers{};
        static inline std::unique_ptr<FrameBufferMultisample> s_gBufferMultisample{};

        static inline std::unique_ptr<UniformBuffer<UMatrices>> s_matricesBuffer{};
        static inline std::unique_ptr<UniformBuffer<UMaterial>> s_materialBuffer{};
        static inline std::unique_ptr<UniformBuffer<UCamera>> s_cameraBuffer{};
        static inline std::unique_ptr<UniformArrayBuffer<Buffer::Access::Dynamic, ULight>> s_lightBuffer{};

        static inline std::unordered_map<std::string, std::unique_ptr<Pipeline>> s_pipelines{};

        static inline std::vector<std::tuple<const std::shared_ptr<const Mesh>, const std::shared_ptr<const Material>, const Transform&>> s_mmt{};
    };
}
