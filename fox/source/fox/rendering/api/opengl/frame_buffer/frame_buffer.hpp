#pragma once

#include <stdafx.hpp>

#include <fox/rendering/base/frame_buffer/frame_buffer.hpp>

import fox.rendering.api.opengl;
import fox.rendering.api.opengl.render_buffer;
import fox.rendering.api.opengl.cubemap;
import fox.rendering.api.opengl.texture;

namespace fox::gfx::api::gl
{
    class FrameBuffer : public gl::Object
    {
    public:
        using Attachment    = api::FrameBuffer::Attachment;
        using Specification = api::FrameBuffer::Specification;
        using Surface       = api::FrameBuffer::Surface;
        using Target        = api::FrameBuffer::Target;

        FrameBuffer()
            : gl::Object{ gl::create_frame_buffer(), [](auto* handle) { gl::delete_frame_buffer(*handle); } }
            , attachments_{}, textureMap_{}, cubemapMap_{}, renderBufferMap_{}, dimensions_{} {}
        FrameBuffer(const gl::Vector2u& dimensions, std::span<const Specification> specifications)
            : gl::Object{ gl::create_frame_buffer(), [](auto* handle) { gl::delete_frame_buffer(*handle); } }
            , attachments_{}, textureMap_{}, cubemapMap_{}, renderBufferMap_{}, dimensions_{ dimensions }
        {
            auto map_texture_attachment       = [](api::Texture::Format      format, gl::uint32_t& colorIndex)
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
            auto map_cubemap_attachment       = [](api::Cubemap::Format      format, gl::uint32_t& colorIndex)
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
            auto map_render_buffer_attachment = [](api::RenderBuffer::Format format, gl::uint32_t& colorIndex)
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

            auto colorIndex = gl::uint32_t{ 0u };
            std::ranges::for_each(specifications, [&](const auto& specification)
                {
                    const auto& [identifier, format] = specification;
                    const auto  overload             = gl::overload
                    {
                        [&](api::Texture     ::Format format)
                        {
                            auto texture    = std::make_shared<gl::Texture2D>(format, api::Texture::Filter::None, api::Texture::Wrapping::Repeat, dimensions_);
                            auto attachment = map_texture_attachment(texture->format(), colorIndex);

                            attach(identifier, attachment, texture);
                        }, 
                        [&](api::Cubemap     ::Format format)
                        {
                            auto cubemap    = std::make_shared<gl::Cubemap>(format, api::Cubemap::Filter::None, api::Cubemap::Wrapping::Repeat, dimensions_);
                            auto attachment = map_cubemap_attachment(cubemap->format(), colorIndex);

                            attach(identifier, attachment, cubemap);
                        }, 
                        [&](api::RenderBuffer::Format format)
                        {
                            auto renderBuffer = std::make_shared<gl::RenderBuffer>(format, dimensions_);
                            auto attachment   = map_render_buffer_attachment(renderBuffer->format(), colorIndex);

                            attach(identifier, attachment, renderBuffer);
                        }, 
                    };

                    std::visit(overload, format);
                });
            
            if (gl::compare<std::equal_to>(colorIndex, gl::uint32_t{ 0u }))
            {
                gl::frame_buffer_read_buffer(handle_, glf::FrameBuffer::Source::None);
                gl::frame_buffer_draw_buffer(handle_, glf::FrameBuffer::Source::None);
            }
            else
            {
                auto colorBufferSources = std::vector<glf::FrameBuffer::Source>(colorIndex);
                std::ranges::for_each(std::views::iota(0u, colorIndex), [&](gl::uint32_t index)
                    {
                        colorBufferSources.at(index) = glf::FrameBuffer::Source::Color0 + index;
                    });

                gl::frame_buffer_draw_buffers(handle_, colorBufferSources);
            }

            if (gl::check_frame_buffer_status(handle_) != glf::FrameBuffer::Status::Complete) throw std::runtime_error{ "Framebuffer is not complete!" };
        }

        void bind(Target target)
        {
            gl::bind_frame_buffer(handle_, gl::map_frame_buffer_target(target));
        }
        template<Surface A = Surface::Texture>
        void bind_surface(const std::string& identifier, gl::binding_t binding) const
        {
            if constexpr (A == Surface::Texture) textureMap_.at(identifier)->bind(binding);
            if constexpr (A == Surface::Cubemap) cubemapMap_.at(identifier)->bind(binding);
        }

