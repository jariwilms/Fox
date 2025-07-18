export module fox.core.types.math.linear_algebra.vector;

import fox.core.types.fundamental;
import vendor.glm;

export namespace fox
{
	template<typename T, fox::uint32_t N> 
	using Vector = glm::vec<N, T, glm::packed_highp>;

	using Vector1i = fox::Vector<fox::int32_t,   1u>;
	using Vector2i = fox::Vector<fox::int32_t,   2u>;
	using Vector3i = fox::Vector<fox::int32_t,   3u>;
	using Vector4i = fox::Vector<fox::int32_t,   4u>;

	using Vector1u = fox::Vector<fox::uint32_t,  1u>;
	using Vector2u = fox::Vector<fox::uint32_t,  2u>;
	using Vector3u = fox::Vector<fox::uint32_t,  3u>;
	using Vector4u = fox::Vector<fox::uint32_t,  4u>;

	using Vector1f = fox::Vector<fox::float32_t, 1u>;
	using Vector2f = fox::Vector<fox::float32_t, 2u>;
	using Vector3f = fox::Vector<fox::float32_t, 3u>;
	using Vector4f = fox::Vector<fox::float32_t, 4u>;

	using Vector1d = fox::Vector<fox::float64_t, 1u>;
	using Vector2d = fox::Vector<fox::float64_t, 2u>;
	using Vector3d = fox::Vector<fox::float64_t, 3u>;
	using Vector4d = fox::Vector<fox::float64_t, 4u>;

	namespace vector
	{
		const auto zero    = fox::Vector4f{  0.0f,  0.0f,  0.0f,  0.0f  };
		const auto one     = fox::Vector4f{  1.0f,  1.0f,  1.0f,  1.0f  };

		const auto right   = fox::Vector4f{  1.0f,  0.0f,  0.0f,  0.0f  };
		const auto up      = fox::Vector4f{  0.0f,  1.0f,  0.0f,  0.0f  };
		const auto forward = fox::Vector4f{  0.0f,  0.0f, -1.0f,  0.0f  };
	}
}