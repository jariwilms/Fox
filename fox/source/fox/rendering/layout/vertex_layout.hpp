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

        auto attributes() const
        {
            return std::span<const Attribute>{ attributes_ };
        }
        auto stride    () const
        {
            return std::accumulate(attributes_.begin(), attributes_.end(), fox::size_t{ 0 }, [](fox::size_t accumulator, const auto& attribute)
                {
                    return accumulator + (attribute.count * attribute.size);
                });
        }

    private:
        std::vector<Attribute> attributes_{};
    };
}
