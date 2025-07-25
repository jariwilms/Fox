export module fox.rendering.api.opengl.frame_buffer;

import std;
import fox.rendering.api.opengl;
import fox.rendering.api.opengl.cubemap;
import fox.rendering.api.opengl.render_buffer;
import fox.rendering.api.opengl.texture;
import fox.rendering.base.frame_buffer;

export namespace fox::gfx::api::gl
{
    class frame_buffer : public gl::object
    {
    public:
        using attachment_e    = api::frame_buffer::attachment_e;
        using specification_e = api::frame_buffer::specification;
        using surface_e       = api::frame_buffer::surface_e;
        using target_e        = api::frame_buffer::target_e;

        frame_buffer()
            : gl::object{ gl::create_frame_buffer(), [](auto* handle) { gl::delete_frame_buffer(*handle); } }
            , attachments_{}, textureMap_{}, cubemapMap_{}, renderBufferMap_{}, dimensions_{} {}
        frame_buffer(const gl::vector2u& dimensions, std::span<const specification_e> specifications)
            : gl::object{ gl::create_frame_buffer(), [](auto* handle) { gl::delete_frame_buffer(*handle); } }
            , attachments_{}, textureMap_{}, cubemapMap_{}, renderBufferMap_{}, dimensions_{ dimensions }
        {
            auto map_texture_attachment       = [](api::Texture::Format      format, gl::uint32_t& colorIndex)
                {
                    switch (format)
                    {
                        case api::Texture::Format::D16_UNORM:
                        case api::Texture::Format::D24_UNORM:
                        case api::Texture::Format::D32_FLOAT:         return api::frame_buffer::attachment_e::depth;

                        case api::Texture::Format::D24_UNORM_S8_UINT:
                        case api::Texture::Format::D32_FLOAT_S8_UINT: return api::frame_buffer::attachment_e::depth_stencil;

                        case api::Texture::Format::S8_UINT:           return api::frame_buffer::attachment_e::stencil;

                        default:                                      return api::frame_buffer::attachment_e::color0 + colorIndex++;
                    }
                };
            auto map_cubemap_attachment       = [](api::cubemap::Format      format, gl::uint32_t& colorIndex)
            {
                switch (format)
                {
                    case api::cubemap::Format::D16_UNORM:
                    case api::cubemap::Format::D24_UNORM:
                    case api::cubemap::Format::D32_FLOAT:         return api::frame_buffer::attachment_e::depth;

                    case api::cubemap::Format::D24_UNORM_S8_UINT:
                    case api::cubemap::Format::D32_FLOAT_S8_UINT: return api::frame_buffer::attachment_e::depth_stencil;

                    case api::cubemap::Format::S8_UINT:           return api::frame_buffer::attachment_e::stencil;

                    default:                                      return api::frame_buffer::attachment_e::color0 + colorIndex++;
                }
            };
            auto map_render_buffer_attachment = [](api::render_buffer::format_e format, gl::uint32_t& colorIndex)
            {
                switch (format)
                {
                    case api::render_buffer::format_e::d16_unorm:
                    case api::render_buffer::format_e::d24_unorm:
                    case api::render_buffer::format_e::d32_float:         return api::frame_buffer::attachment_e::depth;

                    case api::render_buffer::format_e::d24_unorm_s8_uint:
                    case api::render_buffer::format_e::d32_float_s8_uint: return api::frame_buffer::attachment_e::depth_stencil;

                    case api::render_buffer::format_e::s8_uint:           return api::frame_buffer::attachment_e::stencil;

                    default:                                              return api::frame_buffer::attachment_e::color0 + colorIndex++;
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
                        [&](api::cubemap     ::Format format)
                        {
                            auto cubemap    = std::make_shared<gl::cubemap>(format, api::cubemap::Filter::None, api::cubemap::Wrapping::Repeat, dimensions_);
                            auto attachment = map_cubemap_attachment(cubemap->format(), colorIndex);

                            attach(identifier, attachment, cubemap);
                        }, 
                        [&](api::render_buffer::format_e format)
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
                gl::frame_buffer_read_buffer(handle(), gl::frame_buffer_source_e::none);
                gl::frame_buffer_draw_buffer(handle(), gl::frame_buffer_source_e::none);
            }
            else
            {
                auto colorBufferSources = std::vector<gl::frame_buffer_source_e>(colorIndex);
                std::ranges::for_each(std::views::iota(0u, colorIndex), [&](gl::uint32_t index)
                    {
                        colorBufferSources.at(index) = gl::frame_buffer_source_e::color0 + index;
                    });

                gl::frame_buffer_draw_buffers(handle(), colorBufferSources);
            }

            if (gl::check_frame_buffer_status(handle()) != gl::frame_buffer_status_e::complete) throw std::runtime_error{ "Framebuffer is not complete!" };
        }

        void bind(target_e target)
        {
            gl::bind_frame_buffer(handle(), gl::map_frame_buffer_target(target));
        }
        template<surface_e A = surface_e::texture>
        void bind_surface(const std::string& identifier, gl::binding_t binding) const
        {
            if constexpr (A == surface_e::texture) textureMap_.at(identifier)->bind(binding);
            if constexpr (A == surface_e::cubemap) cubemapMap_.at(identifier)->bind(binding);
        }

        void attach(const std::string& identifier, attachment_e attachment, std::shared_ptr<gl::texture2d>    texture     , gl::uint32_t level = 0u)
        {
            gl::frame_buffer_texture(handle(), texture->handle(), gl::map_frame_buffer_attachment(attachment), level);

            attachments_.at(gl::to_underlying(attachment)) = identifier;
            textureMap_.emplace(identifier, texture);
        }
        void attach(const std::string& identifier, attachment_e attachment, std::shared_ptr<gl::cubemap>      cubemap     , gl::uint32_t level = 0u)
        {
            gl::frame_buffer_texture(handle(), cubemap->handle(), gl::map_frame_buffer_attachment(attachment), level);

            attachments_.at(gl::to_underlying(attachment)) = identifier;
            cubemapMap_.emplace(identifier, cubemap);
        }
        void attach(const std::string& identifier, attachment_e attachment, std::shared_ptr<gl::render_buffer> renderBuffer)
        {
            gl::frame_buffer_render_buffer(handle(), renderBuffer->handle(), gl::map_frame_buffer_attachment(attachment));

            attachments_.at(gl::to_underlying(attachment)) = identifier;
            renderBufferMap_.emplace(identifier, renderBuffer);
        }
        
        template<surface_e A = surface_e::texture>
        void detach(const std::string& identifier, attachment_e attachment)
        {
            if constexpr (A == surface_e::texture)
            {
                gl::frame_buffer_texture(handle(), gl::null_object, gl::map_frame_buffer_attachment(attachment), gl::uint32_t{ 0u });
                textureMap_.erase(identifier);
            }
            if constexpr (A == surface_e::cubemap)
            {
                gl::frame_buffer_texture(handle(), gl::null_object, gl::map_frame_buffer_attachment(attachment), gl::uint32_t{ 0u });
                cubemapMap_.erase(identifier);
            }
            if constexpr (A == surface_e::render_buffer)
            {
                gl::frame_buffer_render_buffer(handle(), gl::null_object, gl::map_frame_buffer_attachment(attachment), gl::uint32_t{ 0u });
                renderBufferMap_.erase(identifier);
            }
        }
        
        void read_from(const std::string& identifier, gl::index_t index, gl::uint32_t level = 0u)
        {
            auto& texture = textureMap_.at(identifier);

            gl::frame_buffer_texture    (handle(), texture->handle(), gl::frame_buffer_attachment_e::color0 + index, level);
            gl::frame_buffer_read_buffer(handle(), gl::frame_buffer_source_e::color0 + index);
        }
        void write_to (const std::string& identifier, gl::index_t index, gl::uint32_t level = 0u)
        {
            auto& texture = textureMap_.at(identifier);

            gl::frame_buffer_texture    (handle(), texture->handle(), gl::frame_buffer_attachment_e::color0 + index, level);
            gl::frame_buffer_draw_buffer(handle(), gl::frame_buffer_source_e::color0 + index);
        }

        void resize(const gl::vector2u& dimensions)
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

        template<surface_e A = surface_e::texture>
        auto surface(const std::string& identifier) -> auto
        {
            if constexpr (A == surface_e::texture)
            {
                return textureMap_.at(identifier);
            }
            if constexpr (A == surface_e::cubemap)
            {
                return cubemapMap_.at(identifier);
            }
            if constexpr (A == surface_e::render_buffer)
            {
                return renderBufferMap_.at(identifier);
            }
        }
        
        auto attachment(attachment_e attachment) const -> const std::string&
        {
            return attachments_.at(gl::to_underlying(attachment));
        }
        auto dimensions() const -> const gl::vector2u&
        {
            return dimensions_;
        }

    private:
        std::array<std::string, 11u>                                       attachments_;
        std::unordered_map<std::string, std::shared_ptr<gl::texture2d>>    textureMap_;
        std::unordered_map<std::string, std::shared_ptr<gl::cubemap>>      cubemapMap_;
        std::unordered_map<std::string, std::shared_ptr<gl::render_buffer>> renderBufferMap_;
        gl::vector2u                                                       dimensions_;
    };
    class frame_buffer_ms : public gl::object
    {
    public:
        using attachment_e    = api::frame_buffer::attachment_e;
        using specification_e = api::frame_buffer::specification_ms;
        using surface_e       = api::frame_buffer::surface_e;
        using target_e        = api::frame_buffer::target_e;

