#pragma once

#include <fox/core/types/fundamental/fundamental.hpp>
#include <fox/core/types/linear_algebra/matrix.hpp>
#include <fox/math/linear_algebra/projection.hpp>
#include <fox/math/trigonometry/trigonometry.hpp>

namespace fox
{
    class Camera
    {
    public:
        Camera() = default;
        Camera(fox::float32_t aspect, fox::degrees_t fov)
            : aspect_{ aspect }, fov_{ fov }, projection_{ math::perspective(aspect_, math::to_radians(fov_), 0.01f, 100.0f) } {}
        Camera(fox::float32_t aspect, fox::degrees_t fov, const fox::Matrix4f& projection)
            : aspect_{ aspect }, fov_{ fov }, projection_{ projection } {}

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

    protected:
        fox::float32_t aspect_    {  1.0f };
        fox::float32_t fov_       { 90.0f };
        fox::Matrix4f  projection_{  1.0f };
    };
}
