#pragma once

#include <stdafx.hpp>

#include <fox/rendering/api/opengl/opengl.hpp>
#include <fox/rendering/base/texture/texture.hpp>

import fox.math.texture;
import fox.rendering.api.opengl.mapping;

namespace fox::gfx::api::gl
{
    class Texture1D : public gl::Object
    {
    public:
        using Format        = api::Texture::Format;
        using Filter        = api::Texture::Filter;
        using Wrapping      = api::Texture::Wrapping;
        using WrappingProxy = gl::proxy_t<Wrapping>;

        Texture1D(Format format, Filter filter, WrappingProxy wrapping, const gl::Vector1u& dimensions)
            : gl::Object{ gl::create_texture(glf::Texture::Target::_1D), [](auto* handle) { gl::delete_texture(*handle); } }
            , format_{ format }, filter_{ filter }, wrapping_{ wrapping }, dimensions_{ dimensions }, mipmapLevels_{ 1u }
        {
            if (filter_ != Filter::None)
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
        Texture1D(Format format, Filter filter, WrappingProxy wrapping, const gl::Vector1u& dimensions, std::span<const gl::byte_t> data)
            : Texture1D{ format, filter, wrapping, dimensions }
        {
            copy(format, data);
            generate_mipmap();
        }
        Texture1D(Format format,                                        const gl::Vector1u& dimensions, std::span<const gl::byte_t> data)
            : Texture1D{ format, Filter::Trilinear, Wrapping::Repeat, dimensions, data } {}

        void bind(gl::binding_t binding) const
        {
            gl::bind_texture_unit(handle_, binding);
        }

        void copy      (Format format,                      std::span<const gl::byte_t> data)
        {
            copy_range(format, dimensions_, data);
        }
        void copy_range(Format format, gl::length_t region, std::span<const gl::byte_t> data)
        {
            if (data.empty()) return;
            if (glm::any(glm::greaterThan(region.origin + region.extent, dimensions_))) throw std::out_of_range{ "The given region exceeds texture bounds!" };

            gl::texture_sub_image_1d(handle_, gl::map_texture_format_base(format), gl::map_texture_format_type(format), gl::uint32_t{ 0u }, region, data);
        }

        void apply_wrapping (WrappingProxy wrapping)
        {
            wrapping_ = wrapping;

            const auto& [s] = wrapping_.pack;
            gl::texture_parameter(handle_, glp::wrapping_s{ gl::map_texture_wrapping(s) });
        }
        void generate_mipmap()
        {
            if (filter_ != Filter::None) gl::generate_texture_mipmap(handle_);
        }

        void resize(const gl::Vector1u& dimensions)
        {
            gl::todo();
        }

        auto format       () const -> Format
        {
            return format_;
        }
        auto filter       () const -> Filter
        {
            return filter_;
        }
        auto wrapping     () const -> const std::tuple<Wrapping>&
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
        Format        format_;
        Filter        filter_;
        WrappingProxy wrapping_;
        gl::Vector1u  dimensions_;
        gl::uint32_t  mipmapLevels_;
    };
    class Texture2D : public gl::Object
    {
    public:
        using Format        = api::Texture::Format;
        using Filter        = api::Texture::Filter;
        using Wrapping      = api::Texture::Wrapping;
        using WrappingProxy = gl::proxy_t<Wrapping, Wrapping>;
         
        Texture2D(Format format, Filter filter, WrappingProxy wrapping, const gl::Vector2u& dimensions)
            : gl::Object{ gl::create_texture(glf::Texture::Target::_2D), [](auto* handle) { gl::delete_texture(*handle); } }
            , format_{ format }, filter_{ filter }, wrapping_{ wrapping }, dimensions_{ dimensions }, mipmapLevels_{ 1u }
        {
            if (filter_ != Filter::None)
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
        Texture2D(Format format, Filter filter, WrappingProxy wrapping, const gl::Vector2u& dimensions, std::span<const gl::byte_t> data)
            : Texture2D{ format, filter, wrapping, dimensions }
        {
            copy(format, data);
            generate_mipmap();
        }
        Texture2D(Format format,                                        const gl::Vector2u& dimensions, std::span<const gl::byte_t> data)
            : Texture2D{ format, Filter::Trilinear, Wrapping::Repeat, dimensions, data } {}

        void bind(gl::binding_t binding) const
        {
            gl::bind_texture_unit(handle_, binding);
        }

        void copy      (Format format,                    std::span<const gl::byte_t> data)
        {
            copy_range(format, dimensions_, data);
        }
        void copy_range(Format format, gl::area_t region, std::span<const gl::byte_t> data)
        {
            if (data.empty()) return;
            if (glm::any(glm::greaterThan(region.origin + region.extent, dimensions_))) throw std::out_of_range{ "The given region exceeds texture bounds!" };
            
            gl::texture_sub_image_2d(handle_, gl::map_texture_format_base(format), gl::map_texture_format_type(format), gl::uint32_t{ 0u }, region, data);
        }

        void apply_wrapping (WrappingProxy wrapping)
        {
            wrapping_ = wrapping;

            const auto& [s, t] = wrapping_.pack;
            gl::texture_parameter(handle_, glp::wrapping_s{ gl::map_texture_wrapping(s) });
            gl::texture_parameter(handle_, glp::wrapping_t{ gl::map_texture_wrapping(t) });
        }
        void generate_mipmap()
        {
            if (filter_ != Filter::None) gl::generate_texture_mipmap(handle_);
        }

        void resize(const gl::Vector2u& dimensions)
        {
            if (dimensions != dimensions_) this->operator=(gl::Texture2D{ format_, filter_, wrapping_, dimensions });
        }

        auto format       () const -> Format
        {
            return format_;
        }
        auto filter       () const -> Filter
        {
            return filter_;
        }
        auto wrapping     () const -> const std::tuple<Wrapping, Wrapping>&
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
        Format        format_;
        Filter        filter_;
        WrappingProxy wrapping_;
        gl::Vector2u  dimensions_;
        gl::uint32_t  mipmapLevels_;
    };
    class Texture3D : public gl::Object
    {
    public:
        using Format        = api::Texture::Format;
        using Filter        = api::Texture::Filter;
        using Wrapping      = api::Texture::Wrapping;
        using WrappingProxy = gl::proxy_t<Wrapping, Wrapping, Wrapping>;

