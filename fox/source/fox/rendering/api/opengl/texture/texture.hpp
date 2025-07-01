#pragma once

#include <stdafx.hpp>

#include <fox/rendering/api/opengl/opengl.hpp>
#include <fox/rendering/base/texture/texture.hpp>

namespace fox::gfx::api::gl
{
    class Texture1D : public gl::Object
    {
    public:
        using Format   = api::Texture::Format;
        using Filter   = api::Texture::Filter;
        using Wrapping = api::Texture::Wrapping;

         Texture1D(Format format, Filter filter, Wrapping wrapping, const gl::Vector1u& dimensions)
            : format_{ format }, filter_{ filter }, wrapping_{ wrapping }, dimensions_{ dimensions }
        {
            handle_ = gl::create_texture(glf::Texture::Target::_1D);

            if (filter_ !=Filter::None)
            {
                gl::texture_parameter(handle_, glp::magnification_filter{ gl::map_texture_mag_filter(filter_) });
                gl::texture_parameter(handle_, glp::minification_filter { gl::map_texture_min_filter(filter_) });
                gl::texture_parameter(handle_, glp::maximum_anisotropy  { gl::float32_t{ 1.0f } });

                mipmapLevels_ = math::mipmap_levels(dimensions_);
            }

            gl::texture_parameter(handle_, glp::wrapping_s{ gl::map_texture_wrapping(wrapping_.at(0u)) });
            gl::texture_parameter(handle_, glp::wrapping_t{ gl::map_texture_wrapping(wrapping_.at(1u)) });

            gl::texture_storage_1d(handle_, gl::map_texture_format(format_), dimensions_, mipmapLevels_);
        }
         Texture1D(Format format, Filter filter, Wrapping wrapping, const gl::Vector1u& dimensions, std::span<const gl::byte_t> data)
            : Texture1D{ format, filter, wrapping, dimensions }
        {
            copy(format, data);
            generate_mipmap();
        }
         Texture1D(Format format,                                   const gl::Vector1u& dimensions, std::span<const gl::byte_t> data)
             : Texture1D{ format, Filter::Trilinear, Wrapping::Repeat, dimensions, data } {}
        ~Texture1D()
        {
            gl::delete_texture(handle_);
        }

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

        void apply_wrapping (Wrapping s)
        {
            wrapping_ = { s };

            gl::texture_parameter(handle_, glp::wrapping_s{ gl::map_texture_wrapping(wrapping_.at(0u)) });
        }
        void generate_mipmap()
        {
            if (filter_ != Filter::None) gl::generate_texture_mipmap(handle_);
        }

        void resize(const gl::Vector1u& dimensions)
        {
            auto handle       = gl::create_texture(glf::Texture::Target::_1D);
            auto mipmapLevels = math::mipmap_levels(dimensions);

            gl::texture_storage_1d (handle, gl::map_texture_format(format_), dimensions, mipmapLevels);
            __debugbreak();
            //gl::copy_image_sub_data(handle_, handle, glf::Texture::Target::_1D, glf::Texture::Target::_1D, gl::Vector4u{ dimensions_, 0u, 0u, 0u }, gl::Vector4u{ dimensions, 0u, 0u, 0u });
            gl::delete_texture     (handle_);

            handle_       = handle;
            dimensions_   = dimensions;
            mipmapLevels_ = mipmapLevels;

            generate_mipmap();
        }

        auto format       () const
        {
            return format_;
        }
        auto filter       () const
        {
            return filter_;
        }
        auto wrapping     () const -> std::span<const Wrapping, 1u>
        {
            return wrapping_;
        }
        auto dimensions   () const
        {
            return dimensions_;
        }
        auto mipmap_levels() const
        {
            return mipmapLevels_;
        }

    private:
        Format                  format_{};
        Filter                  filter_{};
        std::array<Wrapping, 1> wrapping_{};
        gl::Vector1u            dimensions_{};
        gl::uint32_t            mipmapLevels_{};
    };
    class Texture2D : public gl::Object
    {
    public:
        using Format   = api::Texture::Format;
        using Filter   = api::Texture::Filter;
        using Wrapping = api::Texture::Wrapping;
         
