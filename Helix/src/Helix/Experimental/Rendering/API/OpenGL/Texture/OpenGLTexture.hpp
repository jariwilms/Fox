#pragma once

#include "stdafx.hpp"

#include "Helix/Experimental/Rendering/API/OpenGL/OpenGL.hpp"
#include "Helix/Experimental/Rendering/Texture/Texture.hpp"

namespace hlx::gfx::api
{
    template<Dimensions D, AntiAliasing A>
    class GTexture<GraphicsAPI::OpenGL, D, A> : public DTexture<D>
    {
    public:
        using vector_t = DTexture<D>::Vector;

        GTexture(Texture::Format format, Texture::Filter filter, Texture::Wrapping wrapping, const vector_t& dimensions)                                      requires (D == Dimensions::_1D && A == AntiAliasing::None)
            : DTexture<D>{ format, filter, wrapping, dimensions }
        {
            m_glId        = gl::create_texture(GL_TEXTURE_1D);
            m_glFormat    = gl::texture_format(this->m_format);
            m_glMinFilter = gl::texture_min_filter(this->m_filter);
            m_glMagFilter = gl::texture_mag_filter(this->m_filter);
            m_glWrapping  = gl::texture_wrapping(this->m_wrapping);

            gl::texture_parameter(m_glId, GL_TEXTURE_MIN_FILTER, m_glMinFilter);
            gl::texture_parameter(m_glId, GL_TEXTURE_MAG_FILTER, m_glMagFilter);
            gl::texture_parameter(m_glId, GL_TEXTURE_WRAP_S, m_glWrapping);

            gl::texture_storage_1d(m_glId, m_glFormat, this->m_dimensions, 0);
        }
        template<typename T>
        GTexture(Texture::Format format, Texture::Filter filter, Texture::Wrapping wrapping, const vector_t& dimensions, std::span<const T> data)             requires (D == Dimensions::_1D && A == AntiAliasing::None)
            : GTexture{ format, filter, wrapping, dimensions }
        {
            copy(format, data);
        }

        GTexture(Texture::Format format, Texture::Filter filter, Texture::Wrapping wrapping, const vector_t& dimensions)                                      requires (D == Dimensions::_2D && A == AntiAliasing::None)
            : DTexture<D>{ format, filter, wrapping, dimensions }
        {
            m_glId        = gl::create_texture(GL_TEXTURE_2D);
            m_glFormat    = gl::texture_format(this->m_format);
            m_glMinFilter = gl::texture_min_filter(this->m_filter);
            m_glMagFilter = gl::texture_mag_filter(this->m_filter);
            m_glWrapping  = gl::texture_wrapping(this->m_wrapping);

            gl::texture_parameter(m_glId, GL_TEXTURE_MIN_FILTER, m_glMinFilter);
            gl::texture_parameter(m_glId, GL_TEXTURE_MAG_FILTER, m_glMagFilter);
            gl::texture_parameter(m_glId, GL_TEXTURE_WRAP_S, m_glWrapping);
            gl::texture_parameter(m_glId, GL_TEXTURE_WRAP_T, m_glWrapping);

            gl::texture_storage_2d(m_glId, m_glFormat, this->m_dimensions, 0);
        }
        GTexture(Texture::Format format, Texture::Filter filter, Texture::Wrapping wrapping, const vector_t& dimensions, u8 samples)                          requires (D == Dimensions::_2D && A == AntiAliasing::MSAA)
            : DTexture<D>{ format, filter, wrapping, dimensions }, m_samples{ samples }
        {
            m_glId        = gl::create_texture(GL_TEXTURE_2D);
            m_glFormat    = gl::texture_format(this->m_format);
            m_glMinFilter = gl::texture_min_filter(this->m_filter);
            m_glMagFilter = gl::texture_mag_filter(this->m_filter);
            m_glWrapping  = gl::texture_wrapping(this->m_wrapping);

            gl::texture_parameter(m_glId, GL_TEXTURE_MIN_FILTER, m_glMinFilter);
            gl::texture_parameter(m_glId, GL_TEXTURE_MAG_FILTER, m_glMagFilter);
            gl::texture_parameter(m_glId, GL_TEXTURE_WRAP_S, m_glWrapping);
            gl::texture_parameter(m_glId, GL_TEXTURE_WRAP_T, m_glWrapping);

            gl::texture_storage_2d_multisample(m_glId, m_glFormat, this->m_dimensions, m_samples);
        }
        template<typename T>
        GTexture(Texture::Format format, Texture::Filter filter, Texture::Wrapping wrapping, const vector_t& dimensions, std::span<const T> data)             requires (D == Dimensions::_2D && A == AntiAliasing::None)
            : GTexture{ format, filter, wrapping, dimensions }
        {
            copy(format, data);
        }
        template<typename T>
        GTexture(Texture::Format format, Texture::Filter filter, Texture::Wrapping wrapping, const vector_t& dimensions, u8 samples, std::span<const T> data) requires (D == Dimensions::_2D && A == AntiAliasing::MSAA)
            : GTexture{ format, filter, wrapping, dimensions, samples }
        {
            copy(format, data);
        }
  
