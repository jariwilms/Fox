#pragma once

#include "stdafx.hpp"

#include "Fox/Rendering/API/RenderBuffer/RenderBuffer.hpp"
#include "Fox/Rendering/API/Texture/Cubemap.hpp"
#include "Fox/Rendering/API/Texture/Texture.hpp"
#include "Fox/Core/Library/Enumeration/Enumeration.hpp"

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

    template<> struct api::enumeration_operator<FrameBuffer::Attachment> { static constexpr fox::bool_t enable = fox::True; };
};
