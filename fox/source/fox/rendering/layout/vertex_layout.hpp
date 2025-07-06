#pragma once

#include <stdafx.hpp>

#include <fox/core/types/common/common.hpp>
#include <fox/core/types/fundamental/fundamental.hpp>
#include <fox/rendering/base/buffer/type.hpp>
#include <fox/rendering/layout/layout.hpp>

namespace fox::gfx
{
    class VertexLayout
    {
    public:
        struct Attribute
        {
            api::Type     type{};
            fox::count_t  count{};
            fox::size_t   size{};
            fox::bool_t   isNormalized{};
            fox::bool_t   isStatic{};
            fox::uint32_t divisionRate{};
        };

        template<typename T>
        void specify(fox::count_t count, fox::bool_t isNormalized = fox::False, fox::bool_t isStatic = fox::False, fox::uint32_t divisionRate = {})
        {
            attributes_.emplace_back(api::map_type<T>(), count, sizeof(T), isNormalized, isStatic, divisionRate);
        }

        auto attributes() const -> std::span<const Attribute>
        {
            return attributes_;
        }
        auto stride    () const -> fox::size_t
        {
            return std::ranges::fold_left(attributes_, fox::size_t{ 0 }, [](fox::size_t accumulator, const auto& attribute) -> fox::size_t
                {
                    return accumulator + (attribute.count * attribute.size);
                });
        }

    private:
        std::vector<Attribute> attributes_{};
    };
}
