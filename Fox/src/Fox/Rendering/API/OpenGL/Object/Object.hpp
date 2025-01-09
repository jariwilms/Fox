#pragma once

#include "Fox/Rendering/API/OpenGL/Types.hpp"

namespace fox::gfx::api::gl
{
    struct Object
    {
    public:
        gl::handle_t handle() const
        {
            return m_handle;
        }

    protected:
        Object() = default;
        ~Object() = default;
        Object(Object&& other) noexcept = default;

        Object& operator=(Object&& other) noexcept = default;

        gl::handle_t m_handle{};
    };
}
