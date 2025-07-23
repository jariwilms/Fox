export module fox.rendering.api.opengl.frame_buffer;

import std;
import fox.rendering.api.opengl;
import fox.rendering.api.opengl.cubemap;
import fox.rendering.api.opengl.render_buffer;
import fox.rendering.api.opengl.texture;
import fox.rendering.base.frame_buffer;

export namespace fox::gfx::api::gl
{
    class frame_buffer : public gl::Object
    {
    public:
        using attachment_e    = api::FrameBuffer::Attachment;
        using specification_e = api::FrameBuffer::Specification;
        using surface_e       = api::FrameBuffer::Surface;
        using target_e        = api::FrameBuffer::Target;

        frame_buffer()
            : gl::Object{ gl::create_frame_buffer(), [](auto* handle) { gl::delete_frame_buffer(*handle); } }
            , attachments_{}, textureMap_{}, cubemapMap_{}, renderBufferMap_{}, dimensions_{} {}
        frame_buffer(const gl::Vector2u& dimensions, std::span<const specification_e> specifications)
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
                            auto texture    = std::make_shared<gl::texture2d>(format, api::Texture::Filter::None, api::Texture::Wrapping::Repeat, dimensions_);
                            auto attachment = map_texture_attachment(texture->format(), colorIndex);

