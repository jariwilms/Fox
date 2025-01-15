#pragma once

#include "stdafx.hpp"

#include "Fox/Rendering/API/OpenGL/OpenGL.hpp"
#include "Fox/Rendering/API/OpenGL/RenderBuffer/RenderBuffer.hpp"
#include "Fox/Rendering/API/OpenGL/Texture/Texture.hpp"
#include "Fox/Rendering/FrameBuffer/FrameBuffer.hpp"
#include "Fox/Rendering/FrameBuffer/Mapping.hpp"

namespace fox::gfx::api::gl
{
    template<AntiAliasing>
    class FrameBuffer;

    template<>
    class FrameBuffer<AntiAliasing::None> : public api::FrameBuffer, public gl::Object
    {
    public:
        using texture_t       = gl::Texture<Dimensions::_2D, AntiAliasing::None>;
        using render_buffer_t = gl::RenderBuffer<AntiAliasing::None>;

        FrameBuffer(const fox::Vector2u& dimensions, std::span<const Manifest> manifests)
            : api::FrameBuffer{ dimensions }
        {
            m_handle = gl::create_frame_buffer();

            std::vector<gl::enum_t> colorBufferIndices{};
            std::ranges::for_each(manifests, [&, this](const Manifest& manifest)
                {
                    const auto& [identifier, format] = manifest;

                    std::visit([&, this](auto&& f) { attach(identifier, f, colorBufferIndices); }, format);
                });

            if (colorBufferIndices.empty())
            {
                gl::frame_buffer_read_buffer(m_handle, glf::FrameBuffer::Source::None);
                gl::frame_buffer_draw_buffer(m_handle, glf::FrameBuffer::Source::None);
            }
            else
            {
                gl::frame_buffer_draw_buffers(m_handle, colorBufferIndices);
            }

            const auto& frameBufferStatus = gl::check_frame_buffer_status(m_handle);
            if (frameBufferStatus != glf::FrameBuffer::Status::Complete) throw std::runtime_error{ "Framebuffer is not complete!" };
        }
        FrameBuffer(FrameBuffer&& other) noexcept = default;
        ~FrameBuffer()
        {
            gl::delete_frame_buffer(m_handle);
        }

        void bind(FrameBuffer::Target target)
        {
            const auto& frameBufferTarget = gl::map_frame_buffer_target(target);
            gl::bind_frame_buffer(m_handle, frameBufferTarget);
        }
        void bind_texture(const std::string& identifier, fox::uint32_t slot)
        {
            const auto& it = m_identifierToTexture.find(identifier);
            if (it == m_identifierToTexture.end()) throw std::invalid_argument{ "Invalid texture identifier!" };

            gl::bind_texture_unit(it->second->handle(), slot);
        }

        FrameBuffer& operator=(FrameBuffer&& other) noexcept = default;

    private:
        void attach(std::string_view identifier, api::Texture::Format      format, std::vector<gl::enum_t>& colorBufferIndices)
        {
            const auto& attachment            = api::map_frame_buffer_texture_attachment(format);
            const auto& frameBufferAttachment = gl::map_frame_buffer_attachment(attachment);
                  auto  attachmentIndex       = static_cast<gl::enum_t>(frameBufferAttachment);

            if (attachment == Attachment::Color)
            {
                attachmentIndex += static_cast<gl::enum_t>(colorBufferIndices.size());
                colorBufferIndices.emplace_back(attachmentIndex);
            }

            const auto& texture = std::make_shared<texture_t>(format, api::Texture::Filter::None, api::Texture::Wrapping::ClampToBorder, m_dimensions);
            gl::frame_buffer_texture(m_handle, texture->handle(), attachmentIndex, 0);

            m_identifierToTexture.emplace(identifier, texture);
        }
        void attach(std::string_view identifier, api::RenderBuffer::Format format, std::vector<gl::enum_t>& colorBufferIndices)
        {
            const auto& attachment            = api::map_frame_buffer_render_buffer_attachment(format);
            const auto& frameBufferAttachment = gl::map_frame_buffer_attachment(attachment);
                  auto  attachmentIndex       = static_cast<gl::enum_t>(frameBufferAttachment);

            if (attachment == Attachment::Color)
            {
                attachmentIndex += static_cast<gl::enum_t>(colorBufferIndices.size());
                colorBufferIndices.emplace_back(attachmentIndex);
            }

            const auto& renderBuffer = std::make_shared<render_buffer_t>(format, m_dimensions);
            gl::frame_buffer_render_buffer(m_handle, renderBuffer->handle(), attachmentIndex);

            m_identifierToRenderBuffer.emplace(identifier, renderBuffer);
        }

