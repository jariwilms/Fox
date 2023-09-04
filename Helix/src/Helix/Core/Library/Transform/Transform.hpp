#pragma once

#include "stdafx.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/matrix_decompose.hpp>

namespace hlx
{
    class Transform
    {
    public:
        Transform() = default;
        Transform(const Transform& transform)
            : position{ transform.position }, rotation{ transform.rotation }, scale{ transform.scale } {}
        Transform(const Vector3f& position, const Vector3f& rotation, const Vector3f& scale)
            : position{ position }, rotation{ Quaternion{ glm::radians(rotation) } }, scale{ scale } {}
        Transform(const Matrix4f& prs)
        {
            Vector3f skew{};
            Vector4f perspective{};

            glm::decompose(prs, scale, rotation, position, skew, perspective);
            rotation = glm::conjugate(rotation);
        }

        void translate(const Vector3f& value)
        {
            position += value;
        }
        void rotate(const Vector3f& value)
        {
            rotation *= Quaternion{ glm::radians(value) };
        }
        void dilate(const Vector3f& value)
        {
            scale *= value;
        }

        void look_at(const Transform& target)
        {
            const auto forward = glm::normalize(target.position - position);
            rotation = glm::quatLookAt(forward, up());
        }

        Vector3f forward() const
        {
            return rotation * Vector3f{ 0.0f, 0.0f, -1.0f };                   //TODO: make decision about which axis is forward
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
        Transform product() const
        {
            if (parent)
            {
                auto res = parent->product() * (*this);
                return res;
            }

            return *this;
        }

        friend Transform operator*(const Transform& lhs, const Transform& rhs)
        {
            auto res = Transform{ lhs.matrix() * rhs.matrix() };
            return res;
        }

        Vector3f   position{ 0.0f };
        Quaternion rotation{ 1.0f, 0.0f, 0.0f, 0.0f };
        Vector3f   scale{ 1.0f };

        Transform* parent{};
    };
}
