#pragma once

#include "stdafx.hpp"

#include "Helix/Rendering/Rendering.hpp"
#include "Helix/Rendering/Renderer/Renderer.hpp"
#include "Helix/Rendering/API/Implementation/GRenderer.hpp"
#include "Helix/Rendering/Mesh/Mesh.hpp"
#include "Helix/Rendering/Material/Material.hpp"
#include "Helix/Core/Library/Transform/Transform.hpp"
#include "Helix/Rendering/Utility/Utility.hpp"

namespace hlx::gfx::imp::api
{
    template<>
    class GRenderer<gfx::api::GraphicsAPI::OpenGL> : public gfx::api::Renderer
    {
    public:
        static void init()
        {
            const u8 samples{ 4 };
            const u32 lightCount{ 8 };
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
            RenderState::apply<RenderState::Parameter::CullingFaceAlpha>(true);
            RenderState::apply<RenderState::Parameter::CullingFace>(RenderState::CullingFace::Back);
            RenderState::apply<RenderState::Parameter::FrontFace>(RenderState::FrontFace::CounterClockwise);
        }

        static void start_render_pass()
        {

        }
        static void finish_render_pass()
        {

        }

        static void render(const std::shared_ptr<const Mesh> mesh, const std::shared_ptr<const Material> material, const Transform& transform)
        {

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
