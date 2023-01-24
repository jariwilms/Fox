#pragma once

#include "stdafx.hpp"

#include "glm/glm.hpp"
#include "glm/gtc/quaternion.hpp"
#include "glm/gtx/quaternion.hpp"
#include "glm/gtx/matrix_decompose.hpp"

#include "Component.hpp"

namespace hlx
{
    class Transform : public Component
    {
    public:
        Transform() = default;
        Transform(const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale)
            : position{ position }, rotation{ glm::quat{ glm::radians(rotation) } }, scale{ scale } {}

        glm::mat4 transform()
        {
            glm::mat4 result{ 1.0f };
            result  = glm::translate(result, position);
            result *= glm::mat4_cast(rotation);
            result  = glm::scale(result, scale);

            return result;
        }

        void translate(const glm::vec3& value)
        {
            position += value;
        }
        void rotate(const glm::vec3& value)
        {
            rotation *= glm::quat(glm::radians(value));
        }
        void dilate(const glm::vec3& value)
        {
            scale *= value;
        }

        void look_at(const Transform& target)
        {
            const auto forward = glm::normalize(target.position - position);
            rotation = glm::quatLookAt(forward, up());
        }

        glm::vec3 forward() const
        {
            return rotation * glm::vec3{ 0.0f, 0.0f, -1.0f };                  //TODO: make decision about which axis is forward
        }
        glm::vec3 right() const
        {
            return rotation * glm::vec3{ 1.0f, 0.0f, 0.0f };
        }
        glm::vec3 up() const
        {
            return rotation * glm::vec3{ 0.0f, 1.0f, 0.0f };
        }

        glm::vec3 euler_angles() const
        {
            return glm::degrees(glm::eulerAngles(rotation));
        }

        glm::vec3 position{ 0.0f };
        glm::quat rotation{ 1.0f, 0.0f, 0.0f, 0.0f };
        glm::vec3 scale{ 1.0f };
    };
}
