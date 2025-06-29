#pragma once

#include <fox/core/types/math/linear_algebra/matrix.hpp>
#include <fox/core/types/math/linear_algebra/quaternion.hpp>
#include <fox/core/types/math/linear_algebra/vector.hpp>
#include <fox/math/math.hpp>

namespace fox
{
    class Transform
    {
    public:
        constexpr Transform()
            : position{ 0.0f }, rotation{ 1.0f, 0.0f, 0.0f, 0.0f }, scale{ 1.0f } {}
        template<typename T, typename U, typename V>
        constexpr Transform(T&& position, U&& rotation, V&& scale)
            : position{ std::forward<T>(position) }, rotation{ std::forward<U>(math::to_radians(rotation)) }, scale{ std::forward<V>(scale) } {}

        static auto from_matrix(const fox::Matrix4f matrix)
        {
            auto transform = fox::Transform{};
            std::tie(transform.position, transform.rotation, transform.scale, std::ignore, std::ignore) = math::decompose(matrix);

            return transform;
        }

        void translate   (const fox::Vector3f& translation)
        {
            this->position += translation;
        }
        void rotate      (const fox::Vector3f& rotation   )
        {
            this->rotation *= fox::Quaternion{ glm::radians(rotation) };
        }
        void dilate      (const fox::Vector3f& scale      )
        {
            this->scale *= scale;
        }

        void look_at     (const fox::Vector3f& target)
        {
            rotation = math::look_at(math::normalize(target - position), up());
        }

        auto forward     () const -> fox::Vector3f 
        {
            return rotation * fox::Vector3f{ 0.0f, 0.0f, -1.0f };
        }
        auto right       () const -> fox::Vector3f 
        {
            return rotation * fox::Vector3f{ 1.0f, 0.0f, 0.0f };
        }
        auto up          () const -> fox::Vector3f 
        {
            return rotation * fox::Vector3f{ 0.0f, 1.0f, 0.0f };
        }

        auto euler_angles() const -> fox::Vector3f 
        {
            return math::to_degrees(math::euler_angles(rotation));
        }
        auto matrix      () const -> fox::Matrix4f 
        {
            fox::Matrix4f matrix{ 1.0f };

            matrix  = math::translate(matrix, position);
            matrix *= math::to_matrix(        rotation);
            matrix  = math::scale    (matrix, scale   );

            return matrix;
        }

        fox::Vector3f   position;
        fox::Quaternion rotation;
        fox::Vector3f   scale   ;
    };

    static auto operator*(const fox::Transform& left, const fox::Transform& right) -> fox::Transform
    {
        auto transform = fox::Transform{};
        std::tie(transform.position, transform.rotation, transform.scale, std::ignore, std::ignore) = math::decompose(left.matrix() * right.matrix());

        return transform;
    }
}
