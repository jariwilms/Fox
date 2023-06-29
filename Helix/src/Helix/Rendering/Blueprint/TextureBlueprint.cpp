#include "stdafx.hpp"

#include "TextureBlueprint.hpp"
#include "Helix/Rendering/API/GraphicsAPI.hpp"

namespace hlx
{
    std::shared_ptr<Texture2D> TextureBlueprint::build(const std::shared_ptr<Image> image, unsigned int mipLevels, bool sRGB) const
    {
        const auto buffer = image->read();
        std::span<const byte> data{ buffer->begin(), buffer->size() };

        return GraphicsAPI::create_tex(format, colorDepth, image->dimensions(), filter, wrappingS, wrappingT, mipLevels, sRGB, Texture::Format::RGBA, data);
    }
    std::shared_ptr<Texture2D> TextureBlueprint::build(const Vector2u& dimensions, unsigned int mipLevels, bool sRGB) const
    {
        return GraphicsAPI::create_tex(format, colorDepth, dimensions, filter, wrappingS, wrappingT, mipLevels, sRGB);
    }
    std::shared_ptr<Texture2DMultisample> TextureBlueprint::build_ms(const Vector2u& dimensions, unsigned int mipLevels, unsigned int samples, bool sRGB) const
    {
        return GraphicsAPI::create_tex_ms(format, colorDepth, dimensions, mipLevels, samples, sRGB);
    }
}
