#pragma once

#include "Fox/Rendering/GraphicsAPI/OpenGL/OpenGL.hpp"

namespace fox::gfx::api::gl
{
	static void debug_callback_impl(gl::enum_t source, gl::enum_t type, gl::uint32_t id, gl::enum_t severity, gl::sizei_t length, const gl::char_t* message, const void* user_param)
    {
        const auto& sourceMessage   = [source]() -> std::string
            {
                switch (source)
                {
                    case GL_DEBUG_SOURCE_API:             return "API";
                    case GL_DEBUG_SOURCE_WINDOW_SYSTEM:   return "WINDOW_SYSTEM";
                    case GL_DEBUG_SOURCE_SHADER_COMPILER: return "SHADER_COMPILER";
                    case GL_DEBUG_SOURCE_THIRD_PARTY:     return "THIRD_PARTY";
                    case GL_DEBUG_SOURCE_APPLICATION:     return "APPLICATION";
                    case GL_DEBUG_SOURCE_OTHER:           return "OTHER";

                    default:                              throw std::invalid_argument{ "Invalid source!" };
                }
            }();
        const auto& typeMessage     = [type]() -> std::string
            {
                switch (type)
                {
                    case GL_DEBUG_TYPE_ERROR:               return "ERROR";
                    case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: return "DEPRECATED_BEHAVIOR";
                    case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:  return "UNDEFINED_BEHAVIOR";
                    case GL_DEBUG_TYPE_PORTABILITY:         return "PORTABILITY";
                    case GL_DEBUG_TYPE_PERFORMANCE:         return "PERFORMANCE";
                    case GL_DEBUG_TYPE_MARKER:              return "MARKER";
                    case GL_DEBUG_TYPE_OTHER:               return "OTHER";

                    default:                                throw std::invalid_argument{ "Invalid type!" };
                }
            }();
        const auto& severityMessage = [severity]() -> std::string
            {
                switch (severity)
                {
                    case GL_DEBUG_SEVERITY_NOTIFICATION: return "NOTIFICATION";
                    case GL_DEBUG_SEVERITY_LOW:          return "LOW";
                    case GL_DEBUG_SEVERITY_MEDIUM:       return "MEDIUM";
                    case GL_DEBUG_SEVERITY_HIGH:         return "HIGH";

                    default:                             throw std::invalid_argument{ "Invalid severity!" };
                }
            }();

        if (severityMessage == "NOTIFICATION") return;

        std::cout << std::format("[GL_DEBUG] {0}, {1}, {2}, {3}: {4}", sourceMessage, typeMessage, severityMessage, id, message) << std::endl;
    }

	class Context
	{
	public:
		static void init()
		{
			s_contextFlags = gl::get_value<glf::Data::ContextFlags>();
			if (s_contextFlags & fox::to_underlying(glf::Context::Flag::Debug))
			{
                gl::enable<glf::Feature::DebugOutput>();
				gl::enable<glf::Feature::DebugOutputSynchronous>();

				gl::debug_message_callback(gl::debug_callback_impl);
				gl::debug_message_control(glf::Debug::Source::DontCare, glf::Debug::Type::DontCare, glf::Debug::Severity::DontCare, gl::True);
			}

			s_contextProfile         = gl::get_value<glf::Data::ContextFlags>();
			s_majorVersion           = gl::get_value<glf::Data::MajorVersion>();
			s_minorVersion           = gl::get_value<glf::Data::MinorVersion>();

			s_vendor                 = gl::get_string<glf::Connection::Vendor>();
			s_renderer               = gl::get_string<glf::Connection::Renderer>();
			s_version                = gl::get_string<glf::Connection::Version>();
            s_shadingLanguageVersion = gl::get_string<glf::Connection::ShadingLanguageVersion>();
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
