#pragma once

#include "stdafx.hpp"

#include "Texture.hpp"

namespace hlx
{
    class CubemapTexture : public Texture
    {
    public:
        virtual ~CubemapTexture() = default;

        virtual void copy(const std::array<std::span<const byte>, 6>& data, unsigned int mipLevel = 0, bool generateMips = true) = 0;
        virtual void copy_range(const Vector2u dimensions, const Vector2u& offset, const std::array<std::span<const byte>, 6>& data, unsigned int mipLevel = 0, bool generateMips = true) = 0;

        const Vector2u& dimensions() const
        {
            return m_dimensions;
        }
        Wrapping wrapping_s() const
        {
            return m_wrappingS;
        }
        Wrapping wrapping_t() const
        {
            return m_wrappingT;
        }
        Wrapping wrapping_r() const
        {
            return m_wrappingR;
        }

    protected:
        CubemapTexture(Format format, Layout layout, const Vector2u& dimensions, unsigned int mipLevels, Wrapping wrappingS, Wrapping wrappingT, Wrapping wrappingR, Filter filter)
            : Texture{ format, layout, mipLevels, filter }, m_dimensions{ dimensions }, m_wrappingS{ wrappingS }, m_wrappingT{ wrappingT }, m_wrappingR{ wrappingR } {}

        const Vector2u m_dimensions{};
        const Wrapping m_wrappingS{};
        const Wrapping m_wrappingT{};
        const Wrapping m_wrappingR{};
    };
}
