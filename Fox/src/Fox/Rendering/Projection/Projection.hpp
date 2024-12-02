#pragma once

#include "stdafx.hpp"

#include <glm/gtc/matrix_transform.hpp>

namespace fox::gfx
{
    class Projection
    {
    public:
        enum class Type
        {
            Perspective,
            Orthographic,
        };

        Projection() = default;
        Projection(const Matrix4f& matrix)
            : m_matrix{ matrix } {}
        
        template<Type T, typename... Args>
        static Projection create(Args... args) = delete;
        template<> 
        static Projection create<Type::Perspective>(float fov, float aspect, float zNear, float zFar)
        {
            const auto& matrix = glm::perspective(glm::radians(fov), aspect, zNear, zFar);

            return Projection{ matrix };
        }
        template<> 
        static Projection create<Type::Orthographic>(float top, float bottom, float left, float right, float zNear, float zFar)
        {
            const auto& matrix = glm::ortho(left, right, bottom, top, zNear, zFar);

            return Projection{ matrix };
        }

        const Matrix4f& matrix() const
        {
            return m_matrix;
        }

    private:
        Matrix4f m_matrix{};
    };
}
