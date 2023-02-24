#pragma once

#include "stdafx.hpp"

#include "Helix/Rendering/Interface/IBindable.hpp"

namespace hlx
{
	class Texture : public IBindable
	{
	public:
		enum class Format
		{
			R = 1, 
			RG, 
			RGB, 
			RGBA, 
		};
		enum class Layout
		{
			RGB8,
			RGB16,
			RGB32,

			RGBA8,
			RGBA16,
			RGBA32,
		};
		enum class Wrapping
		{
			ClampToEdge,
			ClampToBorder,

			MirroredRepeat,
			Repeat,
			MirroredClampToEdge,
		};
        enum class Filter
		{
			Point, 
			Bilinear, 
			Trilinear, 
		};

		virtual ~Texture() = default;

		virtual void bind(unsigned int slot) const = 0;

		Format       format() const
		{
			return m_format;
		}
		Layout       layout() const
		{
			return m_layout;
		}
        Filter       filter() const
        {
            return m_filter;
        }
		unsigned int mip_levels() const
		{
			return m_mipLevels;
		}

	protected:
		Texture(Texture::Format format, Layout layout, unsigned int mipLevels, Filter filter)
			: m_format{ format }, m_layout{ layout }, m_mipLevels{ mipLevels }, m_filter{ filter } {}

		const Format       m_format{};
		const Layout       m_layout{};
		const Filter       m_filter{};
		const unsigned int m_mipLevels{};
	};
}
