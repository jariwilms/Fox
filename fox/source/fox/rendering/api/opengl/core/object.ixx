export module fox.rendering.api.opengl.object;

import std;

import fox.rendering.api.opengl.types;

export namespace fox::gfx::api::gl
{
    constexpr auto NullObject         = gl::handle_t{ 0u };
    constexpr auto DefaultFrameBuffer = gl::handle_t{ 0u };



    class Object
    {
    public:
        explicit Object(Object&& other) noexcept
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
        explicit Object(gl::handle_t handle)
            : handle_{ handle } {}
        template<typename Dx>
        explicit Object(gl::handle_t handle, Dx deleter)
            : handle_{ handle }, deleter_{ &handle_, std::move(deleter) } {}

        gl::handle_t                  handle_ ;
        std::shared_ptr<gl::handle_t> deleter_;
    };
}
