#pragma once

#include "stdafx.hpp"

#include "Texture.hpp"

namespace hlx
{
    class CubemapTexture : public Texture
    {
    public:
        virtual ~CubemapTexture() = default;

        virtual void copy(const Vector2u dimensions, const Vector2u& offset, std::array<std::span<byte>, 6>& data) const = 0;

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
        const Vector2u& dimensions() const
        {
            return m_dimensions;
        }

    protected:
        CubemapTexture(Texture::Format format, Texture::Layout layout, const Vector2u& dimensions, unsigned int mipLevels)
            : Texture{ format, layout, mipLevels }, m_dimensions{ dimensions } {}
        CubemapTexture(Texture::Format format, Texture::Layout layout, const Vector2u& dimensions, unsigned int mipLevels, Wrapping wrappingS, Wrapping wrappingT, Wrapping wrappingR, MinFilter minFilter, MagFilter magFilter)
            : Texture{ format, layout, mipLevels, minFilter, magFilter }, m_dimensions{ dimensions }, m_wrappingS{ wrappingS }, m_wrappingT{ wrappingT }, m_wrappingR{ wrappingR } {}

        const Vector2u m_dimensions{};
        Wrapping       m_wrappingS{ Wrapping::ClampToEdge };
        Wrapping       m_wrappingT{ Wrapping::ClampToEdge };
        Wrapping       m_wrappingR{ Wrapping::ClampToEdge };
    };
}
