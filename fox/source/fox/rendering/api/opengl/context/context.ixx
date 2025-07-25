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
			contextFlags_           = gl::get_value <gl::data_e            ::context_flags           >();
			contextProfile_         = gl::get_value <gl::data_e            ::context_profile_mask    >();
			majorVersion_           = gl::get_value <gl::data_e            ::major_version           >();
			minorVersion_           = gl::get_value <gl::data_e            ::minor_version           >();
			vendor_                 = gl::get_string<gl::context_property_e::vendor                  >();
			renderer_               = gl::get_string<gl::context_property_e::renderer                >();
			version_                = gl::get_string<gl::context_property_e::version                 >();
            shadingLanguageVersion_ = gl::get_string<gl::context_property_e::shading_language_version>();

            if (gl::to_underlying(contextFlags_ & gl::context_flag_e::debug))
			{
                gl::enable<gl::feature_e::debug_output            >();
				gl::enable<gl::feature_e::debug_output_synchronous>();

				gl::debug_message_control (gl::debug_source_e::dont_care, gl::debug_type_e::dont_care, gl::debug_severity_e::dont_care, gl::True);
				gl::debug_message_callback([](gl::enum_t source, gl::enum_t type, gl::uint32_t id, gl::enum_t severity, gl::sizei_t length, const gl::char_t* message, const gl::void_t* const)
                    {
                        auto map_source_message   = [](gl::debug_source_e   source  )
                            {
                                switch (source)
                                {
                                    case gl::debug_source_e::api            : return "API";
                                    case gl::debug_source_e::window_system  : return "Window System";
                                    case gl::debug_source_e::shader_compiler: return "Shader Compiler";
                                    case gl::debug_source_e::third_party    : return "Third Party";
                                    case gl::debug_source_e::application    : return "Application";
                                    case gl::debug_source_e::other          : return "Other";

                                    default: throw std::invalid_argument{ "Invalid source!" };
                                }
                            };
                        auto map_severity_message = [](gl::debug_severity_e severity)
                            {
                                switch (severity)
                                {
                                    case gl::debug_severity_e::high        : return "High";
                                    case gl::debug_severity_e::medium      : return "Medium";
                                    case gl::debug_severity_e::low         : return "Low";
                                    case gl::debug_severity_e::notification: return "Notification";

                                    default: throw std::invalid_argument{ "Invalid severity!" };
                                }
                            };
                        auto map_type_message     = [](gl::debug_type_e type    )
                            {
                                switch (type)
                                {
                                    case gl::debug_type_e::error              : return "Error";
                                    case gl::debug_type_e::deprecated_behavior: return "Deprecated Behavior";
                                    case gl::debug_type_e::undefined_behavior : return "Undefine Behavior";
                                    case gl::debug_type_e::portability        : return "Portability";
                                    case gl::debug_type_e::performance        : return "Performance";
                                    case gl::debug_type_e::marker             : return "Marker";
                                    case gl::debug_type_e::push_group         : return "Push Group";
                                    case gl::debug_type_e::pop_group          : return "Pop Group";
                                    case gl::debug_type_e::other              : return "Other";

                                    default: throw std::invalid_argument{ "Invalid type!" };
                                }
                            };

                        auto eSource              = static_cast<gl::debug_source_e  >(source  );
                        auto eSeverity            = static_cast<gl::debug_severity_e>(severity);
                        auto eType                = static_cast<gl::debug_type_e    >(type    );

                        auto mSource              = map_source_message  (eSource);
                        auto mSeverity            = map_severity_message(eSeverity);
                        auto mType                = map_type_message    (eType);

                        if (eSeverity == gl::debug_severity_e::notification) return;
                        if (eSeverity == gl::debug_severity_e::low         ) return;

                        std::print("@GL_DEBUG [{0}] Type::{1}; Source::{2}; Severity::{3}; Message::{4}", id, mType, mSource, mSeverity, message);
                    });
			}
		}

	private:
		static inline gl::context_flag_e    contextFlags_;
		static inline gl::context_profile_e contextProfile_;
		static inline gl::uint32_t          majorVersion_;
		static inline gl::uint32_t          minorVersion_;
		static inline std::string           vendor_;
		static inline std::string           renderer_;
		static inline std::string           version_;
		static inline std::string           shadingLanguageVersion_;
	};
}
