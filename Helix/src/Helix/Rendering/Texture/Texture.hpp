#pragma once

#include "stdafx.hpp"

#include "glm/glm.hpp"

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
			Nearest,
			Linear,

			NearestMipmapNearest,
			LinearMipmapNearest,

			NearestMipmapLinear,
			LinearMipmapLinear,
		};
		using Levels = unsigned int;

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
		Filter min_filter() const
		{
			return m_minFilter;
		}
		Filter mag_filter() const
		{
			return m_magFilter;
		}

	protected:
		Texture(Texture::Format format, Layout layout)
			: m_format{ format }, m_layout{ layout } {}
		Texture(Texture::Format format, Layout layout, Filter minFilter, Filter magFilter, Levels levels)
            : m_layout{ layout }, m_minFilter{ minFilter }, m_magFilter{ magFilter }, m_levels{ levels } {}

		const Format m_format{};
		const Layout m_layout{};
		const Levels m_levels{ 1 };
		Filter m_minFilter{ Filter::Linear };
		Filter m_magFilter{ Filter::Linear };
	};
}
