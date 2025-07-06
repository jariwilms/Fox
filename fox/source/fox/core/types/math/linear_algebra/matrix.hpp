#pragma once

#include <stdafx.hpp>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/matrix_decompose.hpp>

#include <fox/core/types/math/linear_algebra/quaternion.hpp>
#include <fox/core/types/math/linear_algebra/vector.hpp>

namespace fox
{
    template<typename T, fox::uint32_t N> using Matrix = glm::mat<N, N, T>;

    using Matrix2f = fox::Matrix<fox::float32_t, 2u>;
    using Matrix3f = fox::Matrix<fox::float32_t, 3u>;
    using Matrix4f = fox::Matrix<fox::float32_t, 4u>;

    using composition_t = std::tuple<fox::Vector3f, fox::Quaternion, fox::Vector3f, fox::Vector3f, fox::Vector4f>;

    namespace matrix
    {
        constexpr auto identity = fox::Matrix4f{ 1.0f };
    }
}