        GTexture(Texture::Format format, Texture::Filter filter, Texture::Wrapping wrapping, const vector_t& dimensions)                                      requires (D == Dimensions::_3D && A == AntiAliasing::None)
            : DTexture<D>{ format, filter, wrapping, dimensions }
        {
            m_glId        = gl::create_texture(GL_TEXTURE_3D);
            m_glFormat    = gl::texture_format(this->m_format);
            m_glMinFilter = gl::texture_min_filter(this->m_filter);
            m_glMagFilter = gl::texture_mag_filter(this->m_filter);
            m_glWrapping  = gl::texture_wrapping(this->m_wrapping);

            gl::texture_parameter(m_glId, GL_TEXTURE_MIN_FILTER, m_glMinFilter);
            gl::texture_parameter(m_glId, GL_TEXTURE_MAG_FILTER, m_glMagFilter);
            gl::texture_parameter(m_glId, GL_TEXTURE_WRAP_S, m_glWrapping);
            gl::texture_parameter(m_glId, GL_TEXTURE_WRAP_T, m_glWrapping);
            gl::texture_parameter(m_glId, GL_TEXTURE_WRAP_R, m_glWrapping);

            gl::texture_storage_3d(m_glId, m_glFormat, this->m_dimensions, 0);
        }
        GTexture(Texture::Format format, Texture::Filter filter, Texture::Wrapping wrapping, const vector_t& dimensions, u8 samples)                          requires (D == Dimensions::_3D && A == AntiAliasing::MSAA)
            : DTexture<D>{ format, filter, wrapping, dimensions }, m_samples{ samples }
        {
            m_glId        = gl::create_texture(GL_TEXTURE_3D);
            m_glFormat    = gl::texture_format(this->m_format);
            m_glMinFilter = gl::texture_min_filter(this->m_filter);
            m_glMagFilter = gl::texture_mag_filter(this->m_filter);
            m_glWrapping  = gl::texture_wrapping(this->m_wrapping);

            gl::texture_parameter(m_glId, GL_TEXTURE_MIN_FILTER, m_glMinFilter);
            gl::texture_parameter(m_glId, GL_TEXTURE_MAG_FILTER, m_glMagFilter);
            gl::texture_parameter(m_glId, GL_TEXTURE_WRAP_S, m_glWrapping);
            gl::texture_parameter(m_glId, GL_TEXTURE_WRAP_T, m_glWrapping);
            gl::texture_parameter(m_glId, GL_TEXTURE_WRAP_R, m_glWrapping);

            gl::texture_storage_3d_multisample(m_glId, m_glFormat, this->m_dimensions, m_samples);
        }
        template<typename T>
        GTexture(Texture::Format format, Texture::Filter filter, Texture::Wrapping wrapping, const vector_t& dimensions, std::span<const T> data)             requires (D == Dimensions::_3D && A == AntiAliasing::None)
            : GTexture{ format, filter, wrapping, dimensions }
        {
            copy(format, data);
        }
        template<typename T>
        GTexture(Texture::Format format, Texture::Filter filter, Texture::Wrapping wrapping, const vector_t& dimensions, u8 samples, std::span<const T> data) requires (D == Dimensions::_3D && A == AntiAliasing::MSAA)
            : GTexture{ format, filter, wrapping, dimensions, samples }
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

        void copy(Texture::Format format, std::span<const byte> data)                                                                                         requires (A == AntiAliasing::None)
        {
            copy_range(format, this->m_dimensions, vector_t{}, data);
        }
        void copy_range(Texture::Format format, const vector_t& dimensions, const vector_t& offset, std::span<const byte> data)                               requires (A == AntiAliasing::None)
        {
            if (data.empty()) return;
            if (glm::any(glm::greaterThan(this->m_dimensions, offset + dimensions))) throw std::invalid_argument{ "The data size exceeds texture bounds!" };
            
            if constexpr (D == Dimensions::_1D) gl::texture_sub_image_1d(m_glId, gl::texture_format_base(format), dimensions, offset, 0, data.data());
            if constexpr (D == Dimensions::_2D) gl::texture_sub_image_2d(m_glId, gl::texture_format_base(format), dimensions, offset, 0, data.data());
            if constexpr (D == Dimensions::_3D) gl::texture_sub_image_3d(m_glId, gl::texture_format_base(format), dimensions, offset, 0, data.data());
        }

        GLuint id()      const
        {
            return m_glId;
        }
        u8     samples() const
        {
            return m_samples;
        }

    private:
        GLuint m_glId{};
        GLuint m_glFormat{};
        GLuint m_glMinFilter{};
        GLuint m_glMagFilter{};
        GLuint m_glWrapping{};
        u8     m_samples{};
    };
}
