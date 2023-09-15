#pragma once

#include "stdafx.hpp"

namespace hlx
{
	class RenderBuffer
	{
	public:
        enum class Type
        {
            Color,
            Depth,
            Stencil,
            DepthStencil,
        };
		enum class Layout
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

		virtual void bind() const = 0;
		virtual void unbind() const = 0;
		virtual bool is_bound() const = 0;

		Type type()                  const
		{
			return m_type;
		}
		Layout layout()              const
		{
			return m_layout;
		}
		const Vector2u& dimensions() const
		{
			return m_dimensions;
		}

	protected:
		RenderBuffer(Type type, Layout layout, const Vector2u& dimensions)
			: m_type{ type }, m_layout{ layout }, m_dimensions{ dimensions } {}

		Type m_type{};
		Layout m_layout{};
		Vector2u m_dimensions{};
	};
}
