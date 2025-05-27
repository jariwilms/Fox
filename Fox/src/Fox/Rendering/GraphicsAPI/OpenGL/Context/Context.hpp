#pragma once

#include "Fox/Rendering/GraphicsAPI/OpenGL/OpenGL.hpp"
#include <source_location>

namespace fox::gfx::api::gl
{
	class Context
	{
	public:
		static void init()
		{
			s_contextFlags           = gl::get_value<glf::Data::ContextFlags>();
			s_contextProfile         = gl::get_value<glf::Data::ContextProfileMask>();
			s_majorVersion           = gl::get_value<glf::Data::MajorVersion>();
			s_minorVersion           = gl::get_value<glf::Data::MinorVersion>();
			s_vendor                 = gl::get_string<glf::Connection::Vendor>();
			s_renderer               = gl::get_string<glf::Connection::Renderer>();
			s_version                = gl::get_string<glf::Connection::Version>();
            s_shadingLanguageVersion = gl::get_string<glf::Connection::ShadingLanguageVersion>();

            if (gl::to_underlying(s_contextFlags & glf::Context::Flag::Debug))
			{
                gl::enable<glf::Feature::DebugOutput>();
				gl::enable<glf::Feature::DebugOutputSynchronous>();

				gl::debug_message_control(glf::Debug::Source::DontCare, glf::Debug::Type::DontCare, glf::Debug::Severity::DontCare, gl::True);
				gl::debug_message_callback(debug_callback_impl);
			}
		}

	private:
		 Context() = delete;
		~Context() = delete;

	    static void debug_callback_impl(gl::enum_t source, gl::enum_t type, gl::uint32_t id, gl::enum_t severity, gl::sizei_t length, const gl::char_t* message, const void* user_param)
        {
            const auto& map_source_message   = [](glf::Debug::Source   source  )
                {
                    switch (source)
                    {
                        case glf::Debug::Source::API           : return "API";
                        case glf::Debug::Source::WindowSystem  : return "WINDOW_SYSTEM";
                        case glf::Debug::Source::ShaderCompiler: return "SHADER_COMPILER";
                        case glf::Debug::Source::ThirdParty    : return "THIRD_PARTY";
                        case glf::Debug::Source::Application   : return "APPLICATION";
                        case glf::Debug::Source::Other         : return "OTHER";

                        default: throw std::invalid_argument{ "Invalid source!" };
                    }
                };
            const auto& map_severity_message = [](glf::Debug::Severity severity)
                {
                    switch (severity)
                    {
                        case glf::Debug::Severity::High        : return "HIGH";
                        case glf::Debug::Severity::Medium      : return "MEDIUM";
                        case glf::Debug::Severity::Low         : return "LOW";
                        case glf::Debug::Severity::Notification: return "NOTIFICATION";

                        default: throw std::invalid_argument{ "Invalid severity!" };
                    }
                };
            const auto& map_type_message     = [](glf::Debug::Type     type    )
                {
                    switch (type)
                    {
                        case glf::Debug::Type::Error             : return "ERROR";
                        case glf::Debug::Type::DeprecatedBehavior: return "DEPRECATED_BEHAVIOR";
                        case glf::Debug::Type::UndefinedBehavior : return "UNDEFINED_BEHAVIOR";
                        case glf::Debug::Type::Portability       : return "PORTABILITY";
                        case glf::Debug::Type::Performance       : return "PERFORMANCE";
                        case glf::Debug::Type::Marker            : return "MARKER";
                        case glf::Debug::Type::PushGroup         : return "PUSH_GROUP";
                        case glf::Debug::Type::PopGroup          : return "POP_GROUP";
                        case glf::Debug::Type::Other             : return "OTHER";

                        default: throw std::invalid_argument{ "Invalid type!" };
                    }
                };



            const auto& sourceMessage   = map_source_message  (static_cast<glf::Debug::Source>  (source  ));
            const auto& severityMessage = map_severity_message(static_cast<glf::Debug::Severity>(severity));
            const auto& typeMessage     = map_type_message    (static_cast<glf::Debug::Type>    (type    ));

            if (severityMessage == map_severity_message(glf::Debug::Severity::Notification)) return;

            std::cout << std::format("|GL_DEBUG| ID::{0}; TYPE::{1}; SOURCE::{2}; SEVERITY::{3}; MESSAGE::{4}", id, typeMessage, sourceMessage, severityMessage, message) << std::endl;
        }

		static inline glf::Context::Flag    s_contextFlags{};
		static inline glf::Context::Profile s_contextProfile{};
		static inline gl::uint32_t          s_majorVersion{};
		static inline gl::uint32_t          s_minorVersion{};
		static inline std::string           s_vendor{};
		static inline std::string           s_renderer{};
		static inline std::string           s_version{};
		static inline std::string           s_shadingLanguageVersion{};
	};
}
