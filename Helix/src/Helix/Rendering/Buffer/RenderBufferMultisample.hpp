#pragma once

#include "stdafx.hpp"

#include "RenderBuffer.hpp"

namespace hlx
{
    class RenderBufferMultisample : public RenderBuffer
    {
    public:
        virtual ~RenderBufferMultisample() = default;

        unsigned int samples() const
        {
            return m_samples;
        }

    protected:
        RenderBufferMultisample(RenderBuffer::Format format, const Vector2u& dimensions, unsigned int samples)
            : RenderBuffer{ format, dimensions }, m_samples{ samples } {}

        unsigned int m_samples{};
    };
}
