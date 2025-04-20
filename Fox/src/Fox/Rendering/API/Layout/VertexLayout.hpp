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
        public:
            fox::size_t stride() const
            {
                return (count * typeSize);
            }

            fox::uint32_t count{};
            api::DataType dataType{};
            fox::size_t   typeSize{};
            fox::bool_t   isNormalized{};
            fox::bool_t   isStatic{};
            fox::uint32_t divisionRate{};
        };

        VertexLayout() = default;

        template<typename T>
        void specify(fox::uint32_t count, fox::bool_t isNormalized = false, fox::bool_t isStatic = false, fox::uint32_t divisionRate = 0u)
        {
            m_attributes.emplace_back(count, api::map_data_type<T>(), sizeof(T), isNormalized, isStatic, divisionRate);
        }

        fox::size_t stride() const
        {
            return std::accumulate(m_attributes.begin(), m_attributes.end(), fox::size_t{ 0 }, [](fox::size_t acc, const Attribute& _)
                {
                    return acc + _.stride();
                });
        }

        std::span<const Attribute> attributes() const
        {
            return m_attributes;
        }

    private:
        std::vector<Attribute> m_attributes{};
    };
}