                            attach(identifier, attachment, texture);
                        }, 
                        [&](api::Cubemap     ::Format format)
                        {
                            auto cubemap    = std::make_shared<gl::cubemap>(format, api::Cubemap::Filter::None, api::Cubemap::Wrapping::Repeat, dimensions_);
                            auto attachment = map_cubemap_attachment(cubemap->format(), colorIndex);

                            attach(identifier, attachment, cubemap);
                        }, 
                        [&](api::RenderBuffer::Format format)
                        {
                            auto renderBuffer = std::make_shared<gl::render_buffer>(format, dimensions_);
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

        void bind(target_e target)
        {
            gl::bind_frame_buffer(handle_, gl::map_frame_buffer_target(target));
        }
        template<surface_e A = surface_e::Texture>
        void bind_surface(const std::string& identifier, gl::binding_t binding) const
        {
            if constexpr (A == surface_e::Texture) textureMap_.at(identifier)->bind(binding);
            if constexpr (A == surface_e::Cubemap) cubemapMap_.at(identifier)->bind(binding);
        }

        void attach(const std::string& identifier, attachment_e attachment, std::shared_ptr<gl::texture2d>    texture     , gl::uint32_t level = 0u)
        {
            gl::frame_buffer_texture(handle_, texture->handle(), gl::map_frame_buffer_attachment(attachment), level);

            attachments_.at(gl::to_underlying(attachment)) = identifier;
            textureMap_.emplace(identifier, texture);
        }
        void attach(const std::string& identifier, attachment_e attachment, std::shared_ptr<gl::cubemap>      cubemap     , gl::uint32_t level = 0u)
        {
            gl::frame_buffer_texture(handle_, cubemap->handle(), gl::map_frame_buffer_attachment(attachment), level);

            attachments_.at(gl::to_underlying(attachment)) = identifier;
            cubemapMap_.emplace(identifier, cubemap);
        }
        void attach(const std::string& identifier, attachment_e attachment, std::shared_ptr<gl::render_buffer> renderBuffer)
        {
            gl::frame_buffer_render_buffer(handle_, renderBuffer->handle(), gl::map_frame_buffer_attachment(attachment));

            attachments_.at(gl::to_underlying(attachment)) = identifier;
            renderBufferMap_.emplace(identifier, renderBuffer);
        }
        
        template<surface_e A = surface_e::Texture>
        void detach(const std::string& identifier, attachment_e attachment)
        {
            if constexpr (A == surface_e::Texture)
            {
                gl::frame_buffer_texture(handle_, gl::NullObject, gl::map_frame_buffer_attachment(attachment), gl::uint32_t{ 0u });
                textureMap_.erase(identifier);
            }
            if constexpr (A == surface_e::Cubemap)
            {
                gl::frame_buffer_texture(handle_, gl::NullObject, gl::map_frame_buffer_attachment(attachment), gl::uint32_t{ 0u });
                cubemapMap_.erase(identifier);
            }
            if constexpr (A == surface_e::RenderBuffer)
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

        template<surface_e A = surface_e::Texture>
        auto surface(const std::string& identifier) -> auto
        {
            if constexpr (A == surface_e::Texture)
            {
                return textureMap_.at(identifier);
            }
            if constexpr (A == surface_e::Cubemap)
            {
                return cubemapMap_.at(identifier);
            }
            if constexpr (A == surface_e::RenderBuffer)
            {
                return renderBufferMap_.at(identifier);
            }
        }
        
        auto attachment(attachment_e attachment) const -> const std::string&
        {
            return attachments_.at(gl::to_underlying(attachment));
        }
        auto dimensions() const -> const gl::Vector2u&
        {
            return dimensions_;
        }

    private:
        std::array<std::string, 11u>                                       attachments_;
        std::unordered_map<std::string, std::shared_ptr<gl::texture2d>>    textureMap_;
        std::unordered_map<std::string, std::shared_ptr<gl::cubemap>>      cubemapMap_;
        std::unordered_map<std::string, std::shared_ptr<gl::render_buffer>> renderBufferMap_;
        gl::Vector2u                                                       dimensions_;
    };
    class frame_buffer_ms : public gl::Object
    {
    public:
        using attachment_e    = api::FrameBuffer::Attachment;
        using specification_e = api::FrameBuffer::SpecificationMultisample;
        using surface_e       = api::FrameBuffer::Surface;
        using target_e        = api::FrameBuffer::Target;

        frame_buffer_ms(const gl::Vector2u& dimensions, gl::uint32_t samples)
            : gl::Object{ gl::create_frame_buffer(), [](auto* handle) { gl::delete_frame_buffer(*handle); } }
            , attachments_{}, textureMap_{}, renderBufferMap_{}, dimensions_{ dimensions }, samples_{ samples } {}
        frame_buffer_ms(const gl::Vector2u& dimensions, std::span<const specification_e> specifications, gl::uint32_t samples)
            : gl::Object{ gl::create_frame_buffer(), [](auto* handle) { gl::delete_frame_buffer(*handle); } }
            , attachments_{}, textureMap_{}, renderBufferMap_{}, dimensions_{ dimensions }, samples_{ samples }
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
                            auto texture    = std::make_shared<gl::texture2d_ms>(format, dimensions_, samples_);
                            auto attachment = map_texture_attachment(texture->format(), colorIndex);

                            attach(identifier, attachment, texture);
                        }, 
                        [&](api::RenderBuffer::Format format)
                        {
                            auto renderBuffer = std::make_shared<gl::render_buffer_ms>(format, dimensions_, samples_);
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
        
        void bind(target_e target)
        {
            gl::bind_frame_buffer(handle_, gl::map_frame_buffer_target(target));
        }
        template<surface_e A = surface_e::Texture>
        void bind_surface(const std::string& identifier, gl::binding_t binding) const
        {
            if constexpr (A == surface_e::Texture) textureMap_.at(identifier)->bind(binding);
        }

        void attach(const std::string& identifier, attachment_e attachment, std::shared_ptr<gl::texture2d_ms>    texture, gl::uint32_t level = 0u)
        {
            gl::frame_buffer_texture(handle_, texture->handle(), gl::map_frame_buffer_attachment(attachment), level);

            attachments_.at(gl::to_underlying(attachment)) = identifier;
            textureMap_.emplace(identifier, texture);
        }
        void attach(const std::string& identifier, attachment_e attachment, std::shared_ptr<gl::render_buffer_ms> renderBuffer)
        {
            gl::frame_buffer_render_buffer(handle_, renderBuffer->handle(), gl::map_frame_buffer_attachment(attachment));

            attachments_.at(gl::to_underlying(attachment)) = identifier;
            renderBufferMap_.emplace(identifier, renderBuffer);
        }

        template<surface_e A = surface_e::Texture>
        void detach(const std::string& identifier, attachment_e attachment)
        {
            if constexpr (A == surface_e::Texture)
            {
                gl::frame_buffer_texture(handle_, gl::NullObject, gl::map_frame_buffer_attachment(attachment), gl::uint32_t{ 0u });
                textureMap_.erase(identifier);
            }
            if constexpr (A == surface_e::RenderBuffer)
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

        template<surface_e A = surface_e::Texture>
        auto surface(const std::string& identifier) -> auto
        {
            if constexpr (A == surface_e::Texture)
            {
                return textureMap_.at(identifier);
            }
            if constexpr (A == surface_e::RenderBuffer)
            {
                return renderBufferMap_.at(identifier);
            }
        }

        auto attachment(attachment_e attachment) const -> const std::string&
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
        std::array<std::string, 11u>                                       attachments_;
        std::unordered_map<std::string, std::shared_ptr<gl::texture2d_ms>> textureMap_;
        std::unordered_map<std::string, std::shared_ptr<gl::render_buffer_ms>> renderBufferMap_;
        gl::Vector2u                                                       dimensions_;
        gl::uint32_t                                                       samples_;
    };
}
