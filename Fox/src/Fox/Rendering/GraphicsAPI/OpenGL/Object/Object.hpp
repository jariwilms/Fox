#pragma once

#include "Fox/Rendering/GraphicsAPI/OpenGL/Types.hpp"

namespace fox::gfx::api::gl
{
    class Object
    {
    public:
        Object(Object&& other) noexcept
        {
            m_handle = std::exchange(other.m_handle, gl::NullObject);
        }

        gl::handle_t handle() const
        {
            return m_handle;
        }

        Object& operator=(Object&& other) noexcept
        {
            if (this != &other)
            {
                m_handle = std::exchange(other.m_handle, m_handle);
            }

            return *this;
        }

    protected:
        Object() = default;

        gl::handle_t m_handle{ gl::NullObject };
    };
}
