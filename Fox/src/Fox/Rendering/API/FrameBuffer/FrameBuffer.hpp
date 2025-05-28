#pragma once

#include "stdafx.hpp"

#include "Fox/Rendering/API/RenderBuffer/RenderBuffer.hpp"
#include "Fox/Rendering/API/Texture/Cubemap.hpp"
#include "Fox/Rendering/API/Texture/Texture.hpp"

namespace fox::gfx::api
{
    class FrameBuffer
    {
    public:
        enum class Target
        {
            Read, 
            Write, 
        };
        enum class Attachment
        {
            Color, 
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
    };
};
