#include "stdafx.hpp"

#include "Texture.hpp"

namespace hlx
{
	Texture::Format Texture::format() const
	{
		return m_format;
	}
	Texture::Layout Texture::layout() const
	{
		return m_layout;
	}
	Texture::Filter Texture::min_filter() const
	{
		return m_minFilter;
	}
	Texture::Filter Texture::mag_filter() const
	{
		return m_magFilter;
	}

	Texture::Texture(Texture::Format format, Layout layout)
		: m_format{ format }, m_layout{ layout } {}
	Texture::Texture(Texture::Format format, Layout layout, Filter minFilter, Filter magFilter, Levels levels)
		: m_layout{ layout }, m_minFilter{ minFilter }, m_magFilter{ magFilter }, m_levels{ levels } {}
}
