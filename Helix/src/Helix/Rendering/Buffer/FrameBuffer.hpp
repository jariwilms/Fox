#pragma once

#include "stdafx.hpp"

#include "Helix/Rendering/Texture/Texture2D.hpp"
#include "Helix/Rendering/Blueprint/TextureBlueprint.hpp"
#include "Helix/Rendering/Blueprint/RenderBufferBlueprint.hpp"

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

        struct TextureManifest
        {
            TextureManifest(const std::string& name, Attachment attachment, TextureBlueprint blueprint)
                : name{ name }, attachment{ attachment }, blueprint{ blueprint } {}

            std::string      name{};
            Attachment       attachment{};
            TextureBlueprint blueprint{};
        };
        struct RenderBufferManifest
        {
            RenderBufferManifest(const std::string& name, Attachment attachment, RenderBufferBlueprint blueprint)
                : name{ name }, attachment{ attachment }, blueprint{ blueprint } {}

            std::string           name{};
            Attachment            attachment{};
            RenderBufferBlueprint blueprint{};
        };

		virtual ~FrameBuffer() = default;

		virtual void bind(Target target) const = 0;
		virtual void bind_texture(const std::string& identifier, unsigned int slot) const = 0;

        const Vector2u& dimensions() const
        {
            return m_dimensions;
        }

	protected:
		FrameBuffer(const Vector2u& dimensions)
			: m_dimensions{ dimensions } {}

		Vector2u m_dimensions{};
	};
}
