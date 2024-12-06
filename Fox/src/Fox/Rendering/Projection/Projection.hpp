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
        Projection(const fox::Matrix4f& matrix)
            : m_matrix{ matrix } {}
        
        template<Type T, typename... Args>
        static Projection create(Args... args) = delete;
        template<> 
        static Projection create<Type::Perspective>(fox::float32_t aspectRatio, fox::float32_t fov, fox::float32_t zNear, fox::float32_t zFar)
        {
            const auto& matrix = glm::perspective(glm::radians(fov), aspectRatio, zNear, zFar);

            return Projection{ matrix };
        }
        template<> 
        static Projection create<Type::Orthographic>(fox::float32_t top, fox::float32_t bottom, fox::float32_t left, fox::float32_t right, fox::float32_t zNear, fox::float32_t zFar)
        {
            const auto& matrix = glm::ortho(left, right, bottom, top, zNear, zFar);

            return Projection{ matrix };
        }

        const fox::Matrix4f& matrix() const
        {
            return m_matrix;
        }

    private:
        fox::Matrix4f m_matrix{};
    };
}
