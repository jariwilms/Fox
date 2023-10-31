#pragma once

#include "stdafx.hpp"

#include "Helix/Core/Using/GLM.hpp"

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
        static Matrix4f create(Args... args) = delete;

        template<> 
        static Matrix4f create<Type::Perspective>(float fov, float aspect, float zNear, float zFar)
        {
            return glm::perspective(glm::radians(fov), aspect, zNear, zFar);
        }
        template<> 
        static Matrix4f create<Type::Orthographic>(float top, float bottom, float left, float right, float zNear, float zFar)
        {
            return glm::ortho(left, right, bottom, top, zNear, zFar);
        }
    };
}
