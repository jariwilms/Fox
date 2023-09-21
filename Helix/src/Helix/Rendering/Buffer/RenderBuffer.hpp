#pragma once

#include "stdafx.hpp"

namespace hlx
{
	class RenderBuffer
	{
	public:
		enum class Format
		{
			R8, 
			RG8, 
			RGB8, 
			RGBA8, 

			Depth16, 
			Depth24, 
			Depth32, 

			Depth24Stencil8, 
			Depth32Stencil8, 

			Stencil8, 
		};

		virtual ~RenderBuffer() = default;

		virtual void bind()     const = 0;

		Format          format()     const
		{
			return m_format;
		}
		const Vector2u& dimensions() const
		{
			return m_dimensions;
		}

	protected:
		RenderBuffer(Format format, const Vector2u& dimensions)
			: m_format{ format }, m_dimensions{ dimensions } {}

		Format   m_format{};
		Vector2u m_dimensions{};
	};
}
