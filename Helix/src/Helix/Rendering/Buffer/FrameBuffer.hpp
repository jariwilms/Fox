#pragma once

#include "stdafx.hpp"

#include "Helix/Rendering/Interface/IBindable.hpp"
#include "Helix/Rendering/Texture/Texture2D.hpp"
#include "Helix/Rendering/Buffer/RenderBuffer.hpp"
#include "Helix/Rendering/Blueprint/TextureBlueprint.hpp"
#include "BufferComponent.hpp"

namespace hlx
{
	class FrameBuffer : public IBindable
	{
	public:
		enum class Target
		{
			Default, 
			Read, 
			Write, 
		};
		enum class Attachment
		{
			Color, 
			Depth, 
			Stencil, 
			DepthStencil, 
		};

		virtual ~FrameBuffer() = default;

		virtual void bind() = delete;
		virtual void bind(Target target) = 0;
		virtual void bind_texture(const std::string identifier, unsigned int slot) = 0;

	protected:
		FrameBuffer(const Vector2u& dimensions)
			: m_dimensions{ dimensions } {}

		const Vector2u m_dimensions{};

		std::unordered_map<std::string, std::shared_ptr<Texture2D>> m_attachedTextures{};
		std::unordered_map<std::string, std::shared_ptr<RenderBuffer>> m_attachedRenderBuffers{};
	};
}
