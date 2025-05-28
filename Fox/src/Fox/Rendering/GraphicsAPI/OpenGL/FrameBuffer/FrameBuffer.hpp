#pragma once

#include "stdafx.hpp"

#include "Fox/Rendering/API/FrameBuffer/FrameBuffer.hpp"
#include "Fox/Rendering/GraphicsAPI/OpenGL/OpenGL.hpp"
#include "Fox/Rendering/GraphicsAPI/OpenGL/RenderBuffer/RenderBuffer.hpp"
#include "Fox/Rendering/GraphicsAPI/OpenGL/Texture/Cubemap.hpp"
#include "Fox/Rendering/GraphicsAPI/OpenGL/Texture/Texture.hpp"

#include "Fox/Rendering/API/FrameBuffer/Mapping.hpp" //remove

namespace fox::gfx::api::gl
{
    class FrameBuffer : public gl::Object
    {
    public:
        using Target        = api::FrameBuffer::Target;
        using Attachment    = api::FrameBuffer::Attachment;
        using Specification = api::FrameBuffer::Specification;

        FrameBuffer(const gl::Vector2u& dimensions, std::span<const Specification> specifications)
            : m_dimensions{ dimensions }
        {
            m_handle = gl::create_frame_buffer();

            std::vector<glf::FrameBuffer::Attachment> colorBufferIndices{};

            for (const auto& specification : specifications)
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
            }

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
        ~FrameBuffer()
        {
            gl::delete_frame_buffer(m_handle);
        }

        void bind(Target target)
        {
            gl::bind_frame_buffer(m_handle, gl::map_frame_buffer_target(target));
        }

        void bind_texture(const std::string& identifier, gl::binding_t binding)
        {
            const auto& it = m_identifierToTextureMap.find(identifier);
            if (it == m_identifierToTextureMap.end()) throw std::invalid_argument{ "Invalid texture identifier!" };

            gl::bind_texture_unit(it->second->handle(), binding);
        }
        void bind_cubemap(const std::string& identifier, gl::binding_t binding)
        {
            const auto& it = m_identifierToCubemapMap.find(identifier);
            if (it == m_identifierToCubemapMap.end()) throw std::invalid_argument{ "Invalid texture identifier!" };

            gl::bind_texture_unit(it->second->handle(), binding);
        }

        auto find_texture      (const std::string& identifier)
        {
            return m_identifierToTextureMap.find(identifier)->second;
        }
        auto find_cubemap      (const std::string& identifier)
        {
            return m_identifierToCubemapMap.find(identifier)->second;
        }
        auto find_render_buffer(const std::string& identifier)
        {
            return m_identifierToRenderBufferMap.find(identifier)->second;
        }

        auto dimensions() const
        {
            return m_dimensions;
        }

    private:
        void attach(const std::string& identifier, api::Texture::Format      format, std::vector<glf::FrameBuffer::Attachment>& colorBufferIndices)
        {
            auto textureAttachment     = api::map_frame_buffer_texture_attachment(format);
            auto frameBufferAttachment = gl ::map_frame_buffer_attachment        (textureAttachment);

            if (textureAttachment == Attachment::Color)
            {
                frameBufferAttachment += static_cast<glf::FrameBuffer::Attachment>(colorBufferIndices.size());
                colorBufferIndices.emplace_back(frameBufferAttachment);
            }

            const auto& texture = std::make_shared<gl::Texture2D>(format, api::Texture::Filter::None, api::Texture::Wrapping::Repeat, m_dimensions);
            gl::frame_buffer_texture(m_handle, texture->handle(), frameBufferAttachment, gl::uint32_t{ 0u });

            m_identifierToTextureMap.emplace(identifier, texture);
        }
        void attach(const std::string& identifier, api::Cubemap::Format      format, std::vector<glf::FrameBuffer::Attachment>& colorBufferIndices)
        {
            auto cubemapAttachment     = api::map_frame_buffer_cubemap_attachment(format);
            auto frameBufferAttachment = gl::map_frame_buffer_attachment(cubemapAttachment);

            if (cubemapAttachment == Attachment::Color)
            {
                frameBufferAttachment += static_cast<glf::FrameBuffer::Attachment>(colorBufferIndices.size());
                colorBufferIndices.emplace_back(frameBufferAttachment);
            }

            const auto& cubemap = std::make_shared<gl::Cubemap>(format, api::Texture::Filter::None, api::Texture::Wrapping::Repeat, m_dimensions);
            gl::frame_buffer_texture(m_handle, cubemap->handle(), frameBufferAttachment, gl::uint32_t{ 0u });

            m_identifierToCubemapMap.emplace(identifier, cubemap);
        }
        void attach(const std::string& identifier, api::RenderBuffer::Format format, std::vector<glf::FrameBuffer::Attachment>& colorBufferIndices)
        {
            auto renderBufferAttachment = api::map_frame_buffer_render_buffer_attachment(format);
            auto frameBufferAttachment  = gl::map_frame_buffer_attachment(renderBufferAttachment);

            if (renderBufferAttachment == Attachment::Color)
            {
                frameBufferAttachment += static_cast<glf::FrameBuffer::Attachment>(colorBufferIndices.size());
                colorBufferIndices.emplace_back(frameBufferAttachment);
            }

            const auto& renderBuffer = std::make_shared<gl::RenderBuffer>(format, m_dimensions);
            gl::frame_buffer_render_buffer(m_handle, renderBuffer->handle(), frameBufferAttachment);

            m_identifierToRenderBufferMap.emplace(identifier, renderBuffer);
        }

