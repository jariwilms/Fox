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
		bool is_bound() const override { return false; }

        virtual void forward(const std::string& identifier, const bool&      value) = 0;
        virtual void forward(const std::string& identifier, const int&       value) = 0;
        virtual void forward(const std::string& identifier, const float&     value) = 0;
        virtual void forward(const std::string& identifier, const glm::vec2& value) = 0;
        virtual void forward(const std::string& identifier, const glm::vec3& value) = 0;
        virtual void forward(const std::string& identifier, const glm::vec4& value) = 0;
        virtual void forward(const std::string& identifier, const glm::mat2& value) = 0;
        virtual void forward(const std::string& identifier, const glm::mat3& value) = 0;
        virtual void forward(const std::string& identifier, const glm::mat4& value) = 0;

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
