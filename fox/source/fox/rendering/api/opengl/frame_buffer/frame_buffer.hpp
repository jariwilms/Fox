#pragma once

#include <stdafx.hpp>

#include <fox/rendering/api/opengl/opengl.hpp>
#include <fox/rendering/api/opengl/render_buffer/render_buffer.hpp>
#include <fox/rendering/api/opengl/texture/cubemap.hpp>
#include <fox/rendering/api/opengl/texture/texture.hpp>
#include <fox/rendering/base/frame_buffer/frame_buffer.hpp>

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
            : dimensions_{ dimensions }
        {
            handle_ = gl::create_frame_buffer();
			auto colorIndex = gl::uint32_t{ 0u };

            const auto& map_texture_attachment       = [&colorIndex](api::Texture::Format      format)
                {
                    switch (format)
                    {
                        case api::Texture::Format::D16_UNORM:
			            case api::Texture::Format::D24_UNORM:
			            case api::Texture::Format::D32_FLOAT:         return api::FrameBuffer::Attachment::Depth;

			            case api::Texture::Format::D24_UNORM_S8_UINT:
			            case api::Texture::Format::D32_FLOAT_S8_UINT: return api::FrameBuffer::Attachment::DepthStencil;

			            case api::Texture::Format::S8_UINT:           return api::FrameBuffer::Attachment::Stencil;

			            default:                                      return api::FrameBuffer::Attachment::Color0 + colorIndex++;
                    }
                };
            const auto& map_cubemap_attachment       = [&colorIndex](api::Cubemap::Format      format)
            {
                switch (format)
                {
                    case api::Cubemap::Format::D16_UNORM:
                    case api::Cubemap::Format::D24_UNORM:
                    case api::Cubemap::Format::D32_FLOAT:         return api::FrameBuffer::Attachment::Depth;

                    case api::Cubemap::Format::D24_UNORM_S8_UINT:
                    case api::Cubemap::Format::D32_FLOAT_S8_UINT: return api::FrameBuffer::Attachment::DepthStencil;

                    case api::Cubemap::Format::S8_UINT:           return api::FrameBuffer::Attachment::Stencil;

                    default:                                      return api::FrameBuffer::Attachment::Color0 + colorIndex++;
                }
            };
            const auto& map_render_buffer_attachment = [&colorIndex](api::RenderBuffer::Format format)
            {
                switch (format)
                {
                    case api::RenderBuffer::Format::D16_UNORM:
                    case api::RenderBuffer::Format::D24_UNORM:
                    case api::RenderBuffer::Format::D32_FLOAT:         return api::FrameBuffer::Attachment::Depth;

                    case api::RenderBuffer::Format::D24_UNORM_S8_UINT:
                    case api::RenderBuffer::Format::D32_FLOAT_S8_UINT: return api::FrameBuffer::Attachment::DepthStencil;

                    case api::RenderBuffer::Format::S8_UINT:           return api::FrameBuffer::Attachment::Stencil;

                    default:                                           return api::FrameBuffer::Attachment::Color0 + colorIndex++;
                }
            };

            for (const auto& specification : specifications)
            {
                const auto& [identifier, format] = specification;

                if (std::holds_alternative<api::Texture::Format>     (format))
                {
                    auto texture    = std::make_shared<gl::Texture2D>(std::get<api::Texture::Format>(format), api::Texture::Filter::None, api::Texture::Wrapping::Repeat, dimensions_);
                    auto attachment = map_texture_attachment(texture->format());
                    
                    attach(identifier, attachment, texture);
                }
                if (std::holds_alternative<api::Cubemap::Format>     (format))
                {
                    auto cubemap    = std::make_shared<gl::Cubemap>(std::get<api::Cubemap::Format>(format), api::Texture::Filter::None, api::Texture::Wrapping::Repeat, dimensions_);
                    auto attachment = map_cubemap_attachment(cubemap->format());

                    attach(identifier, attachment, cubemap);
                }
                if (std::holds_alternative<api::RenderBuffer::Format>(format))
                {
                    auto renderBuffer = std::make_shared<gl::RenderBuffer>(std::get<api::RenderBuffer::Format>(format), dimensions_);
                    auto attachment   = map_render_buffer_attachment(renderBuffer->format());

                    attach(identifier, attachment, renderBuffer);
                }
            }
            
            if (colorIndex == 0u)
            {
                gl::frame_buffer_read_buffer(handle_, glf::FrameBuffer::Source::None);
                gl::frame_buffer_draw_buffer(handle_, glf::FrameBuffer::Source::None);
            }
            else
            {
                std::vector<glf::FrameBuffer::Source> colorBufferSources(colorIndex);
                for (auto i : std::views::iota(0u, colorIndex))
                {
					colorBufferSources.at(i) = glf::FrameBuffer::Source::Color0 + i;
				}

                gl::frame_buffer_draw_buffers(handle_, colorBufferSources);
            }

            if (gl::check_frame_buffer_status(handle_) != glf::FrameBuffer::Status::Complete) throw std::runtime_error{ "Framebuffer is not complete!" };
        }
        ~FrameBuffer()
        {
            gl::delete_frame_buffer(handle_);
        }

        void bind(Target target)
        {
            gl::bind_frame_buffer(handle_, gl::map_frame_buffer_target(target));
        }
        template<Surface A = Surface::Texture>
        void bind_surface(const std::string& identifier, gl::binding_t binding)
        {
            if constexpr (A == Surface::Texture)
            {
                textureMap_.at(identifier)->bind(binding);
            }
            if constexpr (A == Surface::Cubemap)
            {
                cubemapMap_.at(identifier)->bind(binding);
            }
        }

        void attach(const std::string& identifier, Attachment attachment, std::shared_ptr<gl::Texture2D>    texture, gl::uint32_t level = 0u)
        {
            gl::frame_buffer_texture(handle_, texture->handle(), gl::map_frame_buffer_attachment(attachment), level);

            attachments_.at(gl::to_underlying(attachment)) = identifier;
            textureMap_.emplace(identifier, texture);
        }
        void attach(const std::string& identifier, Attachment attachment, std::shared_ptr<gl::Cubemap>      cubemap, gl::uint32_t level = 0u)
        {
            gl::frame_buffer_texture(handle_, cubemap->handle(), gl::map_frame_buffer_attachment(attachment), level);

            attachments_.at(gl::to_underlying(attachment)) = identifier;
            cubemapMap_.emplace(identifier, cubemap);
        }
        void attach(const std::string& identifier, Attachment attachment, std::shared_ptr<gl::RenderBuffer> renderBuffer)
        {
            gl::frame_buffer_render_buffer(handle_, renderBuffer->handle(), gl::map_frame_buffer_attachment(attachment));

            attachments_.at(gl::to_underlying(attachment)) = identifier;
            renderBufferMap_.emplace(identifier, renderBuffer);
        }
        
        template<Surface A = Surface::Texture>
        void detach(const std::string& identifier, Attachment attachment)
        {
                 if constexpr (A == Surface::Texture)
            {
                gl::frame_buffer_texture(handle_, gl::NullObject, gl::map_frame_buffer_attachment(attachment), gl::uint32_t{ 0u });
                textureMap_.erase(identifier);
            }
            else if constexpr (A == Surface::Cubemap)
            {
                gl::frame_buffer_texture(handle_, gl::NullObject, gl::map_frame_buffer_attachment(attachment), gl::uint32_t{ 0u });
                cubemapMap_.erase(identifier);
            }
            else if constexpr (A == Surface::RenderBuffer)
            {
                gl::frame_buffer_render_buffer(handle_, gl::NullObject, gl::map_frame_buffer_attachment(attachment), gl::uint32_t{ 0u });
                renderBufferMap_.erase(identifier);
            }
        }
        
        void read_from(const std::string& identifier, gl::index_t index, gl::uint32_t level = 0u)
        {
            auto& texture = textureMap_.at(identifier);

            gl::frame_buffer_texture    (handle_, texture->handle(), glf::FrameBuffer::Attachment::Color0 + index, level);
            gl::frame_buffer_read_buffer(handle_, glf::FrameBuffer::Source::Color0 + index);
        }
        void write_to (const std::string& identifier, gl::index_t index, gl::uint32_t level = 0u)
        {
            auto& texture = textureMap_.at(identifier);

            gl::frame_buffer_texture    (handle_, texture->handle(), glf::FrameBuffer::Attachment::Color0 + index, level);
            gl::frame_buffer_draw_buffer(handle_, glf::FrameBuffer::Source::Color0 + index);
        }

        void resize(const gl::Vector2u& dimensions)
        {
            for (const auto& [identifier, texture]      : textureMap_)
            {
                texture->resize(dimensions);
            }
            for (const auto& [identifier, renderBuffer] : renderBufferMap_)
            {
                renderBuffer->resize(dimensions);
            }

            dimensions_ = dimensions;
        }

        template<Surface A = Surface::Texture>
        auto surface   (const std::string& identifier)
        {
                 if constexpr (A == Surface::Texture)
            {
                return textureMap_.at(identifier);
            }
            else if constexpr (A == Surface::Cubemap)
            {
                return cubemapMap_.at(identifier);
            }
            else if constexpr (A == Surface::RenderBuffer)
            {
                return renderBufferMap_.at(identifier);
            }
        }
        auto attachment(Attachment attachment)
        {
            return attachments_.at(gl::to_underlying(attachment));
        }

        auto dimensions() const
        {
            return dimensions_;
        }

    private:
        gl::Vector2u                                                                          dimensions_{};

        std::array<std::string, 11u>                                                          attachments_{};
        std::unordered_map<std::string, std::shared_ptr<gl::Texture2D>>                       textureMap_{};
        std::unordered_map<std::string, std::shared_ptr<gl::Cubemap>>                         cubemapMap_{};
        std::unordered_map<std::string, std::shared_ptr<gl::RenderBuffer>>                    renderBufferMap_{};
    };
    class FrameBufferMultisample : public gl::Object
    {
    public:
        using Target        = api::FrameBuffer::Target;
        using Attachment    = api::FrameBuffer::Attachment;
        using Specification = api::FrameBuffer::Specification;

         FrameBufferMultisample(const gl::Vector2u& dimensions, std::span<const Specification> specifications, fox::uint32_t samples)
            : dimensions_{ dimensions }, samples_{ samples }
        {
            handle_ = gl::create_frame_buffer();

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
                gl::frame_buffer_read_buffer(handle_, glf::FrameBuffer::Source::None);
                gl::frame_buffer_draw_buffer(handle_, glf::FrameBuffer::Source::None);
            }
            else
            {
                std::vector<glf::FrameBuffer::Source> colorBufferSources(colorBufferIndices.size());
                std::transform(colorBufferIndices.begin(), colorBufferIndices.end(), colorBufferSources.begin(), [](const auto& _)
                    {
                        return static_cast<glf::FrameBuffer::Source>(_);
                    });

                gl::frame_buffer_draw_buffers(handle_, colorBufferSources);
            }

            if (gl::check_frame_buffer_status(handle_) != glf::FrameBuffer::Status::Complete) throw std::runtime_error{ "Framebuffer is not complete!" };
        }
        ~FrameBufferMultisample()
        {
            gl::delete_frame_buffer(handle_);
        }

        void bind(Target target)
        {
            gl::bind_frame_buffer(handle_, gl::map_frame_buffer_target(target));
        }
        
        void bind_texture(const std::string& identifier, gl::binding_t binding)
        {
            const auto& it = identifierToTexture_.find(identifier);
            if (it == identifierToTexture_.end()) throw std::invalid_argument{ "Invalid texture identifier!" };

            gl::bind_texture_unit(it->second->handle(), binding);
        }

        auto dimensions() const
        {
            return dimensions_;
        }
        auto samples   () const
        {
            return samples_;
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

            //const auto& texture = std::make_shared<gl::Texture2DMultisample>(format, dimensions_, samples_);
            //gl::frame_buffer_texture(handle_, texture->handle(), attachmentIndex, gl::uint32_t{ 0u });

            //identifierToTexture_.emplace(identifier, texture);
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

            //const auto& renderBuffer = std::make_shared<gl::RenderBufferMultisample>(format, dimensions_, samples_);
            //gl::frame_buffer_render_buffer(handle_, renderBuffer->handle(), attachmentIndex);

            //identifierToRenderBuffer_.emplace(identifier, renderBuffer);
        }

        gl::Vector2u                                                                  dimensions_{};
        gl::uint32_t                                                                  samples_{};
        std::unordered_map<std::string, std::shared_ptr<gl::Texture2DMultisample>>    identifierToTexture_{};
        std::unordered_map<std::string, std::shared_ptr<gl::RenderBufferMultisample>> identifierToRenderBuffer_{};
    };
}
