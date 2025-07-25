export module fox.rendering.api.opengl.domain;

import std;
import fox.rendering.api.opengl.types;

export namespace fox::gfx::api::gl
{
    template<typename T, gl::uint32_t N>
    struct region
    {
        constexpr region(const gl::vector_t<T, N>& extent = {}, const gl::vector_t<T, N>& origin = {})
            : extent{ extent }, origin{ origin } {}

        auto operator==(const region&) const -> gl::bool_t = default;

        gl::vector_t<T, N> extent{};
        gl::vector_t<T, N> origin{};
    };
    struct range
    {
        constexpr range(gl::count_t count = {}, gl::index_t index = {})
            : count{ count }, index{ index } {}

        auto operator==(const range&) const -> gl::bool_t = default;

        gl::count_t count{};
        gl::index_t index{};
    };
    struct byterange
    {
        constexpr byterange(gl::size_t size = {}, gl::offset_t offset = {})
            : size{ size }, offset{ offset } {}

        auto operator==(const byterange&) const -> gl::bool_t = default;

        gl::size_t   size{};
        gl::offset_t offset{};
    };

    using length_t      = gl::region<gl::uint32_t, 1u>;
    using area_t        = gl::region<gl::uint32_t, 2u>;
    using volume_t      = gl::region<gl::uint32_t, 3u>;
    using hypervolume_t = gl::region<gl::uint32_t, 4u>; //Yes, this exists

}
