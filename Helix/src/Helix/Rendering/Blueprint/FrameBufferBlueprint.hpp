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
            return GraphicsAPI::create_fbo(dimensions, textures, renderBuffers);
        }
        std::shared_ptr<FrameBufferMultisample> build_ms(const Vector2u& dimensions, unsigned int samples) const
        {
            return GraphicsAPI::create_fbo_ms(dimensions, samples, textures, renderBuffers);
        }

        std::vector<std::tuple<std::string, FrameBuffer::Attachment, TextureBlueprint>> textures{};
        std::vector<std::tuple<std::string, FrameBuffer::Attachment, RenderBufferBlueprint>> renderBuffers{};
    };
}
