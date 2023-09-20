#pragma once

#include "stdafx.hpp"

#include "Helix/Rendering/API/GraphicsAPI.hpp"
#include "Helix/Rendering/Blueprint/TextureBlueprint.hpp"
#include "Helix/Rendering/Buffer/FrameBufferMultisample.hpp"

namespace hlx
{
    struct FrameBufferBlueprint
    {
    public:
        std::shared_ptr<FrameBuffer> build(const Vector2u& dimensions) const
        {
            return gfx::create_framebuffer(dimensions, utl::to_span(textures), utl::to_span(renderBuffers));
        }
        std::shared_ptr<FrameBufferMultisample> build_ms(const Vector2u& dimensions, unsigned int samples) const
        {
            return gfx::create_framebuffer_multisample(dimensions, samples, utl::to_span(textures), utl::to_span(renderBuffers));
        }

        std::vector<FrameBuffer::TextureManifest>      textures{};
        std::vector<FrameBuffer::RenderBufferManifest> renderBuffers{};
    };
}
