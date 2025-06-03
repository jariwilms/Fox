#pragma once

#include "stdafx.hpp"

#include "Fox/Rendering/API/FrameBuffer/FrameBuffer.hpp"
#include "Fox/Rendering/GraphicsAPI/OpenGL/OpenGL.hpp"
#include "Fox/Rendering/GraphicsAPI/OpenGL/RenderBuffer/RenderBuffer.hpp"
#include "Fox/Rendering/GraphicsAPI/OpenGL/Texture/Cubemap.hpp"
#include "Fox/Rendering/GraphicsAPI/OpenGL/Texture/Texture.hpp"

namespace fox::gfx::api::gl
{
    class FrameBuffer : public gl::Object
    {
    public:
        using Attachment    = api::FrameBuffer::Attachment;
        using Specification = api::FrameBuffer::Specification;
        using Surface       = api::FrameBuffer::Surface;
        using Target        = api::FrameBuffer::Target;

         FrameBuffer() = default;
         FrameBuffer(const gl::Vector2u& dimensions, std::span<const Specification> specifications)
            : m_dimensions{ dimensions }
        {
            m_handle = gl::create_frame_buffer();

            for (const auto& specification : specifications)
            {
                const auto& [identifier, format] = specification;

                if (std::holds_alternative<api::Texture::Format>     (format))
                {
                    auto texture = std::make_shared<gl::Texture2D>(std::get<api::Texture::Format>(format), api::Texture::Filter::None, api::Texture::Wrapping::Repeat, m_dimensions);
                    attach(identifier, texture);
                }
                if (std::holds_alternative<api::Cubemap::Format>     (format))
                {
                    auto cubemap = std::make_shared<gl::Cubemap>(std::get<api::Cubemap::Format>(format), api::Texture::Filter::None, api::Texture::Wrapping::Repeat, m_dimensions);
                    attach(identifier, cubemap);
                }
                if (std::holds_alternative<api::RenderBuffer::Format>(format))
                {
                    auto renderBuffer = std::make_shared<gl::RenderBuffer>(std::get<api::RenderBuffer::Format>(format), m_dimensions);
                    attach(identifier, renderBuffer);
                }
            }

            if (m_colorBufferIndices.empty())
            {
                gl::frame_buffer_read_buffer(m_handle, glf::FrameBuffer::Source::None);
                gl::frame_buffer_draw_buffer(m_handle, glf::FrameBuffer::Source::None);
            }
            else
            {
                std::vector<glf::FrameBuffer::Source> colorBufferSources(m_colorBufferIndices.size());
                std::transform(m_colorBufferIndices.begin(), m_colorBufferIndices.end(), colorBufferSources.begin(), [](const auto& _)
                    {
                        return static_cast<glf::FrameBuffer::Source>(_);
                    });

                gl::frame_buffer_draw_buffers(m_handle, colorBufferSources);
            }

            if (gl::check_frame_buffer_status(m_handle) != glf::FrameBuffer::Status::Complete) throw std::runtime_error{ "Framebuffer is not complete!" };
        }
        ~FrameBuffer()
        {
            gl::delete_frame_buffer(m_handle);
        }

        void bind(Target target)
        {
            gl::bind_frame_buffer(m_handle, gl::map_frame_buffer_target(target));
        }

        template<Surface A = Surface::Texture>
        auto surface(const std::string& identifier)
        {
                 if constexpr (A == Surface::Texture)
            {
                return m_textureMap.at(identifier);
            }
            else if constexpr (A == Surface::Cubemap)
            {
                return m_cubemapMap.at(identifier);
            }
            else if constexpr (A == Surface::RenderBuffer)
            {
                return m_renderBufferMap.at(identifier);
            }
        }

        template<Surface A = Surface::Texture>
        void bind_surface(const std::string& identifier, gl::binding_t binding)
        {
            if constexpr (A == Surface::Texture)
            {
                m_textureMap.at(identifier)->bind(binding);
            }
            if constexpr (A == Surface::Cubemap)
            {
                m_cubemapMap.at(identifier)->bind(binding);
            }
        }

