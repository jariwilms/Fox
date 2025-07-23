export module fox.core.types.math.linear_algebra.matrix;

import fox.core.types.fundamental;
import vendor.glm;

export namespace fox
{
    template<typename T, fox::uint32_t R, fox::uint32_t C = R> 
    using matrix_t = glm::mat<R, C, T>;
    
    template<typename T = fox::float32_t, fox::uint32_t R = 4u, fox::uint32_t C = R>
    class matrix
    {
    public:
        static inline constexpr auto identity = fox::matrix_t<T, R, C>{ T{ 1 } };
    };

    using matrix2f = fox::matrix_t<fox::float32_t, 2u>;
    using matrix3f = fox::matrix_t<fox::float32_t, 3u>;
    using matrix4f = fox::matrix_t<fox::float32_t, 4u>;
}
