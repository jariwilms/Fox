#pragma once

#include "stdafx.hpp"

#include "Helix/Rendering/Texture/Texture2D.hpp"
#include "Helix/Rendering/Blueprint/TextureBlueprint.hpp"
#include "Helix/Rendering/Blueprint/RenderBufferBlueprint.hpp"
#include "BufferComponent.hpp"

namespace hlx
{
	class FrameBuffer
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

        using Texture2DSpec = std::tuple<std::string, Attachment, Texture2D>;
        using RenderBufferSpec = std::tuple<std::string, Attachment, RenderBuffer>;
        using Texture2DBlueprintSpec = std::tuple<std::string, Attachment, TextureBlueprint>;
        using RenderBufferBlueprintSpec = std::tuple<std::string, Attachment, RenderBufferBlueprint>;

		virtual ~FrameBuffer() = default;

		virtual void bind(Target target) const = 0;
        virtual void unbind()            const = 0;
        virtual bool is_bound()          const = 0;

		virtual void bind_texture(const std::string& identifier, unsigned int slot) const = 0;

        const std::shared_ptr<Texture2D> texture(const std::string& identifier) const
        {
            return m_attachedTextures.at(identifier);
        }

        const Vector2u& dimensions() const
        {
            return m_dimensions;
        }

	protected:
		FrameBuffer(const Vector2u& dimensions)
			: m_dimensions{ dimensions } {}

		Vector2u m_dimensions{};

		std::unordered_map<std::string, std::shared_ptr<Texture2D>>    m_attachedTextures{};
		std::unordered_map<std::string, std::shared_ptr<RenderBuffer>> m_attachedRenderBuffers{};
	};
}
