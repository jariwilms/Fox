#pragma once

#include "stdafx.hpp"

#include "Fox/Rendering/API/OpenGL/OpenGL.hpp"
#include "Fox/Rendering/Texture/Texture.hpp"
#include "TextureTarget.hpp"

namespace fox::gfx::api::gl
{
    template<Dimensions DIMS, AntiAliasing AA>
    class Texture : public api::Texture, public gl::Object
    {
    public:
        using vector_t = gfx::DimensionsToVector<DIMS>::type;

        Texture(const vector_t& dimensions, std::span<const fox::byte> data)
            : Texture{ Texture::Format::RGBA8_UNORM, Texture::Filter::Trilinear, Texture::Wrapping::Repeat, dimensions, data } {}
        Texture(Format format, Filter filter, Wrapping wrapping, const vector_t& dimensions)                                  requires (AA == AntiAliasing::None)
            : api::Texture{ format, filter, wrapping }, m_dimensions{ dimensions }
        {
            m_handle      = gl::create_texture(DimensionsToTarget<DIMS, AA>::target);
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
        Texture(Texture::Format format, Filter filter, Wrapping wrapping, const vector_t& dimensions, fox::uint8_t samples)   requires (DIMS != Dimensions::_1D && AA == AntiAliasing::MSAA)
            : api::Texture{ format, filter, wrapping }, m_dimensions{ dimensions }, m_samples{ samples }
        {
            m_handle      = gl::create_texture(DimensionsToTarget<DIMS, AA>::target);
            m_glFormat    = gl::map_texture_format(m_format);
            m_glMinFilter = gl::map_texture_min_filter(m_filter);
            m_glMagFilter = gl::map_texture_mag_filter(m_filter);
            m_glWrapping  = gl::map_texture_wrapping(m_wrapping);

            if constexpr (DIMS == Dimensions::_2D) gl::texture_storage_2d_multisample(m_handle, m_glFormat, m_dimensions, m_samples);
            if constexpr (DIMS == Dimensions::_3D) gl::texture_storage_3d_multisample(m_handle, m_glFormat, m_dimensions, m_samples);
        }
        Texture(Format format, Filter filter, Wrapping wrapping, const vector_t& dimensions, std::span<const fox::byte> data) requires (AA == AntiAliasing::None)
            : Texture{ format, filter, wrapping, dimensions }
        {
            copy(format, data);
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

        void copy(Format format, std::span<const fox::byte> data)                                                                                requires (AA == AntiAliasing::None)
        {
            copy_range(format, m_dimensions, vector_t{}, data);
        }
        void copy_range(Format format, const vector_t& dimensions, const vector_t& offset, std::span<const fox::byte> data)                      requires (AA == AntiAliasing::None)
        {
            if (data.empty()) return;
            if (glm::any(glm::greaterThan(m_dimensions, offset + dimensions))) throw std::invalid_argument{ "The data size exceeds texture bounds!" };
            
            if constexpr (DIMS == Dimensions::_1D) gl::texture_sub_image_1d(m_handle, gl::map_texture_format_base(format), dimensions, offset, 0, data.data());
            if constexpr (DIMS == Dimensions::_2D) gl::texture_sub_image_2d(m_handle, gl::map_texture_format_base(format), dimensions, offset, 0, data.data());
            if constexpr (DIMS == Dimensions::_3D) gl::texture_sub_image_3d(m_handle, gl::map_texture_format_base(format), dimensions, offset, 0, data.data());
        }

        const vector_t& dimensions() const
        {
            return m_dimensions;
        }
        fox::uint8_t    samples()    const
        {
            return m_samples;
        }

        Texture& operator=(Texture&& other) noexcept
        {
            m_handle      = other.m_handle;
            m_glFormat    = other.m_glFormat;
            m_glMinFilter = other.m_glMinFilter;
            m_glMagFilter = other.m_glMagFilter;
            m_glWrapping  = other.m_glWrapping;
            m_dimensions  = other.m_dimensions;
            m_samples     = other.m_samples;

            other.m_handle      = {};
            other.m_glFormat    = 0u;
            other.m_glMinFilter = 0u;
            other.m_glMagFilter = 0u;
            other.m_glWrapping  = 0u;
            other.m_dimensions  = {};
            other.m_samples     = 0u;

            return *this;
        }

    private:
        gl::uint32_t m_glFormat{};
        gl::uint32_t m_glMinFilter{};
        gl::uint32_t m_glMagFilter{};
        gl::uint32_t m_glWrapping{};

        vector_t     m_dimensions{};
        std::uint8_t m_samples{};
    };
}
