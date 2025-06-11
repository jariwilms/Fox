#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/matrix_decompose.hpp>

#include <fox/types/fundamental.hpp>

namespace fox
{
    template<typename T, fox::uint32_t N> using Matrix = glm::mat<N, N, T>;

    using Matrix2f = fox::Matrix<fox::float32_t, 2u>;
    using Matrix3f = fox::Matrix<fox::float32_t, 3u>;
    using Matrix4f = fox::Matrix<fox::float32_t, 4u>;
}
