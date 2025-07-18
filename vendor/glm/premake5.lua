project "GLM"
	language        "C++"
	cppdialect      "C++23"
	kind            "StaticLib"
	staticruntime   "On"
	enablemodules   "On"
	buildstlmodules "On"
	warnings        "Off"
	
	defines
	{
		"GLM_ENABLE_EXPERIMENTAL", 
		
		"GLM_GTC_INLINE_NAMESPACE", 
		"GLM_EXT_INLINE_NAMESPACE", 
		"GLM_GTX_INLINE_NAMESPACE", 
	}
	
	includedirs
	{
		"include", 
	}	
	
	files
	{
		"include/glm/**.hpp", 
		"include/glm/**.cpp", 
		"include/glm/**.inl", 
		"include/glm/**.ixx", 
	}
