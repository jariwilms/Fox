#pragma once

#include <fox/rendering/api/opengl/opengl.hpp>

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

	    static void debug_callback_impl(gl::enum_t source, gl::enum_t type, gl::uint32_t id, gl::enum_t severity, gl::sizei_t length, const gl::char_t* message, const gl::void_t* user_param)
        {
            const auto& map_source_message   = [](glf::Debug::Source   source  )
                {
                    switch (source)
                    {
                        case glf::Debug::Source::API           : return "API";
                        case glf::Debug::Source::WindowSystem  : return "Window System";
                        case glf::Debug::Source::ShaderCompiler: return "Shader Compiler";
                        case glf::Debug::Source::ThirdParty    : return "Third Party";
                        case glf::Debug::Source::Application   : return "Application";
                        case glf::Debug::Source::Other         : return "Other";

                        default: throw std::invalid_argument{ "Invalid source!" };
                    }
                };
            const auto& map_severity_message = [](glf::Debug::Severity severity)
                {
                    switch (severity)
                    {
                        case glf::Debug::Severity::High        : return "High";
                        case glf::Debug::Severity::Medium      : return "Medium";
                        case glf::Debug::Severity::Low         : return "Low";
                        case glf::Debug::Severity::Notification: return "Notification";

                        default: throw std::invalid_argument{ "Invalid severity!" };
                    }
                };
            const auto& map_type_message     = [](glf::Debug::Type     type    )
                {
                    switch (type)
                    {
                        case glf::Debug::Type::Error             : return "Error";
                        case glf::Debug::Type::DeprecatedBehavior: return "Deprecated Behavior";
                        case glf::Debug::Type::UndefinedBehavior : return "Undefine Behavior";
                        case glf::Debug::Type::Portability       : return "Portability";
                        case glf::Debug::Type::Performance       : return "Performance";
                        case glf::Debug::Type::Marker            : return "Marker";
                        case glf::Debug::Type::PushGroup         : return "Push Group";
                        case glf::Debug::Type::PopGroup          : return "Pop Group";
                        case glf::Debug::Type::Other             : return "Other";

                        default: throw std::invalid_argument{ "Invalid type!" };
                    }
                };

            const auto& eSource              = static_cast<glf::Debug::Source>  (source);
            const auto& eSeverity            = static_cast<glf::Debug::Severity>(severity);
            const auto& eType                = static_cast<glf::Debug::Type>    (type);

            const auto& mSource              = map_source_message  (eSource);
            const auto& mSeverity            = map_severity_message(eSeverity);
            const auto& mType                = map_type_message    (eType);



            if (eSeverity == glf::Debug::Severity::Notification) return;
            if (eSeverity == glf::Debug::Severity::Low         ) return;

            std::print("@GL_DEBUG [{0}] Type::{1}; Source::{2}; Severity::{3}; Message::{4}", id, mType, mSource, mSeverity, message);
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
