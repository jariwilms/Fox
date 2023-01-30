#pragma once

#include "stdafx.hpp"

#include "Helix/Rendering/Interface/IBindable.hpp"
#include "Helix/Core/Library/Semantics/NonCopyable.hpp"

namespace hlx
{
	class Shader : public IBindable
	{
	public:
		enum class Type
		{
			Vertex,
			TessellationControl, 
			TessellationEvaluation, 
			Geometry,
			Fragment,

			Compute, 
		};

		virtual ~Shader() = default;

		void bind() const override {};
		void unbind() const override {};
		bool bound() const override { return false; }

		bool valid() const
		{
			return m_valid;
		}
		std::string_view error() const
		{
			return m_error;
		}

		Type type() const
		{
			return m_type;
		}

	protected:
		Shader(Type type)
			: m_type{ type } {}

		const Type m_type{};
		std::string m_error{};
		bool m_valid{};
	};
}
