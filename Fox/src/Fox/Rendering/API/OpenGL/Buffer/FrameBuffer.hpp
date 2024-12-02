#pragma once

#include "stdafx.hpp"

#include "Fox/Rendering/API/OpenGL/OpenGL.hpp"
#include "Fox/Rendering/API/OpenGL/Texture/Texture.hpp"
#include "Fox/Rendering/API/OpenGL/Texture/RenderBuffer.hpp"
#include "Fox/Rendering/Buffer/FrameBuffer.hpp"

namespace fox::gfx::api::gl
{
    template<AntiAliasing AA>
    class FrameBuffer : public api::FrameBuffer, public gl::Object
    {
    public:
        using texture_t       = gl::Texture<Dimensions::_2D, AA>;
        using render_buffer_t = gl::RenderBuffer<AA>;

        FrameBuffer(const fox::Vector2u& dimensions, std::span<const Manifest> manifests)                       requires (AA == AntiAliasing::None)
            : api::FrameBuffer{ dimensions }
        {
            m_handle = gl::create_frame_buffer();

            bool hasColorBuffer{};
            std::vector<gl::enum_t> colorBuffers{};

            std::ranges::for_each(manifests, [&, this](const Manifest& manifest)
                {
                    const auto& [identifier, attachment, resample, blueprint] = manifest;

                    auto bufferAttachment = static_cast<gl::enum_t>(gl::map_frame_buffer_attachment(attachment));
                    if (attachment == Attachment::Color)
                    {
                        bufferAttachment += static_cast<gl::enum_t>(colorBuffers.size());
                        colorBuffers.emplace_back(bufferAttachment);

                        hasColorBuffer = true;
                    }

                    switch (resample)
                    {
                        case FrameBuffer::Resample::Yes: //Bind as texture
                        {
                            const auto& texture = std::make_shared<texture_t>(blueprint.format, blueprint.filter, blueprint.wrapping, m_dimensions);
                            gl::frame_buffer_texture(m_handle, texture->handle(), bufferAttachment, 0);

                            m_identifierToTexture.emplace(identifier, texture);

                            break;
                        };
                        case FrameBuffer::Resample::No: //Bind as renderbuffer
                        {
                            const auto& renderBuffer = std::make_shared<render_buffer_t>(blueprint.format, m_dimensions);
                            gl::frame_buffer_render_buffer(m_handle, renderBuffer->handle(), bufferAttachment);

                            m_identifierToRenderBuffer.emplace(identifier, renderBuffer);

                            break;
                        };

                        default: throw std::invalid_argument{ "Invalid resample!" };
                    }
                });

            if (hasColorBuffer)
            {
                gl::frame_buffer_draw_buffers(m_handle, colorBuffers);
            }
            else
            {
                gl::frame_buffer_read_buffer(m_handle, gl::Flags::FrameBuffer::Source::None);
                gl::frame_buffer_draw_buffer(m_handle, gl::Flags::FrameBuffer::Source::None);
            }

            const auto& frameBufferStatus = gl::check_frame_buffer_status(m_handle);
            if (gl::check_frame_buffer_status(m_handle) != gl::Flags::FrameBuffer::Status::Complete) throw std::runtime_error{ "Framebuffer is not complete!" };
        }
        FrameBuffer(const fox::Vector2u& dimensions, fox::uint8_t samples, std::span<const Manifest> manifests) requires (AA == AntiAliasing::MSAA)
            : api::FrameBuffer{ dimensions }, m_samples{ samples }
        {
            m_handle = gl::create_frame_buffer();

            bool hasColorBuffer{};
            std::vector<gl::enum_t> colorBuffers{};

            std::ranges::for_each(manifests, [&, this](const Manifest& manifest)
                {
                    const auto& [identifier, attachment, resample, blueprint] = manifest;
                    
                    auto frameBufferAttachment = static_cast<gl::enum_t>(gl::map_frame_buffer_attachment(attachment));
                    if (attachment == FrameBuffer::Attachment::Color)
                    {
                        frameBufferAttachment += static_cast<gl::enum_t>(colorBuffers.size());
                        colorBuffers.emplace_back(frameBufferAttachment);

                        hasColorBuffer = true;
                    }

                    switch (resample)
                    {
                        case FrameBuffer::Resample::Yes: //Bind as texture
                        {
                            const auto& texture = std::make_shared<texture_t>(blueprint.format, blueprint.filter, blueprint.wrapping, m_dimensions, m_samples);
                            gl::frame_buffer_texture(m_handle, texture->handle(), frameBufferAttachment, 0);

                            m_identifierToTexture.emplace(identifier, texture);

                            break;
                        };
                        case FrameBuffer::Resample::No: //Bind as renderbuffer
                        {
                            const auto& renderBuffer = std::make_shared<render_buffer_t>(blueprint.format, m_dimensions, m_samples);
                            gl::frame_buffer_render_buffer(m_handle, renderBuffer->handle(), frameBufferAttachment);

                            m_identifierToRenderBuffer.emplace(identifier, renderBuffer);

                            break;
                        };

                        default: throw std::invalid_argument{ "Invalid resample!" };
                    }
                });

            if (hasColorBuffer)
            {
                gl::frame_buffer_draw_buffers(m_handle, colorBuffers);
            }
            else
            {
                gl::frame_buffer_read_buffer(m_handle, gl::Flags::FrameBuffer::Source::None);
                gl::frame_buffer_draw_buffer(m_handle, gl::Flags::FrameBuffer::Source::None);
            }

            if (gl::check_frame_buffer_status(m_handle) != gl::Flags::FrameBuffer::Status::Complete) throw std::runtime_error{"Framebuffer is not complete!"};
        }
        FrameBuffer(FrameBuffer&& other) noexcept
            : FrameBuffer{ std::move(other.m_dimensions) }
        {
            *this = std::move(other);
        }
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

        FrameBuffer& operator=(FrameBuffer&& other) noexcept
        {
            m_handle                   = other.m_handle;
            m_samples                  = other.m_samples;
            m_identifierToTexture      = std::move(other.m_identifierToTexture);
            m_identifierToRenderBuffer = std::move(other.m_identifierToRenderBuffer);

            other.m_handle  = {};
            other.m_samples = 0u;
            
            return *this;
        }

    private:
        fox::uint8_t m_samples{};

        std::unordered_map<std::string, std::shared_ptr<texture_t>>       m_identifierToTexture{};
        std::unordered_map<std::string, std::shared_ptr<render_buffer_t>> m_identifierToRenderBuffer{};
    };
}
