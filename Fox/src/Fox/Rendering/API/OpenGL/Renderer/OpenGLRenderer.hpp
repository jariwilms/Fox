#pragma once

#include "stdafx.hpp"

#include "Fox/Core/Library/Transform/Transform.hpp"
#include "Fox/Rendering/API/OpenGL/OpenGL.hpp"
#include "Fox/Rendering/Material/Material.hpp"
#include "Fox/Rendering/Mesh/Mesh.hpp"
#include "Fox/Rendering/Renderer/Renderer.hpp"
#include "Fox/Rendering/RenderInfo/RenderInfo.hpp"
#include "Fox/Rendering/Uniform/Uniform.hpp"
#include "Fox/Rendering/Utility/Utility.hpp"
#include "Fox/Rendering/Geometry/Geometry.hpp"

namespace fox::gfx::api::gl
{
    class OpenGLRenderer : public Renderer
    {
    public:
        static void init()
        {
            const std::uint8_t samples{ 4 };
            const std::uint32_t lightCount{ 32u };
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

            s_gBuffer            = std::make_unique<OpenGLFrameBuffer<AntiAliasing::None>>(dimensions, gBufferManifest);
            s_gBufferMultisample = std::make_unique<OpenGLFrameBuffer<AntiAliasing::MSAA>>(dimensions, samples, gBufferManifest);
            s_sBuffer            = std::make_unique<OpenGLFrameBuffer<AntiAliasing::None>>(shadowMapDimensions, sBufferManifest);
            for (auto& ppBuffer : s_ppBuffers)
            {
                ppBuffer = std::make_unique<OpenGLFrameBuffer<AntiAliasing::None>>(dimensions, ppBufferManifest);
            }

            

            s_matricesBuffer = std::make_unique<UniformBuffer<UMatrices>>();
            s_materialBuffer = std::make_unique<UniformBuffer<UMaterial>>();
            s_cameraBuffer   = std::make_unique<UniformBuffer<UCamera>>();
            s_lightBuffer    = std::make_unique<UniformArrayBuffer<api::Buffer::Access::Dynamic, ULight>>(32u);



            const auto& meshShaders     = shaders_from_binaries("shaders/compiled/mesh.vert.spv",                 "shaders/compiled/mesh.frag.spv");
            const auto& lightingShaders = shaders_from_binaries("shaders/compiled/lighting_blinn-phong.vert.spv", "shaders/compiled/lighting_blinn-phong.frag.spv");
            const auto& skyboxShaders   = shaders_from_binaries("shaders/compiled/skybox.vert.spv",               "shaders/compiled/skybox.frag.spv");
            //const auto& shadowShaders   = shaders_from_binaries("shaders/compiled/shadow.vert.spv",               "shaders/compiled/shadow.frag.spv");

            s_pipelines.emplace("Mesh",     std::make_unique<OpenGLPipeline>(Pipeline::Manifest{ .vertexShader = meshShaders.at(0),     .fragmentShader = meshShaders.at(0) }));
            s_pipelines.emplace("Lighting", std::make_unique<OpenGLPipeline>(Pipeline::Manifest{ .vertexShader = lightingShaders.at(0), .fragmentShader = lightingShaders.at(0) }));
            s_pipelines.emplace("Skybox",   std::make_unique<OpenGLPipeline>(Pipeline::Manifest{ .vertexShader = skyboxShaders.at(0),   .fragmentShader = skyboxShaders.at(0) }));
            //s_pipelines.emplace("Shadow",   std::make_unique<Pipeline>(Pipeline::Manifest{ .vertexShader = shadowShaders.at(0),   .fragmentShader = shadowShaders.at(0) }));


            OpenGLRenderState::apply<RenderState::Parameter::ClearColor>(Vector4f{ 0.0f, 0.0f, 0.0f, 1.0f });
            OpenGLRenderState::apply<RenderState::Parameter::DepthFunction>(RenderState::DepthFunction::LessEqual);
            OpenGLRenderState::apply<RenderState::Parameter::FaceCullingAlpha>(true);
            OpenGLRenderState::apply<RenderState::Parameter::FaceCulling>(RenderState::FaceCulling::Back);
            OpenGLRenderState::apply<RenderState::Parameter::FrontFace>(RenderState::FrontFace::CounterClockwise);
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
            OpenGLRenderState::apply<RenderState::Parameter::DepthTestingAlpha>(true);
            OpenGLRenderState::apply<RenderState::Parameter::FaceCullingAlpha>(true);
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



            OpenGLRenderState::apply<RenderState::Parameter::FaceCullingAlpha>(false);

            //Multisampled framebuffer textures can not be sampled like a regular framebuffer, they need to be drawn to a regular framebuffer first
            const auto width{ 1280 };
            const auto height{ 720 };
            const auto& gBufferInternal   = static_cast<gl::uint32_t>(s_gBuffer->handle());
            const auto& gBufferMsInternal = static_cast<gl::uint32_t>(s_gBufferMultisample->handle());

            for (auto i{ 0u }; i < 4; ++i)
            {
                glNamedFramebufferReadBuffer(gBufferMsInternal, GL_COLOR_ATTACHMENT0 + i);
                glNamedFramebufferDrawBuffer(gBufferInternal, GL_COLOR_ATTACHMENT0 + i);
                glBlitNamedFramebuffer(gBufferMsInternal, gBufferInternal, 0, 0, width, height, 0, 0, width, height, GL_COLOR_BUFFER_BIT, GL_NEAREST);
            }
            glBlitNamedFramebuffer(gBufferMsInternal, gBufferInternal, 0, 0, width, height, 0, 0, width, height, GL_DEPTH_BUFFER_BIT, GL_NEAREST);




            //Lighting pass render into ppBuffer
            glDisable(GL_BLEND);

            s_pipelines.at("Lighting")->bind();
            s_ppBuffers[0]->bind(FrameBuffer::Target::Write);
            s_gBuffer->bind_texture("Position", 0);
            s_gBuffer->bind_texture("Albedo", 1);
            s_gBuffer->bind_texture("Normal", 2);
            s_gBuffer->bind_texture("ARM", 3);

            glDisable(GL_DEPTH_TEST);
            Geometry::Plane::mesh()->vertex_array()->bind();
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
            glEnable(GL_BLEND);





        }

