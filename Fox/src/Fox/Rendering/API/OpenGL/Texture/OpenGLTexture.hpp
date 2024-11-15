#pragma once

#include "stdafx.hpp"

#include "Fox/Rendering/API/OpenGL/GL.hpp"
#include "Fox/Rendering/Texture/Texture.hpp"
#include "OpenGLTextureTarget.hpp"

namespace fox::gfx::api::gl
{
    template<Dimensions DIMS, AntiAliasing AA>
    class OpenGLTexture : public Texture, public gl::Object
    {
    public:
        using vector_t = gfx::api::DimensionsToVector<DIMS>::type;

        OpenGLTexture(Texture::Format format, Texture::Filter filter, Texture::Wrapping wrapping, const vector_t& dimensions)                             requires (AA == AntiAliasing::None)
            : Texture{ format, filter, wrapping }, m_dimensions{ dimensions }
        {
            m_handle      = gl::create_texture(DimensionsToTarget<DIMS, AA>::target);
            m_glFormat    = gl::map_texture_format(this->m_format);
            m_glMinFilter = gl::map_texture_min_filter(this->m_filter);
            m_glMagFilter = gl::map_texture_mag_filter(this->m_filter);
            m_glWrapping  = gl::map_texture_wrapping(this->m_wrapping);

            gl::texture_parameter(m_handle, GL_TEXTURE_MIN_FILTER, m_glMinFilter);
            gl::texture_parameter(m_handle, GL_TEXTURE_MAG_FILTER, m_glMagFilter);

                                                   gl::texture_parameter(m_handle, GL_TEXTURE_WRAP_S, m_glWrapping);
            if constexpr (DIMS >= Dimensions::_2D) gl::texture_parameter(m_handle, GL_TEXTURE_WRAP_T, m_glWrapping);
            if constexpr (DIMS >= Dimensions::_3D) gl::texture_parameter(m_handle, GL_TEXTURE_WRAP_R, m_glWrapping);

            if constexpr (DIMS == Dimensions::_1D) gl::texture_storage_1d(m_handle, m_glFormat, m_dimensions, 1);
            if constexpr (DIMS == Dimensions::_2D) gl::texture_storage_2d(m_handle, m_glFormat, m_dimensions, 1);
            if constexpr (DIMS == Dimensions::_3D) gl::texture_storage_3d(m_handle, m_glFormat, m_dimensions, 1);
        }
        OpenGLTexture(Texture::Format format, Texture::Filter filter, Texture::Wrapping wrapping, const vector_t& dimensions, std::uint8_t samples)       requires (DIMS != Dimensions::_1D && AA == AntiAliasing::MSAA)
            : Texture{ format, filter, wrapping }, m_dimensions{ dimensions }, m_samples{ samples }
        {
            m_handle      = gl::create_texture(DimensionsToTarget<DIMS, AA>::target);
            m_glFormat    = gl::map_texture_format(this->m_format);
            m_glMinFilter = gl::map_texture_min_filter(this->m_filter);
            m_glMagFilter = gl::map_texture_mag_filter(this->m_filter);
            m_glWrapping  = gl::map_texture_wrapping(this->m_wrapping);

            //"Multisample textures target doesn't support sampler state"
            //gl::texture_parameter(m_handle, GL_TEXTURE_MIN_FILTER, m_glMinFilter);
            //gl::texture_parameter(m_handle, GL_TEXTURE_MAG_FILTER, m_glMagFilter);

            //                                       gl::texture_parameter(m_handle, GL_TEXTURE_WRAP_S, m_glWrapping);
            //                                       gl::texture_parameter(m_handle, GL_TEXTURE_WRAP_T, m_glWrapping);
            //if constexpr (DIMS == Dimensions::_3D) gl::texture_parameter(m_handle, GL_TEXTURE_WRAP_R, m_glWrapping);

            if constexpr (DIMS == Dimensions::_2D) gl::texture_storage_2d_multisample(m_handle, m_glFormat, m_dimensions, m_samples);
            if constexpr (DIMS == Dimensions::_3D) gl::texture_storage_3d_multisample(m_handle, m_glFormat, m_dimensions, m_samples);
        }
        OpenGLTexture(Texture::Format format, Texture::Filter filter, Texture::Wrapping wrapping, const vector_t& dimensions, std::span<const byte> data) requires (AA == AntiAliasing::None)
            : OpenGLTexture{ format, filter, wrapping, dimensions }
        {
            copy(format, data);
        }
        OpenGLTexture(OpenGLTexture&& other) noexcept
        {
            *this = std::move(other);
        }
        ~OpenGLTexture()
        {
            gl::delete_texture(m_handle);
        }

        void bind(std::uint32_t slot) const
        {
            gl::bind_texture(m_handle, slot);
        }

        void copy(Texture::Format format, std::span<const byte> data)                                                                                requires (AA == AntiAliasing::None)
        {
            copy_range(format, this->m_dimensions, vector_t{}, data);
        }
        void copy_range(Texture::Format format, const vector_t& dimensions, const vector_t& offset, std::span<const byte> data)                      requires (AA == AntiAliasing::None)
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
        std::uint8_t    samples()    const
        {
            return m_samples;
        }

        OpenGLTexture& operator=(OpenGLTexture&& other) noexcept
        {
            m_handle        = other.m_handle;
            m_glFormat    = other.m_glFormat;
            m_glMinFilter = other.m_glMinFilter;
            m_glMagFilter = other.m_glMagFilter;
            m_glWrapping  = other.m_glWrapping;
            m_dimensions  = other.m_dimensions;
            m_samples     = other.m_samples;

            other.m_handle        = 0u;
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
