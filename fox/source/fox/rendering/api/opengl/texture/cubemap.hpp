#pragma once

#include <fox/core/image/image.hpp>
#include <fox/rendering/api/opengl/opengl.hpp>
#include <fox/rendering/api/opengl/texture/texture.hpp>
#include <fox/rendering/base/texture/cubemap.hpp>

namespace fox::gfx::api::gl
{
    class Cubemap : public gl::Object
    {
    public:
        using Format   = api::Cubemap::Format;
        using Filter   = api::Cubemap::Filter;
        using Wrapping = api::Cubemap::Wrapping;
        using Face     = api::Cubemap::Face;

         Cubemap(Format format, Filter filter, Wrapping wrapping, const gl::Vector2u& dimensions)
            : format_{ format }, filter_{ filter }, wrapping_{ wrapping, wrapping }, dimensions_{ dimensions }, mipmapLevels_{ 1u }
        {
            handle_ = gl::create_texture(glf::Texture::Target::CubeMap);

            if (filter != Filter::None)
            {
                gl::texture_parameter(handle_, glp::magnification_filter{ gl::map_texture_mag_filter(filter_) });
                gl::texture_parameter(handle_, glp::minification_filter { gl::map_texture_min_filter(filter_) });
                gl::texture_parameter(handle_, glp::maximum_anisotropy  { gl::float32_t{ 1.0f } });

                mipmapLevels_ = math::mipmap_levels(dimensions_);
            }

            gl::texture_parameter(handle_, glp::wrapping_s{ gl::map_texture_wrapping(wrapping_.at(0)) });
            gl::texture_parameter(handle_, glp::wrapping_t{ gl::map_texture_wrapping(wrapping_.at(1)) });
            
            gl::texture_storage_2d(handle_, gl::map_cubemap_texture_format(format_), dimensions_, mipmapLevels_);
        }
         Cubemap(Format format, Filter filter, Wrapping wrapping, const gl::Vector2u& dimensions, std::span<const fox::Image> faces)
            : Cubemap{ format, filter, wrapping, dimensions }
        {
            attach_faces(faces, format_);
            generate_mipmap();
        }
         Cubemap(Format format,                                   const gl::Vector2u& dimensions, std::span<const fox::Image> faces)
            : Cubemap{ format, Filter::Trilinear, Wrapping::Repeat, dimensions, faces } {}
        ~Cubemap()
        {
            gl::delete_texture(handle_);
        }

        void bind(gl::binding_t binding) const
        {
            gl::bind_texture_unit(handle_, binding);
        }

        void copy      (Face face, Format format,                    std::span<const gl::byte_t> data)
        {
            copy_range(face, format, dimensions_, data);
        }
        void copy_range(Face face, Format format, gl::area_t region, std::span<const gl::byte_t> data)
        {
            if (data.empty()) return;
            if (glm::any(glm::greaterThan(region.origin + region.extent, dimensions_))) throw std::out_of_range{ "The given region exceeds texture bounds!" };

            gl::texture_sub_image_3d(
                handle_,
                gl::map_cubemap_texture_format_base(format),
                gl::map_cubemap_texture_format_type(format),
                gl::uint32_t{ 0u },
                gl::volume_t{ gl::Vector3u{ dimensions_, 1u }, gl::Vector3u{ 0u, 0u, gl::to_underlying(face) } },
                data);
        }

        void generate_mipmap()
        {
            if (filter_ != Filter::None) gl::generate_texture_mipmap(handle_);
        }

        auto format       () const
        {
            return format_;
        }
        auto filter       () const
        {
            return filter_;
        }
        auto wrapping     () const -> std::span<const Wrapping, 2u>
        {
            return wrapping_;
        }
        auto dimensions   () const
        {
            return dimensions_;
        }
        auto mipmap_levels() const
        {
            return mipmapLevels_;
        }

    private:
        void attach_faces(std::span<const fox::Image> faces, Format format)
        {
            //Indices are swapped intentionally          |   |
            std::array<gl::index_t, 6u> indices{ 0u, 1u, 3u, 2u, 4u, 5u };
            
            for (auto&& [index, face] : std::views::enumerate(faces))
            {
                if (face.dimensions() != dimensions_) throw std::invalid_argument{ "Face dimension must be equal to cubemap dimension!" };

                copy(static_cast<Face>(indices.at(index)), format, face.data());
            }
        }

        Format                   format_{};
        Filter                   filter_{};
        std::array<Wrapping, 2u> wrapping_{};
        gl::Vector2u             dimensions_{};
        gl::uint32_t             mipmapLevels_{};
    };
}
