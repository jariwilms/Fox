export module fox.rendering.base.frame_buffer;

import std;

import fox.core.types;
import fox.core.enumeration;
import fox.rendering.base.cubemap;
import fox.rendering.base.texture;
import fox.rendering.base.render_buffer;

export namespace fox::gfx::api
{
    class FrameBuffer
    {
    public:
        enum class Attachment
        {
            Color0, 
            Color1, 
            Color2, 
            Color3, 
            Color4, 
            Color5, 
            Color6, 
            Color7, 

            Depth, 
            Stencil, 
            DepthStencil, 
        };
        struct     Specification
        {
            using format_v = std::variant<api::Texture::Format, api::Cubemap::Format, api::RenderBuffer::Format>;

            Specification(const std::string& identifier, format_v format)
                : identifier{ identifier }, format{ format } {}

            std::string identifier{};
            format_v    format;
        };
        struct     SpecificationMultisample
        {
            using format_v = std::variant<api::Texture::Format, api::RenderBuffer::Format>;

            SpecificationMultisample(const std::string& identifier, format_v format)
                : identifier{ identifier }, format{ format } {}

            std::string identifier{};
            format_v    format;
        };
        enum class Surface
        {
            Texture,
            Cubemap,
            RenderBuffer,
        };
        enum class Target
        {
            Read, 
            Write, 
        };
    };
};
namespace fox
{
    template<> struct fox::enumeration_operator<gfx::api::FrameBuffer::Attachment> { static constexpr auto enable = fox::bool_t{ fox::True }; };
}
