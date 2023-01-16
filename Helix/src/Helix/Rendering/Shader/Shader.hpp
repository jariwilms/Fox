#pragma once

#include "stdafx.hpp"

#include "Helix/Core/Library/Interface/IBindable.hpp"
#include "Helix/Core/Library/Semantics/NonCopyable.hpp"

namespace hlx
{
	class Shader : public IBindable, public NonCopyable
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

		static std::shared_ptr<Shader> create(Type type, std::string_view source);
		static std::shared_ptr<Shader> create(Type type, const std::vector<byte>& source);

		bool valid() const;
		std::string_view error() const;

		Type type() const;

	protected:
		Shader(Type type); //TODO: check if shader starts with "vertex" etc. according to type passed => error

		const Type m_type{};
		std::string m_error{};
		bool m_valid{};
	};
}
