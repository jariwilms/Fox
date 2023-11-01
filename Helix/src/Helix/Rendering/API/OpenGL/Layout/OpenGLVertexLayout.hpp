#pragma once

#include "stdafx.hpp"

#include "Helix/Rendering/API/OpenGL/OpenGL.hpp"
#include "Helix/Rendering/Layout/Layout.hpp"

namespace hlx::gfx::api
{
    template<>
    struct GAttribute<GraphicsAPI::OpenGL>
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
    class GVertexLayout<GraphicsAPI::OpenGL, T...>
    {
    public:
        using Attribute = GAttribute<GraphicsAPI::OpenGL>;
        using span_t = std::span<const Attribute>;

        GVertexLayout()
        {
            (m_attributes.emplace_back(Attribute{ gl::type_enum<typename T::type>(), T::count, T::count * sizeof(typename T::type), T::isNormalized }), ...);
        }

        span_t attributes() const
        {
            return m_attributes;
        }

    private:
        std::vector<Attribute> m_attributes{};
    };
}
