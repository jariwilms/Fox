export module fox.core.transform;

import std;
import fox.core.types;
import fox.math;

export namespace fox
{
    class transform
    {
    public:
        transform()
            : position{ fox::vector<>::zero }, rotation{ fox::quaternion<>::identity }, scale{ fox::vector<>::one } {}
        template<typename V>
        transform(V&& position, V&& rotation, V&& scale)
            : position{ std::forward<V>(position) }, rotation{ math::to_radians(std::forward<V>(rotation)) }, scale{ std::forward<V>(scale) } {}
        template<typename P, typename R, typename S>
        transform(P&& position, R&& rotation, S&& scale)
            : position{ std::forward<P>(position) }, rotation{ std::forward<R>(rotation) }, scale{ std::forward<S>(scale) } {}

        static auto from_matrix(const fox::matrix4f& matrix) -> fox::transform
        {
            auto transform = fox::transform{};
            std::tie(transform.position, transform.rotation, transform.scale, std::ignore, std::ignore) = math::decompose(matrix);

            return transform;
        }

        void translate_by(const fox::vector3f& translation)
        {
            position += translation;
        }
        void rotate_by   (const fox::vector3f& angle      )
        {
            rotation *= math::compose_angles(math::to_radians(angle));
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
        auto matrix      () const -> fox::matrix4f
        {
            auto matrix = fox::matrix<>::identity;

            matrix = math::translate(matrix, position);
            matrix = math::rotate   (matrix, rotation);
            matrix = math::scale    (matrix, scale   );

            return matrix;
        }

        friend auto operator*(const fox::transform& left, const fox::transform& right) -> fox::transform
        {
            return fox::transform::from_matrix(left.matrix() * right.matrix());
        }
        
        fox::vector3f     position;
        fox::quaternion4f rotation;
        fox::vector3f     scale;
    };
}
