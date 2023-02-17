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
        Texture2DMultisample(Texture::Format format, Texture::Layout layout, const Vector2u& dimensions, unsigned int mipLevels, unsigned int samples)
            : Texture2D{ format, layout, dimensions, mipLevels }, m_samples{ samples } {}
        Texture2DMultisample(Texture::Format format, Texture::Layout layout, const Vector2u& dimensions, unsigned int mipLevels, unsigned int samples, Wrapping wrappingS, Wrapping wrappingT, MinFilter minFilter, MagFilter magFilter)
            : Texture2D{ format, layout, dimensions, mipLevels, wrappingS, wrappingT, minFilter, magFilter }, m_samples{ samples } {}

        const unsigned int m_samples{};
    };
}