        void attach(const std::string& identifier, Attachment attachment, std::shared_ptr<gl::Texture2D>    texture     , gl::uint32_t level = 0u)
        {
            gl::frame_buffer_texture(handle_, texture->handle(), gl::map_frame_buffer_attachment(attachment), level);

            attachments_.at(gl::to_underlying(attachment)) = identifier;
            textureMap_.emplace(identifier, texture);
        }
        void attach(const std::string& identifier, Attachment attachment, std::shared_ptr<gl::Cubemap>      cubemap     , gl::uint32_t level = 0u)
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
            if constexpr (A == Surface::Cubemap)
            {
                gl::frame_buffer_texture(handle_, gl::NullObject, gl::map_frame_buffer_attachment(attachment), gl::uint32_t{ 0u });
                cubemapMap_.erase(identifier);
            }
            if constexpr (A == Surface::RenderBuffer)
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
            std::ranges::for_each(textureMap_     , [&](const auto& _)
                {
                    const auto& [identifier, texture] = _;
                    texture->resize(dimensions);
                });
            std::ranges::for_each(renderBufferMap_, [&](const auto& _)
                {
                    const auto& [identifier, renderBuffer] = _;
                    renderBuffer->resize(dimensions);
                });

            dimensions_ = dimensions;
        }

        template<Surface A = Surface::Texture>
        auto surface(const std::string& identifier) -> auto
        {
            if constexpr (A == Surface::Texture)
            {
                return textureMap_.at(identifier);
            }
            if constexpr (A == Surface::Cubemap)
            {
                return cubemapMap_.at(identifier);
            }
            if constexpr (A == Surface::RenderBuffer)
            {
                return renderBufferMap_.at(identifier);
            }
        }
        
        auto attachment(Attachment attachment) const -> const std::string&
        {
            return attachments_.at(gl::to_underlying(attachment));
        }
        auto dimensions() const -> const gl::Vector2u&
        {
            return dimensions_;
        }

