#pragma once

#include "Fox/Core/Library/Image/Image.hpp"
#include "Fox/Rendering/API/OpenGL/Texture/Texture.hpp"

namespace fox::gfx::api::gl
{
    class CubemapTexture : public gl::Object
    {
    public:
        using texture_t = gl::Texture<gfx::Dimensions::_2D, gfx::AntiAliasing::None>;

        CubemapTexture(const gl::Vector2u& dimensions, std::span<const fox::Image> images)
            : m_dimensions{ dimensions }
        {
            m_handle = gl::create_texture(gl::flg::Texture::Target::CubeMap);

            gl::texture_storage_2d(m_handle, gl::flg::Texture::Format::RGB8_UNORM, m_dimensions, gl::size_t{ 1 });

            for (const auto& i : std::ranges::iota_view(0u, 6u))
            {
                const auto& image = images[i];

                if (image.layout()     != fox::Image::Layout::RGB8) throw std::invalid_argument{ "Only RGB images are allowed!" };
                if (image.dimensions() != m_dimensions)             throw std::invalid_argument{ "Image dimensions must be equal!" };

                gl::texture_sub_image_3d(m_handle, gl::flg::Texture::BaseFormat::RGB, gl::Vector3u{ m_dimensions, 1u }, gl::Vector3u{ 0u, 0u, i }, 0, image.data().data());
            }

            gl::texture_parameter(m_handle, gl::flg::Texture::Parameter::MinificationFilter, gl::flg::Texture::MinificationFilter::Linear);
            gl::texture_parameter(m_handle, gl::flg::Texture::Parameter::MagnificationFilter, gl::flg::Texture::MinificationFilter::Linear);
            gl::texture_parameter(m_handle, gl::flg::Texture::Parameter::WrappingS, gl::TextureParameter{ gl::flg::Texture::Wrapping::ClampToEdge });
            gl::texture_parameter(m_handle, gl::flg::Texture::Parameter::WrappingT, gl::TextureParameter{ gl::flg::Texture::Wrapping::ClampToEdge });
            gl::texture_parameter(m_handle, gl::flg::Texture::Parameter::WrappingR, gl::TextureParameter{ gl::flg::Texture::Wrapping::ClampToEdge });
        }

        void bind_index(gl::uint32_t index)
        {
            gl::bind_texture_unit(m_handle, index);
        }

    protected:
        gl::Vector2u m_dimensions{};
    };
}