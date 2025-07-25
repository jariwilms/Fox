export module fox.rendering.api.opengl.object;

import std;

import fox.rendering.api.opengl.types;

export namespace fox::gfx::api::gl
{
    constexpr auto null_object          = gl::handle_t{ 0u };
    constexpr auto default_frame_buffer = gl::handle_t{ 0u };

    class object
    {
    public:
        auto handle() const -> gl::handle_t
        {
            return handle_;
        }

    protected:
        explicit object(gl::handle_t handle)
            : handle_{ handle } {}
        template<typename Dx>
                 object(gl::handle_t handle, Dx deleter)
            : handle_{ handle }, deleter_{ &handle_, std::move(deleter) } {}
        explicit object(object&& other) noexcept
            : handle_{ std::exchange(other.handle_, gl::null_object) } {}

        auto operator=(object&& other) noexcept -> object&
        {
            if (this != &other)
            {
                handle_ = std::exchange(other.handle_, handle_);
            }

            return *this;
        }

    private:
        gl::handle_t                  handle_ ;
        std::shared_ptr<gl::handle_t> deleter_;
    };
}
