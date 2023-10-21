#include "stdafx.hpp"

#include "TextureBlueprint.hpp"

#include "Helix/Core/Library/Utility/Utility.hpp"
#include "Helix/Rendering/API/GraphicsAPI.hpp"

namespace hlx
{
    std::shared_ptr<Texture2D>            TextureBlueprint::build(const std::shared_ptr<Image> image) const
    {
        return GFX_DEPRECATED::create_texture(format, filter, wrapping, image->dimensions(), Texture::Components::RGBA, image->data());
    }
    std::shared_ptr<Texture2D>            TextureBlueprint::build(const Vector2u& dimensions) const
    {
        return GFX_DEPRECATED::create_texture(format, filter, wrapping, dimensions);
    }
    std::shared_ptr<Texture2DMultisample> TextureBlueprint::build_multisample(const Vector2u& dimensions, unsigned int samples) const
    {
        return GFX_DEPRECATED::create_texture_multisample(format, dimensions, samples);
    }
}
