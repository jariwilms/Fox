#pragma once

#include "stdafx.hpp"

#include "Helix/Experimental/Rendering/API/API.hpp"
#include "Helix/Experimental/Rendering/Texture/Texture.hpp"
#include "Helix/Experimental/Rendering/Blueprint/TextureBlueprint.hpp"

namespace hlx::gfx::api
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
            Manifest(const std::string& identifier, FrameBuffer::Attachment attachment, FrameBuffer::Resample resample, const TextureBlueprint& blueprint)
                : identifier{ identifier }, attachment{ attachment }, resample{ resample }, blueprint{ blueprint } {}

            const std::string&      identifier{};
            FrameBuffer::Attachment attachment{};
            FrameBuffer::Resample   resample{};
            const TextureBlueprint& blueprint{};
        };

        const Vector2u& dimensions() const
        {
            return m_dimensions;
        }

    protected:
        FrameBuffer(const Vector2u& dimensions)
            : m_dimensions{ dimensions } {}

        Vector2u m_dimensions{};
    };

    template<GraphicsAPI, AntiAliasing>
    class GFrameBuffer;
};
