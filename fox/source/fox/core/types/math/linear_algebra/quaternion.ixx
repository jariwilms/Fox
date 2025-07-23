export module fox.core.types.math.linear_algebra.quaternion;

import fox.core.types.fundamental;
import vendor.glm;

export namespace fox
{
    template<typename T>
    using quaternion_t = glm::qua<T, glm::packed_highp>;

    template<typename T = fox::float32_t>
    class quaternion
    {
    public:
        static inline constexpr auto identity = fox::quaternion_t<fox::float32_t>{ 1.0f, 0.0f, 0.0f, 0.0f };
    };

    using quaternion4f = quaternion_t<fox::float32_t>;
}
