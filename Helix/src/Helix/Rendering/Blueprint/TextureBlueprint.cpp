#include "stdafx.hpp"

#include "TextureBlueprint.hpp"
#include "Helix/Rendering/API/GraphicsAPI.hpp"

namespace hlx
{
    std::shared_ptr<Texture2D> TextureBlueprint::build(const std::shared_ptr<Image> image, unsigned int mipLevels) const
    {
        const auto buffer = image->read();
        std::span<const byte> data{ buffer->begin(), buffer->size() };

        return GraphicsAPI::create_tex(format, layout, image->dimensions(), mipLevels, wrappingS, wrappingT, filter, data);
    }
    std::shared_ptr<Texture2D> TextureBlueprint::build(const Vector2u& dimensions, unsigned int mipLevels) const
    {
        return GraphicsAPI::create_tex(format, layout, dimensions, mipLevels, wrappingS, wrappingT, filter);
    }
    std::shared_ptr<hlx::Texture2DMultisample> TextureBlueprint::build_ms(const Vector2u& dimensions, unsigned int mipLevels, unsigned int samples) const
    {
        return GraphicsAPI::create_tex_ms(format, layout, dimensions, mipLevels, samples, wrappingS, wrappingT, filter);
    }
}
