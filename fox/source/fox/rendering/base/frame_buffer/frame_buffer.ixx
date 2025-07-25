export module fox.rendering.base.frame_buffer;

import std;
import fox.core.types;
import fox.core.enumeration;
import fox.rendering.base.cubemap;
import fox.rendering.base.texture;
import fox.rendering.base.render_buffer;

export namespace fox::gfx::api
{
    class frame_buffer
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
            using format_v = std::variant<api::Texture::Format, api::cubemap::Format, api::render_buffer::Format>;

            Specification(const std::string& identifier, format_v format)
                : identifier{ identifier }, format{ format } {}

            std::string identifier{};
            format_v    format;
        };
        struct     SpecificationMultisample
        {
            using format_v = std::variant<api::Texture::Format, api::render_buffer::Format>;

            SpecificationMultisample(const std::string& identifier, format_v format)
                : identifier{ identifier }, format{ format } {}

            std::string identifier{};
            format_v    format;
        };
        enum class Surface
        {
            texture, 
            cubemap,
            render_buffer,
        };
        enum class Target
        {
            Read, 
            Write, 
        };

        friend constexpr auto operator+(api::frame_buffer::Attachment first, fox::uint32_t second) -> api::frame_buffer::Attachment
        {
            return static_cast<api::frame_buffer::Attachment>(std::to_underlying(first) + second);
        };
    };
};
