export module fox.rendering.api.opengl.texture;

import std;
import fox.math.texture;
import fox.rendering.api.opengl;
import fox.rendering.base.texture;

export namespace fox::gfx::api::gl
{
    class texture1d : public gl::Object
    {
    public:
        using format_e   = api::Texture::Format;
        using filter_e   = api::Texture::Filter;
        using wrapping_e = api::Texture::Wrapping;
        using wrapping_t = gl::proxy_t<wrapping_e>;

        texture1d(format_e format, filter_e filter, wrapping_t wrapping, const gl::Vector1u& dimensions)
            : gl::Object{ gl::create_texture(glf::Texture::Target::_1D), [](auto* handle) { gl::delete_texture(*handle); } }
            , format_{ format }, filter_{ filter }, wrapping_{ wrapping }, dimensions_{ dimensions }, mipmapLevels_{ 1u }
        {
            if (filter_ != filter_e::None)
            {
                gl::texture_parameter(handle_, glp::magnification_filter{ gl::map_texture_mag_filter(filter_) });
                gl::texture_parameter(handle_, glp::minification_filter { gl::map_texture_min_filter(filter_) });
                gl::texture_parameter(handle_, glp::maximum_anisotropy  { gl::float32_t{ 1.0f } });

                mipmapLevels_ = math::mipmap_levels(dimensions_);
            }

            const auto& [s] = wrapping_.pack;
            gl::texture_parameter(handle_, glp::wrapping_s{ gl::map_texture_wrapping(s) });

            gl::texture_storage_1d(handle_, gl::map_texture_format(format_), dimensions_, mipmapLevels_);
        }
        texture1d(format_e format, filter_e filter, wrapping_t wrapping, const gl::Vector1u& dimensions, std::span<const gl::byte_t> data)
            : texture1d{ format, filter, wrapping, dimensions }
        {
            copy(format, data);
            generate_mipmap();
        }
        texture1d(format_e format,                                        const gl::Vector1u& dimensions, std::span<const gl::byte_t> data)
            : texture1d{ format, filter_e::Trilinear, wrapping_e::Repeat, dimensions, data } {}

        void bind(gl::binding_t binding) const
        {
            gl::bind_texture_unit(handle_, binding);
        }

        void copy      (format_e format,                      std::span<const gl::byte_t> data)
        {
            copy_range(format, dimensions_, data);
        }
        void copy_range(format_e format, gl::length_t region, std::span<const gl::byte_t> data)
        {
            if (data.empty()) return;
            if (glm::any(glm::greaterThan(region.origin + region.extent, dimensions_))) throw std::out_of_range{ "The given region exceeds texture bounds!" };

            gl::texture_sub_image_1d(handle_, gl::map_texture_format_base(format), gl::map_texture_format_type(format), gl::uint32_t{ 0u }, region, data);
        }

        void apply_wrapping (wrapping_t wrapping)
        {
            wrapping_ = wrapping;

            const auto& [s] = wrapping_.pack;
            gl::texture_parameter(handle_, glp::wrapping_s{ gl::map_texture_wrapping(s) });
        }
        void generate_mipmap()
        {
            if (filter_ != filter_e::None) gl::generate_texture_mipmap(handle_);
        }

        void resize(const gl::Vector1u& dimensions)
        {
            gl::todo();
        }

        auto format       () const -> format_e
        {
            return format_;
        }
        auto filter       () const -> filter_e
        {
            return filter_;
        }
        auto wrapping     () const -> const std::tuple<wrapping_e>&
        {
            return wrapping_.pack;
        }
        auto dimensions   () const -> const gl::Vector1u&
        {
            return dimensions_;
        }
        auto mipmap_levels() const -> gl::uint32_t
        {
            return mipmapLevels_;
        }

    private:
        format_e     format_;
        filter_e     filter_;
        wrapping_t   wrapping_;
        gl::Vector1u dimensions_;
        gl::uint32_t mipmapLevels_;
    };
    class texture2d : public gl::Object
    {
    public:
        using format_e   = api::Texture::Format;
        using filter_e   = api::Texture::Filter;
        using wrapping_e = api::Texture::Wrapping;
        using wrapping_t = gl::proxy_t<wrapping_e, wrapping_e>;
         
