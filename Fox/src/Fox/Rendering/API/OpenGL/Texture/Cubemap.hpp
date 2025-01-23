#pragma once

#include "Fox/Rendering/Texture/Cubemap.hpp"
#include "Fox/Rendering/API/OpenGL/Texture/Texture.hpp"

namespace fox::gfx::api::gl
{
    class Cubemap : public api::Cubemap, public gl::Object
    {
    public:
        using texture_t = gl::Texture<gfx::Dimensions::_2D, gfx::AntiAliasing::None>;

        Cubemap(Format format, const gl::Vector2u& dimensions)
            : Cubemap{ format, Filter::Trilinear, Wrapping::ClampToEdge, dimensions } {}
        Cubemap(Format format, Filter filter, Wrapping wrapping, const gl::Vector2u& dimensions)
            : api::Cubemap{ format }, m_dimensions{ dimensions }, m_mipmapLevels{ 1u }
        {
            m_handle = gl::create_texture(glf::Texture::Target::CubeMap);

            if (filter != Filter::None) m_mipmapLevels = gfx::calculate_mipmap_level(m_dimensions);

            gl::texture_storage_2d(m_handle, gl::map_cubemap_texture_format(m_format), m_dimensions, static_cast<gl::size_t>(m_mipmapLevels));

            gl::texture_parameter(m_handle, glf::Texture::Parameter::MinificationFilter,  gl::map_texture_min_filter(filter));
            gl::texture_parameter(m_handle, glf::Texture::Parameter::MagnificationFilter, gl::map_texture_mag_filter(filter));
            gl::texture_parameter(m_handle, glf::Texture::Parameter::WrappingS, gl::TextureParameter{ gl::map_texture_wrapping(wrapping) });
            gl::texture_parameter(m_handle, glf::Texture::Parameter::WrappingT, gl::TextureParameter{ gl::map_texture_wrapping(wrapping) });
            gl::texture_parameter(m_handle, glf::Texture::Parameter::WrappingR, gl::TextureParameter{ gl::map_texture_wrapping(wrapping) });
        }
        Cubemap(Format format, const gl::Vector2u& dimensions, const Layout& layout)
            : Cubemap{ format, Filter::Trilinear, Wrapping::ClampToEdge, dimensions, layout } {}
        Cubemap(Format format, Filter filter, Wrapping wrapping, const gl::Vector2u& dimensions, const Layout& layout)
            : Cubemap{ format, filter, wrapping, dimensions }
        {
            attach_images(layout);
            gl::generate_texture_mipmap(m_handle);
        }

        void bind(gl::uint32_t index) const
        {
            gl::bind_texture_unit(m_handle, index);
        }

    protected:
        void attach_image(const fox::Image& image, fox::uint32_t index)
        {
            if (image.layout()     != fox::Image::Layout::RGB8) throw std::invalid_argument{ "Only RGB images are allowed! (for now)" };
            if (image.dimensions() != m_dimensions)             throw std::invalid_argument{ "Image dimensions must be equal!" };

            gl::texture_sub_image_3d(m_handle, glf::Texture::BaseFormat::RGB, gl::Vector3u{ m_dimensions, 1u }, gl::Vector3u{ 0u, 0u, index }, 0, image.data().data());
        }
        void attach_images(const Layout& layout)
        {
            attach_image(layout.right,  0);
            attach_image(layout.left,   1);
            attach_image(layout.top,    3); //These need to be swapped because OpenGL
            attach_image(layout.bottom, 2); //
            attach_image(layout.front,  4);
            attach_image(layout.back,   5);
        }

        gl::Vector2u  m_dimensions{};
        fox::uint32_t m_mipmapLevels{};
    };
}