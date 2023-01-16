#pragma once

#include "stdafx.hpp"

#include "glm/glm.hpp"

#include "Helix/Core/Library/Interface/IBindable.hpp"

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

		Format format() const;
		Layout layout() const;
		Filter min_filter() const;
		Filter mag_filter() const;

	protected:
		Texture(Texture::Format format, Layout layout);
		Texture(Texture::Format format, Layout layout, Filter minFilter, Filter magFilter, Levels levels = 1);

		const Format m_format{};
		const Layout m_layout{};
		const Levels m_levels{ 1 };
		Filter m_minFilter{ Filter::Linear };
		Filter m_magFilter{ Filter::Linear };
	};
}
