export module fox.core.transform;

import std;
import fox.core.types;
import fox.math;

export namespace fox
{
    class Transform
    {
    public:
        Transform()
            : position{ fox::vector<>::zero }, rotation{ quaternion::identity }, scale{ fox::vector<>::one } {}
        template<typename V>
        Transform(V&& position, V&& rotation, V&& scale)
            : position{ std::forward<V>(position) }, rotation{ math::to_radians(std::forward<V>(rotation)) }, scale{ std::forward<V>(scale) } {}
        template<typename P, typename R, typename S>
        Transform(P&& position, R&& rotation, S&& scale)
            : position{ std::forward<P>(position) }, rotation{ std::forward<R>(rotation) }, scale{ std::forward<S>(scale) } {}

        static auto from_matrix(const fox::Matrix4f& matrix) -> fox::Transform
        {
            auto transform = fox::Transform{};
            std::tie(transform.position, transform.rotation, transform.scale, std::ignore, std::ignore) = math::decompose(matrix);

            return transform;
        }

        void translate_by(const fox::vector3f& translation)
        {
            position += translation;
        }
        void rotate_by   (const fox::vector3f& angle      )
        {
            rotation *= fox::Quaternion{ math::to_radians(angle) };
        }
        void scale_by    (const fox::vector3f& factor     )
        {
            scale *= factor;
        }
        
        void look_at     (const fox::vector3f& target)
        {
            rotation = math::look_at(math::normalize(target - position), up());
        }

        auto forward     () const -> fox::vector3f 
        {
            return rotation * fox::vector<>::forward;
        }
        auto right       () const -> fox::vector3f 
        {
            return rotation * fox::vector<>::right;
        }
        auto up          () const -> fox::vector3f 
        {
            return rotation * fox::vector<>::up;
        }

        auto euler_angles() const -> fox::vector3f 
        {
            return math::to_degrees(math::euler_angles(rotation));
        }
        auto matrix      () const -> fox::Matrix4f
        {
            auto matrix = matrix::identity;

            matrix = math::translate(matrix, position);
            matrix = math::rotate   (matrix, rotation);
            matrix = math::scale    (matrix, scale   );

            return matrix;
        }

        friend auto operator*(const fox::Transform& left, const fox::Transform& right) -> fox::Transform
        {
            return fox::Transform::from_matrix(left.matrix() * right.matrix());
        }
        
        fox::vector3f   position;
        fox::Quaternion rotation;
        fox::vector3f   scale;
    };
}