    private:
        std::array<std::string, 11u>                                       attachments_;
        std::unordered_map<std::string, std::shared_ptr<gl::Texture2D>>    textureMap_;
        std::unordered_map<std::string, std::shared_ptr<gl::Cubemap>>      cubemapMap_;
        std::unordered_map<std::string, std::shared_ptr<gl::RenderBuffer>> renderBufferMap_;
        gl::Vector2u                                                       dimensions_;
    };
    class FrameBufferMultisample : public gl::Object
    {
    public:
        using Attachment    = api::FrameBuffer::Attachment;
        using Specification = api::FrameBuffer::Specification;
        using Surface       = api::FrameBuffer::Surface;
        using Target        = api::FrameBuffer::Target;

        FrameBufferMultisample(const gl::Vector2u& dimensions, gl::uint32_t samples)
            : gl::Object{ gl::create_frame_buffer(), [](auto* handle) { gl::delete_frame_buffer(*handle); } }
            , attachments_{}, textureMap_{}, cubemapMap_{}, renderBufferMap_{}, dimensions_{ dimensions }, samples_{ samples } {}
        FrameBufferMultisample(const gl::Vector2u& dimensions, std::span<const Specification> specifications, fox::uint32_t samples)
            : gl::Object{ gl::create_frame_buffer(), [](auto* handle) { gl::delete_frame_buffer(*handle); } }
            , attachments_{}, textureMap_{}, cubemapMap_{}, renderBufferMap_{}, dimensions_{ dimensions }, samples_{ samples }
        {
            auto map_texture_attachment       = [](api::Texture::Format      format, gl::uint32_t& colorIndex)
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
            auto map_cubemap_attachment       = [](api::Cubemap::Format      format, gl::uint32_t& colorIndex)
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
            auto map_render_buffer_attachment = [](api::RenderBuffer::Format format, gl::uint32_t& colorIndex)
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

            auto colorIndex = gl::uint32_t{ 0u };
            std::ranges::for_each(specifications, [&, this](const auto& specification)
                {
                    const auto& [identifier, format] = specification;
                    const auto  overload             = gl::overload
                    {
                        [&](api::Texture     ::Format format)
                        {
                            auto texture    = std::make_shared<gl::Texture2DMultisample>(format, dimensions_, samples_);
                            auto attachment = map_texture_attachment(texture->format(), colorIndex);

                            attach(identifier, attachment, texture);
                        }, 
                        [&](api::Cubemap     ::Format format)
                        {
                            //auto cubemap    = std::make_shared<gl::Cubemap>(format, api::Cubemap::Filter::None, api::Cubemap::Wrapping::Repeat, dimensions_);
                            //auto attachment = map_cubemap_attachment(cubemap->format(), colorIndex);

                            //attach(identifier, attachment, cubemap);
                        }, 
                        [&](api::RenderBuffer::Format format)
                        {
                            auto renderBuffer = std::make_shared<gl::RenderBufferMultisample>(format, dimensions_, samples_);
                            auto attachment   = map_render_buffer_attachment(renderBuffer->format(), colorIndex);

                            attach(identifier, attachment, renderBuffer);
                        }, 
                    };

                    std::visit(overload, format);
                });

            if (gl::compare<std::equal_to>(colorIndex, gl::uint32_t{ 0u }))
            {
                gl::frame_buffer_read_buffer(handle_, glf::FrameBuffer::Source::None);
                gl::frame_buffer_draw_buffer(handle_, glf::FrameBuffer::Source::None);
            }
            else
            {
                auto colorBufferSources = std::vector<glf::FrameBuffer::Source>(colorIndex);
                std::ranges::for_each(std::views::iota(0u, colorIndex), [&](gl::uint32_t index)
                    {
                        colorBufferSources.at(index) = glf::FrameBuffer::Source::Color0 + index;
                    });

                gl::frame_buffer_draw_buffers(handle_, colorBufferSources);
            }

            if (gl::check_frame_buffer_status(handle_) != glf::FrameBuffer::Status::Complete) throw std::runtime_error{ "Framebuffer is not complete!" };
         }
        
        void bind(Target target)
        {
            gl::bind_frame_buffer(handle_, gl::map_frame_buffer_target(target));
        }
        template<Surface A = Surface::Texture>
        void bind_surface(const std::string& identifier, gl::binding_t binding) const
        {
            if constexpr (A == Surface::Texture) textureMap_.at(identifier)->bind(binding);
            //if constexpr (A == Surface::Cubemap) cubemapMap_.at(identifier)->bind(binding);
        }

        void attach(const std::string& identifier, Attachment attachment, std::shared_ptr<gl::Texture2DMultisample>    texture, gl::uint32_t level = 0u)
        {
            gl::frame_buffer_texture(handle_, texture->handle(), gl::map_frame_buffer_attachment(attachment), level);

            attachments_.at(gl::to_underlying(attachment)) = identifier;
            textureMap_.emplace(identifier, texture);
        }
        void attach(const std::string& identifier, Attachment attachment, std::shared_ptr<gl::Cubemap>                 cubemap, gl::uint32_t level = 0u)
        {
            //gl::frame_buffer_texture(handle_, cubemap->handle(), gl::map_frame_buffer_attachment(attachment), level);

            //attachments_.at(gl::to_underlying(attachment)) = identifier;
            //cubemapMap_.emplace(identifier, cubemap);
        }
        void attach(const std::string& identifier, Attachment attachment, std::shared_ptr<gl::RenderBufferMultisample> renderBuffer)
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
            if constexpr (A == Surface::Cubemap)
            {
                //gl::frame_buffer_texture(handle_, gl::NullObject, gl::map_frame_buffer_attachment(attachment), gl::uint32_t{ 0u });
                //cubemapMap_.erase(identifier);
            }
            if constexpr (A == Surface::RenderBuffer)
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
            std::ranges::for_each(textureMap_     , [&](const auto& _)
                {
                    const auto& [identifier, texture] = _;
                    texture->resize(dimensions);
                });
            std::ranges::for_each(renderBufferMap_, [&](const auto& _)
                {
                    const auto& [identifier, renderBuffer] = _;
                    renderBuffer->resize(dimensions);
                });

            dimensions_ = dimensions;
        }

        template<Surface A = Surface::Texture>
        auto surface(const std::string& identifier) -> auto
        {
            if constexpr (A == Surface::Texture)
            {
                return textureMap_.at(identifier);
            }
            if constexpr (A == Surface::Cubemap)
            {
                //return cubemapMap_.at(identifier);
            }
            if constexpr (A == Surface::RenderBuffer)
            {
                return renderBufferMap_.at(identifier);
            }
        }

        auto attachment(Attachment attachment) const -> const std::string&
        {
            return attachments_.at(gl::to_underlying(attachment));
        }
        auto dimensions() const -> const gl::Vector2u&
        {
            return dimensions_;
        }
        auto samples   () const
        {
            return samples_;
        }

    private:
        std::array<std::string, 11u>                                                  attachments_;
        std::unordered_map<std::string, std::shared_ptr<gl::Texture2DMultisample>>    textureMap_;
        std::unordered_map<std::string, std::shared_ptr<gl::Cubemap>>                 cubemapMap_;
        std::unordered_map<std::string, std::shared_ptr<gl::RenderBufferMultisample>> renderBufferMap_;
        gl::Vector2u                                                                  dimensions_;
        gl::uint32_t                                                                  samples_;
    };
}
