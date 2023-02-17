#pragma once

#include "stdafx.hpp"

#include "FrameBuffer.hpp"
#include "Helix/Rendering/Texture/Texture2DMultisample.hpp"
#include "Helix/Rendering/Buffer/RenderBufferMultisample.hpp"

namespace hlx
{
    class FrameBufferMultisample : public FrameBuffer
    {
    public:
        virtual ~FrameBufferMultisample() = default;

    protected:
        FrameBufferMultisample(const Vector2u& dimensions, unsigned int samples)
            : FrameBuffer{ dimensions }, m_samples{ samples } {}

        std::unordered_map<std::string, std::shared_ptr<Texture2DMultisample>> m_attachedTextures{};
        std::unordered_map<std::string, std::shared_ptr<RenderBufferMultisample>> m_attachedRenderBuffers{};

        unsigned int m_samples{};
    };
}
