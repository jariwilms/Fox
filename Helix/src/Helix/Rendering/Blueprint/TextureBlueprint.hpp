#pragma once

#include "stdafx.hpp"

#include "Helix/Core/Library/Utility/Utility.hpp"
#include "Helix/Rendering/Texture/Texture2D.hpp"
#include "Helix/Rendering/Texture/Texture2DMultisample.hpp"
#include "Helix/IO/Filesystem/Image.hpp"

namespace hlx
{
	struct TextureBlueprint
	{
	public:
		std::shared_ptr<Texture2D>            build(const std::shared_ptr<Image> image) const;
		std::shared_ptr<Texture2D>            build(const Vector2u& dimensions) const;
		std::shared_ptr<Texture2DMultisample> build_ms(const Vector2u& dimensions, unsigned int samples) const;

		Texture::Format   format  { Texture::Format::RGBA8_UNORM };
		Texture::Filter   filter  { Texture::Filter::Point };
		Texture::Wrapping wrapping{ Texture::Wrapping::Repeat };
	};
}
