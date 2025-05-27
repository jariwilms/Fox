#pragma once

#include "Fox/Rendering/API/Texture/Cubemap.hpp"
#include "Fox/Rendering/GraphicsAPI/OpenGL/OpenGL.hpp"
#include "Fox/Rendering/GraphicsAPI/OpenGL/Texture/Texture.hpp"

namespace fox::gfx::api::gl
{
    class Cubemap : public gl::Object
    {
    public:
        using Format   = api::Cubemap::Format;
        using Filter   = api::Cubemap::Filter;
        using Wrapping = api::Cubemap::Wrapping;
        using Face     = api::Cubemap::Face;

         Cubemap(Format format,                                   const gl::Vector2u& dimensions)
            : Cubemap{ format, Filter::Trilinear, Wrapping::ClampToEdge, dimensions } {}
         Cubemap(Format format, Filter filter, Wrapping wrapping, const gl::Vector2u& dimensions)
            : m_format{ format }, m_filter{ filter }, m_wrapping{ wrapping, wrapping }, m_dimensions{ dimensions }, m_mipmapLevels{ 1u }
        {
            m_handle = gl::create_texture(glf::Texture::Target::CubeMap);

            if (filter != Filter::None)
            {
                gl::texture_parameter(m_handle, glp::magnification_filter{ gl::map_texture_mag_filter(m_filter) });
                gl::texture_parameter(m_handle, glp::minification_filter { gl::map_texture_min_filter(m_filter) });
                gl::texture_parameter(m_handle, glp::maximum_anisotropy  { gl::float32_t{ 1.0f } });

                m_mipmapLevels = api::calculate_mipmap_level(m_dimensions);
            }

            gl::texture_parameter(m_handle, glp::wrapping_s{ gl::map_texture_wrapping(m_wrapping.at(0)) });
            gl::texture_parameter(m_handle, glp::wrapping_t{ gl::map_texture_wrapping(m_wrapping.at(1)) });
            
            gl::texture_storage_2d(m_handle, gl::map_cubemap_texture_format(m_format), m_dimensions, m_mipmapLevels);
        }
         Cubemap(Format format,                                   const gl::Vector2u& dimensions, std::span<const fox::Image> faces)
            : Cubemap{ format, Filter::Trilinear, Wrapping::ClampToEdge, dimensions, faces } {}
         Cubemap(Format format, Filter filter, Wrapping wrapping, const gl::Vector2u& dimensions, std::span<const fox::Image> faces)
            : Cubemap{ format, filter, wrapping, dimensions }
        {
            attach_faces(faces, m_format);
            generate_mipmap();
        }
        ~Cubemap()
        {
            gl::delete_texture(m_handle);
        }

        void bind(gl::binding_t binding) const
        {
            gl::bind_texture_unit(m_handle, binding);
        }

        void copy      (Face face, Format format,                    std::span<const gl::byte_t> data)
        {
            copy_range(face, format, m_dimensions, data);
        }
        void copy_range(Face face, Format format, gl::area_t region, std::span<const gl::byte_t> data)
        {
            if (data.empty()) return;
            if (glm::any(glm::greaterThan(region.origin + region.extent, m_dimensions))) throw std::out_of_range{ "The given region exceeds texture bounds!" };

            gl::texture_sub_image_3d(
                m_handle,
                gl::map_cubemap_texture_format_base(format),
                gl::map_cubemap_texture_format_type(format),
                gl::uint32_t{ 0u },
                gl::volume_t{ gl::Vector3u{ m_dimensions, 1u }, gl::Vector3u{ 0u, 0u, gl::to_underlying(face) } },
                data);
        }

        void generate_mipmap()
        {
            if (m_filter != Filter::None) gl::generate_texture_mipmap(m_handle);
        }

        auto format    () const
        {
            return m_format;
        }
        auto filter    () const
        {
            return m_filter;
        }
        auto wrapping  () const
        {
            return m_wrapping;
        }
        auto dimensions() const
        {
            return m_dimensions;
        }

    private:
        void attach_faces(std::span<const fox::Image> faces, Format format)
        {
            //Indices are swapped intentionally          |   |
            std::array<gl::index_t, 6u> indices{ 0u, 1u, 3u, 2u, 4u, 5u };
            
            for (gl::index_t index{}; const auto& face : faces)
            {
                if (face.dimensions() != m_dimensions) throw std::invalid_argument{ "Face dimension is not equal to cubemap dimension!" };

                copy(static_cast<Face>(indices.at(index++)), format, face.data());
            }
        }

        Format                   m_format{};
        Filter                   m_filter{};
        std::array<Wrapping, 2u> m_wrapping{};
        gl::Vector2u             m_dimensions{};
        gl::uint32_t             m_mipmapLevels{};
    };
}
