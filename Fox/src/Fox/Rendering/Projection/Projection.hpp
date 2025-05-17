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

        struct perspective_p
        {
            perspective_p(fox::float32_t aspectRatio, fox::float32_t fov, fox::float32_t near, fox::float32_t far)
                : aspectRatio{ aspectRatio }, fov{ fov }, near{ near }, far{ far } {}

            fox::float32_t aspectRatio; 
            fox::float32_t fov;
            fox::float32_t near;
            fox::float32_t far;
        };
        struct orthographic_p
        {
            orthographic_p(fox::float32_t left, fox::float32_t right, fox::float32_t bottom, fox::float32_t top, fox::float32_t near, fox::float32_t far)
                : left{ left }, right{ right }, bottom{ bottom }, top{ top }, near{ near }, far{ far } {}

            fox::float32_t left;
            fox::float32_t right;
            fox::float32_t bottom;
            fox::float32_t top;
            fox::float32_t near;
            fox::float32_t far;
        };
        using projection_v = std::variant<perspective_p, orthographic_p>;

        Projection() = default;
        Projection(projection_v value)
        {
            if (std::holds_alternative<perspective_p> (value))
            {
                const auto& v = std::get<perspective_p>(value);

                m_matrix = glm::perspective(glm::radians(v.fov), v.aspectRatio, v.near, v.far);
                m_type   = Type::Perspective;
            }
            if (std::holds_alternative<orthographic_p>(value))
            {
                const auto& v = std::get<orthographic_p>(value);

                m_matrix = glm::ortho(v.left, v.right, v.bottom, v.top, v.near, v.far);
                m_type   = Type::Orthographic;
            }
        }

        const fox::Matrix4f& matrix() const
        {
            return m_matrix;
        }
              Type           type  () const
              {
                  return m_type;
              }

    private:
        fox::Matrix4f m_matrix{ 1.0f };
        Type          m_type  { Type::Perspective };
    };
}