        texture2d(format_e format, filter_e filter, wrapping_t wrapping, const gl::Vector2u& dimensions)
            : gl::Object{ gl::create_texture(glf::Texture::Target::_2D), [](auto* handle) { gl::delete_texture(*handle); } }
            , format_{ format }, filter_{ filter }, wrapping_{ wrapping }, dimensions_{ dimensions }, mipmapLevels_{ 1u }
        {
            if (filter_ != filter_e::None)
            {
                gl::texture_parameter(handle_, glp::magnification_filter{ gl::map_texture_mag_filter(filter_) });
                gl::texture_parameter(handle_, glp::minification_filter { gl::map_texture_min_filter(filter_) });
                gl::texture_parameter(handle_, glp::maximum_anisotropy  { gl::float32_t{ 1.0f } });

                mipmapLevels_ = math::mipmap_levels(dimensions_);
            }

            const auto& [s, t] = wrapping_.pack;
            gl::texture_parameter(handle_, glp::wrapping_s{ gl::map_texture_wrapping(s) });
            gl::texture_parameter(handle_, glp::wrapping_t{ gl::map_texture_wrapping(t) });

            gl::texture_storage_2d(handle_, gl::map_texture_format(format_), dimensions_, mipmapLevels_);
        }
        texture2d(format_e format, filter_e filter, wrapping_t wrapping, const gl::Vector2u& dimensions, std::span<const gl::byte_t> data)
            : texture2d{ format, filter, wrapping, dimensions }
        {
            copy(format, data);
            generate_mipmap();
        }
        texture2d(format_e format,                                       const gl::Vector2u& dimensions, std::span<const gl::byte_t> data)
            : texture2d{ format, filter_e::Trilinear, wrapping_e::Repeat, dimensions, data } {}

        void bind(gl::binding_t binding) const
        {
            gl::bind_texture_unit(handle_, binding);
        }

        void copy      (format_e format,                    std::span<const gl::byte_t> data)
        {
            copy_range(format, dimensions_, data);
        }
        void copy_range(format_e format, gl::area_t region, std::span<const gl::byte_t> data)
        {
            if (data.empty()) return;
            if (glm::any(glm::greaterThan(region.origin + region.extent, dimensions_))) throw std::out_of_range{ "The given region exceeds texture bounds!" };
            
            gl::texture_sub_image_2d(handle_, gl::map_texture_format_base(format), gl::map_texture_format_type(format), gl::uint32_t{ 0u }, region, data);
        }

        void apply_wrapping (wrapping_t wrapping)
        {
            wrapping_ = wrapping;

            const auto& [s, t] = wrapping_.pack;
            gl::texture_parameter(handle_, glp::wrapping_s{ gl::map_texture_wrapping(s) });
            gl::texture_parameter(handle_, glp::wrapping_t{ gl::map_texture_wrapping(t) });
        }
        void generate_mipmap()
        {
            if (filter_ != filter_e::None) gl::generate_texture_mipmap(handle_);
        }

        void resize(const gl::Vector2u& dimensions)
        {
            if (dimensions != dimensions_) gl::texture2d::operator=(gl::texture2d{ format_, filter_, wrapping_, dimensions });
        }

        auto format       () const -> format_e
        {
            return format_;
        }
        auto filter       () const -> filter_e
        {
            return filter_;
        }
        auto wrapping     () const -> const std::tuple<wrapping_e, wrapping_e>&
        {
            return wrapping_.pack;
        }
        auto dimensions   () const -> const gl::Vector2u&
        {
            return dimensions_;
        }
        auto mipmap_levels() const -> gl::uint32_t
        {
            return mipmapLevels_;
        }

    private:
        format_e     format_;
        filter_e     filter_;
        wrapping_t   wrapping_;
        gl::Vector2u dimensions_;
        gl::uint32_t mipmapLevels_;
    };
    class texture3d : public gl::Object
    {
    public:
        using format_e   = api::Texture::Format;
        using filter_e   = api::Texture::Filter;
        using wrapping_e = api::Texture::Wrapping;
        using wrapping_t = gl::proxy_t<wrapping_e, wrapping_e, wrapping_e>;

        texture3d(format_e format, filter_e filter, wrapping_t wrapping, const gl::Vector3u& dimensions)
            : gl::Object{ gl::create_texture(glf::Texture::Target::_3D), [](auto* handle) { gl::delete_texture(*handle); } }
            , format_{ format }, filter_{ filter }, wrapping_{ wrapping }, dimensions_{ dimensions }, mipmapLevels_{ 1u }
        {
            if (filter_ != filter_e::None)
            {
                gl::texture_parameter(handle_, glp::magnification_filter{ gl::map_texture_mag_filter(filter_) });
                gl::texture_parameter(handle_, glp::minification_filter { gl::map_texture_min_filter(filter_) });
                gl::texture_parameter(handle_, glp::maximum_anisotropy  { gl::float32_t{ 1.0f } });

                mipmapLevels_ = math::mipmap_levels(dimensions_);
            }

            const auto& [s, t, r] = wrapping_.pack;
            gl::texture_parameter(handle_, glp::wrapping_s{ gl::map_texture_wrapping(s) });
            gl::texture_parameter(handle_, glp::wrapping_t{ gl::map_texture_wrapping(t) });
            gl::texture_parameter(handle_, glp::wrapping_r{ gl::map_texture_wrapping(r) });

            gl::texture_storage_3d(handle_, gl::map_texture_format(format_), dimensions_, mipmapLevels_);
        }
        texture3d(format_e format, filter_e filter, wrapping_t wrapping, const gl::Vector3u& dimensions, std::span<const gl::byte_t> data)
            : texture3d{ format, filter, wrapping, dimensions }
        {
            copy(format, data);
            generate_mipmap();
        }
        texture3d(format_e format,                                       const gl::Vector3u& dimensions, std::span<const gl::byte_t> data)
            : texture3d{ format, filter_e::Trilinear, wrapping_e::Repeat, dimensions, data } {}