         Texture2D(Format format, Filter filter, Wrapping wrapping, const gl::Vector2u& dimensions)
             : format_{ format }, filter_{ filter }, wrapping_{ wrapping, wrapping }, dimensions_{ dimensions }, mipmapLevels_{ 1u }
        {
            handle_ = gl::create_texture(glf::Texture::Target::_2D);

            if (filter_ !=Filter::None)
            {
                gl::texture_parameter(handle_, glp::magnification_filter{ gl::map_texture_mag_filter(filter_) });
                gl::texture_parameter(handle_, glp::minification_filter { gl::map_texture_min_filter(filter_) });
                gl::texture_parameter(handle_, glp::maximum_anisotropy  { gl::float32_t{ 1.0f } });

                mipmapLevels_ = math::mipmap_levels(dimensions_);
            }

            gl::texture_parameter(handle_, glp::wrapping_s{ gl::map_texture_wrapping(wrapping_.at(0u)) });
            gl::texture_parameter(handle_, glp::wrapping_t{ gl::map_texture_wrapping(wrapping_.at(1u)) });

            gl::texture_storage_2d(handle_, gl::map_texture_format(format_), dimensions_, mipmapLevels_);
        }
         Texture2D(Format format, Filter filter, Wrapping wrapping, const gl::Vector2u& dimensions, std::span<const gl::byte_t> data)
            : Texture2D{ format, filter, wrapping, dimensions }
        {
            copy(format, data);
            generate_mipmap();
        }
         Texture2D(Format format,                                   const gl::Vector2u& dimensions, std::span<const gl::byte_t> data)
             : Texture2D{ format, Filter::Trilinear, Wrapping::Repeat, dimensions, data } {}
        ~Texture2D()
        {
            gl::delete_texture(handle_);
        }

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

        void apply_wrapping (Wrapping s, Wrapping t)
        {
            wrapping_ = { s, t };

            gl::texture_parameter(handle_, glp::wrapping_s{ gl::map_texture_wrapping(wrapping_.at(0u)) });
            gl::texture_parameter(handle_, glp::wrapping_t{ gl::map_texture_wrapping(wrapping_.at(1u)) });
        }
        void generate_mipmap()
        {
            if (filter_ != Filter::None) gl::generate_texture_mipmap(handle_);
        }

        void resize(const gl::Vector2u& dimensions)
        {
            auto handle       = gl::create_texture(glf::Texture::Target::_2D);
            auto mipmapLevels = math::mipmap_levels(dimensions);
            
            gl::texture_storage_2d(handle, gl::map_texture_format(format_), dimensions, mipmapLevels);
            __debugbreak();
            //gl::copy_image_sub_data(handle_, handle, glf::Texture::Target::_2D, glf::Texture::Target::_2D, gl::Vector4u{ dimensions_, 0u, 0u }, gl::Vector4u{ dimensions, 0u, 0u });
            gl::delete_texture(handle_);

            handle_       = handle;
            dimensions_   = dimensions;
            mipmapLevels_ = mipmapLevels;

            generate_mipmap();
        }

        auto format       () const
        {
            return format_;
        }
        auto filter       () const
        {
            return filter_;
        }
        auto wrapping     () const -> std::span<const Wrapping, 2u>
        {
            return wrapping_;
        }
        auto dimensions   () const
        {
            return dimensions_;
        }
        auto mipmap_levels() const
        {
            return mipmapLevels_;
        }

    private:
        Format                   format_{};
        Filter                   filter_{};
        std::array<Wrapping, 2u> wrapping_{};
        gl::Vector2u             dimensions_{};
        gl::uint32_t             mipmapLevels_{};
    };
    class Texture3D : public gl::Object
    {
    public:
        using Format   = api::Texture::Format;
        using Filter   = api::Texture::Filter;
        using Wrapping = api::Texture::Wrapping;

         Texture3D(Format format, Filter filter, Wrapping wrapping, const gl::Vector3u& dimensions)
            : format_{ format }, filter_{ filter }, wrapping_{ wrapping, wrapping }, dimensions_{ dimensions }
        {
            handle_ = gl::create_texture(glf::Texture::Target::_3D);

            if (filter_ !=Filter::None)
            {
                gl::texture_parameter(handle_, glp::magnification_filter{ gl::map_texture_mag_filter(filter_) });
                gl::texture_parameter(handle_, glp::minification_filter { gl::map_texture_min_filter(filter_) });
                gl::texture_parameter(handle_, glp::maximum_anisotropy  { gl::float32_t{ 1.0f } });

                mipmapLevels_ = math::mipmap_levels(dimensions_);
            }

            gl::texture_parameter(handle_, glp::wrapping_s{ gl::map_texture_wrapping(wrapping_.at(0u)) });
            gl::texture_parameter(handle_, glp::wrapping_t{ gl::map_texture_wrapping(wrapping_.at(1u)) });
            gl::texture_parameter(handle_, glp::wrapping_r{ gl::map_texture_wrapping(wrapping_.at(2u)) });

            gl::texture_storage_3d(handle_, gl::map_texture_format(format_), dimensions_, mipmapLevels_);
        }
         Texture3D(Format format, Filter filter, Wrapping wrapping, const gl::Vector3u& dimensions, std::span<const gl::byte_t> data)
            : Texture3D{ format, filter, wrapping, dimensions }
        {
            copy(format, data);
            generate_mipmap();
        }
         Texture3D(Format format,                                   const gl::Vector3u& dimensions, std::span<const gl::byte_t> data)
             : Texture3D{ format, Filter::Trilinear, Wrapping::Repeat, dimensions, data } {}
        ~Texture3D()
        {
            gl::delete_texture(handle_);
        }

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

