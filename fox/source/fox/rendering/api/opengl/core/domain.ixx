export module fox.rendering.api.opengl.domain;

import std;
import fox.rendering.api.opengl.types;

export namespace fox::gfx::api::gl
{
    template<typename T, gl::uint32_t N>
    struct region_t
    {
        constexpr region_t(const gl::Vector<T, N>& extent = {}, const gl::Vector<T, N>& origin = {})
            : extent{ extent }, origin{ origin } {}

        auto operator==(const region_t&) const -> gl::bool_t = default;

        gl::Vector<T, N> extent{};
        gl::Vector<T, N> origin{};
    };
    struct range_t
    {
        constexpr range_t(gl::count_t count = {}, gl::index_t index = {})
            : count{ count }, index{ index } {}

        auto operator==(const range_t&) const -> gl::bool_t = default;

        gl::count_t count{};
        gl::index_t index{};
    };
    struct byterange_t
    {
        constexpr byterange_t(gl::size_t size = {}, gl::offset_t offset = {})
            : size{ size }, offset{ offset } {}

        auto operator==(const byterange_t&) const -> gl::bool_t = default;

        gl::size_t   size{};
        gl::offset_t offset{};
    };

    using length_t      = gl::region_t<gl::uint32_t, 1u>;
    using area_t        = gl::region_t<gl::uint32_t, 2u>;
    using volume_t      = gl::region_t<gl::uint32_t, 3u>;
    using hypervolume_t = gl::region_t<gl::uint32_t, 4u>; //Yes, this exists

    using lock_t        = std::tuple<gl::range_t, gl::sync_t>;
}
