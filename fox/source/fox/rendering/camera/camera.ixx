export module fox.rendering.camera;

import std;

import fox.core.types;
import fox.math;

export namespace fox
{
    class camera
    {
    public:
        camera()
            : aspect_{ 1.0f }, fov_{ 90.0f }, projection_{ fox::matrix<>::identity } {}
        camera(fox::float32_t aspect, fox::degrees_t fov)
            : aspect_{ aspect }, fov_{ fov }, projection_{ math::perspective(aspect_, math::to_radians(fov_), 0.01f, 1000.0f) } {}
        camera(fox::float32_t aspect, fox::degrees_t fov, fox::matrix4f&& projection)
            : aspect_{ aspect }, fov_{ fov }, projection_{ std::forward<fox::matrix4f>(projection) } {}

        auto aspect_ratio () const -> fox::float32_t
        {
            return aspect_;
        }
        auto field_of_view() const -> fox::float32_t
        {
            return fov_;
        }
        auto projection   () const -> const fox::matrix4f&
        {
            return projection_;
        }

    private:
        fox::float32_t aspect_;
        fox::float32_t fov_;
        fox::matrix4f  projection_;
    };
}
