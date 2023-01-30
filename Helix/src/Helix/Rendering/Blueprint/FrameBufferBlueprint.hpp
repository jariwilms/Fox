#pragma once

#include "stdafx.hpp"

#include "Helix/Rendering/API/GraphicsAPI.hpp"
#include "Helix/Rendering/Blueprint/TextureBlueprint.hpp"

namespace hlx
{
    struct FrameBufferBlueprint
    {
    public:
        FrameBufferBlueprint() = default;

        std::shared_ptr<FrameBuffer> build(const Vector2u& dimensions) const
        {
            return GraphicsAPI::create_fbo(dimensions, textures, renderBuffers);
        }

        std::vector<std::tuple<std::string, FrameBuffer::Attachment, TextureBlueprint>> textures{};
        std::vector<std::tuple<std::string, FrameBuffer::Attachment, RenderBufferBlueprint>> renderBuffers{};
    };
}
