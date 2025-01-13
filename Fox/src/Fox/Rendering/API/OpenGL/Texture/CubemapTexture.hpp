#pragma once

#include "Fox/Rendering/Texture/CubemapTexture.hpp"
#include "Fox/Rendering/API/OpenGL/Texture/Texture.hpp"

namespace fox::gfx::api::gl
{
    class CubemapTexture : public api::CubemapTexture, public gl::Object
    {
    public:
        using texture_t = gl::Texture<gfx::Dimensions::_2D, gfx::AntiAliasing::None>;

        CubemapTexture(const gl::Vector2u& dimensions, const Layout& layout)
            : m_dimensions{ dimensions }
        {
            m_handle       = gl::create_texture(glf::Texture::Target::CubeMap);
            m_mipmapLevels = gfx::calculate_mipmap_level(m_dimensions);

            gl::texture_storage_2d(m_handle, glf::Texture::Format::RGB8_UNORM, m_dimensions, static_cast<gl::size_t>(m_mipmapLevels));

            attach_images(layout);

            gl::texture_parameter(m_handle, glf::Texture::Parameter::MinificationFilter,  glf::Texture::MinificationFilter::LinearMipmapLinear);
            gl::texture_parameter(m_handle, glf::Texture::Parameter::MagnificationFilter, glf::Texture::MinificationFilter::Linear);
            gl::texture_parameter(m_handle, glf::Texture::Parameter::WrappingS, gl::TextureParameter{ glf::Texture::Wrapping::ClampToEdge });
            gl::texture_parameter(m_handle, glf::Texture::Parameter::WrappingT, gl::TextureParameter{ glf::Texture::Wrapping::ClampToEdge });
            gl::texture_parameter(m_handle, glf::Texture::Parameter::WrappingR, gl::TextureParameter{ glf::Texture::Wrapping::ClampToEdge });

            gl::generate_texture_mipmap(m_handle);
        }

        void bind_index(gl::uint32_t index) const
        {
            gl::bind_texture_unit(m_handle, index);
        }

    protected:
        void attach_image(const fox::Image& image, fox::uint32_t index)
        {
            if (image.layout()     != fox::Image::Layout::RGB8) throw std::invalid_argument{ "Only RGB images are allowed!" };
            if (image.dimensions() != m_dimensions)             throw std::invalid_argument{ "Image dimensions must be equal!" };

            gl::texture_sub_image_3d(m_handle, glf::Texture::BaseFormat::RGB, gl::Vector3u{ m_dimensions, 1u }, gl::Vector3u{ 0u, 0u, index }, 0, image.data().data());
        }
        void attach_images(const Layout& layout)
        {
            attach_image(layout.right,  0);
            attach_image(layout.left,   1);
            attach_image(layout.top,    3); //These are flipped because OpenGL is a bitch
            attach_image(layout.bottom, 2);
            attach_image(layout.front,  4);
            attach_image(layout.back,   5);
        }

        gl::Vector2u m_dimensions{};
        fox::uint32_t m_mipmapLevels{};
    };
}