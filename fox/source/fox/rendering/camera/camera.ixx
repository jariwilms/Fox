export module fox.rendering.camera;

import std;

import fox.core.types;
import fox.math;

export namespace fox
{
    class Camera
    {
    public:
        Camera()
            : aspect_{ 1.0f }, fov_{ 90.0f }, projection_{ matrix::identity } {}
        Camera(fox::float32_t aspect, fox::degrees_t fov)
            : aspect_{ aspect }, fov_{ fov }, projection_{ math::perspective(aspect_, math::to_radians(fov_), 0.01f, 1000.0f) } {}
        Camera(fox::float32_t aspect, fox::degrees_t fov, fox::Matrix4f&& projection)
            : aspect_{ aspect }, fov_{ fov }, projection_{ std::forward<fox::Matrix4f>(projection) } {}

        auto aspect_ratio () const -> fox::float32_t
        {
            return aspect_;
        }
        auto field_of_view() const -> fox::float32_t
        {
            return fov_;
        }
        auto projection   () const -> const fox::Matrix4f&
        {
            return projection_;
        }

    private:
        fox::float32_t aspect_;
        fox::float32_t fov_;
        fox::Matrix4f  projection_;
    };
}
