#pragma once

#include "stdafx.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/matrix_decompose.hpp>

namespace fox
{
    class Transform
    {
    public:
        Transform() = default;
        Transform(const Transform& transform) = default;
        Transform(const fox::Vector3f& position, const fox::Vector3f& rotation, const fox::Vector3f& scale)
            : position{ position }, rotation{ fox::Quaternion{ glm::radians(rotation) } }, scale{ scale } {}
        Transform(const fox::Matrix4f& matrix)
        {
            fox::Vector3f skew{};
            fox::Vector4f perspective{};

            glm::decompose(matrix, scale, rotation, position, skew, perspective);
            rotation = glm::conjugate(rotation);
        }

        void translate(const fox::Vector3f& translation)
        {
            this->position += translation;
        }
        void rotate(const fox::Vector3f& rotation)
        {
            this->rotation *= fox::Quaternion{ glm::radians(rotation) };
        }
        void dilate(const fox::Vector3f& scale)
        {
            this->scale *= scale;
        }

        void look_at(const Transform& target)
        {
            const auto& forward = glm::normalize(target.position - position);
            rotation = glm::quatLookAt(forward, up());
        }

        fox::Vector3f forward() const
        {
            return rotation * fox::Vector3f{ 0.0f, 0.0f, -1.0f };
        }
        fox::Vector3f right() const
        {
            return rotation * fox::Vector3f{ 1.0f, 0.0f, 0.0f };
        }
        fox::Vector3f up() const
        {
            return rotation * fox::Vector3f{ 0.0f, 1.0f, 0.0f };
        }

        fox::Vector3f euler_angles() const
        {
            return glm::degrees(glm::eulerAngles(rotation));
        }

        fox::Matrix4f matrix() const
        {
            fox::Matrix4f result{ 1.0f };

            result  = glm::translate(result, position);
            result *= glm::mat4_cast(rotation);
            result  = glm::scale(result, scale);

            return result;
        }

        friend Transform operator*(const Transform& lhs, const Transform& rhs)
        {
            return Transform{ lhs.matrix() * rhs.matrix() };
        }

        fox::Vector3f   position{ 0.0f };
        fox::Quaternion rotation{ 1.0f, 0.0f, 0.0f, 0.0f };
        fox::Vector3f   scale{ 1.0f };
    };
}
