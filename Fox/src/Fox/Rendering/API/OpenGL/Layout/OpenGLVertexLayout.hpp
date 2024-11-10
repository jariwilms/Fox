#pragma once

#include "stdafx.hpp"

#include "Fox/Rendering/API/OpenGL/GL.hpp"
#include "Fox/Rendering/Layout/Layout.hpp"

namespace fox::gfx::api::gl
{
    struct OpenGLAttribute
    {
    public:
        size_t stride() const
        {
            return count * typeSize;
        }

        GLenum glType{};

        std::uint32_t count{};
        size_t        typeSize{};
        bool          isNormalized{};
    };

    template<typename... T>
    class OpenGLVertexLayout
    {
    public:
        OpenGLVertexLayout()
        {
            (m_attributes.emplace_back(OpenGLAttribute{ gl::type_enum<typename T::type>(), T::count, T::count * sizeof(typename T::type), T::isNormalized }), ...);
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

        std::span<const OpenGLAttribute> attributes() const
        {
            return m_attributes;
        }

    private:
        std::vector<OpenGLAttribute> m_attributes{};
    };
}
