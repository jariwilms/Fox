#pragma once

#include "stdafx.hpp"

#include "Helix/Experimental/Rendering/API/OpenGL/OpenGL.hpp"
#include "Helix/Experimental/Rendering/Layout/VertexLayout.hpp"

namespace hlx::gfx::api
{
    template<>
    struct Attribute<GraphicsAPI::OpenGL>
    {
    public:
        size_t stride() const
        {
            return count * typeSize;
        }

        GLenum glType{};
        u32    count{};
        size_t typeSize{};
        bool   isNormalized{};
    };

    template<typename... T>
    class VertexLayout<GraphicsAPI::OpenGL, T...>
    {
    public:
        using Attribute = Attribute<GraphicsAPI::OpenGL>;
        using span_t = std::span<const Attribute>;

        VertexLayout()
        {
            (m_attributes.emplace_back(Attribute{ gl::type_enum<typename T::type>(), T::count, T::count * sizeof(typename T::type), T::isNormalized }), ...);
        }

        size_t stride()     const
        {
            size_t result{};
            for (const auto& attribute : m_attributes)
            {
                result += attribute.stride();
            }

            return result;
        }
        span_t attributes() const
        {
            return m_attributes;
        }

    private:
        std::vector<Attribute> m_attributes{};
    };
}