        void apply_wrapping (Wrapping s, Wrapping t, Wrapping r)
        {
            wrapping_ = { s, t, r };

            gl::texture_parameter(handle_, glp::wrapping_s{ gl::map_texture_wrapping(wrapping_.at(0u)) });
            gl::texture_parameter(handle_, glp::wrapping_t{ gl::map_texture_wrapping(wrapping_.at(1u)) });
            gl::texture_parameter(handle_, glp::wrapping_r{ gl::map_texture_wrapping(wrapping_.at(2u)) });
        }
        void generate_mipmap()
        {
            if (filter_ != Filter::None) gl::generate_texture_mipmap(handle_);
        }

        void resize(const gl::Vector3u& dimensions)
        {
            auto handle       = gl::create_texture(glf::Texture::Target::_3D);
            auto mipmapLevels = math::mipmap_levels(dimensions);

            gl::texture_storage_3d (handle, gl::map_texture_format(format_), dimensions, mipmapLevels);
            __debugbreak();
            //gl::copy_image_sub_data(handle_, handle, glf::Texture::Target::_3D, glf::Texture::Target::_3D, gl::Vector4u{ dimensions_, 0u }, gl::Vector4u{ dimensions, 0u });
            gl::delete_texture     (handle_);

            handle_       = handle;
            dimensions_   = dimensions;
            mipmapLevels_ = mipmapLevels;

            generate_mipmap();
        }

        auto format       () const
        {
            return format_;
        }
        auto filter       () const
        {
            return filter_;
        }
        auto wrapping     () const -> std::span<const Wrapping, 3u>
        {
            return wrapping_;
        }
        auto dimensions   () const
        {
            return dimensions_;
        }
        auto mipmap_levels() const
        {
            return mipmapLevels_;
        }

    private:
        Format                  format_{};
        Filter                  filter_{};
        std::array<Wrapping, 3> wrapping_{};
        gl::Vector3u            dimensions_{};
        gl::uint32_t            mipmapLevels_{};
    };

    class Texture2DMultisample : public gl::Object
    {
    public:
        using Format = api::Texture::Format;

         Texture2DMultisample(Format format, const gl::Vector2u& dimensions, gl::uint32_t samples)
             : format_{ format }, dimensions_{ dimensions }, samples_{ samples }
        {
             handle_ = gl::create_texture(glf::Texture::Target::_2DMultisample);
             
             gl::texture_storage_2d_multisample(handle_, gl::map_texture_format(format_), dimensions_, samples_);
        }
        ~Texture2DMultisample()
        {
            gl::delete_texture(handle_);
        }

        void bind(gl::binding_t binding) const
        {
            gl::bind_texture_unit(handle_, binding);
        }
        
        void resize(const gl::Vector2u& dimensions)
        {
            auto handle = gl::create_texture(glf::Texture::Target::_2DMultisample);

            gl::texture_storage_2d_multisample(handle, gl::map_texture_format(format_), dimensions, samples_);
            gl::delete_texture                (handle_);

            handle_     = handle;
            dimensions_ = dimensions;
        }

        auto format    () const
        {
            return format_;
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
        Format       format_{};
        gl::Vector2u dimensions_{};
        gl::uint32_t samples_{};
    };
    class Texture3DMultisample : public gl::Object
    {
    public:
        using Format = api::Texture::Format;

         Texture3DMultisample(Format format, const gl::Vector3u& dimensions, gl::uint32_t samples)
             : format_{ format }, dimensions_{ dimensions }, samples_{ samples }
        {
             handle_ = gl::create_texture(glf::Texture::Target::_2DMultisampleArray);
             
             gl::texture_storage_3d_multisample(handle_, gl::map_texture_format(format_), dimensions_, samples_);
        }
        ~Texture3DMultisample()
        {
            gl::delete_texture(handle_);
        }

        void bind(gl::binding_t binding) const
        {
            gl::bind_texture_unit(handle_, binding);
        }

        void resize(const gl::Vector3u& dimensions)
        {
            auto handle = gl::create_texture(glf::Texture::Target::_2DMultisampleArray);

            gl::texture_storage_3d_multisample(handle, gl::map_texture_format(format_), dimensions, samples_);
            gl::delete_texture                (handle_);

            handle_     = handle;
            dimensions_ = dimensions;
        }

        auto format    () const
        {
            return format_;
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
        Format       format_{};
        gl::Vector3u dimensions_{};
        gl::uint32_t samples_{};
    };
}
