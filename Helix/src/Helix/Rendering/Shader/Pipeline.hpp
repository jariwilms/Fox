#pragma once

#include "stdafx.hpp"

#include "glad/glad.h"
#include "glfw/glfw3.h"
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "Shader.hpp"
#include "Helix/Core/Library/Interface/IBindable.hpp"
#include "Helix/Core/Library/Semantics/NonCopyable.hpp"

namespace hlx
{
	class Pipeline : public IBindable, public NonCopyable
	{
	public:
		virtual ~Pipeline() = default;

		static std::shared_ptr<Pipeline> create();
		static std::shared_ptr<Pipeline> create(std::initializer_list<std::shared_ptr<Shader>> shaders);

		virtual void stage(std::shared_ptr<Shader> shader) = 0;

        virtual void forward(std::string_view identifier, const bool& value)      = 0;
        virtual void forward(std::string_view identifier, const int& value)       = 0;
        virtual void forward(std::string_view identifier, const float& value)     = 0;
        virtual void forward(std::string_view identifier, const glm::vec2& value) = 0;
        virtual void forward(std::string_view identifier, const glm::vec3& value) = 0;
        virtual void forward(std::string_view identifier, const glm::vec4& value) = 0;
        virtual void forward(std::string_view identifier, const glm::mat2& value) = 0;
        virtual void forward(std::string_view identifier, const glm::mat3& value) = 0;
        virtual void forward(std::string_view identifier, const glm::mat4& value) = 0;

        template<typename T>
        void forward_uniform(std::string_view identifier, const T& value)
        {
            forward_uniform(identifier, sizeof(T), &value);
        }

	protected:
        Pipeline() = default;

        virtual void forward_uniform(std::string_view identifier, size_t size, const void* data) = 0;
	};
}