        Texture3D(Format format, Filter filter, WrappingProxy wrapping, const gl::Vector3u& dimensions)
            : gl::Object{ gl::create_texture(glf::Texture::Target::_3D), [](auto* handle) { gl::delete_texture(*handle); } }
            , format_{ format }, filter_{ filter }, wrapping_{ wrapping }, dimensions_{ dimensions }, mipmapLevels_{ 1u }
        {
            if (filter_ != Filter::None)
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
        Texture3D(Format format, Filter filter, WrappingProxy wrapping, const gl::Vector3u& dimensions, std::span<const gl::byte_t> data)
            : Texture3D{ format, filter, wrapping, dimensions }
        {
            copy(format, data);
            generate_mipmap();
        }
        Texture3D(Format format,                                        const gl::Vector3u& dimensions, std::span<const gl::byte_t> data)
            : Texture3D{ format, Filter::Trilinear, Wrapping::Repeat, dimensions, data } {}

        void bind(gl::binding_t binding) const
        {
            gl::bind_texture_unit(handle_, binding);
        }

        void copy      (Format format,                      std::span<const gl::byte_t> data)
        {
            copy_range(format, dimensions_, data);
        }
        void copy_range(Format format, gl::volume_t region, std::span<const gl::byte_t> data)
        {
            if (data.empty()) return;
            if (glm::any(glm::greaterThan(region.origin + region.extent, dimensions_))) throw std::out_of_range{ "The given region exceeds texture bounds!" };

            gl::texture_sub_image_3d(handle_, gl::map_texture_format_base(format), gl::map_texture_format_type(format), gl::uint32_t{ 0u }, region, data);
        }

        void apply_wrapping (WrappingProxy wrapping)
        {
            wrapping_ = wrapping;

            const auto& [s, t, r] = wrapping_.pack;
            gl::texture_parameter(handle_, glp::wrapping_s{ gl::map_texture_wrapping(s) });
            gl::texture_parameter(handle_, glp::wrapping_t{ gl::map_texture_wrapping(t) });
            gl::texture_parameter(handle_, glp::wrapping_r{ gl::map_texture_wrapping(r) });
        }
        void generate_mipmap()
        {
            if (filter_ != Filter::None) gl::generate_texture_mipmap(handle_);
        }

        void resize(const gl::Vector3u& dimensions)
        {
            gl::todo();
        }

        auto format       () const -> Format
        {
            return format_;
        }
        auto filter       () const -> Filter
        {
            return filter_;
        }
        auto wrapping     () const -> const std::tuple<Wrapping, Wrapping, Wrapping>&
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
        Format        format_;
        Filter        filter_;
        WrappingProxy wrapping_;
        gl::Vector3u  dimensions_;
        gl::uint32_t  mipmapLevels_;
    };

    class Texture2DMultisample : public gl::Object
    {
    public:
        using Format = api::Texture::Format;

        Texture2DMultisample(Format format, const gl::Vector2u& dimensions, gl::uint32_t samples)
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

        auto format    () const -> Format
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
        Format       format_;
        gl::Vector2u dimensions_;
        gl::uint32_t samples_;
    };
    class Texture3DMultisample : public gl::Object
    {
    public:
        using Format = api::Texture::Format;

        Texture3DMultisample(Format format, const gl::Vector3u& dimensions, gl::uint32_t samples)
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

        auto format    () const -> Format
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
        Format       format_;
        gl::Vector3u dimensions_;
        gl::uint32_t samples_;
    };
}
