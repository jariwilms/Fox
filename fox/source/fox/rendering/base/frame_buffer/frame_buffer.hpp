#pragma once

#include <stdafx.hpp>

#include <fox/core/enumeration/enumeration.hpp>
#include <fox/rendering/base/render_buffer/render_buffer.hpp>
#include <fox/rendering/base/texture/cubemap.hpp>
#include <fox/rendering/base/texture/texture.hpp>

namespace fox::gfx::api
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
