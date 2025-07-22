export module fox.core.image;

import std;
import fox.config;
import fox.core.types;
import vendor.stb;

export namespace fox
{
    class image
    {
    public:
        enum class e_format
        {
            r8,
            rg8,
            rgb8,
            rgba8,

            r16,
            rg16,
            rgb16,
            rgba16,

            rgb16_float,
            rgba16_float,

            rgb32_float,
            rgba32_float,
        };
        enum class e_extension
        {
            bmp,
            hdr,
            jpg,
            png,
        };

        template<std::ranges::range R>
        image(e_format format, const fox::vector2u& dimensions, R&& range)
            : format_{ format }, dimensions_{ dimensions }, data_{ std::from_range, std::forward<R>(range) } {}

        template<e_extension E>
        static auto encode(const fox::image& image) -> auto
        {
            stb::set_flip_vertically_on_write(cfg::flip_images);

            using enum e_extension;
            if constexpr (E == bmp) return stb::write_bmp_to_function(data_, std::to_underlying(map_channels(format_)), dimensions_);
            if constexpr (E == jpg) return stb::write_jpg_to_function(data_, std::to_underlying(map_channels(format_)), dimensions_);
            if constexpr (E == png) return stb::write_png_to_function(data_, std::to_underlying(map_channels(format_)), dimensions_);
            if constexpr (E == hdr) return stb::write_hdr_to_function(data_, std::to_underlying(map_channels(format_)), dimensions_);
        }
        static auto decode(e_format format, std::span<const fox::byte_t> data) -> fox::image
        {
            stb::set_flip_vertically_on_load(cfg::flip_images);

            const auto channels = std::invoke([&](auto format) -> fox::uint32_t
                {
                    switch (format)
                    {
                        using enum e_format;

                        case r8          :
                        case r16         : return fox::uint32_t{ 1u };

                        case rg8         :
                        case rg16        : return fox::uint32_t{ 2u };

                        case rgb8        :
                        case rgb16       :
                        case rgb16_float :
                        case rgb32_float : return fox::uint32_t{ 3u };

                        case rgba8       :
                        case rgba16      :
                        case rgba16_float:
                        case rgba32_float: return fox::uint32_t{ 4u };

                        default: throw std::invalid_argument{ "Invalid format!" };
                    }
                }, format);
            const auto result   = std::invoke([&](auto format)
                {
                    switch (format)
                    {
                        using enum e_format;

                        case r8          :
                        case rg8         :
                        case rgb8        :
                        case rgba8       : return stb::load_from_memory<fox::uint8_t  >(channels, data);

                        case r16         :
                        case rg16        :
                        case rgb16       :
                        case rgba16      : return stb::load_from_memory<fox::uint16_t >(channels, data);

                        case rgb16_float :
                        case rgba16_float:
                        case rgb32_float :
                        case rgba32_float: return stb::load_from_memory<fox::float32_t>(channels, data);

                        default: throw std::invalid_argument{ "Invalid format!" };
                    };
                }, format);

            return fox::image{ format, result.dimensions, std::move(result.data) };
        }

        auto format    () const -> e_format
        {
            return format_;
        }
        auto dimensions() const -> const fox::vector2u&
        {
            return dimensions_;
        }
        auto data      () const -> std::span<const fox::byte_t>
        {
            return data_;
        }

    private:
        e_format                 format_;
        fox::vector2u            dimensions_;
        std::vector<fox::byte_t> data_;
    };
}
