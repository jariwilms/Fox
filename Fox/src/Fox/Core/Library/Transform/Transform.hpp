#pragma once

#include "stdafx.hpp"

#include "Fox/Core/Include/GLM.hpp"

namespace fox
{
    class Transform
    {
    public:
        Transform() = default;
        Transform(const Transform& transform) = default;
        Transform(const Vector3f& position, const Vector3f& rotation, const Vector3f& scale)
            : position{ position }, rotation{ Quaternion{ glm::radians(rotation) } }, scale{ scale } {}
        Transform(const Matrix4f& matrix)
        {
            Vector3f skew{};
            Vector4f perspective{};

            glm::decompose(matrix, scale, rotation, position, skew, perspective);
            rotation = glm::conjugate(rotation);
        }

        void translate(const Vector3f& translation)
        {
            position += translation;
        }
        void rotate(const Vector3f& rotation)
        {
            this->rotation *= Quaternion{ glm::radians(rotation) };
        }
        void dilate(const Vector3f& scale)
        {
            this->scale *= scale;
        }

        void look_at(const Transform& target)
        {
            const auto forward = glm::normalize(target.position - position);
            rotation = glm::quatLookAt(forward, up());
        }

        Vector3f forward() const
        {
            return rotation * Vector3f{ 0.0f, 0.0f, -1.0f }; //Inwards to the screen
        }
        Vector3f right() const
        {
            return rotation * Vector3f{ 1.0f, 0.0f, 0.0f };
        }
        Vector3f up() const
        {
            return rotation * Vector3f{ 0.0f, 1.0f, 0.0f };
        }

        Vector3f euler_angles() const
        {
            return glm::degrees(glm::eulerAngles(rotation));
        }

        Matrix4f matrix() const
        {
            Matrix4f result{ 1.0f };
            result  = glm::translate(result, position);
            result *= glm::mat4_cast(rotation);
            result  = glm::scale(result, scale);

            return result;
        }

        friend Transform operator*(const Transform& lhs, const Transform& rhs)
        {
            return Transform{ lhs.matrix() * rhs.matrix() };
        }

        Vector3f   position{ 0.0f };
        Quaternion rotation{ 1.0f, 0.0f, 0.0f, 0.0f };
        Vector3f   scale{ 1.0f };
    };
}
