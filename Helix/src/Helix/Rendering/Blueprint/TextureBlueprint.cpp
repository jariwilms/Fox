#include "stdafx.hpp"

#include "TextureBlueprint.hpp"
#include "Helix/Rendering/API/GraphicsAPI.hpp"

namespace hlx
{
    std::shared_ptr<Texture2D>            TextureBlueprint::build(const std::shared_ptr<Image> image) const
    {
        const auto& imageData = image->read();
        return GraphicsAPI::create_tex(format, filter, wrapping, image->dimensions(), Texture::Components::RGBA, utl::to_span(*imageData));
    }
    std::shared_ptr<Texture2D>            TextureBlueprint::build(const Vector2u& dimensions) const
    {
        return GraphicsAPI::create_tex(format, filter, wrapping, dimensions);
    }
    std::shared_ptr<Texture2DMultisample> TextureBlueprint::build_ms(const Vector2u& dimensions, unsigned int samples) const
    {
        return GraphicsAPI::create_tex_ms(format, dimensions, samples);
    }
}
