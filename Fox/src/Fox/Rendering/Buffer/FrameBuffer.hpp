#pragma once

#include "stdafx.hpp"

#include "Fox/Rendering/Texture/Texture.hpp"
#include "Fox/Rendering/Blueprint/TextureBlueprint.hpp"

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
        enum class Resample
        {
            No, 
            Yes, 
        };
        struct Manifest
        {
            Manifest(const std::string& identifier, Attachment attachment, Resample resample, const api::TextureBlueprint& blueprint)
                : identifier{ identifier }, attachment{ attachment }, resample{ resample }, blueprint{ blueprint } {}

            std::string             identifier{};
            Attachment              attachment{};
            Resample                resample{};
            TextureBlueprint        blueprint{ Texture::Format::RGBA8_UNORM };
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
