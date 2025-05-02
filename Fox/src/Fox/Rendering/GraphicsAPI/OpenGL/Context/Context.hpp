#pragma once

#include "Fox/Rendering/GraphicsAPI/OpenGL/OpenGL.hpp"

namespace fox::gfx::api::gl
{
	class Context
	{
	public:
		static void init()
		{
			s_contextFlags = gl::get_value<glf::Data::ContextFlags>();
			if (s_contextFlags & std::to_underlying(glf::Context::Flag::Debug))
			{
				gl::enable(glf::Feature::DebugOutput);
				gl::enable(glf::Feature::DebugOutputSynchronous);

				//gl::debug_message_callback(gl::debug_callback);
				gl::debug_message_control(glf::Debug::Source::DontCare, glf::Debug::Type::DontCare, glf::Debug::Severity::DontCare, gl::True);
			}

			s_contextProfile         = gl::get_value<glf::Data::ContextFlags>();
			s_majorVersion           = gl::get_value<glf::Data::MajorVersion>();
			s_minorVersion           = gl::get_value<glf::Data::MinorVersion>();

			s_vendor                 = gl::get_string(glf::Connection::Vendor,                 {});
			s_renderer               = gl::get_string(glf::Connection::Renderer,               {});
			s_version                = gl::get_string(glf::Connection::Version,                {});
			s_shadingLanguageVersion = gl::get_string(glf::Connection::ShadingLanguageVersion, {});
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