        void attach(const std::string& identifier, std::shared_ptr<gl::Texture2D>    texture)
        {
            auto attachment = gl::map_frame_buffer_texture_attachment(texture->format());

            if (attachment == glf::FrameBuffer::Attachment::ColorIndex)
            {
                attachment += static_cast<glf::FrameBuffer::Attachment>(m_colorBufferIndices.size());
                m_colorBufferIndices.emplace_back(attachment);
            }

            gl::frame_buffer_texture(m_handle, texture->handle(), attachment, gl::uint32_t{ 0u });
            m_textureMap.emplace(identifier, texture);
        }
        void attach(const std::string& identifier, std::shared_ptr<gl::Cubemap>      cubemap)
        {
            auto attachment = gl::map_frame_buffer_cubemap_attachment(cubemap->format());

            if (attachment == glf::FrameBuffer::Attachment::ColorIndex)
            {
                attachment += static_cast<glf::FrameBuffer::Attachment>(m_colorBufferIndices.size());
                m_colorBufferIndices.emplace_back(attachment);
            }

            gl::frame_buffer_texture(m_handle, cubemap->handle(), attachment, gl::uint32_t{ 0u });
            m_cubemapMap.emplace(identifier, cubemap);
        }
        void attach(const std::string& identifier, std::shared_ptr<gl::RenderBuffer> renderBuffer)
        {
            auto attachment = gl::map_frame_buffer_render_buffer_attachment(renderBuffer->format());

            if (attachment == glf::FrameBuffer::Attachment::ColorIndex)
            {
                attachment += static_cast<glf::FrameBuffer::Attachment>(m_colorBufferIndices.size());
                m_colorBufferIndices.emplace_back(attachment);
            }

            gl::frame_buffer_render_buffer(m_handle, renderBuffer->handle(), attachment);
            m_renderBufferMap.emplace(identifier, renderBuffer);
        }



        void attach_test2(const std::string& identifier, Attachment attachment, std::shared_ptr<gl::Texture2D> texture, gl::uint32_t level = 0u)
        {
            gl::frame_buffer_texture(m_handle, texture->handle(), gl::map_frame_buffer_attachment(attachment), level);

            m_attachments.at(gl::to_underlying(attachment)) = identifier;
            m_textureMap.emplace(identifier, texture);
        }

        template<Surface A = Surface::Texture>
        void detach(const std::string& identifier, glf::FrameBuffer::Attachment attachment)
        {
            auto isColor = (attachment == std::clamp(attachment, glf::FrameBuffer::Attachment::ColorIndex, glf::FrameBuffer::Attachment::ColorIndex + 31u));
            if (isColor) attachment -= glf::FrameBuffer::Attachment::ColorIndex;

                 if constexpr (A == Surface::Texture)
            {
                gl::frame_buffer_texture(m_handle, gl::NullObject, attachment, gl::uint32_t{ 0u });
                m_textureMap.erase(identifier);
            }
            else if constexpr (A == Surface::Cubemap)
            {
                gl::frame_buffer_texture(m_handle, gl::NullObject, attachment, gl::uint32_t{ 0u });
                m_cubemapMap.erase(identifier);
            }
            else if constexpr (A == Surface::RenderBuffer)
            {
                gl::frame_buffer_render_buffer(m_handle, gl::NullObject, attachment, gl::uint32_t{ 0u });
                m_renderBufferMap.erase(identifier);
            }
        }



        void read_from(const std::string& identifier, gl::index_t index, gl::uint32_t level = 0u)
        {
            auto texture = surface<Surface::Texture>(identifier);

            gl::frame_buffer_texture    (m_handle, texture->handle(), glf::FrameBuffer::Attachment::ColorIndex + index, level);
            gl::frame_buffer_read_buffer(m_handle, glf::FrameBuffer::Source::ColorIndex + index);
        }
        void write_to (const std::string& identifier, gl::index_t index, gl::uint32_t level = 0u)
        {
            auto texture = surface<Surface::Texture>(identifier);

            gl::frame_buffer_texture    (m_handle, texture->handle(), glf::FrameBuffer::Attachment::ColorIndex + index, level);
            gl::frame_buffer_draw_buffer(m_handle, glf::FrameBuffer::Source::ColorIndex + index);
        }

        void resize(const gl::Vector2u& dimensions)
        {
            for (const auto& [identifier, texture]      : m_textureMap)
            {
                texture->resize(dimensions);
            }
            for (const auto& [identifier, renderBuffer] : m_renderBufferMap)
            {
                renderBuffer->resize(dimensions);
            }

            m_dimensions = dimensions;
        }

        auto dimensions() const
        {
            return m_dimensions;
        }

    private:

        gl::Vector2u                                                                          m_dimensions{};

        std::vector<glf::FrameBuffer::Attachment>                                             m_colorBufferIndices{};
        std::array<std::string, 11u>                                                          m_attachments{};
        std::unordered_map<std::string, std::shared_ptr<gl::Texture2D>>                       m_textureMap{};
        std::unordered_map<std::string, std::shared_ptr<gl::Cubemap>>                         m_cubemapMap{};
        std::unordered_map<std::string, std::shared_ptr<gl::RenderBuffer>>                    m_renderBufferMap{};
    };
    class FrameBufferMultisample : public gl::Object
    {
    public:
        using Target        = api::FrameBuffer::Target;
        using Attachment    = api::FrameBuffer::Attachment;
        using Specification = api::FrameBuffer::Specification;

