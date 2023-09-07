#pragma once

#include "stdafx.hpp"

#include "Texture.hpp"

namespace hlx
{
    class CubemapTexture : public Texture
    {
    public:
        virtual ~CubemapTexture() = default;

        virtual void copy(Format dataFormat, std::span<std::span<const byte>, 6> data, unsigned int mipLevel = 0, bool generateMips = true) = 0;
        virtual void copy_range(const Vector2u& dimensions, const Vector2u& offset, Format dataFormat, std::span<std::span<const byte>, 6> data, unsigned int mipLevel = 0, bool generateMips = true) = 0;

        const Vector2u& dimensions() const
        {
            return m_dimensions;
        }
        Wrapping wrapping_r() const
        {
            return m_wrappingR;
        }
        Wrapping wrapping_s() const
        {
            return m_wrappingS;
        }
        Wrapping wrapping_t() const
        {
            return m_wrappingT;
        }

    protected:
        CubemapTexture(Format format, ColorDepth colorDepth, const Vector2u& dimensions, Filter filter, Wrapping wrappingR, Wrapping wrappingS, Wrapping wrappingT, unsigned int mipLevels, bool sRGB)
            : Texture{ format, colorDepth, filter, mipLevels, sRGB }, m_dimensions{ dimensions }, m_wrappingR{ wrappingR }, m_wrappingS{ wrappingS }, m_wrappingT{ wrappingT } {}

        const Vector2u m_dimensions{};
        const Wrapping m_wrappingR{};
        const Wrapping m_wrappingS{};
        const Wrapping m_wrappingT{};
    };
}
