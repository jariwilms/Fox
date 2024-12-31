#pragma once

#include "stdafx.hpp"

#include "Fox/Rendering/API/OpenGL/OpenGL.hpp"
#include "Fox/Rendering/API/OpenGL/Texture/TextureTarget.hpp"
#include "Fox/Rendering/Texture/Texture.hpp"

namespace fox::gfx::api::gl
{
    template<Dimensions DIMS, AntiAliasing AA>
    class Texture;

    template<Dimensions DIMS>
    class Texture<DIMS, AntiAliasing::None> : public api::Texture, public gl::Object
    {
    public:
        using Vector = gfx::MapDimensionsToVector<DIMS>::type;

        Texture(Format format, const Vector& dimensions, std::span<const fox::byte> data)
            : Texture{ format, Texture::Filter::Trilinear, Texture::Wrapping::Repeat, dimensions, data } {}
        Texture(Format format, Filter filter, Wrapping wrapping, const Vector& dimensions, std::span<const fox::byte> data)
            : Texture{ format, filter, wrapping, dimensions }
        {
            copy(format, data);
            generate_mip_map();
        }
        Texture(Format format, Filter filter, Wrapping wrapping, const Vector& dimensions)
            : api::Texture{ format, filter, wrapping }, m_dimensions{ dimensions }
        {
            constexpr auto glTarget = gl::map_texture_target<DIMS, AntiAliasing::None>();
            
            m_handle      = gl::create_texture(glTarget);
            m_glFormat    = gl::map_texture_format(m_format);
            m_glMinFilter = gl::map_texture_min_filter(m_filter);
            m_glMagFilter = gl::map_texture_mag_filter(m_filter);
            m_glWrapping  = gl::map_texture_wrapping(m_wrapping);

            gl::texture_parameter(m_handle, gl::Flags::Texture::Parameter::MinificationFilter,  m_glMinFilter);
            gl::texture_parameter(m_handle, gl::Flags::Texture::Parameter::MagnificationFilter, m_glMagFilter);

                                                   gl::texture_parameter(m_handle, gl::Flags::Texture::Parameter::WrappingS, m_glWrapping);
            if constexpr (DIMS >= Dimensions::_2D) gl::texture_parameter(m_handle, gl::Flags::Texture::Parameter::WrappingT, m_glWrapping);
            if constexpr (DIMS >= Dimensions::_3D) gl::texture_parameter(m_handle, gl::Flags::Texture::Parameter::WrappingR, m_glWrapping);

            if constexpr (DIMS == Dimensions::_1D) gl::texture_storage_1d(m_handle, m_glFormat, m_dimensions, 1);
            if constexpr (DIMS == Dimensions::_2D) gl::texture_storage_2d(m_handle, m_glFormat, m_dimensions, 1);
            if constexpr (DIMS == Dimensions::_3D) gl::texture_storage_3d(m_handle, m_glFormat, m_dimensions, 1);
        }
        Texture(Texture&& other) noexcept
        {
            *this = std::move(other);
        }
        ~Texture()
        {
            gl::delete_texture(m_handle);
        }

        void bind(fox::uint32_t slot) const
        {
            gl::bind_texture(m_handle, slot);
        }

        void copy(Format format, std::span<const fox::byte> data)
        {
            copy_range(format, m_dimensions, Vector{}, data);
        }
        void copy_range(Format format, const Vector& dimensions, const Vector& offset, std::span<const fox::byte> data)
        {
            if (data.empty()) return;
            if (glm::any(glm::greaterThan(m_dimensions, offset + dimensions))) throw std::invalid_argument{ "The data size exceeds texture bounds!" };

            if constexpr (DIMS == Dimensions::_1D) gl::texture_sub_image_1d(m_handle, gl::map_texture_format_base(format), dimensions, offset, 0, data.data());
            if constexpr (DIMS == Dimensions::_2D) gl::texture_sub_image_2d(m_handle, gl::map_texture_format_base(format), dimensions, offset, 0, data.data());
            if constexpr (DIMS == Dimensions::_3D) gl::texture_sub_image_3d(m_handle, gl::map_texture_format_base(format), dimensions, offset, 0, data.data());
        }

        void generate_mip_map()
        {
            gl::generate_texture_mip_map(m_handle);
        }

        const Vector& dimensions() const
        {
            return m_dimensions;
        }

        Texture& operator=(Texture&& other) noexcept
        {
            m_handle      = other.m_handle;
            m_glFormat    = other.m_glFormat;
            m_glMinFilter = other.m_glMinFilter;
            m_glMagFilter = other.m_glMagFilter;
            m_glWrapping  = other.m_glWrapping;
            m_dimensions  = other.m_dimensions;

            other.m_handle      = {};
            other.m_dimensions  = {};
            other.m_glFormat    = 0u;
            other.m_glMinFilter = 0u;
            other.m_glMagFilter = 0u;
            other.m_glWrapping  = 0u;

            return *this;
        }

    private:
        gl::uint32_t m_glFormat{};
        gl::uint32_t m_glMinFilter{};
        gl::uint32_t m_glMagFilter{};
        gl::uint32_t m_glWrapping{};
        fox::bool_t  m_mipMaps{};

        Vector       m_dimensions{};
    };
    template<Dimensions DIMS>
    class Texture<DIMS, AntiAliasing::MSAA> : public api::Texture, public gl::Object 
    {
    public:
        using Vector = gfx::MapDimensionsToVector<DIMS>::type;

        Texture(Format format, const Vector& dimensions, fox::uint8_t samples)
            : api::Texture{ format, Filter::None, Wrapping::Repeat }, m_dimensions{ dimensions }, m_samples{ samples }
        {
            static_assert(DIMS != Dimensions::_1D, "1D Multisampled textures are not supported!");

            constexpr auto glTarget = gl::map_texture_target<DIMS, AntiAliasing::MSAA>();

            m_handle   = gl::create_texture(glTarget);
            m_glFormat = gl::map_texture_format(m_format);

            if constexpr (DIMS == Dimensions::_2D) gl::texture_storage_2d_multisample(m_handle, m_glFormat, m_dimensions, m_samples);
            if constexpr (DIMS == Dimensions::_3D) gl::texture_storage_3d_multisample(m_handle, m_glFormat, m_dimensions, m_samples);
        }
        Texture(Texture&& other) noexcept
        {
            *this = std::move(other);
        }
        ~Texture()
        {
            gl::delete_texture(m_handle);
        }

        void bind(fox::uint32_t slot) const
        {
            gl::bind_texture(m_handle, slot);
        }

        const Vector& dimensions() const
        {
            return m_dimensions;
        }

        Texture& operator=(Texture&& other) noexcept
        {
            m_handle      = other.m_handle;
            m_glFormat    = other.m_glFormat;
            m_samples     = other.m_samples;
            m_dimensions  = other.m_dimensions;

            other.m_handle      = {};
            other.m_glFormat    = 0u;
            other.m_samples     = 0u;
            other.m_dimensions  = {};

            return *this;
        }

    private:
        gl::uint32_t  m_glFormat{};
        fox::uint8_t  m_samples{};

        Vector m_dimensions{};
    };
}
