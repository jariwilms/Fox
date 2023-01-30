#pragma once

#include "stdafx.hpp"

#include "Helix/Rendering/Buffer/RenderBuffer.hpp"

namespace hlx
{
    struct RenderBufferBlueprint
    {
    public:

        std::shared_ptr<RenderBuffer> build(const Vector2u& dimensions, unsigned int multiSamples) const;

        RenderBuffer::Type type{};
        RenderBuffer::Layout layout{};
    };
}
