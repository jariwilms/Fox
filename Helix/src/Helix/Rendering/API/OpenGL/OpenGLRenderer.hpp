#pragma once

#include "stdafx.hpp"

#include "Helix/Core/Library/Transform/Transform.hpp"
#include "Helix/Rendering/API/Implementation/GRenderer.hpp"
#include "Helix/Rendering/Material/Material.hpp"
#include "Helix/Rendering/Mesh/Mesh.hpp"
#include "Helix/Rendering/Renderer/Renderer.hpp"
#include "Helix/Rendering/Rendering.hpp"
#include "Helix/Rendering/Utility/Utility.hpp"

namespace hlx::gfx::imp::api
{
    template<>
    class GRenderer<gfx::api::GraphicsAPI::OpenGL>
    {
    public:
        GRenderer()
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

            m_gBuffer            = std::make_unique<FrameBuffer>(dimensions, gBufferManifest);
            m_gBufferMultisample = std::make_unique<FrameBufferMultisample>(dimensions, samples, gBufferManifest);
            m_sBuffer            = std::make_unique<FrameBuffer>(shadowMapDimensions, sBufferManifest);
            for (auto& ppBuffer : m_ppBuffers)
            {
                ppBuffer = std::make_unique<FrameBuffer>(dimensions, ppBufferManifest);
            }

            

            m_matricesBuffer = std::make_unique<UniformBuffer<UMatrices>>();
            m_materialBuffer = std::make_unique<UniformBuffer<UMaterial>>();
            m_cameraBuffer   = std::make_unique<UniformBuffer<UCamera>>();
            m_lightBuffer    = std::make_unique<UniformArrayBuffer<Buffer::Access::Dynamic, ULight>>(2u);



            const auto& meshShaders     = shaders_from_binaries("shaders/compiled/mesh.vert.spv",                 "shaders/compiled/mesh.frag.spv");
            const auto& lightingShaders = shaders_from_binaries("shaders/compiled/lighting_blinn-phong.vert.spv", "shaders/compiled/lighting_blinn-phong.frag.spv");
            const auto& skyboxShaders   = shaders_from_binaries("shaders/compiled/skybox.vert.spv",               "shaders/compiled/skybox.frag.spv");
            const auto& shadowShaders   = shaders_from_binaries("shaders/compiled/shadow.vert.spv",               "shaders/compiled/shadow.frag.spv");

            m_pipelines.emplace("Mesh",     std::make_unique<Pipeline>(meshShaders.at(0),     meshShaders.at(1)));
            m_pipelines.emplace("Lighting", std::make_unique<Pipeline>(lightingShaders.at(0), lightingShaders.at(1)));
            m_pipelines.emplace("Skybox",   std::make_unique<Pipeline>(skyboxShaders.at(0),   skyboxShaders.at(1)));
            m_pipelines.emplace("Shadow",   std::make_unique<Pipeline>(shadowShaders.at(0),   shadowShaders.at(1)));



            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
            glDepthFunc(GL_LEQUAL);
            glEnable(GL_CULL_FACE);
            glCullFace(GL_BACK);
            glFrontFace(GL_CCW);
        }
        ~GRenderer()
        {

        }

        void start()
        {

        }
        void finish()
        {

        }

        void render(const std::shared_ptr<const Mesh> mesh, const std::shared_ptr<const Material> material, const Transform& transform)
        {

        }

    private:
        std::unique_ptr<FrameBuffer> m_gBuffer{};
        std::unique_ptr<FrameBuffer> m_sBuffer{};
        std::array<std::unique_ptr<FrameBuffer>, 2> m_ppBuffers{};
        std::unique_ptr<FrameBufferMultisample> m_gBufferMultisample{};

        std::unique_ptr<UniformBuffer<UMatrices>> m_matricesBuffer{};
        std::unique_ptr<UniformBuffer<UMaterial>> m_materialBuffer{};
        std::unique_ptr<UniformBuffer<UCamera>> m_cameraBuffer{};
        std::unique_ptr<UniformArrayBuffer<Buffer::Access::Dynamic, ULight>> m_lightBuffer{};

        std::unordered_map<std::string, std::unique_ptr<Pipeline>> m_pipelines{};

        std::vector<std::tuple<const std::shared_ptr<const Mesh>, const std::shared_ptr<const Material>, const Transform&>> m_mmt{};
    };
}
