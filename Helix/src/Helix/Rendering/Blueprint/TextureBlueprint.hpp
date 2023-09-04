#pragma once

#include "stdafx.hpp"

#include "Helix/Rendering/Texture/Texture2D.hpp"
#include "Helix/Rendering/Texture/Texture2DMultisample.hpp"
#include "Helix/IO/Filesystem/Image.hpp"

namespace hlx
{
	struct TextureBlueprint
	{
	public:
		std::shared_ptr<Texture2D> build(const std::shared_ptr<Image> image, unsigned int mipLevels = 1u, bool sRGB = false) const;
		std::shared_ptr<Texture2D> build(const Vector2u& dimensions, unsigned int mipLevels = 1u, bool sRGB = false) const;
		std::shared_ptr<Texture2DMultisample> build_ms(const Vector2u& dimensions, unsigned int mipLevels = 1u, unsigned int samples = 0u, bool sRGB = false) const;

		Texture::Format     format{ Texture::Format::RGBA };
		Texture::ColorDepth colorDepth{ Texture::ColorDepth::_8bit };
		Texture::Filter     filter{ Texture::Filter::Point };
		Texture::Wrapping   wrappingS{ Texture::Wrapping::ClampToEdge };
		Texture::Wrapping   wrappingT{ Texture::Wrapping::ClampToEdge };
	};
}
