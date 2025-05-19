#pragma once

#include "Fox/Rendering/GraphicsAPI/OpenGL/Texture/Texture.hpp"
#include "Fox/Rendering/GraphicsAPI/OpenGL/OpenGL.hpp"
#include "Fox/Rendering/API/Texture/Cubemap.hpp"

namespace fox::gfx::api::gl
{
    class Cubemap : public api::Cubemap, public gl::Object
    {
    public:
        using texture_t = gl::Texture<api::Dimensions::_2D, api::AntiAliasing::None>;
        using range_t   = gl::Texture<api::Dimensions::_3D, api::AntiAliasing::None>::range_t;

        Cubemap(Format format, const gl::Vector2u& dimensions)
            : Cubemap{ format, Filter::Trilinear, Wrapping::ClampToEdge, dimensions } {}
        Cubemap(Format format, Filter filter, Wrapping wrapping, const gl::Vector2u& dimensions)
            : api::Cubemap{ format, filter }, m_wrapping{ wrapping }, m_mipmapLevels{ 1u }, m_dimensions{ dimensions }
        {
            m_handle = gl::create_texture(glf::Texture::Target::CubeMap);

            if (filter != Filter::None) m_mipmapLevels = api::calculate_mipmap_level(m_dimensions);

            gl::texture_storage_2d(m_handle, gl::map_cubemap_texture_format(m_format), m_dimensions, static_cast<gl::size_t>(m_mipmapLevels));

            gl::texture_parameter(m_handle, gl::magnification_filter_p{ gl::map_texture_mag_filter(m_filter)   });
            gl::texture_parameter(m_handle, gl::minification_filter_p { gl::map_texture_min_filter(m_filter)   });
            gl::texture_parameter(m_handle, gl::wrapping_s_p          { gl::map_texture_wrapping  (m_wrapping) });
            gl::texture_parameter(m_handle, gl::wrapping_t_p          { gl::map_texture_wrapping  (m_wrapping) });
            gl::texture_parameter(m_handle, gl::wrapping_r_p          { gl::map_texture_wrapping  (m_wrapping) });
        }
        Cubemap(Format format, const gl::Vector2u& dimensions, const Faces& face)
            : Cubemap{ format, Filter::Trilinear, Wrapping::ClampToEdge, dimensions, face } {}
        Cubemap(Format format, Filter filter, Wrapping wrapping, const gl::Vector2u& dimensions, const Faces& face)
            : Cubemap{ format, filter, wrapping, dimensions }
        {
            const auto& type = gl::map_cubemap_texture_format_type(format);

            attach_images(face, type);
            gl::generate_texture_mipmap(m_handle);
        }
        Cubemap(Cubemap&&) noexcept = default;
        ~Cubemap()
        {
            gl::delete_texture(m_handle);
        }

        void bind(gl::uint32_t index) const
        {
            gl::bind_texture_unit(m_handle, index);
        }

              Wrapping      wrapping()      const
        {
            return m_wrapping;
        }
        const gl::Vector2u& dimensions()    const
        {
            return m_dimensions;
        }
              gl::uint32_t  mipmap_levels() const
        {
            return m_mipmapLevels;
        }

        Cubemap& operator=(Cubemap&&) noexcept = default;

    protected:
        void attach_image(const fox::Image& image, glf::PixelData::Type type, fox::uint32_t index)
        {
            if (image.dimensions() != m_dimensions) throw std::invalid_argument{ "Image dimensions must be equal!" };

            gl::texture_sub_image_3d(m_handle, glf::Texture::BaseFormat::RGB, type, range_t{ gl::Vector3u{ 0u, 0u, index }, gl::Vector3u{ m_dimensions, 1u } }, 0, image.data());
        }
        void attach_images(const Faces& face, glf::PixelData::Type type)
        {
            attach_image(face.right,  type, 0);
            attach_image(face.left,   type, 1);
            attach_image(face.top,    type, 3); //These need to be swapped because OpenGL
            attach_image(face.bottom, type, 2); //
            attach_image(face.front,  type, 4);
            attach_image(face.back,   type, 5);
        }

        Wrapping      m_wrapping{};
        fox::uint32_t m_mipmapLevels{};
        gl::Vector2u  m_dimensions{};
    };
}
