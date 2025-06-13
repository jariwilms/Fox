#pragma once

#include "stdafx.hpp"

#include "Fox/Rendering/API/Layout/Layout.hpp"
#include "Fox/Rendering/API/Concepts/Concepts.hpp"
#include "Fox/Rendering/API/Buffer/DataType.hpp"

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
            m_attributes.emplace_back(api::map_type<T>(), count, sizeof(T), isNormalized, isStatic, divisionRate);
        }

        auto attributes() const
        {
            return std::span<const Attribute>{ m_attributes };
        }
        auto stride    () const
        {
            return std::accumulate(m_attributes.begin(), m_attributes.end(), fox::size_t{ 0 }, [](fox::size_t accumulator, const auto& attribute)
                {
                    return accumulator + (attribute.count * attribute.size);
                });
        }

    private:
        std::vector<Attribute> m_attributes{};
    };
}
