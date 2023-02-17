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
        enum class MinFilter //GL_LINEAR is bilinear, and GL_LINEAR_MIPMAP_LINEAR is trilinear filtering.
		{
			NearestMipmapNearest,
			NearestMipmapLinear,

			LinearMipmapNearest,
			LinearMipmapLinear,
		};
		enum class MagFilter
		{
            Nearest, 
            Linear, 
		};

		virtual ~Texture() = default;

		virtual void bind(unsigned int slot) const = 0;

		Format format() const
		{
			return m_format;
		}
		Layout layout() const
		{
			return m_layout;
		}
		MinFilter min_filter() const
		{
			return m_minFilter;
		}
		MagFilter mag_filter() const
		{
			return m_magFilter;
		}

	protected:
		Texture(Texture::Format format, Layout layout, unsigned int mipLevels)
			: m_format{ format }, m_layout{ layout }, m_mipLevels{ mipLevels } {}
		Texture(Texture::Format format, Layout layout, unsigned int mipLevels, MinFilter minFilter, MagFilter magFilter)
			: m_format{ format }, m_layout{ layout }, m_mipLevels{ mipLevels }, m_minFilter{ minFilter }, m_magFilter{ magFilter } {}

		const Format       m_format{};
		const Layout       m_layout{};
		const unsigned int m_mipLevels{};

        MinFilter          m_minFilter{ MinFilter::NearestMipmapNearest };
        MagFilter          m_magFilter{ MagFilter::Nearest };
	};
}
