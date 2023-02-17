#pragma once

#include "stdafx.hpp"

#include "Helix/Rendering/Interface/IBindable.hpp"

namespace hlx
{
	class RenderBuffer : public IBindable
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

		Type type() const
		{
			return m_type;
		}
		Layout layout() const
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

		const Type m_type{};
		const Layout m_layout{};
		const Vector2u m_dimensions{};
	};
}