        frame_buffer_ms(const gl::vector2u& dimensions, gl::uint32_t samples)
            : gl::object{ gl::create_frame_buffer(), [](auto* handle) { gl::delete_frame_buffer(*handle); } }
            , attachments_{}, textureMap_{}, renderBufferMap_{}, dimensions_{ dimensions }, samples_{ samples } {}
        frame_buffer_ms(const gl::vector2u& dimensions, std::span<const specification_e> specifications, gl::uint32_t samples)
            : gl::object{ gl::create_frame_buffer(), [](auto* handle) { gl::delete_frame_buffer(*handle); } }
            , attachments_{}, textureMap_{}, renderBufferMap_{}, dimensions_{ dimensions }, samples_{ samples }
        {
            auto map_texture_attachment       = [](api::Texture::Format      format, gl::uint32_t& colorIndex)
                {
                    switch (format)
                    {
                        case api::Texture::Format::D16_UNORM:
                        case api::Texture::Format::D24_UNORM:
                        case api::Texture::Format::D32_FLOAT:         return api::frame_buffer::attachment_e::depth;

                        case api::Texture::Format::D24_UNORM_S8_UINT:
                        case api::Texture::Format::D32_FLOAT_S8_UINT: return api::frame_buffer::attachment_e::depth_stencil;

                        case api::Texture::Format::S8_UINT:           return api::frame_buffer::attachment_e::stencil;

                        default:                                      return api::frame_buffer::attachment_e::color0 + colorIndex++;
                    }
                };
            auto map_render_buffer_attachment = [](api::render_buffer::format_e format, gl::uint32_t& colorIndex)
            {
                switch (format)
                {
                    case api::render_buffer::format_e::d16_unorm:
                    case api::render_buffer::format_e::d24_unorm:
                    case api::render_buffer::format_e::d32_float:         return api::frame_buffer::attachment_e::depth;

                    case api::render_buffer::format_e::d24_unorm_s8_uint:
                    case api::render_buffer::format_e::d32_float_s8_uint: return api::frame_buffer::attachment_e::depth_stencil;

                    case api::render_buffer::format_e::s8_uint:           return api::frame_buffer::attachment_e::stencil;

                    default:                                              return api::frame_buffer::attachment_e::color0 + colorIndex++;
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
                        [&](api::render_buffer::format_e format)
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
                gl::frame_buffer_read_buffer(handle(), gl::frame_buffer_source_e::none);
                gl::frame_buffer_draw_buffer(handle(), gl::frame_buffer_source_e::none);
            }
            else
            {
                auto colorBufferSources = std::vector<gl::frame_buffer_source_e>(colorIndex);
                std::ranges::for_each(std::views::iota(0u, colorIndex), [&](gl::uint32_t index)
                    {
                        colorBufferSources.at(index) = gl::frame_buffer_source_e::color0 + index;
                    });

                gl::frame_buffer_draw_buffers(handle(), colorBufferSources);
            }

            if (gl::check_frame_buffer_status(handle()) != gl::frame_buffer_status_e::complete) throw std::runtime_error{ "Framebuffer is not complete!" };
         }
        
        void bind(target_e target)
        {
            gl::bind_frame_buffer(handle(), gl::map_frame_buffer_target(target));
        }
        template<surface_e A = surface_e::texture>
        void bind_surface(const std::string& identifier, gl::binding_t binding) const
        {
            if constexpr (A == surface_e::texture) textureMap_.at(identifier)->bind(binding);
        }

        void attach(const std::string& identifier, attachment_e attachment, std::shared_ptr<gl::texture2d_ms>    texture, gl::uint32_t level = 0u)
        {
            gl::frame_buffer_texture(handle(), texture->handle(), gl::map_frame_buffer_attachment(attachment), level);

            attachments_.at(gl::to_underlying(attachment)) = identifier;
            textureMap_.emplace(identifier, texture);
        }
        void attach(const std::string& identifier, attachment_e attachment, std::shared_ptr<gl::render_buffer_ms> renderBuffer)
        {
            gl::frame_buffer_render_buffer(handle(), renderBuffer->handle(), gl::map_frame_buffer_attachment(attachment));

            attachments_.at(gl::to_underlying(attachment)) = identifier;
            renderBufferMap_.emplace(identifier, renderBuffer);
        }

        template<surface_e A = surface_e::texture>
        void detach(const std::string& identifier, attachment_e attachment)
        {
            if constexpr (A == surface_e::texture)
            {
                gl::frame_buffer_texture(handle_, gl::null_object, gl::map_frame_buffer_attachment(attachment), gl::uint32_t{ 0u });
                textureMap_.erase(identifier);
            }
            if constexpr (A == surface_e::render_buffer)
            {
                gl::frame_buffer_render_buffer(handle_, gl::null_object, gl::map_frame_buffer_attachment(attachment), gl::uint32_t{ 0u });
                renderBufferMap_.erase(identifier);
            }
        }

        void read_from(const std::string& identifier, gl::index_t index, gl::uint32_t level = 0u)
        {
            auto& texture = textureMap_.at(identifier);

            gl::frame_buffer_texture    (handle(), texture->handle(), gl::frame_buffer_attachment_e::color0 + index, level);
            gl::frame_buffer_read_buffer(handle(), gl::frame_buffer_source_e::color0 + index);
        }
        void write_to (const std::string& identifier, gl::index_t index, gl::uint32_t level = 0u)
        {
            auto& texture = textureMap_.at(identifier);

            gl::frame_buffer_texture    (handle(), texture->handle(), gl::frame_buffer_attachment_e::color0 + index, level);
            gl::frame_buffer_draw_buffer(handle(), gl::frame_buffer_source_e::color0 + index);
        }

        void resize(const gl::vector2u& dimensions)
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

        template<surface_e A = surface_e::texture>
        auto surface(const std::string& identifier) -> auto
        {
            if constexpr (A == surface_e::texture)
            {
                return textureMap_.at(identifier);
            }
            if constexpr (A == surface_e::render_buffer)
            {
                return renderBufferMap_.at(identifier);
            }
        }

        auto attachment(attachment_e attachment) const -> const std::string&
        {
            return attachments_.at(gl::to_underlying(attachment));
        }
        auto dimensions() const -> const gl::vector2u&
        {
            return dimensions_;
        }
        auto samples   () const
        {
            return samples_;
        }

    private:
        std::array<std::string, 11u>                                           attachments_;
        std::unordered_map<std::string, std::shared_ptr<gl::texture2d_ms>>     textureMap_;
        std::unordered_map<std::string, std::shared_ptr<gl::render_buffer_ms>> renderBufferMap_;
        gl::vector2u                                                           dimensions_;
        gl::uint32_t                                                           samples_;
    };
}
