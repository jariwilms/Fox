export module vendor.stb;

import std;
import <stb/stb_image.h>;
import <stb/stb_image_write.h>;
import fox.core.types;
import fox.core.memory.adapter.no_init;
import fox.core.utility;

       namespace stb
{
    template<typename T>
    void write_function(fox::void_t* context, fox::void_t* data, fox::int32_t size)
    {
        auto ctx     = std::bit_cast<std::vector<T>*>(context);
        auto pointer = std::bit_cast<const T*>(data);
        auto span    = std::span{ pointer, static_cast<fox::size_t>(size) };

        ctx->append_range(span);
    }
    void free_image    (fox::byte_t* pointer)
    {
        stbi_image_free(pointer);
    }
}
export namespace stb
{
    struct image_data
    {
        fox::uint32_t            channels;
        fox::Vector2u            dimensions;
        std::vector<fox::byte_t> data;
    };

    void set_flip_vertically_on_load (fox::bool_t value)
    {
        ::stbi_set_flip_vertically_on_load(value);
    }
    void set_flip_vertically_on_write(fox::bool_t value)
    {
        ::stbi_flip_vertically_on_write(value);
    }

    template<typename T>
    auto load_from_memory            (fox::uint32_t channels, std::span<const fox::byte_t> data) -> stb::image_data
    {
        auto stbDimensions = fox::Vector2i{};
        auto stbChannels   = fox::int32_t {};

        if constexpr (std::is_same_v<T, fox::uint8_t  >)
        {
            const auto stbPointer = std::bit_cast<fox::byte_t*>(::stbi_load_from_memory(data.data(), static_cast<fox::int32_t>(data.size_bytes()), &stbDimensions.x, &stbDimensions.y, &stbChannels, channels));
            const auto stbSize    = sizeof(fox::uint8_t) * channels * stbDimensions.x * stbDimensions.y;
            const auto stbSpan    = std::span<const fox::byte_t>{ stbPointer, stbSize };
            const auto stbImage   = stb::image_data
            {
                static_cast<fox::uint32_t>(stbChannels), 
                static_cast<fox::Vector2u>(stbDimensions), 
                std::vector<fox::byte_t>{ std::from_range, stbSpan }
            };

            stb::free_image(stbPointer);
            return stbImage;
        }
        if constexpr (std::is_same_v<T, fox::uint16_t >)
        {
            const auto stbPointer = std::bit_cast<fox::byte_t*>(::stbi_load_16_from_memory(data.data(), static_cast<fox::int32_t>(data.size_bytes()), &stbDimensions.x, &stbDimensions.y, &stbChannels, channels));
            const auto stbSize    = sizeof(fox::uint16_t) * channels * stbDimensions.x * stbDimensions.y;
            const auto stbSpan    = std::span<const fox::byte_t>{ stbPointer, stbSize };
            const auto stbImage   = stb::image_data
            {
                static_cast<fox::uint32_t>(stbChannels), 
                static_cast<fox::Vector2u>(stbDimensions), 
                std::vector<fox::byte_t>{ std::from_range, stbSpan }
            };

            stb::free_image(stbPointer);
            return stbImage;
        }
        if constexpr (std::is_same_v<T, fox::float32_t>)
        {
            const auto stbPointer = std::bit_cast<fox::byte_t*>(::stbi_loadf_from_memory(data.data(), static_cast<fox::int32_t>(data.size_bytes()), &stbDimensions.x, &stbDimensions.y, &stbChannels, channels));
            const auto stbSize    = sizeof(fox::float32_t) * channels * stbDimensions.x * stbDimensions.y;
            const auto stbSpan    = std::span<const fox::byte_t>{ stbPointer, stbSize };
            const auto stbImage   = stb::image_data
            {
                static_cast<fox::uint32_t>(stbChannels), 
                static_cast<fox::Vector2u>(stbDimensions), 
                std::vector<fox::byte_t>{ std::from_range, stbSpan }
            };

            stb::free_image(stbPointer);
            return stbImage;
        }
    }

    auto write_bmp_to_function       (std::span<const fox::byte_t> data, fox::uint32_t channels, const fox::Vector2u& dimensions) -> std::vector<fox::byte_t>
    {
        auto vector = std::vector<fox::byte_t>{};

        ::stbi_write_bmp_to_func(
            stb::write_function<fox::byte_t>, 
            &vector, dimensions.x, dimensions.y, 
            channels, data.data());

        return vector;
    }
    auto write_hdr_to_function       (std::span<const fox::byte_t> data, fox::uint32_t channels, const fox::Vector2u& dimensions) -> std::vector<fox::float32_t>
    {
        auto vector = std::vector<fox::float32_t>{};

        ::stbi_write_hdr_to_func(
            stb::write_function<fox::float32_t>, 
            &vector, dimensions.x, dimensions.y, 
            channels, std::bit_cast<const fox::float32_t*>(data.data()));

        return vector;
    }
    auto write_jpg_to_function       (std::span<const fox::byte_t> data, fox::uint32_t channels, const fox::Vector2u& dimensions) -> std::vector<fox::byte_t>
    {
        auto vector = std::vector<fox::byte_t>{};

        ::stbi_write_jpg_to_func(
            stb::write_function<fox::byte_t>, 
            &vector, dimensions.x, dimensions.y, 
            channels, data.data(), fox::int32_t{ 100u });

        return vector;
    }
    auto write_png_to_function       (std::span<const fox::byte_t> data, fox::uint32_t channels, const fox::Vector2u& dimensions) -> std::vector<fox::byte_t>
    {
        auto vector = std::vector<fox::byte_t>{};

        ::stbi_write_png_to_func(
            stb::write_function<fox::byte_t>, 
            &vector, dimensions.x, dimensions.y, 
            channels, data.data(), channels * dimensions.x);

        return vector;
    }
}
