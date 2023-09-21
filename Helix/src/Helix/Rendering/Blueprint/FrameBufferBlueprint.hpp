#pragma once

#include "stdafx.hpp"

#include "Helix/Rendering/Buffer/FrameBuffer.hpp"
#include "Helix/Rendering/Buffer/FrameBufferMultisample.hpp"

namespace hlx
{
    struct FrameBufferBlueprint
    {
    public:
        std::shared_ptr<FrameBuffer>            build(const Vector2u& dimensions) const;
        std::shared_ptr<FrameBufferMultisample> build_multisample(const Vector2u& dimensions, unsigned int samples) const;

        std::vector<FrameBuffer::TextureManifest>      textures{};
        std::vector<FrameBuffer::RenderBufferManifest> renderBuffers{};
    };
}
