#pragma once

#include "stdafx.hpp"

#include "Helix/Experimental/Rendering/Renderer.hpp"
#include "Helix/Experimental/Rendering/Rendering.hpp"

namespace hlx::gfx::api
{
    template<>
    class GRenderer<GraphicsAPI::OpenGL> : public Renderer
    {
    public:
        GRenderer()
        {
            const u8 samples{ 4 };
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

            m_gBuffer            = std::make_unique<FrameBuffer>(dimensions, gBufferManifest);
            m_gBufferMultisample = std::make_unique<FrameBufferMultisample>(dimensions, samples, gBufferManifest);



            std::array<FrameBuffer::Manifest, 1> sBufferManifest
            {
                FrameBuffer::Manifest{ "Depth", FrameBuffer::Attachment::Depth, FrameBuffer::Resample::Yes, TextureBlueprint{ Texture::Format::D24_UNORM } },
            };

            m_sBuffer = std::make_unique<FrameBuffer>(shadowMapDimensions, sBufferManifest);











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

        std::vector<std::tuple<const std::shared_ptr<const Mesh>, const std::shared_ptr<const Material>, const Transform&>> m_mmt{};
    };
}
