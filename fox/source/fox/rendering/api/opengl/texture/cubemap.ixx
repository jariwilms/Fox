export module fox.rendering.api.opengl.cubemap;

import std;

import fox.core.image;
import fox.core.types.math;
import fox.math.texture;
import fox.rendering.api.opengl;
import fox.rendering.api.opengl.texture;
import fox.rendering.base.cubemap;

export namespace fox::gfx::api::gl
{
    class cubemap : public gl::Object
    {
    public:
        using format_e   = api::Cubemap::Format;
        using filter_e   = api::Cubemap::Filter;
        using wrapping_e = api::Cubemap::Wrapping;
        using wrapping_t = gl::proxy_t<wrapping_e, wrapping_e>;
        using face_e     = api::Cubemap::Face;

         cubemap(format_e format, filter_e filter, wrapping_t wrapping, const gl::Vector2u& dimensions)
            : gl::Object{ gl::create_texture(glf::Texture::Target::CubeMap), [](auto* handle) { gl::delete_texture(*handle); } }
            , format_{ format }, filter_{ filter }, wrapping_{ wrapping }, dimensions_{ dimensions }, mipmapLevels_{ 1u }
        {
            if (filter != filter_e::None)
            {
                gl::texture_parameter(handle_, glp::magnification_filter{ gl::map_texture_mag_filter(filter_) });
                gl::texture_parameter(handle_, glp::minification_filter { gl::map_texture_min_filter(filter_) });
                gl::texture_parameter(handle_, glp::maximum_anisotropy  { gl::float32_t{ 1.0f } });

                mipmapLevels_ = math::mipmap_levels(dimensions_);
            }

            const auto& [s, t] = wrapping_.pack;
            gl::texture_parameter(handle_, glp::wrapping_s{ gl::map_texture_wrapping(s) });
            gl::texture_parameter(handle_, glp::wrapping_t{ gl::map_texture_wrapping(t) });
            
            gl::texture_storage_2d(handle_, gl::map_cubemap_texture_format(format_), dimensions_, mipmapLevels_);
        }
         cubemap(format_e format, filter_e filter, wrapping_t wrapping, const gl::Vector2u& dimensions, std::span<const fox::image> faces)
            : cubemap{ format, filter, wrapping, dimensions }
        {
            attach_faces(faces, format_);
            generate_mipmap();
        }
         cubemap(format_e format,                                        const gl::Vector2u& dimensions, std::span<const fox::image> faces)
            : cubemap{ format, filter_e::Trilinear, wrapping_e::Repeat, dimensions, faces } {}

        void bind(gl::binding_t binding) const
        {
            gl::bind_texture_unit(handle_, binding);
        }

        void copy      (face_e face, format_e format,                    std::span<const gl::byte_t> data)
        {
            copy_range(face, format, dimensions_, data);
        }
        void copy_range(face_e face, format_e format, gl::area_t region, std::span<const gl::byte_t> data)
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

        void apply_wrapping (wrapping_t wrapping)
        {
            wrapping_ = wrapping;

            const auto& [s, t] = wrapping_.pack;
            gl::texture_parameter(handle_, glp::wrapping_s{ gl::map_texture_wrapping(s) });
            gl::texture_parameter(handle_, glp::wrapping_s{ gl::map_texture_wrapping(t) });
        }
        void generate_mipmap()
        {
            if (filter_ != filter_e::None) gl::generate_texture_mipmap(handle_);
        }

        auto format       () const -> format_e
        {
            return format_;
        }
        auto filter       () const -> filter_e
        {
            return filter_;
        }
        auto wrapping     () const -> const std::tuple<wrapping_e, wrapping_e>&
        {
            return wrapping_.pack;
        }
        auto dimensions   () const -> const gl::Vector2u&
        {
            return dimensions_;
        }
        auto mipmap_levels() const -> gl::uint32_t
        {
            return mipmapLevels_;
        }

    private:
        void attach_faces(std::span<const fox::image> faces, format_e format)
        {
            //These indices are swapped intentionally    |   |
            std::array<gl::index_t, 6u> indices{ 0u, 1u, 3u, 2u, 4u, 5u };
            
            for (auto&& [index, face] : std::views::enumerate(faces))
            {
                if (face.dimensions() != dimensions_) throw std::invalid_argument{ "Face dimension must be equal to cubemap dimension!" };

                copy(static_cast<face_e>(indices.at(index)), format, face.data());
            }
        }

        format_e     format_;
        filter_e     filter_;
        wrapping_t   wrapping_;
        gl::Vector2u dimensions_;
        gl::uint32_t mipmapLevels_;
    };
}