         FrameBufferMultisample(const gl::Vector2u& dimensions, std::span<const Specification> specifications, fox::uint32_t samples)
            : m_dimensions{ dimensions }, m_samples{ samples }
        {
            m_handle = gl::create_frame_buffer();

            std::vector<glf::FrameBuffer::Attachment> colorBufferIndices{};
            std::ranges::for_each(specifications, [&, this](const auto& specification)
                {
                    const auto& [identifier, format] = specification;

                    if (std::holds_alternative<api::Texture::Format>     (format))
                    {
                        const auto& v = std::get<api::Texture::Format>(format);
                        attach(identifier, v, colorBufferIndices);
                    }
                    if (std::holds_alternative<api::Cubemap::Format>     (format))
                    {
                        const auto& v = std::get<api::Cubemap::Format>(format);
                        attach(identifier, v, colorBufferIndices);
                    }
                    if (std::holds_alternative<api::RenderBuffer::Format>(format))
                    {
                        const auto& v = std::get<api::RenderBuffer::Format>(format);
                        attach(identifier, v, colorBufferIndices);
                    }
                });

            if (colorBufferIndices.empty())
            {
                gl::frame_buffer_read_buffer(m_handle, glf::FrameBuffer::Source::None);
                gl::frame_buffer_draw_buffer(m_handle, glf::FrameBuffer::Source::None);
            }
            else
            {
                std::vector<glf::FrameBuffer::Source> colorBufferSources(colorBufferIndices.size());
                std::transform(colorBufferIndices.begin(), colorBufferIndices.end(), colorBufferSources.begin(), [](const auto& _)
                    {
                        return static_cast<glf::FrameBuffer::Source>(_);
                    });

                gl::frame_buffer_draw_buffers(m_handle, colorBufferSources);
            }

            if (gl::check_frame_buffer_status(m_handle) != glf::FrameBuffer::Status::Complete) throw std::runtime_error{ "Framebuffer is not complete!" };
        }
        ~FrameBufferMultisample()
        {
            gl::delete_frame_buffer(m_handle);
        }

        void bind(Target target)
        {
            gl::bind_frame_buffer(m_handle, gl::map_frame_buffer_target(target));
        }
        
        void bind_texture(const std::string& identifier, gl::binding_t binding)
        {
            const auto& it = m_identifierToTexture.find(identifier);
            if (it == m_identifierToTexture.end()) throw std::invalid_argument{ "Invalid texture identifier!" };

            gl::bind_texture_unit(it->second->handle(), binding);
        }

        auto dimensions() const
        {
            return m_dimensions;
        }
        auto samples   () const
        {
            return m_samples;
        }

    private:
        void attach(std::string_view identifier, api::Texture::Format      format, std::vector<glf::FrameBuffer::Attachment>& colorBufferIndices)
        {
            //const auto& textureAttachment     = api::map_frame_buffer_texture_attachment(format);
            //const auto& frameBufferAttachment = gl::map_frame_buffer_attachment(textureAttachment);
            //      auto  attachmentIndex       = frameBufferAttachment;

            //if (textureAttachment == Attachment::Color)
            //{
            //    attachmentIndex += static_cast<glf::FrameBuffer::Attachment>(colorBufferIndices.size());
            //    colorBufferIndices.emplace_back(attachmentIndex);
            //}

            //const auto& texture = std::make_shared<gl::Texture2DMultisample>(format, m_dimensions, m_samples);
            //gl::frame_buffer_texture(m_handle, texture->handle(), attachmentIndex, gl::uint32_t{ 0u });

            //m_identifierToTexture.emplace(identifier, texture);
        }
        void attach(std::string_view identifier, api::Cubemap::Format      format, std::vector<glf::FrameBuffer::Attachment>& colorBufferIndices)
        {
            throw std::logic_error{ "The method or operation has not been implemented!" };
        }
        void attach(std::string_view identifier, api::RenderBuffer::Format format, std::vector<glf::FrameBuffer::Attachment>& colorBufferIndices)
        {
            //const auto& renderBufferAttachment = api::map_frame_buffer_render_buffer_attachment(format);
            //const auto& frameBufferAttachment  = gl::map_frame_buffer_attachment(renderBufferAttachment);
            //      auto  attachmentIndex        = frameBufferAttachment;

            //if (renderBufferAttachment == Attachment::Color)
            //{
            //    attachmentIndex += static_cast<glf::FrameBuffer::Attachment>(colorBufferIndices.size());
            //    colorBufferIndices.emplace_back(attachmentIndex);
            //}

            //const auto& renderBuffer = std::make_shared<gl::RenderBufferMultisample>(format, m_dimensions, m_samples);
            //gl::frame_buffer_render_buffer(m_handle, renderBuffer->handle(), attachmentIndex);

            //m_identifierToRenderBuffer.emplace(identifier, renderBuffer);
        }

        gl::Vector2u                                                                  m_dimensions{};
        gl::uint32_t                                                                  m_samples{};
        std::unordered_map<std::string, std::shared_ptr<gl::Texture2DMultisample>>    m_identifierToTexture{};
        std::unordered_map<std::string, std::shared_ptr<gl::RenderBufferMultisample>> m_identifierToRenderBuffer{};
    };
}
