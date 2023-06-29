#pragma once

#include "stdafx.hpp"

#include "Texture.hpp"

namespace hlx
{
    class Texture2DMultisample : public Texture2D
    {
    public:
        virtual ~Texture2DMultisample() = default;

        unsigned int samples() const
        {
            return m_samples;
        }

    protected:
        Texture2DMultisample(Format format, ColorDepth colorDepth, const Vector2u& dimensions, unsigned int mipLevels, unsigned int samples, bool sRGB)
            : Texture2D{ format, colorDepth, dimensions, Filter::Point, Wrapping::ClampToEdge, Wrapping::ClampToEdge, mipLevels, sRGB }, m_samples{ samples } {}

        const unsigned int m_samples{};
    };
}
