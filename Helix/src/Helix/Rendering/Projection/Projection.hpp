#pragma once

#include "stdafx.hpp"

#include "Helix/Core/Include/GLM.hpp"

namespace hlx::gfx
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
        static Projection create<Type::Perspective>(f32 fov, f32 aspect, f32 zNear, f32 zFar)
        {
            const auto& matrix = glm::perspective(glm::radians(fov), aspect, zNear, zFar);

            return Projection{ matrix };
        }
        template<> 
        static Projection create<Type::Orthographic>(f32 top, f32 bottom, f32 left, f32 right, f32 zNear, f32 zFar)
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