        std::unordered_map<std::string, std::shared_ptr<texture_t>>       m_identifierToTexture{};
        std::unordered_map<std::string, std::shared_ptr<render_buffer_t>> m_identifierToRenderBuffer{};
    };
    template<>
    class FrameBuffer<AntiAliasing::MSAA> : public api::FrameBuffer, public gl::Object
    {
    public:
        using texture_t       = gl::Texture<Dimensions::_2D, AntiAliasing::MSAA>;
        using render_buffer_t = gl::RenderBuffer<AntiAliasing::MSAA>;

        FrameBuffer(const fox::Vector2u& dimensions, fox::uint8_t samples, std::span<const Manifest> manifests)
            : api::FrameBuffer{ dimensions }, m_samples{ samples }
        {
            m_handle = gl::create_frame_buffer();

            std::vector<gl::enum_t> colorBufferIndices{};
            std::ranges::for_each(manifests, [&, this](const Manifest& manifest)
                {
                    const auto& [identifier, format] = manifest;

                    std::visit([&, this](auto&& f) { attach(identifier, f, colorBufferIndices); }, format);
                });

            if (colorBufferIndices.empty())
            {
                gl::frame_buffer_read_buffer(m_handle, glf::FrameBuffer::Source::None);
                gl::frame_buffer_draw_buffer(m_handle, glf::FrameBuffer::Source::None);
            }
            else
            {
                gl::frame_buffer_draw_buffers(m_handle, colorBufferIndices);
            }

            const auto& frameBufferStatus = gl::check_frame_buffer_status(m_handle);
            if (frameBufferStatus != glf::FrameBuffer::Status::Complete) throw std::runtime_error{ "Framebuffer is not complete!" };
        }
        FrameBuffer(FrameBuffer&& other) noexcept = default;
        ~FrameBuffer()
        {
            gl::delete_frame_buffer(m_handle);
        }

        void bind(FrameBuffer::Target target)
        {
            const auto& frameBufferTarget = gl::map_frame_buffer_target(target);
            gl::bind_frame_buffer(m_handle, frameBufferTarget);
        }
        void bind_texture(const std::string& identifier, fox::uint32_t slot)
        {
            const auto& it = m_identifierToTexture.find(identifier);
            if (it == m_identifierToTexture.end()) throw std::invalid_argument{ "Invalid texture identifier!" };

            gl::bind_texture_unit(it->second->handle(), slot);
        }

        fox::uint8_t samples() const
        {
            return m_samples;
        }

        FrameBuffer& operator=(FrameBuffer&& other) noexcept = default;

    private:
        void attach(std::string_view identifier, api::Texture::Format format,      std::vector<gl::enum_t>& colorBufferIndices)
        {
            const auto& attachment            = api::map_frame_buffer_texture_attachment(format);
            const auto& frameBufferAttachment = gl::map_frame_buffer_attachment(attachment);
                  auto  attachmentIndex       = static_cast<gl::enum_t>(frameBufferAttachment);

            if (attachment == Attachment::Color)
            {
                attachmentIndex += static_cast<gl::enum_t>(colorBufferIndices.size());
                colorBufferIndices.emplace_back(attachmentIndex);
            }

            const auto& texture = std::make_shared<texture_t>(format, m_dimensions, m_samples);
            gl::frame_buffer_texture(m_handle, texture->handle(), attachmentIndex, 0);

            m_identifierToTexture.emplace(identifier, texture);
        }
        void attach(std::string_view identifier, api::RenderBuffer::Format format, std::vector<gl::enum_t>& colorBufferIndices)
        {
            const auto& attachment            = api::map_frame_buffer_render_buffer_attachment(format);
            const auto& frameBufferAttachment = gl::map_frame_buffer_attachment(attachment);
                  auto  attachmentIndex       = static_cast<gl::enum_t>(frameBufferAttachment);

            if (attachment == Attachment::Color)
            {
                attachmentIndex += static_cast<gl::enum_t>(colorBufferIndices.size());
                colorBufferIndices.emplace_back(attachmentIndex);
            }

            const auto& renderBuffer = std::make_shared<render_buffer_t>(format, m_dimensions, m_samples);
            gl::frame_buffer_render_buffer(m_handle, renderBuffer->handle(), attachmentIndex);

            m_identifierToRenderBuffer.emplace(identifier, renderBuffer);
        }

        fox::uint8_t m_samples{};

        std::unordered_map<std::string, std::shared_ptr<texture_t>>       m_identifierToTexture{};
        std::unordered_map<std::string, std::shared_ptr<render_buffer_t>> m_identifierToRenderBuffer{};
    };
}
