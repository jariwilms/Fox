#pragma once

#include "stdafx.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/matrix_decompose.hpp>

namespace fox
{
    //Represents spatial transformations as a position, rotation, and scale
    //Rotation is stored in radians, arguments must be passed in degrees
    class Transform
    {
    public:
        Transform() = default;
        Transform(const fox::Vector3f& position, const fox::Vector3f&   rotation, const fox::Vector3f& scale)
            : position{ position }, rotation{ fox::Quaternion{ glm::radians(rotation) } }, scale{ scale } {}
        Transform(const fox::Vector3f& position, const fox::Quaternion& rotation, const fox::Vector3f& scale)
            : position{ position }, rotation{ fox::Quaternion{ rotation } }, scale{ scale } {}
        Transform(const fox::Matrix4f& matrix)
        {
            *this = matrix;
        }

        void translate(const fox::Vector3f& translation)
        {
            this->position += translation;
        }
        void rotate(   const fox::Vector3f& rotation)
        {
            this->rotation *= fox::Quaternion{ glm::radians(rotation) };
        }
        void dilate(   const fox::Vector3f& scale)
        {
            this->scale *= scale;
        }

        void look_at(const fox::Vector3f& target)
        {
            const auto& direction = glm::normalize(target - position);
                        rotation  = glm::quatLookAt(direction, up());
        }

        fox::Vector3f forward() const
        {
            return rotation * fox::Vector3f{ 0.0f, 0.0f, -1.0f };
        }
        fox::Vector3f right()   const
        {
            return rotation * fox::Vector3f{ 1.0f, 0.0f, 0.0f };
        }
        fox::Vector3f up()      const
        {
            return rotation * fox::Vector3f{ 0.0f, 1.0f, 0.0f };
        }

        fox::Vector3f euler_angles() const
        {
            return glm::degrees(glm::eulerAngles(rotation));
        }
        fox::Matrix4f matrix()       const
        {
            fox::Matrix4f matrix{ 1.0f };

            matrix  = glm::translate(matrix, position);
            matrix *= glm::mat4_cast(rotation);
            matrix  = glm::scale(    matrix, scale);

            return matrix;
        }

        Transform& operator=(const fox::Matrix4f& matrix)
        {
            fox::Vector3f skew{};
            fox::Vector4f perspective{};

            glm::decompose(matrix, scale, rotation, position, skew, perspective);
            rotation = glm::conjugate(rotation);

            return *this;
        }

        friend Transform operator*(const Transform& first, const Transform& second)
        {
            return Transform{ first.matrix() * second.matrix() };
        }

        fox::Vector3f   position{ 0.0f };
        fox::Quaternion rotation{ 1.0f, 0.0f, 0.0f, 0.0f };
        fox::Vector3f   scale   { 1.0f };
    };
}