        static void render(std::shared_ptr<const Mesh> mesh, std::shared_ptr<const Material> material, const Transform& transform)
        {
            s_mmt.emplace_back(mesh, material, transform);
        }

    private:
        OpenGLRenderer() = delete;

        static inline std::unique_ptr<OpenGLFrameBuffer<AntiAliasing::None>> s_gBuffer{};
        static inline std::unique_ptr<OpenGLFrameBuffer<AntiAliasing::None>> s_sBuffer{};
        static inline std::array<std::unique_ptr<OpenGLFrameBuffer<AntiAliasing::None>>, 2> s_ppBuffers{};
        static inline std::unique_ptr<OpenGLFrameBuffer<AntiAliasing::MSAA>> s_gBufferMultisample{};
        
        static inline std::unique_ptr<UniformBuffer<UMatrices>> s_matricesBuffer{};
        static inline std::unique_ptr<UniformBuffer<UMaterial>> s_materialBuffer{};
        static inline std::unique_ptr<UniformBuffer<UCamera>> s_cameraBuffer{};
        static inline std::unique_ptr<UniformArrayBuffer<api::Buffer::Access::Dynamic, ULight>> s_lightBuffer{};

        static inline std::unordered_map<std::string, std::unique_ptr<OpenGLPipeline>> s_pipelines{};

        static inline std::vector<std::tuple<const std::shared_ptr<const Mesh>, const std::shared_ptr<const Material>, const Transform&>> s_mmt{};
    };
}
