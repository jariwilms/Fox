#pragma once

#include <stdafx.hpp>

#include <fox/rendering/api/opengl/core/types.hpp>

namespace fox::gfx::api::gl
{
    class Object
    {
    public:
        Object(Object&& other) noexcept
            : handle_{ std::exchange(other.handle_, gl::NullObject) } {}

        auto handle() const -> gl::handle_t
        {
            return handle_;
        }

        auto operator=(Object&& other) noexcept -> Object&
        {
            if (this != &other)
            {
                handle_ = std::exchange(other.handle_, handle_);
            }

            return *this;
        }

    protected:
        Object(gl::handle_t handle)
            : handle_{ handle } {}
        template<typename Dx>
        Object(gl::handle_t handle, Dx deleter)
            : handle_{ handle }, deleter_{ std::shared_ptr<gl::handle_t>{ &handle_, std::move(deleter) } } {}

        gl::handle_t                  handle_ ;
        std::shared_ptr<gl::handle_t> deleter_;
    };
}
