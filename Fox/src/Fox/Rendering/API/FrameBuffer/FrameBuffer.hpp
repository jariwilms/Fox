#pragma once

#include "stdafx.hpp"

#include "Fox/Rendering/API/RenderBuffer/RenderBuffer.hpp"
#include "Fox/Rendering/API/Texture/Texture.hpp"
#include "Fox/Rendering/API/Texture/Cubemap.hpp"

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
        struct     Manifest
        {
            using surface_t = std::variant<Texture::Format, RenderBuffer::Format, Cubemap::Format>;

            Manifest(const std::string& identifier, surface_t format)
                : identifier{ identifier }, format{ format } {}

            std::string identifier{};
            surface_t   format;
        };

        FrameBuffer(FrameBuffer&& other) noexcept = default;

        const fox::Vector2u& dimensions() const
        {
            return m_dimensions;
        }

        FrameBuffer& operator=(FrameBuffer&& other) noexcept = default;

    protected:
        FrameBuffer(const fox::Vector2u& dimensions)
            : m_dimensions{ dimensions } {}

        fox::Vector2u m_dimensions{};
    };
};
