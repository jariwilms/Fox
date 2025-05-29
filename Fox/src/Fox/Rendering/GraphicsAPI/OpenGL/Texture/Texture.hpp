#pragma once

#include "stdafx.hpp"

#include "Fox/Rendering/API/Texture/Texture.hpp"
#include "Fox/Rendering/GraphicsAPI/OpenGL/OpenGL.hpp"

namespace fox::gfx::api::gl
{
    class Texture1D : public gl::Object
    {
    public:
        using Format   = api::Texture::Format;
        using Filter   = api::Texture::Filter;
        using Wrapping = api::Texture::Wrapping;

         Texture1D(Format format, Filter filter, Wrapping wrapping, const gl::Vector1u& dimensions)
            : m_format{ format }, m_filter{ filter }, m_wrapping{ wrapping }, m_dimensions{ dimensions }
        {
            m_handle = gl::create_texture(glf::Texture::Target::_1D);

            if (m_filter !=Filter::None)
            {
                gl::texture_parameter(m_handle, glp::magnification_filter{ gl::map_texture_mag_filter(m_filter) });
                gl::texture_parameter(m_handle, glp::minification_filter { gl::map_texture_min_filter(m_filter) });
                gl::texture_parameter(m_handle, glp::maximum_anisotropy  { gl::float32_t{ 1.0f } });

                m_mipmapLevels = api::Texture::calculate_mipmap_levels(m_dimensions);
            }

            gl::texture_parameter(m_handle, glp::wrapping_s{ gl::map_texture_wrapping(m_wrapping.at(0u)) });
            gl::texture_parameter(m_handle, glp::wrapping_t{ gl::map_texture_wrapping(m_wrapping.at(1u)) });

            gl::texture_storage_1d(m_handle, gl::map_texture_format(m_format), m_dimensions, m_mipmapLevels);
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
            gl::delete_texture(m_handle);
        }

        void bind(gl::binding_t binding) const
        {
            gl::bind_texture_unit(m_handle, binding);
        }

        void copy      (Format format,                      std::span<const gl::byte_t> data)
        {
            copy_range(format, m_dimensions, data);
        }
        void copy_range(Format format, gl::length_t region, std::span<const gl::byte_t> data)
        {
            if (data.empty()) return;
            if (glm::any(glm::greaterThan(region.origin + region.extent, m_dimensions))) throw std::out_of_range{ "The given region exceeds texture bounds!" };

            gl::texture_sub_image_1d(m_handle, gl::map_texture_format_base(format), gl::map_texture_format_type(format), gl::uint32_t{ 0u }, region, data);
        }

        void apply_wrapping (Wrapping s)
        {
            m_wrapping = { s };

            gl::texture_parameter(m_handle, glp::wrapping_s{ gl::map_texture_wrapping(m_wrapping.at(0u)) });
        }
        void generate_mipmap()
        {
            if (m_filter != Filter::None) gl::generate_texture_mipmap(m_handle);
        }

        void resize(const gl::Vector1u& dimensions)
        {
            auto handle       = gl::create_texture(glf::Texture::Target::_1D);
            auto mipmapLevels = api::Texture::calculate_mipmap_levels(dimensions);

            gl::texture_storage_1d (handle, gl::map_texture_format(m_format), dimensions, mipmapLevels);
            __debugbreak();
            //gl::copy_image_sub_data(m_handle, handle, glf::Texture::Target::_1D, glf::Texture::Target::_1D, gl::Vector4u{ m_dimensions, 0u, 0u, 0u }, gl::Vector4u{ dimensions, 0u, 0u, 0u });
            gl::delete_texture     (m_handle);

            m_handle       = handle;
            m_dimensions   = dimensions;
            m_mipmapLevels = mipmapLevels;

            generate_mipmap();
        }

        auto format       () const
        {
            return m_format;
        }
        auto filter       () const
        {
            return m_filter;
        }
        auto wrapping     () const
        {
            return std::span<const Wrapping>{ m_wrapping };
        }
        auto dimensions   () const
        {
            return m_dimensions;
        }
        auto mipmap_levels() const
        {
            return m_mipmapLevels;
        }

    private:
        Format                  m_format{};
        Filter                  m_filter{};
        std::array<Wrapping, 1> m_wrapping{};
        gl::Vector1u            m_dimensions{};
        gl::uint32_t            m_mipmapLevels{};
    };
    class Texture2D : public gl::Object
    {
    public:
        using Format   = api::Texture::Format;
        using Filter   = api::Texture::Filter;
        using Wrapping = api::Texture::Wrapping;
         
