#pragma once

#include "stdafx.hpp"

#include "Fox/Rendering/RenderBuffer/RenderBuffer.hpp"
#include "Fox/Rendering/Texture/Texture.hpp"
#include "Fox/Rendering/Texture/Cubemap.hpp"

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

        struct Manifest
        {
            using var_t = std::variant<Texture::Format, RenderBuffer::Format, Cubemap::Format>;

            Manifest(const std::string& identifier, var_t format)
                : identifier{ identifier }, format{ format } {}

            std::string identifier{};
            var_t       format;
        };

        const fox::Vector2u& dimensions() const
        {
            return m_dimensions;
        }

    protected:
        FrameBuffer(const fox::Vector2u& dimensions)
            : m_dimensions{ dimensions } {}

        fox::Vector2u m_dimensions{};
    };
};
