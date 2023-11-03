#pragma once

#include "stdafx.hpp"

#include "Helix/Rendering/API/OpenGL/OpenGL.hpp"
#include "Helix/Rendering/API/OpenGL/Texture/OpenGLTexture.hpp"
#include "Helix/Rendering/API/OpenGL/Texture/OpenGLRenderBuffer.hpp"
#include "Helix/Rendering/API/Implementation/GFrameBuffer.hpp"
#include "Helix/Rendering/Buffer/FrameBuffer.hpp"

namespace hlx::gfx::imp::api
{
    template<AntiAliasing AA>
    class GFrameBuffer<gfx::api::GraphicsAPI::OpenGL, AA> final : public gfx::api::FrameBuffer
    {
    public:
        using texture_t       = GTexture<gfx::api::GraphicsAPI::OpenGL, Dimensions::_2D, AA>;
        using render_buffer_t = GRenderBuffer<AA>;

        GFrameBuffer(const Vector2u& dimensions,             std::span<const FrameBuffer::Manifest> manifests) requires (AA == AntiAliasing::None)
            : FrameBuffer{ dimensions }
        {
            m_glId = gl::create_frame_buffer();

            bool hasColorBuffer{};
            std::vector<GLenum> colorBuffers{};

            std::ranges::for_each(manifests, [&, this](const FrameBuffer::Manifest& manifest)
                {
                    const auto& [identifier, blueprint, attachment, resample] = manifest;

                    auto glAttachment = gl::frame_buffer_attachment(attachment);
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
                            gl::frame_buffer_texture(m_glId, texture->id(), glAttachment, 0);

                            m_identifierToTexture.emplace(identifier, texture);

                            break;
                        };
                        case FrameBuffer::Resample::No: //Bind as renderbuffer
                        {
                            const auto& renderBuffer = std::make_shared<render_buffer_t>(blueprint.format, blueprint.filter, blueprint.wrapping, m_dimensions);
                            gl::frame_buffer_render_buffer(m_glId, renderBuffer->id(), glAttachment);

                            m_identifierToRenderBuffer.emplace(identifier, renderBuffer);

                            break;
                        };

                        default: throw std::invalid_argument{ "Invalid resample!" };
                    }
                });

            if (hasColorBuffer)
            {
                gl::frame_buffer_draw_buffers(m_glId, colorBuffers);
            }
            else
            {
                gl::frame_buffer_read_buffer(m_glId, GL_NONE);
                gl::frame_buffer_draw_buffer(m_glId, GL_NONE);
            }

            if (gl::check_frame_buffer_status(m_glId) != GL_FRAMEBUFFER_COMPLETE) throw std::runtime_error{ "Framebuffer is not complete!" };
        }
        GFrameBuffer(const Vector2u& dimensions, u8 samples, std::span<const FrameBuffer::Manifest> manifests) requires (AA == AntiAliasing::MSAA)
            : FrameBuffer{ dimensions }, m_samples{ samples }
        {
            m_glId = gl::create_frame_buffer();

            bool hasColorBuffer{};
            std::vector<GLenum> colorBuffers{};

            std::ranges::for_each(manifests, [&, this](const FrameBuffer::Manifest& manifest)
                {
                    const auto& [identifier, blueprint, attachment, resample] = manifest;

                    auto glAttachment = gl::frame_buffer_attachment(attachment);
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
                            gl::frame_buffer_texture(m_glId, texture->id(), glAttachment, 0);

                            m_identifierToTexture.emplace(identifier, texture);

                            break;
                        };
                        case FrameBuffer::Resample::No: //Bind as renderbuffer
                        {
                            const auto& renderBuffer = std::make_shared<render_buffer_t>(blueprint.format, blueprint.filter, blueprint.wrapping, m_dimensions, m_samples);
                            gl::frame_buffer_render_buffer(m_glId, renderBuffer->id(), glAttachment);

                            m_identifierToRenderBuffer.emplace(identifier, renderBuffer);

                            break;
                        };

                        default: throw std::invalid_argument{ "Invalid resample!" };
                    }
                });

            if (hasColorBuffer)
            {
                gl::frame_buffer_draw_buffers(m_glId, colorBuffers);
            }
            else
            {
                gl::frame_buffer_read_buffer(m_glId, GL_NONE);
                gl::frame_buffer_draw_buffer(m_glId, GL_NONE);
            }

            if (gl::check_frame_buffer_status(m_glId) != GL_FRAMEBUFFER_COMPLETE) throw std::runtime_error{ "Framebuffer is not complete!" };
        }
        ~GFrameBuffer()
        {
            gl::delete_frame_buffer(m_glId);
        }

        void bind(FrameBuffer::Target target)
        {
            gl::bind_frame_buffer(m_glId);
        }
        void bind_texture(const std::string& identifier, u32 slot)
        {
            const auto& it = m_identifierToTexture.find(identifier);
            if (it == m_identifierToTexture.end()) throw std::invalid_argument{ "Invalid texture identifier!" };

            gl::bind_texture(it->second->id(), slot);
        }

        u8     samples() const
        {
            return m_samples;
        }

    private:
        GLuint m_glId{};
        u8     m_samples{};

        std::unordered_map<std::string, std::shared_ptr<texture_t>>       m_identifierToTexture{};
        std::unordered_map<std::string, std::shared_ptr<render_buffer_t>> m_identifierToRenderBuffer{};
    };
}
