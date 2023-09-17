#pragma once

#include "stdafx.hpp"

#include "Texture2D.hpp"

namespace hlx
{
    class Texture2DMultisample : public Texture2D
    {
    public:
        virtual ~Texture2DMultisample() = default;

        template<typename T>
        void copy(Components components, std::span<const T> data) = delete;
        template<typename T>
        void copy_range(const Vector2u& dimensions, const Vector2u& offset, Components dataComponents, std::span<const T> data) = delete;

        unsigned int samples() const
        {
            return m_samples;
        }

    protected:
        Texture2DMultisample(Format format, const Vector2u& dimensions, unsigned int samples)
            : Texture2D{ format, Filter::None, Wrapping::Repeat, dimensions }, m_samples{ samples } {}

        unsigned int m_samples{};

    private:
        void _copy(Components components, const std::type_info& dataType, std::span<const byte> data) final {}
        void _copy_range(const Vector2u& dimensions, const Vector2u& offset, Components dataComponents, const std::type_info& dataType, std::span<const byte> data) final {}
    };
}
