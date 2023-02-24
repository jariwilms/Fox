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
        Texture2DMultisample(Format format, Layout layout, const Vector2u& dimensions, unsigned int mipLevels, unsigned int samples, Wrapping wrappingS, Wrapping wrappingT, Filter filter)
            : Texture2D{ format, layout, dimensions, mipLevels, wrappingS, wrappingT, filter }, m_samples{ samples } {}

        const unsigned int m_samples{};
    };
}
