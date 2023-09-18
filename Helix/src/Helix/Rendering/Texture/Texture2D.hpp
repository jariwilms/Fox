#pragma once

#include "stdafx.hpp"

#include "Texture.hpp"

#include "Helix/Core/Library/Utility/Utility.hpp"

namespace hlx
{
	class Texture2D : public Texture
	{
	public:
		virtual ~Texture2D() = default;
		
		template<typename T>
		void copy(Components components, std::span<const T> data)
		{
			copy(components, utl::as_bytes(data));
		}
		template<typename T>
		void copy_range(const Vector2u& dimensions, const Vector2u& offset, Components components, std::span<const T> data)
		{
			copy_range(dimensions, offset, components, utl::as_bytes(data));
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
		Texture2D(Format format, Filter filter, Wrapping wrapping, const Vector2u& dimensions)
			: Texture{ format, filter, wrapping }, m_dimensions{ dimensions }
		{
			if (m_filter != Filter::None) m_mipLevels = static_cast<unsigned int>(std::floor(std::log2(std::max(m_dimensions.x, m_dimensions.y)))) + 1u;
			else                          m_mipLevels = 1u;
		}

        virtual void copy(Components components, std::span<const byte> data) = 0;
        virtual void copy_range(const Vector2u& dimensions, const Vector2u& offset, Components components, std::span<const byte> data) = 0;

		Vector2u     m_dimensions{};
		unsigned int m_mipLevels{};
	};
}
