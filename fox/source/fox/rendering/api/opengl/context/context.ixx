export module fox.rendering.api.opengl.context;

import std;

import fox.rendering.api.opengl;

export namespace fox::gfx::api::gl
{
	class context
	{
	public:
		static void init()
		{
			contextFlags_           = gl::get_value <glf::Data             ::ContextFlags          >();
			contextProfile_         = gl::get_value <glf::Data             ::ContextProfileMask    >();
			majorVersion_           = gl::get_value <glf::Data             ::MajorVersion          >();
			minorVersion_           = gl::get_value <glf::Data             ::MinorVersion          >();
			vendor_                 = gl::get_string<glf::Context::Property::Vendor                >();
			renderer_               = gl::get_string<glf::Context::Property::Renderer              >();
			version_                = gl::get_string<glf::Context::Property::Version               >();
            shadingLanguageVersion_ = gl::get_string<glf::Context::Property::ShadingLanguageVersion>();

            if (gl::to_underlying(contextFlags_ & glf::Context::Flag::Debug))
			{
                gl::enable<glf::Feature::DebugOutput>();
				gl::enable<glf::Feature::DebugOutputSynchronous>();

				gl::debug_message_control (glf::Debug::Source::DontCare, glf::Debug::Type::DontCare, glf::Debug::Severity::DontCare, gl::True);
				gl::debug_message_callback([](gl::enum_t source, gl::enum_t type, gl::uint32_t id, gl::enum_t severity, gl::sizei_t length, const gl::char_t* message, const gl::void_t* const)
                    {
                        auto map_source_message   = [](glf::Debug::Source   source  )
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
                        auto map_severity_message = [](glf::Debug::Severity severity)
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
                        auto map_type_message     = [](glf::Debug::Type     type    )
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

                        auto eSource              = static_cast<glf::Debug::Source>  (source  );
                        auto eSeverity            = static_cast<glf::Debug::Severity>(severity);
                        auto eType                = static_cast<glf::Debug::Type>    (type    );

                        auto mSource              = map_source_message  (eSource);
                        auto mSeverity            = map_severity_message(eSeverity);
                        auto mType                = map_type_message    (eType);

                        if (eSeverity == glf::Debug::Severity::Notification) return;
                        if (eSeverity == glf::Debug::Severity::Low         ) return;

                        std::print("@GL_DEBUG [{0}] Type::{1}; Source::{2}; Severity::{3}; Message::{4}", id, mType, mSource, mSeverity, message);
                    });
			}
		}

	private:
		static inline glf::Context::Flag    contextFlags_;
		static inline glf::Context::Profile contextProfile_;
		static inline gl::uint32_t          majorVersion_;
		static inline gl::uint32_t          minorVersion_;
		static inline std::string           vendor_;
		static inline std::string           renderer_;
		static inline std::string           version_;
		static inline std::string           shadingLanguageVersion_;
	};
}
