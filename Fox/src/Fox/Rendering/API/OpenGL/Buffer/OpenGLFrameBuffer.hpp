#pragma once

#include "stdafx.hpp"

#include "Fox/Rendering/API/OpenGL/GL.hpp"
#include "Fox/Rendering/API/OpenGL/Texture/OpenGLTexture.hpp"
#include "Fox/Rendering/API/OpenGL/Texture/OpenGLRenderBuffer.hpp"
#include "Fox/Rendering/Buffer/FrameBuffer.hpp"

namespace fox::gfx::api::gl
{
    template<AntiAliasing AA>
    class OpenGLFrameBuffer : public api::FrameBuffer, public gl::Object
    {
    public:
        using texture_t       = OpenGLTexture<Dimensions::_2D, AA>;
        using render_buffer_t = OpenGLRenderBuffer<AA>;

        OpenGLFrameBuffer(const Vector2u& dimensions, std::span<const FrameBuffer::Manifest> manifests)                       requires (AA == AntiAliasing::None)
            : FrameBuffer{ dimensions }
        {
            m_handle = gl::create_frame_buffer();

            bool hasColorBuffer{};
            std::vector<GLenum> colorBuffers{};

            std::ranges::for_each(manifests, [&, this](const FrameBuffer::Manifest& manifest)
                {
                    const auto& [identifier, attachment, resample, blueprint] = manifest;

                    auto glAttachment = gl::map_frame_buffer_attachment(attachment);
                    if (attachment == FrameBuffer::Attachment::Color)
                    {
                        glAttachment += static_cast<GLenum>(colorBuffers.size());
                        colorBuffers.emplace_back(glAttachment);

                        hasColorBuffer = true;
                    }

                    switch (resample)
                    {
                        case FrameBuffer::Resample::Yes: //Bind as texture
                        {
                            const auto& texture = std::make_shared<texture_t>(blueprint.format, blueprint.filter, blueprint.wrapping, m_dimensions);
                            gl::frame_buffer_texture(m_handle, texture->expose_internals().glId, glAttachment, 0);

                            m_identifierToTexture.emplace(identifier, texture);

                            break;
                        };
                        case FrameBuffer::Resample::No: //Bind as renderbuffer
                        {
                            const auto& renderBuffer = std::make_shared<render_buffer_t>(blueprint.format, m_dimensions);
                            gl::frame_buffer_render_buffer(m_handle, renderBuffer->expose_internals().glId, glAttachment);

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
                gl::frame_buffer_read_buffer(m_handle, GL_NONE);
                gl::frame_buffer_draw_buffer(m_handle, GL_NONE);
            }

            const auto& test = gl::check_frame_buffer_status(m_handle);
            if (gl::check_frame_buffer_status(m_handle) != GL_FRAMEBUFFER_COMPLETE) throw std::runtime_error{ "Framebuffer is not complete!" };
        }
        OpenGLFrameBuffer(const Vector2u& dimensions, std::uint8_t samples, std::span<const FrameBuffer::Manifest> manifests) requires (AA == AntiAliasing::MSAA)
            : FrameBuffer{ dimensions }, m_samples{ samples }
        {
            m_handle = gl::create_frame_buffer();

            bool hasColorBuffer{};
            std::vector<GLenum> colorBuffers{};

            std::ranges::for_each(manifests, [&, this](const FrameBuffer::Manifest& manifest)
                {
                    const auto& [identifier, attachment, resample, blueprint] = manifest;

                    auto glAttachment = gl::map_frame_buffer_attachment(attachment);
                    if (attachment == FrameBuffer::Attachment::Color)
                    {
                        glAttachment += static_cast<GLenum>(colorBuffers.size());
                        colorBuffers.emplace_back(glAttachment);

                        hasColorBuffer = true;
                    }

                    switch (resample)
                    {
                        case FrameBuffer::Resample::Yes: //Bind as texture
                        {
                            const auto& texture = std::make_shared<texture_t>(blueprint.format, blueprint.filter, blueprint.wrapping, m_dimensions, m_samples);
                            gl::frame_buffer_texture(m_handle, texture->expose_internals().glId, glAttachment, 0);

                            m_identifierToTexture.emplace(identifier, texture);

                            break;
                        };
                        case FrameBuffer::Resample::No: //Bind as renderbuffer
                        {
                            const auto& renderBuffer = std::make_shared<render_buffer_t>(blueprint.format, m_dimensions, m_samples);
                            gl::frame_buffer_render_buffer(m_handle, renderBuffer->expose_internals().glId, glAttachment);

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
                gl::frame_buffer_read_buffer(m_handle, GL_NONE);
                gl::frame_buffer_draw_buffer(m_handle, GL_NONE);
            }

            if (gl::check_frame_buffer_status(m_handle) != GL_FRAMEBUFFER_COMPLETE) throw std::runtime_error{ "Framebuffer is not complete!" };
        }
        OpenGLFrameBuffer(OpenGLFrameBuffer&& other) noexcept
            : FrameBuffer{ std::move(other.m_dimensions) }
        {
            *this = std::move(other);
        }
        ~OpenGLFrameBuffer()
        {
            gl::delete_frame_buffer(m_handle);
        }

        void bind(FrameBuffer::Target target)
        {
            const auto& glTarget = gl::map_frame_buffer_target(target);
            gl::bind_frame_buffer(m_handle, glTarget);
        }
        void bind_texture(const std::string& identifier, std::uint32_t slot)
        {
            const auto& it = m_identifierToTexture.find(identifier);
            if (it == m_identifierToTexture.end()) throw std::invalid_argument{ "Invalid texture identifier!" };

            gl::bind_texture(it->second->handle(), slot);
        }

        std::uint8_t samples() const
        {
            return m_samples;
        }

        OpenGLFrameBuffer& operator=(OpenGLFrameBuffer&& other) noexcept
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
        std::uint8_t m_samples{};

        std::unordered_map<std::string, std::shared_ptr<texture_t>>       m_identifierToTexture{};
        std::unordered_map<std::string, std::shared_ptr<render_buffer_t>> m_identifierToRenderBuffer{};
    };
}
