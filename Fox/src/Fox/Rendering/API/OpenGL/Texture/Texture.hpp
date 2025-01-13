#pragma once

#include "stdafx.hpp"

#include "Fox/Rendering/API/OpenGL/OpenGL.hpp"
#include "Fox/Rendering/Texture/AntiAliasing.hpp"
#include "Fox/Rendering/Texture/Dimensions.hpp"
#include "Fox/Rendering/Texture/MipMap.hpp"
#include "Fox/Rendering/Texture/Texture.hpp"

namespace fox::gfx::api::gl
{
    template<Dimensions, AntiAliasing>
    class Texture;

    template<Dimensions DIMS>
    class Texture<DIMS, AntiAliasing::None> : public api::Texture, public gl::Object
    {
    public:
        using wrap_t   = gfx::DimensionsToWrappingMap<DIMS>::wrap_t;
        using vector_t = gfx::DimensionsToVectorMap<DIMS>::type;
        
        Texture(Format format, const vector_t& dimensions, std::span<const fox::byte> data)
            : Texture{ format, Filter::Trilinear, Wrapping::Repeat, dimensions, data } {
        }
        Texture(Format format, Filter filter, wrap_t wrapping, const vector_t& dimensions, std::span<const fox::byte> data)
            : Texture{ format, filter, wrapping, dimensions }
        {
            copy(format, data);
            generate_mipmap();
        }
        Texture(Format format, Filter filter, wrap_t wrapping, const vector_t& dimensions)
            : api::Texture{ format, filter }, m_mipmapLevels{ 1u }, m_wrapping{ wrapping }, m_dimensions{ dimensions }
        {
            constexpr auto target = gl::map_texture_target<DIMS, gfx::AntiAliasing::None>();
            m_handle = gl::create_texture(target);

            if (filter != Filter::None)
            {
                gl::texture_parameter(m_handle, glf::Texture::Parameter::MinificationFilter,  gl::map_texture_min_filter(m_filter));
                gl::texture_parameter(m_handle, glf::Texture::Parameter::MagnificationFilter, gl::map_texture_mag_filter(m_filter));

                m_mipmapLevels = gfx::calculate_mipmap_level(m_dimensions);
            }

                                                   gl::texture_parameter(m_handle, glf::Texture::Parameter::WrappingS, gl::map_texture_wrapping(m_wrapping.s));
            if constexpr (DIMS >= Dimensions::_2D) gl::texture_parameter(m_handle, glf::Texture::Parameter::WrappingT, gl::map_texture_wrapping(m_wrapping.t));
            if constexpr (DIMS >= Dimensions::_3D) gl::texture_parameter(m_handle, glf::Texture::Parameter::WrappingR, gl::map_texture_wrapping(m_wrapping.r));

            if constexpr (DIMS == Dimensions::_1D) gl::texture_storage_1d(m_handle, gl::map_texture_format(m_format), m_dimensions, m_mipmapLevels);
            if constexpr (DIMS == Dimensions::_2D) gl::texture_storage_2d(m_handle, gl::map_texture_format(m_format), m_dimensions, m_mipmapLevels);
            if constexpr (DIMS == Dimensions::_3D) gl::texture_storage_3d(m_handle, gl::map_texture_format(m_format), m_dimensions, m_mipmapLevels);
        }
        Texture(Texture&& other) noexcept = default;
        ~Texture()
        {
            gl::delete_texture(m_handle);
        }

        void bind(fox::uint32_t index) const
        {
            gl::bind_texture_unit(m_handle, index);
        }

        void copy(Format format, std::span<const fox::byte> data)
        {
            copy_range(format, m_dimensions, vector_t{}, data);
        }
        void copy_range(Format format, const vector_t& dimensions, const vector_t& offset, std::span<const fox::byte> data)
        {
            if (data.empty()) return;
            if (glm::any(glm::greaterThan(m_dimensions, offset + dimensions))) throw std::invalid_argument{ "The data size exceeds texture bounds!" };

            if constexpr (DIMS == Dimensions::_1D) gl::texture_sub_image_1d(m_handle, gl::map_texture_format_base(format), dimensions, offset, 0, data.data());
            if constexpr (DIMS == Dimensions::_2D) gl::texture_sub_image_2d(m_handle, gl::map_texture_format_base(format), dimensions, offset, 0, data.data());
            if constexpr (DIMS == Dimensions::_3D) gl::texture_sub_image_3d(m_handle, gl::map_texture_format_base(format), dimensions, offset, 0, data.data());
        }

        void generate_mipmap()
        {
            gl::generate_texture_mipmap(m_handle);
        }
        void apply_wrapping(wrap_t wrapping)
        {
            m_wrapping = wrapping;

                                                   gl::texture_parameter(m_handle, glf::Texture::Parameter::WrappingS, std::to_underlying(gl::map_texture_wrapping(m_wrapping.s)));
            if constexpr (DIMS >= Dimensions::_2D) gl::texture_parameter(m_handle, glf::Texture::Parameter::WrappingT, std::to_underlying(gl::map_texture_wrapping(m_wrapping.t)));
            if constexpr (DIMS >= Dimensions::_3D) gl::texture_parameter(m_handle, glf::Texture::Parameter::WrappingR, std::to_underlying(gl::map_texture_wrapping(m_wrapping.r)));
        }

        fox::uint32_t   mipmap_levels() const
        {
            return m_mipmapLevels;
        }
        wrap_t          wrapping()      const
        {
            return m_wrapping;
        }
        const vector_t& dimensions()    const
        {
            return m_dimensions;
        }

        Texture& operator=(Texture&& other) noexcept = default;

    private:
        wrap_t        m_wrapping{};
        vector_t      m_dimensions{};
        fox::uint32_t m_mipmapLevels{};
    };
    template<Dimensions DIMS> requires (DIMS != Dimensions::_1D)
    class Texture<DIMS, AntiAliasing::MSAA> : public api::Texture, public gl::Object
    {
    public:
        using vector_t = gfx::DimensionsToVectorMap<DIMS>::type;

        Texture(Format format, const vector_t& dimensions, fox::uint8_t samples)
            : api::Texture{ format }, m_dimensions{ dimensions }, m_samples{ samples }
        {
            constexpr auto target = gl::map_texture_target<DIMS, gfx::AntiAliasing::MSAA>();
            m_handle = gl::create_texture(target);

            if constexpr (DIMS == Dimensions::_2D) gl::texture_storage_2d_multisample(m_handle, gl::map_texture_format(m_format), m_dimensions, m_samples);
            if constexpr (DIMS == Dimensions::_3D) gl::texture_storage_3d_multisample(m_handle, gl::map_texture_format(m_format), m_dimensions, m_samples);
        }
        Texture(Texture&& other) noexcept = default;
        ~Texture()
        {
            gl::delete_texture(m_handle);
        }

        void bind(fox::uint32_t slot) const
        {
            gl::bind_texture_unit(m_handle, slot);
        }

        fox::uint8_t    samples()    const
        {
            return m_samples;
        }
        const vector_t& dimensions() const
        {
            return m_dimensions;
        }

        Texture& operator=(Texture&& other) noexcept = default;

    private:
        vector_t     m_dimensions{};
        fox::uint8_t m_samples{};
    };
}
