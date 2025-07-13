#pragma once

import fox.core.types.fundamental;
import vendor.glm;

namespace fox
{
    template<typename T, fox::uint32_t N> using Matrix = glm::mat<N, N, T>;

    using Matrix2f = fox::Matrix<fox::float32_t, 2u>;
    using Matrix3f = fox::Matrix<fox::float32_t, 3u>;
    using Matrix4f = fox::Matrix<fox::float32_t, 4u>;

    namespace matrix
    {
        const auto identity = fox::Matrix4f{ 1.0f };
    }
}
