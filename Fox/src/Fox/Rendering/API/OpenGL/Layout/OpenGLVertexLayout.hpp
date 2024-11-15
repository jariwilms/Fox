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

        enum_t glType{};

        std::uint32_t count{};
        size_t        typeSize{};
        bool          isNormalized{};
    };

    template<typename... T>
    class OpenGLVertexLayout
    {
    public:
        OpenGLVertexLayout(std::initializer_list<const std::uint32_t> count)
        {
            auto* first = count.begin();

            std::int32_t index{};
            ((m_attributes.emplace_back(OpenGLAttribute{ gl::type_enum<T>(), *(first + index), static_cast<size_t>(*(first + index) * sizeof(T)), false }), ++index), ...);
            //(m_attributes.emplace_back(OpenGLAttribute{ gl::type_enum<typename T::type>(), T::count, T::count * sizeof(typename T::type), T::isNormalized }), ...);
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



    void test()
    {

    }
}
