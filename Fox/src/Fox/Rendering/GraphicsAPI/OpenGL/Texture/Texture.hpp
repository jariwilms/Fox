#pragma once

#include "stdafx.hpp"

#include "Fox/Rendering/API/Texture/AntiAliasing.hpp"
#include "Fox/Rendering/API/Texture/Dimensions.hpp"
#include "Fox/Rendering/API/Texture/MipMap.hpp"
#include "Fox/Rendering/API/Texture/Texture.hpp"
#include "Fox/Rendering/GraphicsAPI/OpenGL/OpenGL.hpp"

namespace fox::gfx::api::gl
{
    template<api::Dimensions, api::AntiAliasing>
    class Texture;

    template<api::Dimensions DIMS>
    class Texture<DIMS, api::AntiAliasing::None> : public api::Texture, public gl::Object
    {
    public:
        using wrap_t   = api::DimensionsToWrappingMap<DIMS>::wrap_t;
        using vector_t = api::DimensionsToVectorMap<DIMS>::type;

        Texture(Format format, const vector_t& dimensions, std::span<const fox::byte_t> data)
            : Texture{ format, Filter::Trilinear, Wrapping::Repeat, dimensions, data } {
        }
        Texture(Format format, Filter filter, const wrap_t& wrapping, const vector_t& dimensions, std::span<const fox::byte_t> data)
            : Texture{ format, filter, wrapping, dimensions }
        {
            copy(format, data);
            generate_mipmap();
        }
        Texture(Format format, Filter filter, const wrap_t& wrapping, const vector_t& dimensions)
            : api::Texture{ format, filter }, m_mipmapLevels{ 1u }, m_wrapping{ wrapping }, m_dimensions{ dimensions }
        {
            constexpr auto target = gl::map_texture_target<DIMS, api::AntiAliasing::None>();
            m_handle = gl::create_texture(target);

            if (filter != Filter::None)
            {
                gl::texture_parameter(m_handle, glf::Texture::Parameter::MinificationFilter,  gl::map_texture_min_filter(m_filter));
                gl::texture_parameter(m_handle, glf::Texture::Parameter::MagnificationFilter, gl::map_texture_mag_filter(m_filter));

                m_mipmapLevels = api::calculate_mipmap_level(m_dimensions);
            }

                                                        gl::texture_parameter(m_handle, glf::Texture::Parameter::WrappingS, gl::map_texture_wrapping(m_wrapping.s));
            if constexpr (DIMS >= api::Dimensions::_2D) gl::texture_parameter(m_handle, glf::Texture::Parameter::WrappingT, gl::map_texture_wrapping(m_wrapping.t));
            if constexpr (DIMS >= api::Dimensions::_3D) gl::texture_parameter(m_handle, glf::Texture::Parameter::WrappingR, gl::map_texture_wrapping(m_wrapping.r));

            if constexpr (DIMS == api::Dimensions::_1D) gl::texture_storage_1d(m_handle, gl::map_texture_format(m_format), m_dimensions, m_mipmapLevels);
            if constexpr (DIMS == api::Dimensions::_2D) gl::texture_storage_2d(m_handle, gl::map_texture_format(m_format), m_dimensions, m_mipmapLevels);
            if constexpr (DIMS == api::Dimensions::_3D) gl::texture_storage_3d(m_handle, gl::map_texture_format(m_format), m_dimensions, m_mipmapLevels);
        }
        Texture(Texture&&) noexcept = default;
        ~Texture()
        {
            gl::delete_texture(m_handle);
        }

        void bind(gl::uint32_t index) const
        {
            gl::bind_texture_unit(m_handle, index);
        }

        void copy(Format format, std::span<const fox::byte_t> data)
        {
            copy_range(format, m_dimensions, vector_t{}, data);
        }
        void copy_range(Format format, const vector_t& dimensions, const vector_t& offset, std::span<const fox::byte_t> data)
        {
            if (data.empty()) return;
            if (glm::any(glm::greaterThan(m_dimensions, offset + dimensions))) throw std::invalid_argument{ "The data size exceeds texture bounds!" };

            if constexpr (DIMS == api::Dimensions::_1D) gl::texture_sub_image_1d(m_handle, gl::map_texture_format_base(format), dimensions, offset, 0, data);
            if constexpr (DIMS == api::Dimensions::_2D) gl::texture_sub_image_2d(m_handle, gl::map_texture_format_base(format), dimensions, offset, 0, data);
            if constexpr (DIMS == api::Dimensions::_3D) gl::texture_sub_image_3d(m_handle, gl::map_texture_format_base(format), dimensions, offset, 0, data);
        }

        void apply_wrapping(wrap_t wrapping)
        {
            m_wrapping = wrapping;

                                                        gl::texture_parameter(m_handle, glf::Texture::Parameter::WrappingS, gl::map_texture_wrapping(m_wrapping.s));
            if constexpr (DIMS >= api::Dimensions::_2D) gl::texture_parameter(m_handle, glf::Texture::Parameter::WrappingT, gl::map_texture_wrapping(m_wrapping.t));
            if constexpr (DIMS >= api::Dimensions::_3D) gl::texture_parameter(m_handle, glf::Texture::Parameter::WrappingR, gl::map_texture_wrapping(m_wrapping.r));
        }
        void generate_mipmap()
        {
            gl::generate_texture_mipmap(m_handle);
        }

        wrap_t          wrapping()      const
        {
            return m_wrapping;
        }
        const vector_t& dimensions()    const
        {
            return m_dimensions;
        }
        fox::uint32_t   mipmap_levels() const
        {
            return m_mipmapLevels;
        }

        Texture& operator=(Texture&&) noexcept = default;

    protected:
        wrap_t        m_wrapping{};
        vector_t      m_dimensions{};
        fox::uint32_t m_mipmapLevels{};
    };
    template<api::Dimensions DIMS> requires (DIMS != api::Dimensions::_1D)
    class Texture<DIMS, api::AntiAliasing::MSAA> : public api::Texture, public gl::Object
    {
    public:
        using vector_t = api::DimensionsToVectorMap<DIMS>::type;

        Texture(Format format, const vector_t& dimensions, fox::uint8_t samples)
            : api::Texture{ format, Filter::None }, m_dimensions{ dimensions }, m_samples{ samples }
        {
            constexpr auto target = gl::map_texture_target<DIMS, api::AntiAliasing::MSAA>();
            m_handle = gl::create_texture(target);

            if constexpr (DIMS == api::Dimensions::_2D) gl::texture_storage_2d_multisample(m_handle, gl::map_texture_format(m_format), m_dimensions, m_samples);
            if constexpr (DIMS == api::Dimensions::_3D) gl::texture_storage_3d_multisample(m_handle, gl::map_texture_format(m_format), m_dimensions, m_samples);
        }
        Texture(Texture&&) noexcept = default;
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

        Texture& operator=(Texture&&) noexcept = default;

    private:
        vector_t     m_dimensions{};
        fox::uint8_t m_samples{};
    };
}
