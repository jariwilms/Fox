#pragma once

#include "stdafx.hpp"

#include "Helix/Rendering/API/OpenGL/GL.hpp"
#include "Helix/Rendering/API/Implementation/GVertexLayout.hpp"
#include "Helix/Rendering/Layout/Layout.hpp"

namespace hlx::gfx::imp::api
{
    template<>
    struct GAttribute<gfx::api::GraphicsAPI::OpenGL>
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
    class GVertexLayout<gfx::api::GraphicsAPI::OpenGL, T...>
    {
    public:
        using Attribute = GAttribute<gfx::api::GraphicsAPI::OpenGL>;

        GVertexLayout()
        {
            (m_attributes.emplace_back(Attribute{ gl::type_enum<typename T::type>(), T::count, T::count * sizeof(typename T::type), T::isNormalized }), ...);
        }

        size_t stride() const
        {
            size_t result{};

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
