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
			s_contextFlags = gl::integer_v(glf::Data::ContextFlags);
			if (s_contextFlags & std::to_underlying(glf::Context::Flag::Debug))
			{
				gl::enable(glf::Feature::DebugOutput);
				gl::enable(glf::Feature::DebugOutputSynchronous);

				gl::debug_message_callback(gl::debug_callback);
				gl::debug_message_control(gl::True, glf::Debug::Source::DontCare, glf::Debug::Type::DontCare, glf::Debug::Severity::DontCare);
			}

			//s_contextProfile         = gl::integer_v(glf::Data::ContextProfile);
			s_majorVersion           = gl::integer_v(glf::Data::MajorVersion);
			s_minorVersion           = gl::integer_v(glf::Data::MinorVersion);

			s_vendor                 = gl::string(glf::Connection::Vendor);
			s_renderer               = gl::string(glf::Connection::Renderer);
			s_version                = gl::string(glf::Connection::Version);
			s_shadingLanguageVersion = gl::string(glf::Connection::ShadingLanguageVersion);
		}

	private:
		Context() = delete;
		~Context() = delete;

		static inline gl::enum_t  s_contextFlags{};
		static inline gl::enum_t  s_contextProfile{};
		static inline gl::enum_t  s_majorVersion{};
		static inline gl::enum_t  s_minorVersion{};
		static inline std::string s_vendor{};
		static inline std::string s_renderer{};
		static inline std::string s_version{};
		static inline std::string s_shadingLanguageVersion{};
	};
}
