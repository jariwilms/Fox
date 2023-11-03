#pragma once

#include "stdafx.hpp"

#include "Helix/Rendering/API/OpenGL/OpenGL.hpp"
#include "Helix/Rendering/Texture/Texture.hpp"
#include "Helix/Rendering/API/OpenGL/Internal/InternalView.hpp"
#include "OpenGLTextureTarget.hpp"

namespace hlx::gfx::imp::api
{
    template<Dimensions DIMS, AntiAliasing AA>
    class GTexture<gfx::api::GraphicsAPI::OpenGL, DIMS, AA> : public Texture
    {
    public:
        using vector_t = gfx::api::DimensionsToVector<DIMS>::type;

        GTexture(Texture::Format format, Texture::Filter filter, Texture::Wrapping wrapping, const vector_t& dimensions)                             requires (AA == AntiAliasing::None)
            : Texture{ format, filter, wrapping }, m_dimensions{ dimensions }
        {
            m_glId        = gl::create_texture(DimensionsToTarget<DIMS>::target);
            m_glFormat    = gl::texture_format(this->m_format);
            m_glMinFilter = gl::texture_min_filter(this->m_filter);
            m_glMagFilter = gl::texture_mag_filter(this->m_filter);
            m_glWrapping  = gl::texture_wrapping(this->m_wrapping);

            gl::texture_parameter(m_glId, GL_TEXTURE_MIN_FILTER, m_glMinFilter);
            gl::texture_parameter(m_glId, GL_TEXTURE_MAG_FILTER, m_glMagFilter);

                                                   gl::texture_parameter(m_glId, GL_TEXTURE_WRAP_S, m_glWrapping);
            if constexpr (DIMS >= Dimensions::_2D) gl::texture_parameter(m_glId, GL_TEXTURE_WRAP_T, m_glWrapping);
            if constexpr (DIMS >= Dimensions::_3D) gl::texture_parameter(m_glId, GL_TEXTURE_WRAP_R, m_glWrapping);

            if constexpr (DIMS == Dimensions::_1D) gl::texture_storage_1d(m_glId, m_glFormat, m_dimensions, 0);
            if constexpr (DIMS == Dimensions::_2D) gl::texture_storage_2d(m_glId, m_glFormat, m_dimensions, 0);
            if constexpr (DIMS == Dimensions::_3D) gl::texture_storage_3d(m_glId, m_glFormat, m_dimensions, 0);
        }
        GTexture(Texture::Format format, Texture::Filter filter, Texture::Wrapping wrapping, const vector_t& dimensions, u8 samples)                 requires (DIMS != Dimensions::_1D && AA == AntiAliasing::MSAA)
            : Texture{ format, filter, wrapping }, m_dimensions{ dimensions }, m_samples{ samples }
        {
            m_glId        = gl::create_texture(DimensionsToTarget<DIMS>::target);
            m_glFormat    = gl::texture_format(this->m_format);
            m_glMinFilter = gl::texture_min_filter(this->m_filter);
            m_glMagFilter = gl::texture_mag_filter(this->m_filter);
            m_glWrapping  = gl::texture_wrapping(this->m_wrapping);

            gl::texture_parameter(m_glId, GL_TEXTURE_MIN_FILTER, m_glMinFilter);
            gl::texture_parameter(m_glId, GL_TEXTURE_MAG_FILTER, m_glMagFilter);

                                                   gl::texture_parameter(m_glId, GL_TEXTURE_WRAP_S, m_glWrapping);
                                                   gl::texture_parameter(m_glId, GL_TEXTURE_WRAP_T, m_glWrapping);
            if constexpr (DIMS == Dimensions::_3D) gl::texture_parameter(m_glId, GL_TEXTURE_WRAP_R, m_glWrapping);

            if constexpr (DIMS == Dimensions::_2D) gl::texture_storage_2d_multisample(m_glId, m_glFormat, m_dimensions, m_samples);
            if constexpr (DIMS == Dimensions::_3D) gl::texture_storage_3d_multisample(m_glId, m_glFormat, m_dimensions, m_samples);
        }
        GTexture(Texture::Format format, Texture::Filter filter, Texture::Wrapping wrapping, const vector_t& dimensions, std::span<const byte> data) requires (AA == AntiAliasing::None)
            : GTexture{ format, filter, wrapping, dimensions }
        {
            copy(format, data);
        }
        ~GTexture()
        {
            gl::delete_texture(m_glId);
        }

        void bind(u32 slot)
        {
            gl::bind_texture(m_glId, slot);
        }

        void copy(Texture::Format format, std::span<const byte> data)                                                                                requires (AA == AntiAliasing::None)
        {
            copy_range(format, this->m_dimensions, vector_t{}, data);
        }
        void copy_range(Texture::Format format, const vector_t& dimensions, const vector_t& offset, std::span<const byte> data)                      requires (AA == AntiAliasing::None)
        {
            if (data.empty()) return;
            if (glm::any(glm::greaterThan(m_dimensions, offset + dimensions))) throw std::invalid_argument{ "The data size exceeds texture bounds!" };
            
            if constexpr (DIMS == Dimensions::_1D) gl::texture_sub_image_1d(m_glId, gl::texture_format_base(format), dimensions, offset, 0, data.data());
            if constexpr (DIMS == Dimensions::_2D) gl::texture_sub_image_2d(m_glId, gl::texture_format_base(format), dimensions, offset, 0, data.data());
            if constexpr (DIMS == Dimensions::_3D) gl::texture_sub_image_3d(m_glId, gl::texture_format_base(format), dimensions, offset, 0, data.data());
        }

        const vector_t& dimensions() const
        {
            return m_dimensions;
        }
        u8              samples()    const
        {
            return m_samples;
        }

        auto expose_internals() const
        {
            return InternalView<GTexture<gfx::api::GraphicsAPI::OpenGL, DIMS, AA>>
            {
                m_glId,
                m_glFormat,
                m_glMinFilter,
                m_glMagFilter,
                m_glWrapping,
            };
        }

    private:
        GLuint m_glId{};
        GLuint m_glFormat{};
        GLuint m_glMinFilter{};
        GLuint m_glMagFilter{};
        GLuint m_glWrapping{};

        vector_t m_dimensions{};
        u8       m_samples{};
    };
}
