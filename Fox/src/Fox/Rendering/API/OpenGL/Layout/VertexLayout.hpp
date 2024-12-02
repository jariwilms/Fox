#pragma once

#include "stdafx.hpp"

#include "Fox/Rendering/API/OpenGL/OpenGL.hpp"
#include "Fox/Rendering/Layout/Layout.hpp"

namespace fox::gfx::api::gl
{
    struct Attribute
    {
    public:
        gl::size_t stride() const
        {
            return static_cast<gl::size_t>(count * typeSize);
        }

        gl::enum_t    type{};

        fox::uint32_t count{};
        fox::size_t   typeSize{};
        fox::bool_t   isNormalized{};
    };

    template<typename... T>
    class VertexLayout
    {
    public:
        VertexLayout(std::initializer_list<const fox::uint32_t> count)
        {
            auto* first = count.begin();

            fox::int32_t index{};
            //((m_attributes.emplace_back(Attribute{ gl::map_type<T>(), *(first + index), static_cast<fox::size_t>(*(first + index) * sizeof(T)), false }), ++index), ...);
            ((m_attributes.emplace_back(Attribute{ gl::map_type<T>(), *(first + index), static_cast<fox::size_t>(sizeof(T)), false }), ++index), ...);
        }

        fox::size_t stride() const
        {
            fox::size_t result{};

            for (const auto& attribute : m_attributes)
            {
                result += attribute.stride();
            }

            return result;
        }

        std::span<const Attribute> attributes() const
        {
            return m_attributes;
        }

    private:
        std::vector<Attribute> m_attributes{};
    };
}
