#pragma once

#include "stdafx.hpp"

#include "Fox/Rendering/API/OpenGL/OpenGL.hpp"
#include "Fox/Rendering/Layout/Layout.hpp"
#include "Fox/Rendering/Concepts/Concepts.hpp"
#include "Fox/Rendering/Buffer/DataTypes.hpp"

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
            gfx::DataType dataType{};
            fox::size_t   typeSize{};
            fox::bool_t   isNormalized{};
            fox::bool_t   isStatic{};
            fox::uint32_t divisionRate{};
        };

        VertexLayout() = default;

        template<typename T>
        void specify(fox::uint32_t count, fox::bool_t isNormalized = false, fox::bool_t isStatic = false, fox::uint32_t divisionRate = 0u)
        {
            m_attributes.emplace_back(count, gfx::map_data_type<T>(), sizeof(T), isNormalized, isStatic, divisionRate);
        }

        fox::size_t stride() const
        {
            const auto& stride = std::accumulate(m_attributes.begin(), m_attributes.end(), fox::size_t{ 0 }, [](fox::size_t acc, const Attribute& _)
                {
                    return acc + _.stride();
                });

            return stride;
        }

        std::span<const Attribute> attributes() const
        {
            return m_attributes;
        }

    private:
        std::vector<Attribute> m_attributes{};
    };
}