        void bind(gl::binding_t binding) const
        {
            gl::bind_texture_unit(handle_, binding);
        }

        void copy      (format_e format,                      std::span<const gl::byte_t> data)
        {
            copy_range(format, dimensions_, data);
        }
        void copy_range(format_e format, gl::volume_t region, std::span<const gl::byte_t> data)
        {
            if (data.empty()) return;
            if (glm::any(glm::greaterThan(region.origin + region.extent, dimensions_))) throw std::out_of_range{ "The given region exceeds texture bounds!" };

            gl::texture_sub_image_3d(handle_, gl::map_texture_format_base(format), gl::map_texture_format_type(format), gl::uint32_t{ 0u }, region, data);
        }

        void apply_wrapping (wrapping_t wrapping)
        {
            wrapping_ = wrapping;

            const auto& [s, t, r] = wrapping_.pack;
            gl::texture_parameter(handle_, glp::wrapping_s{ gl::map_texture_wrapping(s) });
            gl::texture_parameter(handle_, glp::wrapping_t{ gl::map_texture_wrapping(t) });
            gl::texture_parameter(handle_, glp::wrapping_r{ gl::map_texture_wrapping(r) });
        }
        void generate_mipmap()
        {
            if (filter_ != filter_e::None) gl::generate_texture_mipmap(handle_);
        }

        void resize(const gl::Vector3u& dimensions)
        {
            gl::todo();
        }

        auto format       () const -> format_e
        {
            return format_;
        }
        auto filter       () const -> filter_e
        {
            return filter_;
        }
        auto wrapping     () const -> const std::tuple<wrapping_e, wrapping_e, wrapping_e>&
        {
            return wrapping_.pack;
        }
        auto dimensions   () const -> const gl::Vector3u&
        {
            return dimensions_;
        }
        auto mipmap_levels() const -> gl::uint32_t
        {
            return mipmapLevels_;
        }

    private:
        format_e     format_;
        filter_e     filter_;
        wrapping_t   wrapping_;
        gl::Vector3u dimensions_;
        gl::uint32_t mipmapLevels_;
    };

    class texture2d_ms : public gl::Object
    {
    public:
        using format_e = api::Texture::Format;

        texture2d_ms(format_e format, const gl::Vector2u& dimensions, gl::uint32_t samples)
            : gl::Object{ gl::create_texture(glf::Texture::Target::_2DMultisample), [](auto* handle) { gl::delete_texture(*handle); } }
            , format_{ format }, dimensions_{ dimensions }, samples_{ samples }
        {
             gl::texture_storage_2d_multisample(handle_, gl::map_texture_format(format_), dimensions_, samples_);
        }

        void bind(gl::binding_t binding) const
        {
            gl::bind_texture_unit(handle_, binding);
        }
        
        void resize(const gl::Vector2u& dimensions)
        {
            gl::todo();
        }

        auto format    () const -> format_e
        {
            return format_;
        }
        auto dimensions() const -> const gl::Vector2u&
        {
            return dimensions_;
        }
        auto samples   () const -> gl::uint32_t
        {
            return samples_;
        }

    private:
        format_e     format_;
        gl::Vector2u dimensions_;
        gl::uint32_t samples_;
    };
    class texture3d_ms : public gl::Object
    {
    public:
        using format_e = api::Texture::Format;

        texture3d_ms(format_e format, const gl::Vector3u& dimensions, gl::uint32_t samples)
            : gl::Object{ gl::create_texture(glf::Texture::Target::_2DMultisampleArray), [](auto* handle) { gl::delete_texture(*handle); } }
            , format_{ format }, dimensions_{ dimensions }, samples_{ samples }
        {
             gl::texture_storage_3d_multisample(handle_, gl::map_texture_format(format_), dimensions_, samples_);
        }

        void bind(gl::binding_t binding) const
        {
            gl::bind_texture_unit(handle_, binding);
        }

        void resize(const gl::Vector3u& dimensions)
        {
            gl::todo();
        }

        auto format    () const -> format_e
        {
            return format_;
        }
        auto dimensions() const -> const gl::Vector3u&
        {
            return dimensions_;
        }
        auto samples   () const -> gl::uint32_t
        {
            return samples_;
        }

    private:
        format_e       format_;
        gl::Vector3u dimensions_;
        gl::uint32_t samples_;
    };
}
