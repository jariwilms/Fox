#pragma once

#include "stdafx.hpp"

#include "Helix/Rendering/Interface/IBindable.hpp"
#include "Helix/Rendering/Texture/Texture2D.hpp"
#include "Helix/Rendering/Blueprint/TextureBlueprint.hpp"
#include "Helix/Rendering/Blueprint/RenderBufferBlueprint.hpp"
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
        enum class Option
        {
            None, 

            NoRead,
            NoDraw, 
        };

        using Texture2DSpec = std::tuple<std::string, Attachment, Texture2D>;
        using RenderBufferSpec = std::tuple<std::string, Attachment, RenderBuffer>;
        using Texture2DBlueprintSpec = std::tuple<std::string, Attachment, TextureBlueprint>;
        using RenderBufferBlueprintSpec = std::tuple<std::string, Attachment, RenderBufferBlueprint>;

		virtual ~FrameBuffer() = default;

		virtual void bind() = delete;
		virtual void bind(Target target) = 0;

		virtual void bind_texture(const std::string& identifier, unsigned int slot) = 0;

        virtual std::shared_ptr<Texture2D> texture(const std::string& identifier) = 0;

	protected:
		FrameBuffer(const Vector2u& dimensions)
			: m_dimensions{ dimensions } {}

		const Vector2u m_dimensions{};

		std::unordered_map<std::string, std::shared_ptr<Texture2D>> m_attachedTextures{};
		std::unordered_map<std::string, std::shared_ptr<RenderBuffer>> m_attachedRenderBuffers{};
	};
}
