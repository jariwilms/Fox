export module fox.rendering.base.frame_buffer;

import std;
import fox.core.types;
import fox.rendering.base.cubemap;
import fox.rendering.base.texture;
import fox.rendering.base.render_buffer;

export namespace fox::gfx::api
{
    struct frame_buffer
    {
        enum class attachment_e
        {
            color0, 
            color1, 
            color2, 
            color3, 
            color4, 
            color5, 
            color6, 
            color7, 
            depth, 
            stencil, 
            depth_stencil, 
        };
        struct     specification
        {
            using format_v = std::variant<api::Texture::format_e, api::cubemap::format_e, api::render_buffer::format_e>;

            specification(const std::string& identifier, format_v format)
                : identifier{ identifier }, format{ format } {}

            std::string identifier;
            format_v    format;
        };
        struct     specification_ms
        {
            using format_v = std::variant<api::Texture::format_e, api::render_buffer::format_e>;

            specification_ms(const std::string& identifier, format_v format)
                : identifier{ identifier }, format{ format } {}

            std::string identifier;
            format_v    format;
        };
        enum class surface_e
        {
            texture, 
            cubemap,
            render_buffer,
        };
        enum class target_e
        {
            read, 
            write, 
        };

        friend constexpr auto operator+(attachment_e first, fox::uint32_t second) -> api::frame_buffer::attachment_e
        {
            return static_cast<api::frame_buffer::attachment_e>(std::to_underlying(first) + second);
        };
    };
};