         Texture2D(Format format, Filter filter, Wrapping wrapping, const gl::Vector2u& dimensions)
             : m_format{ format }, m_filter{ filter }, m_wrapping{ wrapping, wrapping }, m_dimensions{ dimensions }, m_mipmapLevels{ 1u }
        {
            m_handle = gl::create_texture(glf::Texture::Target::_2D);

            if (m_filter !=Filter::None)
            {
                gl::texture_parameter(m_handle, glp::magnification_filter{ gl::map_texture_mag_filter(m_filter) });
                gl::texture_parameter(m_handle, glp::minification_filter { gl::map_texture_min_filter(m_filter) });
                gl::texture_parameter(m_handle, glp::maximum_anisotropy  { gl::float32_t{ 1.0f } });

                m_mipmapLevels = api::Texture::calculate_mipmap_levels(m_dimensions);
            }

            gl::texture_parameter(m_handle, glp::wrapping_s{ gl::map_texture_wrapping(m_wrapping.at(0u)) });
            gl::texture_parameter(m_handle, glp::wrapping_t{ gl::map_texture_wrapping(m_wrapping.at(1u)) });

            gl::texture_storage_2d(m_handle, gl::map_texture_format(m_format), m_dimensions, m_mipmapLevels);
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
            gl::delete_texture(m_handle);
        }

        void bind(gl::binding_t binding) const
        {
            gl::bind_texture_unit(m_handle, binding);
        }

        void copy      (Format format,                    std::span<const gl::byte_t> data)
        {
            copy_range(format, m_dimensions, data);
        }
        void copy_range(Format format, gl::area_t region, std::span<const gl::byte_t> data)
        {
            if (data.empty()) return;
            if (glm::any(glm::greaterThan(region.origin + region.extent, m_dimensions))) throw std::out_of_range{ "The given region exceeds texture bounds!" };
            
            gl::texture_sub_image_2d(m_handle, gl::map_texture_format_base(format), gl::map_texture_format_type(format), gl::uint32_t{ 0u }, region, data);
        }

        void apply_wrapping (Wrapping s, Wrapping t)
        {
            m_wrapping = { s, t };

            gl::texture_parameter(m_handle, glp::wrapping_s{ gl::map_texture_wrapping(m_wrapping.at(0u)) });
            gl::texture_parameter(m_handle, glp::wrapping_t{ gl::map_texture_wrapping(m_wrapping.at(1u)) });
        }
        void generate_mipmap()
        {
            if (m_filter != Filter::None) gl::generate_texture_mipmap(m_handle);
        }

        void resize(const gl::Vector2u& dimensions)
        {
            auto handle       = gl::create_texture(glf::Texture::Target::_2D);
            auto mipmapLevels = api::Texture::calculate_mipmap_levels(dimensions);

            gl::texture_storage_2d (handle, gl::map_texture_format(m_format), dimensions, mipmapLevels);
            __debugbreak();
            //gl::copy_image_sub_data(m_handle, handle, glf::Texture::Target::_2D, glf::Texture::Target::_2D, gl::Vector4u{ m_dimensions, 0u, 0u }, gl::Vector4u{ dimensions, 0u, 0u });
            gl::delete_texture     (m_handle);

            m_handle       = handle;
            m_dimensions   = dimensions;
            m_mipmapLevels = mipmapLevels;

            generate_mipmap();
        }

        auto format       () const
        {
            return m_format;
        }
        auto filter       () const
        {
            return m_filter;
        }
        auto wrapping     () const
        {
            return std::span<const Wrapping>{ m_wrapping };
        }
        auto dimensions   () const
        {
            return m_dimensions;
        }
        auto mipmap_levels() const
        {
            return m_mipmapLevels;
        }

    private:
        Format                   m_format{};
        Filter                   m_filter{};
        std::array<Wrapping, 2u> m_wrapping{};
        gl::Vector2u             m_dimensions{};
        gl::uint32_t             m_mipmapLevels{};
    };
    class Texture3D : public gl::Object
    {
    public:
        using Format   = api::Texture::Format;
        using Filter   = api::Texture::Filter;
        using Wrapping = api::Texture::Wrapping;

         Texture3D(Format format, Filter filter, Wrapping wrapping, const gl::Vector3u& dimensions)
            : m_format{ format }, m_filter{ filter }, m_wrapping{ wrapping, wrapping }, m_dimensions{ dimensions }
        {
            m_handle = gl::create_texture(glf::Texture::Target::_3D);

            if (m_filter !=Filter::None)
            {
                gl::texture_parameter(m_handle, glp::magnification_filter{ gl::map_texture_mag_filter(m_filter) });
                gl::texture_parameter(m_handle, glp::minification_filter { gl::map_texture_min_filter(m_filter) });
                gl::texture_parameter(m_handle, glp::maximum_anisotropy  { gl::float32_t{ 1.0f } });

                m_mipmapLevels = api::Texture::calculate_mipmap_levels(m_dimensions);
            }

            gl::texture_parameter(m_handle, glp::wrapping_s{ gl::map_texture_wrapping(m_wrapping.at(0u)) });
            gl::texture_parameter(m_handle, glp::wrapping_t{ gl::map_texture_wrapping(m_wrapping.at(1u)) });
            gl::texture_parameter(m_handle, glp::wrapping_r{ gl::map_texture_wrapping(m_wrapping.at(2u)) });

            gl::texture_storage_3d(m_handle, gl::map_texture_format(m_format), m_dimensions, m_mipmapLevels);
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
            gl::delete_texture(m_handle);
        }

        void bind(gl::binding_t binding) const
        {
            gl::bind_texture_unit(m_handle, binding);
        }

