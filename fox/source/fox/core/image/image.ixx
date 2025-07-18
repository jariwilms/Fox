export module fox.core.image;

import std;
import fox.config;
import fox.core.types;
import vendor.stb;

export namespace fox
{
    class Image
    {
    public:
        enum class Format
        {
            R8, 
            RG8, 
            RGB8, 
            RGBA8, 

            R16, 
            RG16, 
            RGB16, 
            RGBA16, 

            RGB16_FLOAT,
            RGBA16_FLOAT,

            RGB32_FLOAT, 
            RGBA32_FLOAT, 
        };
        enum class Extension
        {
            BMP, 
            HDR, 
            JPG, 
            PNG, 
        };

        template<std::ranges::range R>
        Image(Format format, const fox::Vector2u& dimensions, R&& range)
            : format_{ format }, dimensions_{ dimensions }, data_{ std::from_range, std::forward<R>(range) } {}

        template<Extension E>
        static auto encode(const fox::Image& image) -> auto
        {
            stb::set_flip_vertically_on_write(cfg::FLIP_IMAGES);
            
            if constexpr (E == Extension::BMP) return stb::write_bmp_to_function(data_, std::to_underlying(map_channels(format_)), dimensions_);
            if constexpr (E == Extension::JPG) return stb::write_jpg_to_function(data_, std::to_underlying(map_channels(format_)), dimensions_);
            if constexpr (E == Extension::PNG) return stb::write_png_to_function(data_, std::to_underlying(map_channels(format_)), dimensions_);
            if constexpr (E == Extension::HDR) return stb::write_hdr_to_function(data_, std::to_underlying(map_channels(format_)), dimensions_);
        }
        static auto decode(Format format, std::span<const fox::byte_t> data) -> fox::Image
        {
            stb::set_flip_vertically_on_load(cfg::FLIP_IMAGES);

            const auto channels = std::invoke([ ](Format format) -> fox::uint32_t
                {
                    switch (format)
                    {
                        case Format::R8:
                        case Format::R16:          return fox::uint32_t{ 1u };

                        case Format::RG8:
                        case Format::RG16:         return fox::uint32_t{ 2u };

                        case Format::RGB8:
                        case Format::RGB16:
                        case Format::RGB16_FLOAT:
                        case Format::RGB32_FLOAT:  return fox::uint32_t{ 3u };

                        case Format::RGBA8:
                        case Format::RGBA16:
                        case Format::RGBA16_FLOAT:
                        case Format::RGBA32_FLOAT: return fox::uint32_t{ 4u };

                        default: throw std::invalid_argument{ "Invalid format!" };
                    }
                }, format);
            const auto result   = std::invoke([&](Format format)
                {
                    switch (format)
                    {
                        case Format::R8:
                        case Format::RG8:
                        case Format::RGB8:
                        case Format::RGBA8:        return stb::load_from_memory<fox::uint8_t  >(channels, data);

                        case Format::R16:
                        case Format::RG16:
                        case Format::RGB16:
                        case Format::RGBA16:       return stb::load_from_memory<fox::uint16_t >(channels, data);

                        case Format::RGB16_FLOAT:
                        case Format::RGBA16_FLOAT:
                        case Format::RGB32_FLOAT:
                        case Format::RGBA32_FLOAT: return stb::load_from_memory<fox::float32_t>(channels, data);

                        default: throw std::invalid_argument{ "Invalid format!" };
                    };
                }, format);

            return fox::Image{ format, result.dimensions, std::move(result.data) };
        }

        auto format    () const -> Format
        {
            return format_;
        }
        auto dimensions() const -> const fox::Vector2u&
        {
            return dimensions_;
        }
        auto data      () const -> std::span<const fox::byte_t>
        {
            return data_;
        }

    private:
        Format                   format_;
        fox::Vector2u            dimensions_;
        std::vector<fox::byte_t> data_;
    };
}
