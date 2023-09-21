#pragma once

#include "stdafx.hpp"

#include "Helix/Rendering/Buffer/RenderBuffer.hpp"
#include "Helix/Rendering/Buffer/RenderBufferMultisample.hpp"

namespace hlx
{
    struct RenderBufferBlueprint
    {
    public:
        std::shared_ptr<RenderBuffer> build(const Vector2u& dimensions) const;
        std::shared_ptr<RenderBuffer> build_multisample(const Vector2u& dimensions, unsigned int samples) const;

        RenderBuffer::Format format{};
    };
}
