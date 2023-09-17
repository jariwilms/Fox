#pragma once

#include "stdafx.hpp"

#include "Texture.hpp"

namespace hlx
{
    class CubemapTexture : public Texture
    {
    public:
        enum class Face
        {
            PositiveX, 
            NegativeX, 
            PositiveY, 
            NegativeY, 
            PositiveZ, 
            NegativeZ, 
        };

        virtual ~CubemapTexture() = default;

        template<typename T>
        void copy(Components dataComponents, std::span<std::span<const T>, 6> data)
        {
            _copy(dataComponents, typeid(T), data);
        }
        template<typename T>
        void copy_face(Face face, Components dataComponents, std::span<const T> data)
        {
            _copy_face(face, dataComponents, typeid(T), utl::as_bytes(data));
        }
        template<typename T>
        void copy_face_range(Face face, const Vector2u& dimensions, const Vector2u& offset, Components dataComponents, std::span<const T> data)
        {
            _copy_face_range(face, dimensions, offset, dataComponents, typeid(T), utl::as_bytes(data));
        }

        const Vector2u& dimensions() const
        {
            return m_dimensions;
        }
        unsigned int    mip_levels() const
        {
            return m_mipLevels;
        }

    protected:
        CubemapTexture(Format format, Filter filter, Wrapping wrapping, const Vector2u& dimensions)
            : Texture{ format, filter, wrapping }, m_dimensions{ dimensions }
        {
            if (m_filter != Filter::None) m_mipLevels = static_cast<unsigned int>(std::floor(std::log2(std::max(m_dimensions.x, m_dimensions.y)))) + 1u;
            else                          m_mipLevels = 1u;
        }

        virtual void _copy(Components dataComponents, const std::type_info& dataType, std::span<std::span<const byte>, 6> data) = 0;
        virtual void _copy_face(Face face, Components dataComponents, const std::type_info& dataType, std::span<const byte> data) = 0;
        virtual void _copy_face_range(Face face, const Vector2u& dimensions, const Vector2u& offset, Components dataComponents, const std::type_info& dataType, std::span<const byte> data) = 0;

        Vector2u     m_dimensions{};
        unsigned int m_mipLevels{};
    };
}
