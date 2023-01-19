#pragma once

#include "stdafx.hpp"

#include "glm/glm.hpp"

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
		unsigned int samples() const
		{
			return m_samples;
		}
		const glm::uvec2& dimensions() const
		{
			return m_dimensions;
		}

	protected:
		RenderBuffer(Type type, Layout layout, unsigned int samples, const glm::uvec2& dimensions)
			: m_type{ type }, m_layout{ layout }, m_samples{ samples }, m_dimensions{ dimensions } {}

		const Type m_type{};
		const Layout m_layout{};
		const glm::uvec2 m_dimensions{};
		const unsigned int m_samples{};
	};
}
