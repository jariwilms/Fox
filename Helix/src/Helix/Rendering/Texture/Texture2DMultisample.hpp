#pragma once

#include "stdafx.hpp"

#include "Texture2D.hpp"

namespace hlx
{
    class Texture2DMultisample : public Texture
    {
    public:
        virtual ~Texture2DMultisample() = default;

        template<typename T>
        void copy(Components components, std::span<const T> data) = delete;
        template<typename T>
        void copy_range(const Vector2u& dimensions, const Vector2u& offset, Components components, std::span<const T> data) = delete;

        const Vector2u& dimensions() const
        {
            return m_dimensions;
        }
        unsigned int    samples()   const
        {
            return m_samples;
        }

    protected:
        Texture2DMultisample(Format format, const Vector2u& dimensions, unsigned int samples)
            : Texture{ format, Filter::None, Wrapping::Repeat }, m_dimensions{ dimensions }, m_samples{ samples } {}

        Vector2u     m_dimensions{};
        unsigned int m_samples{};
    };
}