        void copy      (Format format,                      std::span<const gl::byte_t> data)
        {
            copy_range(format, m_dimensions, data);
        }
        void copy_range(Format format, gl::volume_t region, std::span<const gl::byte_t> data)
        {
            if (data.empty()) return;
            if (glm::any(glm::greaterThan(region.origin + region.extent, m_dimensions))) throw std::out_of_range{ "The given region exceeds texture bounds!" };

            gl::texture_sub_image_3d(m_handle, gl::map_texture_format_base(format), gl::map_texture_format_type(format), gl::uint32_t{ 0u }, region, data);
        }

        void apply_wrapping (Wrapping s, Wrapping t, Wrapping r)
        {
            m_wrapping = { s, t, r };

            gl::texture_parameter(m_handle, glp::wrapping_s{ gl::map_texture_wrapping(m_wrapping.at(0u)) });
            gl::texture_parameter(m_handle, glp::wrapping_t{ gl::map_texture_wrapping(m_wrapping.at(1u)) });
            gl::texture_parameter(m_handle, glp::wrapping_r{ gl::map_texture_wrapping(m_wrapping.at(2u)) });
        }
        void generate_mipmap()
        {
            if (m_filter != Filter::None) gl::generate_texture_mipmap(m_handle);
        }

        void resize(const gl::Vector3u& dimensions)
        {
            auto handle       = gl::create_texture(glf::Texture::Target::_3D);
            auto mipmapLevels = api::Texture::calculate_mipmap_levels(dimensions);

            gl::texture_storage_3d (handle, gl::map_texture_format(m_format), dimensions, mipmapLevels);
            __debugbreak();
            //gl::copy_image_sub_data(m_handle, handle, glf::Texture::Target::_3D, glf::Texture::Target::_3D, gl::Vector4u{ m_dimensions, 0u }, gl::Vector4u{ dimensions, 0u });
            gl::delete_texture     (m_handle);

            m_handle       = handle;
            m_dimensions   = dimensions;
            m_mipmapLevels = mipmapLevels;

            generate_mipmap();
        }

        auto format       () const
        {
            return m_format;
        }
        auto filter       () const
        {
            return m_filter;
        }
        auto wrapping     () const
        {
            return std::span<const Wrapping>{ m_wrapping };
        }
        auto dimensions   () const
        {
            return m_dimensions;
        }
        auto mipmap_levels() const
        {
            return m_mipmapLevels;
        }

    private:
        Format                  m_format{};
        Filter                  m_filter{};
        std::array<Wrapping, 3> m_wrapping{};
        gl::Vector3u            m_dimensions{};
        gl::uint32_t            m_mipmapLevels{};
    };

    class Texture2DMultisample : public gl::Object
    {
    public:
        using Format = api::Texture::Format;

         Texture2DMultisample(Format format, const gl::Vector2u& dimensions, gl::uint32_t samples)
             : m_format{ format }, m_dimensions{ dimensions }, m_samples{ samples }
        {
             m_handle = gl::create_texture(glf::Texture::Target::_2DMultisample);
             
             gl::texture_storage_2d_multisample(m_handle, gl::map_texture_format(m_format), m_dimensions, m_samples);
        }
        ~Texture2DMultisample()
        {
            gl::delete_texture(m_handle);
        }

        void bind(gl::binding_t binding) const
        {
            gl::bind_texture_unit(m_handle, binding);
        }
        
        void resize(const gl::Vector2u& dimensions)
        {
            auto handle = gl::create_texture(glf::Texture::Target::_2DMultisample);

            gl::texture_storage_2d_multisample(handle, gl::map_texture_format(m_format), dimensions, m_samples);
            gl::delete_texture                (m_handle);

            m_handle     = handle;
            m_dimensions = dimensions;
        }

        auto format    () const
        {
            return m_format;
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
        Format       m_format{};
        gl::Vector2u m_dimensions{};
        gl::uint32_t m_samples{};
    };
    class Texture3DMultisample : public gl::Object
    {
    public:
        using Format = api::Texture::Format;

         Texture3DMultisample(Format format, const gl::Vector3u& dimensions, gl::uint32_t samples)
             : m_format{ format }, m_dimensions{ dimensions }, m_samples{ samples }
        {
             m_handle = gl::create_texture(glf::Texture::Target::_2DMultisampleArray);
             
             gl::texture_storage_3d_multisample(m_handle, gl::map_texture_format(m_format), m_dimensions, m_samples);
        }
        ~Texture3DMultisample()
        {
            gl::delete_texture(m_handle);
        }

        void bind(gl::binding_t binding) const
        {
            gl::bind_texture_unit(m_handle, binding);
        }

        void resize(const gl::Vector3u& dimensions)
        {
            auto handle = gl::create_texture(glf::Texture::Target::_2DMultisampleArray);

            gl::texture_storage_3d_multisample(handle, gl::map_texture_format(m_format), dimensions, m_samples);
            gl::delete_texture                (m_handle);

            m_handle     = handle;
            m_dimensions = dimensions;
        }

        auto format    () const
        {
            return m_format;
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
        Format       m_format{};
        gl::Vector3u m_dimensions{};
        gl::uint32_t m_samples{};
    };
}
