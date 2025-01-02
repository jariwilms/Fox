#pragma once

#include "stdafx.hpp"

#include "Fox/Rendering/API/OpenGL/OpenGL.hpp"
#include "Fox/Rendering/API/OpenGL/Texture/Texture.hpp"
#include "Fox/Rendering/API/OpenGL/Texture/RenderBuffer.hpp"
#include "Fox/Rendering/Buffer/FrameBuffer.hpp"

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
                    const auto& [identifier, attachment, resample, blueprint] = manifest;
                    const auto& frameBufferAttachment = gl::map_frame_buffer_attachment(attachment);
                          auto  attachmentIndex       = static_cast<gl::enum_t>(frameBufferAttachment);

                    if (attachment == Attachment::Color)
                    {
                        attachmentIndex += static_cast<gl::enum_t>(colorBufferIndices.size());
                        colorBufferIndices.emplace_back(attachmentIndex);
                    }

                    switch (resample)
                    {
                        case FrameBuffer::Resample::Yes: //Bind as texture
                        {
                            const auto& texture = std::make_shared<texture_t>(blueprint.format, blueprint.filter, blueprint.wrapping, m_dimensions);
                            gl::frame_buffer_texture(m_handle, texture->handle(), attachmentIndex, 0);

                            m_identifierToTexture.emplace(identifier, texture);

                            break;
                        };
                        case FrameBuffer::Resample::No: //Bind as renderbuffer
                        {
                            const auto& renderBuffer = std::make_shared<render_buffer_t>(blueprint.format, m_dimensions);
                            gl::frame_buffer_render_buffer(m_handle, renderBuffer->handle(), attachmentIndex);

                            m_identifierToRenderBuffer.emplace(identifier, renderBuffer);

                            break;
                        };

                        default: throw std::invalid_argument{ "Invalid resample!" };
                    }
                });

            if (!colorBufferIndices.empty())
            {
                gl::frame_buffer_draw_buffers(m_handle, colorBufferIndices);
            }
            else
            {
                gl::frame_buffer_read_buffer(m_handle, gl::Flags::FrameBuffer::Source::None);
                gl::frame_buffer_draw_buffer(m_handle, gl::Flags::FrameBuffer::Source::None);
            }

            const auto& frameBufferStatus = gl::check_frame_buffer_status(m_handle);
            if (frameBufferStatus != gl::Flags::FrameBuffer::Status::Complete) throw std::runtime_error{ "Framebuffer is not complete!" };
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

            gl::bind_texture(it->second->handle(), slot);
        }

        FrameBuffer& operator=(FrameBuffer&& other) noexcept = default;

    private:
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

            std::vector<gl::enum_t> colorBuffers{};
            std::ranges::for_each(manifests, [&, this](const Manifest& manifest)
                {
                    const auto& [identifier, attachment, resample, blueprint] = manifest;
                    const auto& frameBufferAttachment = gl::map_frame_buffer_attachment(attachment);
                          auto  attachmentIndex       = static_cast<gl::enum_t>(frameBufferAttachment);

                    if (attachment == FrameBuffer::Attachment::Color)
                    {
                        attachmentIndex += static_cast<gl::enum_t>(colorBuffers.size());
                        colorBuffers.emplace_back(attachmentIndex);
                    }

                    switch (resample)
                    {
                    case FrameBuffer::Resample::Yes:
                    {
                        const auto& texture = std::make_shared<texture_t>(blueprint.format, m_dimensions, m_samples);
                        gl::frame_buffer_texture(m_handle, texture->handle(), attachmentIndex, 0);

                        m_identifierToTexture.emplace(identifier, texture);

                        break;
                    };
                    case FrameBuffer::Resample::No:
                    {
                        const auto& renderBuffer = std::make_shared<render_buffer_t>(blueprint.format, m_dimensions, m_samples);
                        gl::frame_buffer_render_buffer(m_handle, renderBuffer->handle(), attachmentIndex);

                        m_identifierToRenderBuffer.emplace(identifier, renderBuffer);

                        break;
                    };

                    default: throw std::invalid_argument{ "Invalid resample!" };
                    }
                });

            if (!colorBuffers.empty())
            {
                gl::frame_buffer_draw_buffers(m_handle, colorBuffers);
            }
            else
            {
                gl::frame_buffer_read_buffer(m_handle, gl::Flags::FrameBuffer::Source::None);
                gl::frame_buffer_draw_buffer(m_handle, gl::Flags::FrameBuffer::Source::None);
            }

            const auto& frameBufferStatus = gl::check_frame_buffer_status(m_handle);
            if (frameBufferStatus != gl::Flags::FrameBuffer::Status::Complete) throw std::runtime_error{ "Framebuffer is not complete!" };
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

            gl::bind_texture(it->second->handle(), slot);
        }

        fox::uint8_t samples() const
        {
            return m_samples;
        }

        FrameBuffer& operator=(FrameBuffer&& other) noexcept = default;

    private:
        fox::uint8_t m_samples{};

        std::unordered_map<std::string, std::shared_ptr<texture_t>>       m_identifierToTexture{};
        std::unordered_map<std::string, std::shared_ptr<render_buffer_t>> m_identifierToRenderBuffer{};
    };
}
