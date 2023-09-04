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

			D, 
			S, 
			DS, 
		};
		enum class ColorDepth
		{
			_8bit, 
			_16bit, 
			_24bit, 
			_32bit, 
		};
        enum class Filter
		{
			Point, 
			Bilinear, 
			Trilinear, 
		};
		enum class Wrapping
		{
			ClampToEdge,
			ClampToBorder,

			Repeat,
			MirroredRepeat,
			MirroredClampToEdge,
		};

		virtual ~Texture() = default;

		virtual void bind(unsigned int slot) const = 0;

		Format format() const
		{
			return m_format;
		}
		ColorDepth color_depth() const
		{
			return m_colorDepth;
		}
        Filter filter() const
        {
            return m_filter;
        }
		unsigned int mip_levels() const
		{
			return m_mipLevels;
		}
		bool standard_rgb() const
		{
			return m_sRGB;
		}

	protected:
		Texture(Texture::Format format, ColorDepth colorDepth, Filter filter, unsigned int mipLevels, bool sRGB)
			: m_format{ format }, m_colorDepth{ colorDepth }, m_filter{ filter }, m_mipLevels{ mipLevels }, m_sRGB{ sRGB } {}

		const Format       m_format{};
		const ColorDepth   m_colorDepth{};
		const Filter       m_filter{};
		const unsigned int m_mipLevels{};
		const bool         m_sRGB{};
	};
}