        gl::Vector2u                                                       m_dimensions{};
        std::unordered_map<std::string, std::shared_ptr<gl::Texture2D>>    m_identifierToTextureMap{};
        std::unordered_map<std::string, std::shared_ptr<gl::RenderBuffer>> m_identifierToRenderBufferMap{};
        std::unordered_map<std::string, std::shared_ptr<gl::Cubemap>>      m_identifierToCubemapMap{};
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

        auto find_texture      (const std::string& identifier)
        {
            return m_identifierToTexture.find(identifier)->second;
        }
        auto find_render_buffer(const std::string& identifier)
        {
            return m_identifierToRenderBuffer.find(identifier)->second;
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
            const auto& textureAttachment     = api::map_frame_buffer_texture_attachment(format);
            const auto& frameBufferAttachment = gl::map_frame_buffer_attachment(textureAttachment);
                  auto  attachmentIndex       = frameBufferAttachment;

            if (textureAttachment == Attachment::Color)
            {
                attachmentIndex += static_cast<glf::FrameBuffer::Attachment>(colorBufferIndices.size());
                colorBufferIndices.emplace_back(attachmentIndex);
            }

            const auto& texture = std::make_shared<gl::Texture2DMultisample>(format, m_dimensions, m_samples);
            gl::frame_buffer_texture(m_handle, texture->handle(), attachmentIndex, gl::uint32_t{ 0u });

            m_identifierToTexture.emplace(identifier, texture);
        }
        void attach(std::string_view identifier, api::Cubemap::Format      format, std::vector<glf::FrameBuffer::Attachment>& colorBufferIndices)
        {
            throw std::logic_error{ "The method or operation has not been implemented!" };
        }
        void attach(std::string_view identifier, api::RenderBuffer::Format format, std::vector<glf::FrameBuffer::Attachment>& colorBufferIndices)
        {
            const auto& renderBufferAttachment = api::map_frame_buffer_render_buffer_attachment(format);
            const auto& frameBufferAttachment  = gl::map_frame_buffer_attachment(renderBufferAttachment);
                  auto  attachmentIndex        = frameBufferAttachment;

            if (renderBufferAttachment == Attachment::Color)
            {
                attachmentIndex += static_cast<glf::FrameBuffer::Attachment>(colorBufferIndices.size());
                colorBufferIndices.emplace_back(attachmentIndex);
            }

            const auto& renderBuffer = std::make_shared<gl::RenderBufferMultisample>(format, m_dimensions, m_samples);
            gl::frame_buffer_render_buffer(m_handle, renderBuffer->handle(), attachmentIndex);

            m_identifierToRenderBuffer.emplace(identifier, renderBuffer);
        }

        gl::Vector2u                                                                  m_dimensions{};
        gl::uint32_t                                                                  m_samples{};
        std::unordered_map<std::string, std::shared_ptr<gl::Texture2DMultisample>>    m_identifierToTexture{};
        std::unordered_map<std::string, std::shared_ptr<gl::RenderBufferMultisample>> m_identifierToRenderBuffer{};
    };
}
