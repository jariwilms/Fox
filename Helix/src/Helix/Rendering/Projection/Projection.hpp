#pragma once

#include "stdafx.hpp"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace hlx
{
    class Projection
    {
    public:
        enum class Type
        {
            Perspective,
            Orthographic,
        };

        template<Type T, typename... Args>
        static glm::mat4 create(Args... args) = delete;
        template<> static glm::mat4 create<Type::Perspective>(float fov, float aspect, float zNear, float zFar)
        {
            return glm::perspective(glm::radians(fov), aspect, zNear, zFar);
        }
        template<> static glm::mat4 create<Type::Orthographic>(float top, float bottom, float left, float right, float zNear, float zFar)
        {
            return glm::ortho(left, right, bottom, top, zNear, zFar);
        }
    };
}
