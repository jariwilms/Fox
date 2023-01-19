#pragma once

#include "stdafx.hpp"

#include "glm/glm.hpp"

#include "Helix/Rendering/Interface/IBindable.hpp"
#include "Helix/Rendering/Texture/Texture2D.hpp"
#include "Helix/Rendering/Buffer/RenderBuffer.hpp"

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

		virtual ~FrameBuffer() = default;

		static std::shared_ptr<FrameBuffer> create(const glm::uvec2& dimensions);

		virtual void bind(Target target) const = 0;

		std::shared_ptr<Texture2D> attachment(std::string_view name) const //optional?
		{
			const auto it = m_attachedTextures.find(std::string{ name });
			if (it != m_attachedTextures.end()) return it->second;
			
			return {};
		}

	protected:
		FrameBuffer(const glm::uvec2& dimensions)
			: m_dimensions{ dimensions } {}

		std::unordered_map<std::string, std::shared_ptr<Texture2D>> m_attachedTextures{};
		std::unordered_map<std::string, std::shared_ptr<RenderBuffer>> m_attachedRenderBuffers{};

		const glm::uvec2 m_dimensions{};
	};
}
