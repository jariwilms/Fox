#pragma once

#include "Fox/Rendering/API/OpenGL/OpenGL.hpp"
#include "Fox/Rendering/Context/Context.hpp"

namespace fox::gfx::api::gl
{
	class Context : public api::Context
	{
	public:
		static void init()
		{
			s_contextFlags = gl::integer_v(gl::Flags::Data::ContextFlags);
			if (s_contextFlags & static_cast<gl::enum_t>(gl::Flags::Context::Flag::Debug))
			{
				gl::enable(gl::Flags::Capability::DebugOutput);
				gl::enable(gl::Flags::Capability::DebugOutputSynchronous);

				gl::debug_message_callback(gl::debug_callback);
				gl::debug_message_control(gl::True, gl::Flags::Debug::Source::DontCare, gl::Flags::Debug::Type::DontCare, gl::Flags::Debug::Severity::DontCare);
			}

			s_contextProfile = gl::integer_v(gl::Flags::Data::ContextProfile);


		}

	private:
		Context() = delete;
		~Context() = delete;

		static inline gl::enum_t  s_contextFlags{};
		static inline gl::enum_t  s_contextProfile{};
		static inline gl::enum_t  s_majorVersion{};
		static inline gl::enum_t  s_minorVersion{};
		static inline std::string s_renderer{};
		static inline std::string s_shadingLanguageVersion{};
		static inline std::string s_vendor{};
		static inline std::string s_version{};
	};
}
